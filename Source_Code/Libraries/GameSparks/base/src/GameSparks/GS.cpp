// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.

#if defined(WINAPI_FAMILY)
#	define __STDC_WANT_SECURE_LIB__ 0
#	define sprintf_s(buf, size, fmt, ...) sprintf(buf, fmt, __VA_ARGS__)
#	define swprintf_s(buf, size, fmt, ...) swprintf(buf, size, fmt, __VA_ARGS__)
#endif

#include <GameSparks/GS.h>
//#include <iostream>
#include <GameSparks/GSUtil.h>
//#include <sstream>
#include <GameSparks/GSMessage.h>
#include <cassert>
#include <ctime>
#include <easywsclient/easywsclient.hpp>

#include <stdio.h>
#if (defined(WIN32) || defined(WINAPI_FAMILY)) && !defined(IW_SDK) && !defined(snprintf)
#	define snprintf _snprintf
#endif /* WIN32 */

using namespace GameSparks;
using namespace GameSparks::Core;
using namespace GameSparks::Api::Messages;

/*__declspec(dllexport) GS GameSparks::Core::GS = GS();*/

GS::GS()
    : GameSparksAvailable()
    , GameSparksAuthenticated()
    , OnPersistentQueueLoadedCallback()
    , m_GSPlatform(NULL)
    , m_RequestCounter(0)
    , m_Ready(false)
    , m_Paused(false)
    , m_Initialized(false)
    , m_durableQueuePaused(false)
    , m_durableQueueRunning(true)
    , m_nextReconnectSeconds(0.0f)
    , m_SessionId("")
{
	/*
		If this assertion fails, your compiler fails to initialize
		GameSparksAvailable, even though a default initialization was
		requested in the initializer list.
	*/
	assert( !GameSparksAvailable );
	assert( !GameSparksAuthenticated );
}

GS::~GS()
{
	for (t_ConnectionContainer::iterator it = m_Connections.begin(); it != m_Connections.end(); ++it)
	{
		// this is to avoid the assert in the destructor of GSConnection firing.
		(*it)->m_PendingRequests.clear();
		delete *it;
	}
	m_Connections.clear();
    
    for(t_MessageHandlerMap::iterator i = m_MessageHandlers.begin(); i != m_MessageHandlers.end(); ++i)
    {
        delete i->second;
    }
    m_MessageHandlers.clear();
}

void GS::Initialise(IGSPlatform* gSPlatform)
{
	m_Initialized = true;
	m_Paused = false;
	m_GSPlatform = gSPlatform;
	m_ServiceUrl = m_GSPlatform->GetServiceUrl();

	gSPlatform->DurableInit();
    InitialisePersistentQueue();
    SetDurableQueueRunning(true);
	
	m_Connections.push_back(new GSConnection(this, m_GSPlatform));
	DebugLog("Initialized");


	/*
	TODO: put into Test
	
	RequestQueue q;
	q.push_back(GSRequest(*this, "fooRequestType"));
	q.push_back(GSRequest(*this, "fooRequestType"));
	q.push_back(GSRequest(*this, "fooRequestType"));
	q.push_back(GSRequest(*this, "fooRequestType"));
	SaveRequestQueue("foo", q);

	RequestQueue q2 = LoadRequestQueue("foo");
	assert(SerializeRequestQueue(q) == SerializeRequestQueue(q2));*/
}

void GameSparks::Core::GS::ShutDown()
{
	//DebugLog("Shutdown");
	m_Initialized = false;
	m_Paused = true;
	Stop(true);
	// clear the connections
	//UpdateConnections(0);
}

void GameSparks::Core::GS::NewConnection()
{
	GS_CODE_TIMING_ASSERT();
	if (!m_Paused)
	{
		DebugLog("Create new connection");
		Stop(false);
		gsstl::reverse(m_Connections.begin(), m_Connections.end());
		m_Connections.push_back(new GSConnection(this, m_GSPlatform));
		gsstl::reverse(m_Connections.begin(), m_Connections.end());
	}
}

void GS::Stop(bool termiante)
{
	for (t_ConnectionContainer::iterator it = m_Connections.begin(); it != m_Connections.end(); ++it)
	{
		GSConnection* connection = *it;
		if (termiante) connection->Terminate();
		else connection->Stop();
	}


	SetAvailability(false);
}

void GS::OnMessageReceived(const gsstl::string& message, GSConnection& connection)
{
	GS_CODE_TIMING_ASSERT();

	GSObject response = GSObject::FromJSON(message);

	if (response.ContainsKey("connectUrl"))
	{
		DebugLog("Received new connection url from gamesparks backend. Establishing new connection now.");
		m_ServiceUrl = response.GetString("connectUrl").GetValue();
		NewConnection();
	}

	if (response.ContainsKey("authToken"))
	{
		DebugLog("Received auth token");
		m_GSPlatform->SetAuthToken(response.GetString("authToken").GetValue());
	}

	if (response.GetType().HasValue())
	{
		if (response.GetType().GetValue() == ".AuthenticatedConnectResponse")
		{
			DebugLog("Handle authentication connect response with immediate handshake");
			Handshake(response, connection);
		}
		else
		{
			ProcessReceivedItem(response, &connection);
		}
	}


	//std::cout << "@class: " << response.GetType().first.c_str() << std::endl;
	//std::cout << "@class: " << response.GetJSON().c_str() << std::endl;
}



void GameSparks::Core::GS::Handshake(GSObject& response, GSConnection& connection)
{
	GS_CODE_TIMING_ASSERT();

	if (response.ContainsKey("error"))
	{
		// this method can be called indirectly from the websockets _dispatch member function
		// if we'd call shutdown here, we'd delete the socket, while a member function of of the
		// web socket is still on the callstack. Therefore we defer the shutdown
		m_nextReconnectSeconds = 5.0f;

		DebugLog("Got error during handshake. Please make sure, that you've setup you credentials.");
		DebugLog("Backing off for five seconds");
	}
	else if (response.ContainsKey("nonce"))
	{
		SendHandshake(response, connection);
	}
	else
	{
		if (response.ContainsKey("sessionId"))
		{
			m_SessionId = response.GetString("sessionId").GetValue();
			if (response.ContainsKey("authToken"))
			{
				m_GSPlatform->SetAuthToken(response.GetString("authToken").GetValue());
			}
			else
			{
				m_GSPlatform->SetAuthToken("0");
			}
			connection.SetReady(true);
			SetAvailability(true);

			if (response.ContainsKey("userId"))
			{
				SetUserId(response.GetString("userId").GetValue());
			}
		}
	}
}

void GameSparks::Core::GS::SendHandshake(GSObject& response, GSConnection& connection)
{
	GSRequest handshakeRequest(*this, ".AuthenticatedConnectRequest");
	handshakeRequest.AddString("hmac", GameSparks::Util::getHMAC(response.GetString("nonce").GetValue(), m_GSPlatform->GetGameSparksSecret()));
	handshakeRequest.AddString("os", m_GSPlatform->GetDeviceOS());
	handshakeRequest.AddString("platform", m_GSPlatform->GetPlatform());
	handshakeRequest.AddString("deviceId", m_GSPlatform->GetDeviceId());
	
	if (m_GSPlatform->GetAuthToken() != "" && m_GSPlatform->GetAuthToken() != "0")
	{
		handshakeRequest.AddString("authToken", m_GSPlatform->GetAuthToken());
	}

	if (m_SessionId != "")
	{
		handshakeRequest.AddString("sessionId", m_SessionId);
	}

	connection.SendImmediate(handshakeRequest);
	DebugLog("Handshake request sent");
}

void GameSparks::Core::GS::SendDurable(GSRequest& request)
{
	request.AddString("requestId", GetUniqueRequestId(true));
	m_PersistentQueue.push_front(request);
	WritePersistentQueue();
}

void GameSparks::Core::GS::Send(GSRequest& request)
{
	if (request.GetDurable())
	{
		SendDurable(request);
		return;
	}


	request.m_CancelSeconds = request.m_ResponseTimeout != 0 ? request.m_ResponseTimeout : m_GSPlatform->GetRequestTimeoutSeconds();
	request.m_WaitForResponseSeconds = request.m_ResponseTimeout != 0 ? request.m_ResponseTimeout : m_GSPlatform->GetRequestTimeoutSeconds();

	if (m_Connections.size() == 0)
	{
		NewConnection();
	}

	if (m_Connections.size() > 0 && m_Connections[0]->GetReady())
	{
		m_Connections[0]->SendImmediate(request);
	}
	else
	{
		m_SendQueue.push_back(request);
	}
}

void GS::Update(Seconds deltaTimeInSeconds)
{
	GS_CODE_TIMING_ASSERT();
	if (m_Initialized)
	{
		m_nextReconnectSeconds -= deltaTimeInSeconds;
		UpdateConnections(deltaTimeInSeconds);
		ProcessQueues(deltaTimeInSeconds);
	}
}

void GameSparks::Core::GS::DebugLog(const gsstl::string& message)
{
	GS_CODE_TIMING_ASSERT();
	m_GSPlatform->DebugMsg(message);
}

void GS::UpdateConnections(Seconds deltaTimeInSeconds)
{
	GS_CODE_TIMING_ASSERT();
	for (t_ConnectionContainer::size_type i = 0; i < m_Connections.size(); ++i)
	{
		GSConnection* connection = m_Connections[i];

		if(connection->IsWebSocketConnectionAlive() && !connection->Update(deltaTimeInSeconds))
			break;
	}
}

gsstl::string GameSparks::Core::GS::GetUniqueRequestId(bool durable)
{
	GS_CODE_TIMING_ASSERT();
	static char buffer[256];
	snprintf(buffer, sizeof(buffer)/sizeof(buffer[0]), "%ld_%ld", (long)time(0), m_RequestCounter++);
	if (durable)
	{
		return "d_" + gsstl::string(buffer);
	}else
	{
		return gsstl::string(buffer);
	}

}

void GameSparks::Core::GS::OnWebSocketClientError(const easywsclient::WSError& error, GSConnection* connection)
{
	/*if(error.code == easywsclient::WSError::DNS_LOOKUP_FAILED)
	{
		Disconnect();
	}

	if(m_Connections.size() > 0 && m_Connections[0] == connection)
	{
		SetAvailability(false);

	}*/

	if(!m_Connections.empty() && m_Connections.front() == connection)
	{
        //Reset the url to the load balancer url in case the server being connected to no longer exsts
        m_ServiceUrl = m_GSPlatform->GetServiceUrl();
        
		DebugLog("Received websocket error: " + error.message);
		DebugLog("Got websocket error. Please make sure, that you've setup you credentials.");
		DebugLog("Backing off for one seconds");
		SetAvailability(false);
		m_nextReconnectSeconds = 1.0f;
	}
}

void GameSparks::Core::GS::SetAvailability(bool available)
{
	if (m_Ready != available)
	{
		m_Ready = available;
		
		if (GameSparksAvailable)
		{
			GameSparksAvailable(*this, available);
		}
	}
}

void GameSparks::Core::GS::ConnectIfRequired()
{
	GS_CODE_TIMING_ASSERT();
	if (m_nextReconnectSeconds <= Seconds(0.0) &&
		(m_Connections.size() == 0 ||
		m_Connections[0]->m_Stopped) )
	{
		NewConnection();
	}
}

bool GameSparks::Core::GS::GetAuthenticated() const
{
	return m_Ready && m_GSPlatform->GetAuthToken() != "" && m_GSPlatform->GetAuthToken() != "0";
}

/*void GameSparks::Core::GS::SendDurable(GSRequest& request)
{

}*/

void GameSparks::Core::GS::ProcessSendQueue(Seconds deltaTimeInSeconds)
{
	if (m_SendQueue.size() > 0)
	{
		GSRequest& request = *m_SendQueue.begin();

		request.m_CancelSeconds -= deltaTimeInSeconds;

		if (request.m_CancelSeconds <= 0)
		{
			CancelRequest(request); // needs to be called, before it's popped from the queue
			m_SendQueue.pop_front();
		}

		if (m_Connections.size() > 0 && m_Connections[0]->GetReady())
		{
			m_Connections[0]->SendImmediate(request);
			m_SendQueue.pop_front();
		}
	}
}

void GameSparks::Core::GS::ProcessPendingQueue(Seconds deltaTimeInSeconds)
{
	for(t_ConnectionContainer::iterator connection = m_Connections.begin(); connection != m_Connections.end(); ++connection)
	{
		gsstl::vector<GSRequest> toCancel;
		for(GSConnection::t_RequestMap::iterator request=(*connection)->m_PendingRequests.begin(); request!=(*connection)->m_PendingRequests.end(); ++request)
		{
			request->second.m_WaitForResponseSeconds -= deltaTimeInSeconds;

			if(request->second.m_WaitForResponseSeconds < Seconds(0))
			{
				toCancel.push_back(request->second);
			}
		}

		for(gsstl::vector<GSRequest>::iterator request = toCancel.begin(); request != toCancel.end(); ++request)
		{
			CancelRequest(*request, *connection);
		}
	}
}

void GameSparks::Core::GS::CancelRequest(GSRequest& request)
{
	GSObject error("ClientError");
	error.AddObject("error", GSRequestData().AddString("error", "timeout"));
	error.AddString("requestId", request.GetString("requestId").GetValue());

	request.Complete(error);
}

void GameSparks::Core::GS::CancelRequest(GSRequest& request, GSConnection* connection)
{
	GSObject error("ClientError");
	error.AddObject("error", GSRequestData().AddString("error", "timeout"));
	error.AddString("requestId", request.GetString("requestId").GetValue());
	ProcessReceivedResponse(error, connection);
}

void GameSparks::Core::GS::ProcessQueues(Seconds deltaTimeInSeconds)
{
	GS_CODE_TIMING_ASSERT();
	ConnectIfRequired();

	TrimOldConnections();
	ProcessPersistantQueue(deltaTimeInSeconds);
	ProcessSendQueue(deltaTimeInSeconds);
	ProcessPendingQueue(deltaTimeInSeconds);
}

void GameSparks::Core::GS::TrimOldConnections()
{
	GS_CODE_TIMING_ASSERT();
	for (t_ConnectionContainer::iterator it = m_Connections.begin(); it != m_Connections.end(); )
	{
		GSConnection* connection = *it;

		if (connection->m_PendingRequests.size() == 0 && connection->m_Stopped)
		{
			connection->Close();
			it = m_Connections.erase(it);
			delete connection;
		}
		else
		{
			++it;
		}
	}
}

void GameSparks::Core::GS::ProcessReceivedResponse(const GSObject& response, GSConnection* connection)
{
	if (response.GetString("requestId").HasValue())
	{
		gsstl::string requestId = response.GetString("requestId").GetValue();
		
		GSConnection::t_RequestMap::iterator findIt = connection->m_PendingRequests.find(requestId);
		if (findIt != connection->m_PendingRequests.end())
		{
			GSRequest request = findIt->second;
			connection->m_PendingRequests.erase(findIt);

			if (request.GetDurable() && request.m_DurableRetrySeconds > 0)
			{
				// remove from persistent queue
				//It's durable request, if it's a ClientError do nothing as it will be retried
                if (request.ContainsKey("@class") && request.GetString("@class").GetValue() != "ClientError")
                {
					RemoveDurableQueueEntry(request);
					request.Complete(response);
                }
			}
			else
			{
				request.Complete(response);
			}
		}
	}
}

bool GameSparks::Core::GS::RemoveDurableQueueEntry(const GSRequest& request)
{
	gsstl::string idToRemove = request.GetString("requestId").GetValue();
	for (t_PersistentQueue::iterator it = m_PersistentQueue.begin(); it != m_PersistentQueue.end(); it++)
	{
		if (it->GetString("requestId").GetValue() == idToRemove)
		{
			m_PersistentQueue.erase(it);
			WritePersistentQueue();
			m_GSPlatform->DebugMsg("Removed request from persistent queue");

			return true;
		}
	}
	return false;
}

size_t GameSparks::Core::GS::GetRequestQueueCount()
{
	return m_PersistentQueue.size();
}

bool GameSparks::Core::GS::GetDurableQueueRunning()
{
	return m_durableQueueRunning;
}
void GameSparks::Core::GS::SetDurableQueueRunning(bool value)
{
	m_durableQueueRunning = value;
}

bool StringEndsWith(const gsstl::string& str, const gsstl::string& pattern)
{
	return  (str.size() >= pattern.size() && str.substr(str.size() - pattern.size()) == pattern);
}

void GameSparks::Core::GS::ProcessReceivedItem(const GSObject& response, GSConnection* connection)
{
	GS_CODE_TIMING_ASSERT();
	gsstl::string responseType = response.GetType().GetValue();
	
	if (StringEndsWith(responseType, "Response"))
	{
		if (responseType == ".AuthenticationResponse")
		{
			SetUserId(response.GetString("userId").GetValue());
		}
		ProcessReceivedResponse(response, connection);
	}
	else if (StringEndsWith(responseType, "Message"))
	{
        t_MessageHandlerMap::iterator pos = m_MessageHandlers.find(responseType);
        
        if (pos != m_MessageHandlers.end()){
            pos->second->CallMessageListener(*this, response);
        }
        //GSMessage::NotifyHandlers(response);
	}
}

void GameSparks::Core::GS::ProcessPersistantQueue(Seconds deltaTimeInSeconds)
{
	GS_CODE_TIMING_ASSERT();
	if(!GetDurableQueueRunning() || m_durableQueuePaused)
	{
		return;
	}
	for (t_PersistentQueue::iterator request = m_PersistentQueue.begin(); request != m_PersistentQueue.end(); request++)
	{
		request->m_DurableRetrySeconds -= deltaTimeInSeconds;
		if (request->m_DurableRetrySeconds <= 0)
		{
			if (m_Connections.size() > 0 && m_Connections[0]->GetReady())
			{
				request->m_WaitForResponseSeconds = m_GSPlatform->GetRequestTimeoutSeconds();
				request->m_CancelSeconds = m_GSPlatform->GetRequestTimeoutSeconds();
				request->m_DurableRetrySeconds = Seconds(10);
				m_Connections[0]->SendImmediate(*request);
			}
		}
	}

}

void GameSparks::Core::GS::SetUserId(const gsstl::string& userId)
{
	GS_CODE_TIMING_ASSERT();
	// TODO: Review
	if(m_GSPlatform->GetUserId() != userId)
	{
		m_GSPlatform->SetUserId(userId);
		// clear the pending durable requests for recent user. 
        //Log("New UserId init persistent queue");
		
		//Temporarily stop durable queue processing
		m_durableQueuePaused = true;


		//GSPlatform.ExecuteOnMainThread (() => 
		{
			InitialisePersistentQueue();

			//We want this to be callback to the user code to allow them to make decisions 
			//about the queue before we start processing it, but after it's been initialised
			if (GameSparksAuthenticated)
			{
				GameSparksAuthenticated(*this, userId);
			}
			//Resume queue processing.
			m_durableQueuePaused = false;
		}
	}
    else
	{
		//Log("UserId already known");
	}
}


void GameSparks::Core::GS::Disconnect()
{
	GS_CODE_TIMING_ASSERT();
	m_Paused = true;
	Stop(false);
}

void GameSparks::Core::GS::Reconnect()
{
	GS_CODE_TIMING_ASSERT();
	m_Paused = false;
	ConnectIfRequired();
}

void GameSparks::Core::GS::NetworkChange(bool available)
{
	GS_CODE_TIMING_ASSERT();
	if (available)
	{
		Disconnect();
	}
	else
	{
		Reconnect();
	}
}

void GameSparks::Core::GS::Reset()
{
	GS_CODE_TIMING_ASSERT();
	Disconnect();
	m_SessionId = "";
	m_GSPlatform->SetAuthToken("0");
	Reconnect();
}


//! save requests queue as name
void GS::WritePersistentQueue()
{
	GS_CODE_TIMING_ASSERT();
	gsstl::string json = SerializeRequestQueue(m_PersistentQueue);
	m_GSPlatform->StoreValue(m_GSPlatform->GetUserId() + "_persistentQueue", json);
}

//! an empty queue will be returned, if no queue named queue can be found
void GS::InitialisePersistentQueue()
{
	GS_CODE_TIMING_ASSERT();
	gsstl::string json = m_GSPlatform->LoadValue( m_GSPlatform->GetUserId() + "_persistentQueue");
	m_PersistentQueue = DeserializeRequestQueue(json);
    
    if (OnPersistentQueueLoadedCallback)
    {
        OnPersistentQueueLoadedCallback(*this);
    }
}


gsstl::string GS::SerializeRequestQueue(const t_PersistentQueue& q)
{
	GS_CODE_TIMING_ASSERT();
	cJSON* list = cJSON_CreateArray();

	for (t_PersistentQueue::const_iterator i = q.begin(); i != q.end(); ++i)
	{
		cJSON* item = i->GetBaseData();
		cJSON_AddItemReferenceToArray(list, item);
	}

	char* asText = cJSON_Print(list);
	gsstl::string result(asText);
	free(asText);
	cJSON_Delete(list);

	return result;
}


GS::t_PersistentQueue GS::DeserializeRequestQueue(const gsstl::string& s)
{
	GS_CODE_TIMING_ASSERT();
	cJSON* list = cJSON_Parse(s.c_str());

	t_PersistentQueue result;
	if (list)
	{
		int size = cJSON_GetArraySize(list);
		for (int i = 0; i < size; ++i)
		{
			if (cJSON* item = cJSON_GetArrayItem(list, i))
			{
				GSRequest request(*this, item);
                request.SetDurable(true); // every request from the queue is durable!
				result.push_back(request);
			}
		}

		cJSON_Delete(list);
	}

	return result;
}


GS::t_PersistentQueue& GS::GetDurableQueueEntries()
{
	return m_PersistentQueue;
}

struct UserDataEqualTo
{
	UserDataEqualTo(const void* userData) : userData_(userData) {}
	bool operator()(const GSRequest& request) { return request.GetUserData() == userData_; }
	bool operator()(const gsstl::pair<gsstl::string, GSRequest>& p) { return p.second.GetUserData() == userData_; }
	const void* userData_;
};

void GS::ChangeUserDataForRequests(const void *from, void* to)
{
	GS_CODE_TIMING_ASSERT();
	assert(m_Initialized);
	assert(this->m_GSPlatform);

	// erase from send queue
	for (t_SendQueue::iterator i = m_SendQueue.begin(); i != m_SendQueue.end(); ++i)
	{
		if (i->GetUserData() == from)
		{
			i->SetUserData(to);
		}
	}

	for (t_PersistentQueue::iterator i = m_PersistentQueue.begin(); i != m_PersistentQueue.end(); ++i)
	{
		if (i->GetUserData() == from)
		{
			i->SetUserData(to);
		}
	}

	// also change it it on all pending requests in all connections
	for (t_ConnectionContainer::iterator i = m_Connections.begin(); i != m_Connections.end(); ++i)
	{
		for (GSConnection::t_RequestMap::iterator j = (*i)->m_PendingRequests.begin(); j != (*i)->m_PendingRequests.end(); ++j)
		{
			if (j->second.GetUserData() == from)
			{
				j->second.SetUserData(to);
			}
		}
	}
}
