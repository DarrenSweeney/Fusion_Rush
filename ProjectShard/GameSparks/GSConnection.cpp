// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#include <easywsclient/easywsclient.hpp>
#include <GameSparks/GSConnection.h>
#include <GameSparks/GSMessage.h>
#include <GameSparks/GSUtil.h>
//#include <iostream>

using namespace GameSparks;
using namespace GameSparks::Core;
using namespace easywsclient;


GameSparks::Core::GSConnection::GSConnection(GS* gs, IGSPlatform* gsPlatform)
	: m_GS(gs)
	, m_GSPlatform(gsPlatform)
	, m_WebSocket(NULL)
	, m_Initialized(false)
	, m_Stopped(false)
    , m_lastActivity(0)
{
	m_URL = gs->GetServiceUrl();
	/*m_URL += "?deviceOS=" + m_GSPlatform->GetDeviceOS();
	m_URL += "&deviceID=" + m_GSPlatform->GetDeviceId();
	m_URL += "&SDK=" + m_GSPlatform->GetSDK();*/
	EnsureConnected();
}

void GameSparks::Core::GSConnection::EnsureConnected()
{
	// is it stopped?
	if (m_Stopped) return;

	// should it connect?
	if (GameSparks::Util::shouldConnect() == false) return;

	// connect
	if (m_WebSocket == NULL)
	{
		m_WebSocket = WebSocket::from_url(m_URL.c_str());
	}
}

void GameSparks::Core::GSConnection::Terminate()
{
	m_GS->DebugLog("Starting connection terminate");
	Stop();
	Close();
	m_GS->DebugLog("Connection terminated");
}

void GameSparks::Core::GSConnection::Stop()
{
	m_Stopped = true;
}

void GameSparks::Core::GSConnection::Close()
{
	if (m_WebSocket != NULL &&
		(m_WebSocket->getReadyState() == WebSocket::OPEN || m_WebSocket->getReadyState() == WebSocket::CONNECTING))
	{
		m_WebSocket->close();
		m_GS->DebugLog("WebSocket closed");
	}

    if (m_WebSocket != NULL)
    {
        delete m_WebSocket;
        m_WebSocket = NULL;
    }
}

void GameSparks::Core::GSConnection::SendImmediate(GSRequest& request)
{
	GS_CODE_TIMING_ASSERT();
	if (request.GetType().GetValue() != ".AuthenticatedConnectRequest")
	{
		if (request.GetString("requestId").HasValue() == false)
		{
			request.AddString("requestId", m_GS->GetUniqueRequestId());
		}

		m_PendingRequests.insert(t_RequestMapPair(request.GetString("requestId").GetValue(), request));
	}

	m_GS->DebugLog("Send immediate request: " + request.GetJSON());
    m_lastActivity = 0;
	m_WebSocket->send(request.GetJSON().c_str());
}

bool GameSparks::Core::GSConnection::GetReady() const
{
	GS_CODE_TIMING_ASSERT();
	return (m_WebSocket != NULL && m_WebSocket->getReadyState() == WebSocket::OPEN && m_Initialized);
}

void GameSparks::Core::GSConnection::SetReady(bool ready)
{
	m_Initialized = ready;
}

void GameSparks::Core::GSConnection::OnError(const gsstl::string& errorMessage)
{
    m_GS->DebugLog("WebSocket Error: " + errorMessage);
	m_Stopped = true;

}

GameSparks::Core::GSConnection::~GSConnection()
{
	assert(m_PendingRequests.empty());
	if (m_WebSocket != NULL)
	{
		delete m_WebSocket;
		m_WebSocket = NULL;
	}
}

bool GameSparks::Core::GSConnection::IsWebSocketConnectionAlive() const
{
	return m_WebSocket != NULL && m_WebSocket->getReadyState() != WebSocket::CLOSED;
}

void GSConnection::OnWebSocketCallback(const gsstl::string& message, void* userData)
{
	GS_CODE_TIMING_ASSERT();
	GSConnection *connectionObj = static_cast<GSConnection *>(userData);
	connectionObj->m_GS->DebugLog("WebSocket callback: " + message);
	connectionObj->GetGSInstance()->OnMessageReceived(message, *connectionObj);
}

void GSConnection::OnWebSocketError(const easywsclient::WSError& error, void* userData)
{
	GSConnection *self = static_cast<GSConnection *>(userData);

	if (error.code != easywsclient::WSError::CONNECTION_CLOSED)
	{
		self->m_GS->OnWebSocketClientError(error, self);
	}

	self->Stop();
}

bool GSConnection::Update(float deltaTime)
{
    m_lastActivity += deltaTime;

	if (m_WebSocket != NULL)
	{
		if (m_WebSocket->getReadyState() != WebSocket::CLOSED)
		{
			{
				m_WebSocket->poll(0, OnWebSocketError, this);
			}
			if (m_Stopped) return false;

			{
				m_WebSocket->dispatch(OnWebSocketCallback, OnWebSocketError, this);
			}

			if (m_Stopped) return false;
            
            if(m_lastActivity > 60)
			{
                m_lastActivity = 0;
				{
					m_WebSocket->send(" ");
				}
            }
            
		}
		else if (m_WebSocket->getReadyState() == WebSocket::CLOSED)
		{
			m_GSPlatform->DebugMsg("Websocket closed");
		}
	}

	return true;
}
