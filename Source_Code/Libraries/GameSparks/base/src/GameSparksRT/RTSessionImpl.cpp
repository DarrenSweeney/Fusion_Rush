#include "./RTSessionImpl.hpp"
#include "Commands/Requests/CustomRequest.hpp"
#include "Connection/FastConnection.hpp"
#include "Connection/ReliableConnection.hpp"
#include "Commands/LogCommand.hpp"
#include "Commands/ActionCommand.hpp"
#include "Commands/CommandFactory.hpp"
#include "../System/Threading/Thread.hpp"
#include <iostream>

namespace GameSparks { namespace RT {

IRTSessionListener::~IRTSessionListener(){
    if(session)
    {
        assert(session->SessionListener == this);
        session->SessionListener = nullptr;
    }
}


RTSessionImpl::RTSessionImpl(const std::string &connectToken_, const std::string &hostName_,
                             const std::string &tcpPort_, const std::string &udpPort_)
:connectToken(connectToken_)
,hostName(hostName_)
,TcpPort(tcpPort_)
{
    FastPort(udpPort_);
}

RTSessionImpl::~RTSessionImpl()
{
	if (running)
	{
		Stop();
	}
	
	if(SessionListener != nullptr)
        SessionListener->session = nullptr;
    SessionListener = nullptr;

    running = false;
}


int RTSessionImpl::SendData(int opCode, GameSparksRT::DeliveryIntent intent, const System::Bytes &payload,
                            const RTData &data, const std::vector<int> &targetPlayers)
{
    if(!payload.empty())
    {
        return SendRTDataAndBytes (opCode, intent, payload, data, targetPlayers);
    }
    else
    {
        System::Bytes dummy;
        return SendRTDataAndBytes (opCode, intent, dummy, data, targetPlayers);
    }
}


int RTSessionImpl::SendRTData(int opCode, GameSparksRT::DeliveryIntent deliveryIntent, const RTData &data,
                              const std::vector<int> &targetPlayers)
{
    System::Bytes dummy;
    return SendRTDataAndBytes (opCode, deliveryIntent, dummy, data, targetPlayers);
}

int RTSessionImpl::SendBytes(int opCode, GameSparksRT::DeliveryIntent deliveryIntent,
                             const System::ArraySegment<System::Byte> &payload,
                             const std::vector<int> &targetPlayers)
{
    RTData dummy;
    return SendRTDataAndBytes (opCode, deliveryIntent, payload, dummy, targetPlayers);
}


int RTSessionImpl::SendRTDataAndBytes(int opCode, GameSparksRT::DeliveryIntent intent,
                                      const System::ArraySegment<System::Byte> &payload, const RTData &data,
                                      const std::vector<int> &targetPlayers)
{
    if(opCode == 0)
    {
        Log("IRTSession", GameSparksRT::LogLevel::LL_WARN, "opCode must be greater than zero.");
        return 0;
    }

    CustomRequest csr(opCode, intent, payload, data, targetPlayers);
    GS_TRY
    {
        std::lock_guard<std::mutex> lock(sendMutex);

        if(intent != GameSparksRT::DeliveryIntent::RELIABLE && GetConnectState() >= GameSparksRT::ConnectState::ReliableAndFastSend )
        {
            GS_RETURN_RESULT_OR_CATCH(fastConnection->Send(csr));
        }
        else
        {
            if(GetConnectState() >= GameSparksRT::ConnectState::ReliableOnly)
            {
                GS_RETURN_RESULT_OR_CATCH(reliableConnection->Send(csr));
            }
        }
    }
    GS_CATCH(e)
    {
        (void)e;
    }
    return 0;
}

void RTSessionImpl::Stop() {
    Log("IRTSession", GameSparksRT::LogLevel::LL_DEBUG, "Stopped");

    running = false;
    Ready = false;

    std::lock_guard<std::mutex> lock(sendMutex);

    if(fastConnection)
        fastConnection->Stop ();

    if(reliableConnection)
        reliableConnection->Stop ();

    SetConnectState(GameSparksRT::ConnectState::Disconnected);
}

void RTSessionImpl::Start() {
    running = true;
}

void RTSessionImpl::CheckConnection(){
    std::lock_guard<std::mutex> lock(sendMutex);

    // actually none of the called functions GS_THROW at the moment.
    GS_TRY
    {
        if (GetConnectState() == GameSparksRT::ConnectState::Disconnected) {
            Log("IRTSession", GameSparksRT::LogLevel::LL_INFO, "Disconnected, trying to connect");
            SetConnectState(GameSparksRT::ConnectState::Connecting);
            ConnectReliable ();
        } else if (GetConnectState() == GameSparksRT::ConnectState::Connecting && std::chrono::steady_clock::now() > mustConnnectBy){
            SetConnectState(GameSparksRT::ConnectState::Disconnected);
            Log("IRTSession", GameSparksRT::LogLevel::LL_INFO, "Not connected in time, retrying");

            if(reliableConnection){
                reliableConnection->StopInternal();
                reliableConnection.reset(nullptr);
            }
            if(fastConnection){
                fastConnection->StopInternal();
                fastConnection.reset(nullptr);
            }
            ConnectReliable ();
        }
    }
    GS_CATCH(e)
    {
        //General exception, ignore it
        Log("IRTSession", GameSparksRT::LogLevel::LL_ERROR, e.Format());
    }

}

void RTSessionImpl::Update() {
    if(running)
        CheckConnection();

    while(std::unique_ptr<IRTCommand> toExecute = GetNextAction())
    {
        toExecute->Execute ();
    }

    if(reliableConnection)
    {
        std::lock_guard<std::mutex> lock(sendMutex);
        reliableConnection->Poll();
    }
}

void RTSessionImpl::DoLog(const std::string &tag, GameSparks::RT::GameSparksRT::LogLevel level, const std::string &msg) {
    if(GameSparksRT::ShouldLog(tag, level))
    {
        std::unique_ptr<IRTCommand> cmd(new LogCommand(tag, level, msg));
        SubmitAction(cmd);
    }
}

std::string RTSessionImpl::ConnectToken() const {
    return connectToken;
}

void RTSessionImpl::ConnectToken(const std::string& token)
{
    connectToken = token;
}

std::string RTSessionImpl::FastPort() const
{
    return fastPort;
}

void RTSessionImpl::FastPort(const std::string& port)
{
    fastPort = port;
}


void RTSessionImpl::ConnectReliable() {
    mustConnnectBy = std::chrono::steady_clock::now() + std::chrono::seconds(GameSparksRT::TCP_CONNECT_TIMEOUT_SECONDS);
    reliableConnection.reset(new Connection::ReliableConnection (hostName, TcpPort, this));
}

void RTSessionImpl::ConnectFast() {
    Log("IRTSession", GameSparksRT::LogLevel::LL_DEBUG, "{0}: Creating new fastConnection to {1}", PeerId, FastPort());
    fastConnection.reset(new Connection::FastConnection (hostName, FastPort(), this));
}

bool RTSessionImpl::ShouldExecute(int peerId, System::Nullable<int> sequence) {
    if (!sequence.HasValue()) {
        return true;
    } else if (!peerMaxSequenceNumbers.count(peerId)) {
        peerMaxSequenceNumbers[peerId] = 0;
    }

    if (peerMaxSequenceNumbers[peerId] > sequence.Value()) {
        Log ("IRTSession", GameSparksRT::LogLevel::LL_DEBUG, "Discarding sequence id {0} from peer {1}",
             sequence.Value(), peerId);
        return false;
    } else {
        peerMaxSequenceNumbers [peerId] = sequence.Value();
        return true;
    }
}

void RTSessionImpl::SubmitAction(std::unique_ptr<IRTCommand>& action) {
    std::lock_guard<std::mutex> lock(actionQueueMutex);
    actionQueue.push(std::move(action));
}

std::unique_ptr<IRTCommand> RTSessionImpl::GetNextAction() {
    std::lock_guard<std::mutex> lock(actionQueueMutex);
    if (!actionQueue.empty()) {
        auto ret = std::move(actionQueue.front());
        actionQueue.pop();
        return ret;
    }
    return {};
}


int RTSessionImpl::NextSequenceNumber() {
    return sequenceNumber++;
}

void RTSessionImpl::OnPlayerConnect(int peerId) {
    ResetSequenceForPeer (peerId);
    if (SessionListener != nullptr) {
        if (this->Ready) {
            SessionListener->OnPlayerConnect(peerId);
        }
    }
}

void RTSessionImpl::OnPlayerDisconnect(int peerId) {
    if (SessionListener != nullptr) {
        if (this->Ready) {
            SessionListener->OnPlayerDisconnect(peerId);
        }
    }
}

void RTSessionImpl::OnReady(bool ready) {
    if(!this->Ready && ready){
        SendData (Commands::OpCodes::PlayerReadyMessage, GameSparksRT::DeliveryIntent::RELIABLE, {}, {}, {});
        if(PeerId.HasValue() && std::find(ActivePeers.begin(), ActivePeers.end(), PeerId.Value()) == ActivePeers.end()){
            ActivePeers.push_back(PeerId.Value());
        }
    }
    this->Ready = ready;

    if (!this->Ready) {
        SetConnectState(GameSparksRT::ConnectState::Disconnected);
    }

    if (SessionListener != nullptr) {
        std::unique_ptr<IRTCommand> cmd(new ActionCommand([this, ready](){
            if(this->SessionListener != nullptr)
            {
                SessionListener->OnReady(ready);
            }
            else
            {
                std::clog << "INFO: SessionListener was unregistered" << std::endl;
            }
        }));
        SubmitAction (cmd);
    }
}

void RTSessionImpl::OnPacket(const RTPacket &/*packet*/)
{
    GS_PROGRAMMING_ERROR("This should never be called");
}

void RTSessionImpl::ResetSequenceForPeer (int peerId)
{
    if (peerMaxSequenceNumbers.count(peerId)) {
        peerMaxSequenceNumbers[peerId] = 0;
    }
}

GameSparksRT::ConnectState RTSessionImpl::GetConnectState() const {
    return internalState;
}

void RTSessionImpl::SetConnectState(GameSparksRT::ConnectState value) {
    if (value != internalState) {
        if (internalState < value) {
            Log ("IRTSession", GameSparksRT::LogLevel::LL_DEBUG, "State Change : from {0} to {1}, ActivePeers {2}", internalState, value, ActivePeers.size());
            internalState = value;
        }
    }
}

}} /* namespace GameSparks.RT */
