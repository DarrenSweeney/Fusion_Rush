
#include <GameSparksRT/GameSparksRT.hpp>
#include <ostream>
#include <iostream>
#include "./RTSessionImpl.hpp"

namespace GameSparks { namespace RT {

int GameSparksRT::TCP_CONNECT_TIMEOUT_SECONDS = 5;

/// Constructor
GameSparksRTSessionBuilder::GameSparksRTSessionBuilder()
:pimpl(new Pimpl()) {}

/// Destructor
GameSparksRTSessionBuilder::~GameSparksRTSessionBuilder()
{
	delete pimpl;
}


GameSparksRTSessionBuilder& GameSparksRTSessionBuilder::SetConnectToken(const std::string& connectToken_){
    this->pimpl->connectToken = connectToken_;
    return *this;
}

GameSparksRTSessionBuilder& GameSparksRTSessionBuilder::SetHost(const std::string& host_){
    this->pimpl->host = host_;
    return *this;
}

/// sets TcpPort and FastPort to the same value
GameSparksRTSessionBuilder& GameSparksRTSessionBuilder::SetPort(const std::string& port_){
    this->pimpl->port = port_;
    return *this;
}

GameSparksRTSessionBuilder& GameSparksRTSessionBuilder::SetPort(int _port) {
	assert(_port > 0);
	assert(_port <= 65535);

	std::stringstream ss;
	ss << _port;
	this->pimpl->port = ss.str();
	return *this;
}

GameSparksRTSessionBuilder& GameSparksRTSessionBuilder::SetListener(IRTSessionListener* listener_){

    // if this assertion fails, you have already registered a session listener.
    assert(this->pimpl->listener == nullptr || listener_ == nullptr);

    this->pimpl->listener = listener_;
    return *this;
}

/// you own the return value. make sure to put it into a std::unique_ptr or std::shared_ptr (or delete it manually).
IRTSession* GameSparksRTSessionBuilder::Build() const{
    IRTSession* session = new RTSessionImpl (pimpl->connectToken, pimpl->host, pimpl->port, pimpl->port);
    session->SessionListener = pimpl->listener;
    if(pimpl->listener)
		pimpl->listener->session = session;
    return session;
}

// not a member variable to avoid DLL linking issues
static std::map<std::string, GameSparksRT::LogLevel> tagLevels;

std::function<void (const std::string&)> GameSparksRT::Logger = [](const std::string& msg){
    std::clog << msg << std::endl;
};

GameSparksRT::LogLevel GameSparksRT::logLevel = GameSparksRT::LogLevel::LL_ERROR;


void GameSparksRT::SetRootLogLevel(GameSparksRT::LogLevel level) {
    logLevel = level;
}

void GameSparksRT::SetLogLevel(const std::string &tag, GameSparksRT::LogLevel level) {
    tagLevels.insert(std::make_pair(tag, level));
}

bool GameSparksRT::ShouldLog(const std::string &tag, GameSparksRT::LogLevel level) {
    // TODO: only search once via find()
    if (tagLevels.count(tag)) {
        return tagLevels[tag] >= level;
    }
    return logLevel >= level;
}

GameSparksRTSessionBuilder GameSparksRT::SessionBuilder() {
    return RT::GameSparksRTSessionBuilder();
}

}} /* namespace GameSparks.RT */
