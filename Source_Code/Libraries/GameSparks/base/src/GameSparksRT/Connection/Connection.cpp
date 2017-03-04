#include "./Connection.hpp"
#include "../Proto/Packet.hpp"
#include "../Commands/CustomCommand.hpp"
#include "../Commands/Results/AbstractResult.hpp"

namespace GameSparks { namespace RT { namespace Connection {

Connection::Connection (const std::string& remoteHost, const std::string& port, IRTSessionInternal* session_)
:session(session_)
,stopped(false)
{
    assert(session);
    //emptyStream.Wrap (new BinaryWriteMemoryStream ());

    //IPAddress ipAddress;
    //IPAddress.TryParse (remoteHost, out ipAddress);

    //if (ipAddress == null) {
    //    IPHostEntry ipHostInfo = Dns.GetHostEntry(remoteHost);
    //    ipAddress = ipHostInfo.AddressList[0];
    //}

    //remoteEndPoint = new IPEndPoint(ipAddress, port);
    remoteEndPoint.Host = remoteHost;
    remoteEndPoint.Port = port;
}

System::Failable<void> Connection::OnPacketReceived(Proto::Packet& p)
{
    assert(session);

    if (p.Command != nullptr) {
        //if (typeof(AbstractResult).IsAssignableFrom (p.Command.GetType ())) {
        //    AbstractResult result = ((AbstractResult)p.Command);
        AbstractResult* result = p.Command->asAbstractResult();
        if(result) {
            result->Configure (p, *session);
            if (result->ExecuteAsync ()) {
                session->SubmitAction (p.Command);
            } else {
                p.Command->Execute ();
            }
        } else {
            session->SubmitAction (p.Command);
        }

    } else {
        //If it has a payload, we've already got the IRTCommand from the user
        if (!p.hasPayload) {
            System::IO::MemoryStream emptyStream;
            GS_ASSIGN_OR_THROW(tmp, CustomCommand::Deserialize(p.OpCode, p.Sender.GetValueOrDefault(0), emptyStream, p.Data, 0, *session));
            std::unique_ptr<IRTCommand> cmd(tmp);
            session->SubmitAction ( cmd );
        }
    }
    return {};
}

}}} /* namespace GameSparks.RT.Connection */

	