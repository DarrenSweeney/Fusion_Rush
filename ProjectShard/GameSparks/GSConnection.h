// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#ifndef GSConnection_h__
#define GSConnection_h__

#pragma once

#include "GS.h"
#include "IGSPlatform.h"
#include "GSRequest.h"
#include <GameSparks/GSLeakDetector.h>

namespace easywsclient 
{
	class WebSocket;
	struct WSError;
}

namespace GameSparks
{
	namespace Core
	{
		class GS;
		class GSRequest;

		/// represents a connection. This is an internal class and there should be no need to interact with it directly.
		class GSConnection
		{
		public:
			GSConnection(GS* gs, IGSPlatform* gsPlatform);
			~GSConnection();

			void Terminate();
			void Stop();
			void Close();
			void OnOpened();
			void OnClosed();
			void OnError(const gsstl::string& errorMessage);
			void EnsureConnected();
			bool GetReady() const;
			void SetReady(bool ready);
			void SendImmediate(GSRequest& request);

			bool Update(float deltaTime);
			 GS* GetGSInstance() const { return m_GS; }
			 bool IsWebSocketConnectionAlive() const;
		protected:
			static void OnWebSocketCallback(const gsstl::string& message, void* userData);
			static void OnWebSocketError(const easywsclient::WSError& error, void* userData);
		private:
			GS* m_GS;
			IGSPlatform* m_GSPlatform;

			easywsclient::WebSocket* m_WebSocket;
			gsstl::string m_URL;
			bool m_Initialized;
			bool m_Stopped;
            float m_lastActivity;

			typedef gsstl::map<gsstl::string, GSRequest> t_RequestMap;
			typedef gsstl::pair<gsstl::string, GSRequest> t_RequestMapPair;
			t_RequestMap m_PendingRequests;

			friend class GS;
            
            GS_LEAK_DETECTOR(GSConnection)
		};
	}
}
#endif // GSConnection_h__
