// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#ifndef GS_h__
#define GS_h__

#pragma once
#include "IGSPlatform.h"
#include "GSRequest.h"
#include "GSConnection.h"
#include <GameSparks/GSLeakDetector.h>
#include <cassert>

#include "./gsstl.h"

namespace easywsclient
{
	struct WSError;	
}

//! root GameSparks namespace
namespace GameSparks
{
	//! This namespace contains the hand written gist of the SDK
	namespace Core
	{
		class GSConnection;
		class GSObject;
		class GSRequest;

		/*! The Core GS-API Object.
		  * You can either create an instance of this class locally or create it where ever convenient for you.
		  * Please note, that it is discouraged to have multiple instances of this class at the same time.
		  */
		class GS // this naming should be discussed, it was chosen because we need the static object with the name "GS"
		{
			public:
				#if defined(GS_USE_STD_FUNCTION)
					typedef gsstl::function<void(GS&, bool)> t_AvailableCallback;
				#else
					typedef void(*t_AvailableCallback)(GS&, bool);
				#endif /* GS_USE_STD_FUNCTION */

				/// Callback which is triggered whenever the service becomes available or the connection to the service is lost. 
				t_AvailableCallback GameSparksAvailable;

				#if defined(GS_USE_STD_FUNCTION)
					typedef gsstl::function<void(GS&,const gsstl::string& userId)> t_AuthenticatedCallback;
				#else
					typedef void(*t_AuthenticatedCallback)(GS&, const gsstl::string& userId);
				#endif /* GS_USE_STD_FUNCTION */

				/// Callback which is triggered whenever a new user is authenticated
				t_AuthenticatedCallback GameSparksAuthenticated;

				GS();

				~GS();

				bool GetDurableQueueRunning();
				void SetDurableQueueRunning(bool running);

				typedef gsstl::list<GSRequest> t_PersistentQueue;
            
                /*!
                    This gives you direct access to the items currently in the durable queue.

                    Note, that this is slightly different to the .NET SDK: The .NET SDK is returning
                    a list of references to requests. The C++ SDK is returning an internal reference.
                 */
				t_PersistentQueue& GetDurableQueueEntries();

				bool RemoveDurableQueueEntry(const GSRequest& request);

				size_t GetRequestQueueCount();

				#if defined(GS_USE_STD_FUNCTION)
					typedef gsstl::function<void(GS&)> t_OnPersistentQueueLoadedCallback;
				#else
					typedef void(*t_OnPersistentQueueLoadedCallback)(GS&);
				#endif /* GS_USE_STD_FUNCTION */
            
                /*!
             
                    This callback will be called each time the persistent queue is deserialized. It can be used
                    to re-attach the callbacks to the requests in the persistent queue via request.SetCallback.
             
                    This is necessary because callbacks cannot be serialized.
             
                    Be carfull when modifying the passed queue !
                 */
                t_OnPersistentQueueLoadedCallback OnPersistentQueueLoadedCallback;


				/// Initialize this GS instance. This has to be called before calling any other member functions.
				void Initialise(IGSPlatform* gSPlatform);

				void printConnections();

				/// shutdown this GS instance. You cannot call any other member function after this call.
				void ShutDown();

				/// Stops all connections. 
				void Disconnect();

				/// Reconnect to the GameSparks service. 
				void Reconnect();

				/// Stops all connections, resets the authentication token and establishes a new connection to the service. 
				void Reset();

				/// True if a connection to the service is available for use. 
				bool GetAvailable() const { return m_Ready; }

				/// True if a connection is available and the user is authenticated. 
				bool GetAuthenticated() const;

				/// <summary>
				/// Send the given request durable. 
				/// Durable requests are persisted automatically. 
				/// If it cannot be send right now the sdk will try to send it later. 
				/// </summary>
				void SendDurable(GSRequest& request);

				/// Send the given request. 
				void Send(GSRequest& request);

				// True if a connection to the service is available for use. 
				// bool GetGameSparksAvailable();

				/// Update this GS-instance. This has to be called as often as possible
				/// @param deltaTimeInSeconds the time since the last call to Update() in seconds
				void Update(Seconds deltaTimeInSeconds);

	            /*!
	                Registers MessageListener via GS.SetMessageListener(OnAchievementEarnedMessage)
	                if you pass null, the MessageListener is unregistered.

	                Note: the signature could also be written as:
	                void SetMessageListener(const typename MessageType::t_ListenerFunction& listener)
	             
	                but writing out the type (e.g. not using a dependent type name) enabled the compiler to
	                deduce MessageType. So the user can write:
	                    GS.SetMessageListener(OnAchievementEarnedMessage)
	                instead of
	                    GS.SetMessageListener<GameSparks::Api::Messages::AchievementEarnedMessage>(OnAchievementEarnedMessage);
	             
	                This of cause only works, if the passed MessageListener has the correct Signature:
	                    
	                void OnAchievementEarnedMessage(GameSparks::Core::GS& gsInstance, const MessageType& message)

	                @tparam MessageType the type of the message you want to listen for
	             */
	            template <typename MessageType>
	            #if defined(GS_USE_STD_FUNCTION)
	                void SetMessageListener(const gsstl::function<void(class GS&, const MessageType&)>& listener)
	            #else
	                void SetMessageListener( void(*listener)(class GS&, const MessageType&) )
	            #endif /* GS_USE_STD_FUNCTION */
	            {
	                const char* messageTypeName = MessageType::GetTypeName();
	                t_MessageHandlerMap::iterator pos = m_MessageHandlers.find(messageTypeName);
	                
	                if (pos != m_MessageHandlers.end())
					{
						delete pos->second;
						m_MessageHandlers.erase(pos);
					}

	                if (listener)
	                {
	                    m_MessageHandlers[ MessageType::GetTypeName() ] = new MessageListener<MessageType>(listener);
	                }
	            }

	            /// returns the Device-Id provided by IGSPlatform instance this GS-instance was initialized with.
	            gsstl::string GetDeviceId() const
	            {
	            	// you have to call Initialize with a non-null platform instance first
	            	assert(m_GSPlatform);
	            	return m_GSPlatform->GetDeviceId();
	            }

	            /// returns the Device-OS provided by IGSPlatform instance this GS-instance was initialized with.
	            gsstl::string GetDeviceOS() const
	            {
	            	// you have to call Initialize with a non-null platform instance first
	            	assert(m_GSPlatform);
	            	return m_GSPlatform->GetDeviceOS();
	            }

	            /// change user-data to *to* for all requests that currently have user-data *from*
	            /// If the request was already delivered, but the response is outstanding, the callbacks
            	/// wont be called. This is usefully if the object userData is pointing to gets destroyed
				void ChangeUserDataForRequests(const void *from, void* to);
			private:
				friend class GSConnection;
				void OnWebSocketClientError(const easywsclient::WSError& errorMessage, GSConnection* connection);
				void OnMessageReceived(const gsstl::string& message, GSConnection& connection);
				gsstl::string GetServiceUrl() const { return m_ServiceUrl; }
				void SetAvailability(bool available);
				Seconds GetRequestTimeoutSeconds();

				void DebugLog(const gsstl::string& message);

				void NetworkChange(bool available);
				void UpdateConnections(Seconds deltaTimeInSeconds);
				void Stop(bool termiante);
				void NewConnection();
				void Handshake(GSObject& response, GSConnection& connection);
				void SendHandshake(GSObject& response, GSConnection& connection);
				gsstl::string GetUniqueRequestId(bool durable=false);
				void ConnectIfRequired();
				void ProcessSendQueue(Seconds deltaTimeInSeconds);
				void CancelRequest(GSRequest& request);
				void CancelRequest(GSRequest& request, GSConnection* connection);
				void ProcessQueues(Seconds deltaTimeInSeconds);
				void TrimOldConnections();
				void ProcessReceivedResponse(const GSObject& response, GSConnection* connection);
				void ProcessReceivedItem(const GSObject& response, GSConnection* connection);
				void ProcessPendingQueue(Seconds deltaTimeInSeconds);

				void InitialisePersistentQueue();
				void ProcessPersistantQueue(Seconds deltaTimeInSeconds);
				void WritePersistentQueue();
				void SetUserId(const gsstl::string& userId);


				
				gsstl::string SerializeRequestQueue(const t_PersistentQueue& q);
				t_PersistentQueue DeserializeRequestQueue(const gsstl::string& s);

				IGSPlatform* m_GSPlatform;
				typedef gsstl::vector<GSConnection*> t_ConnectionContainer;
				t_ConnectionContainer m_Connections;
				gsstl::string m_ServiceUrl;

				typedef gsstl::list<GSRequest> t_SendQueue;
				t_SendQueue m_SendQueue;

				t_PersistentQueue m_PersistentQueue;

				long m_RequestCounter;

				// BS: we might want to change this to a state enum. they appear to be mutually exclusive.
				bool m_Ready;
				bool m_Paused;
				bool m_Initialized;
				bool m_durableQueuePaused; // internal value
				bool m_durableQueueRunning; // user controlled value
				Seconds m_nextReconnectSeconds;
				gsstl::string m_SessionId;

	            /*
	                MessageListeners
	             */
	            
	            // base class - provides the interface
	            struct MessageListenerBase
	            {
	                virtual void CallMessageListener(GS& gsInstance, const GSData& message) const = 0;
	                virtual ~MessageListenerBase(){}
	                
	                private:
	                GS_LEAK_DETECTOR(MessageListenerBase)
	            };
	            
	            // specialisation for a concrete MessageType
	            template <typename MessageType>
	            struct MessageListener : public MessageListenerBase
	            {
	                #if defined(GS_USE_STD_FUNCTION)
	                    typedef gsstl::function<void(class GS&, const MessageType&)> t_ListenerFunction;
	                #else
	                    typedef void(*t_ListenerFunction)(class GS&, const MessageType&);
	                #endif /* GS_USE_STD_FUNCTION */

	                MessageListener(const t_ListenerFunction& listener)
	                :m_Listener(listener) {}

	                virtual void CallMessageListener(GS& gsInstance, const GSData& data) const
	                {
	                    MessageType message(data); // convert jelly bean GSData to concrete GSMessage
	                    m_Listener(gsInstance, message); // call the listener
	                }
	                
	                t_ListenerFunction m_Listener;
	                
	                GS_LEAK_DETECTOR(MessageListener)
	            };
	            
	            typedef gsstl::map<gsstl::string, MessageListenerBase*> t_MessageHandlerMap;
	            t_MessageHandlerMap m_MessageHandlers;
	            
	            private:
	            GS_LEAK_DETECTOR(GS)
		};


		#if defined(__GNUC__) || defined(__clang__)
		#	define GS_DEPRECATED(func) func __attribute__ ((deprecated))
		#elif defined(_MSC_VER)
		#	define GS_DEPRECATED(func) __declspec(deprecated) func
		#else
		#	pragma message("WARNING: You need to implement DEPRECATED for this compiler")
		#	define GS_DEPRECATED(func) func
		#endif

		// GS_ is deprecated and will be removed in future versions. Use GS instead
		typedef GS GS_DEPRECATED(GS_);
	} /* namespace Core */

	/// \example sample01Connect.cpp This is an example of how to use the GS class.
	/// \example sample02ConnectStatic.cpp This is an example of how to use GameSparks via a global GS-objects.
	/// \example sample03Authentication.cpp This is an example of how to authenticate a user.
	/// \example sample05Challangerequest.cpp This is an example on how to use CreateChallengeRequest.
	/// \example sample04Listachievements.cpp This is an example of how to list some achievements.

	/// \example sample06Stresstest.cpp This is more a test than an example. It shows, that the teardown and assignment works cleanly.

	// this block is here for doxygen
	//! This namespace contains the auto-generated classes related to the built-in GameSparks API. 
	//! For more information on the topic visit https://docs.gamesparks.net/documentation/
	namespace Api
	{
		//! built-in Messages. For more information visit https://docs.gamesparks.net/documentation/gamesparks-message-api
		namespace Messages {}
		
		//! built-in Requests. For more information visit https://docs.gamesparks.net/documentation/gamesparks-service-request-api
		namespace Requests {}

		//! built-in Responses. For more information visit https://docs.gamesparks.net/uncategorized/gamesparks-service-response-api
		namespace Responses {}

		//! Types used commonly by the built-in Requests, Responses and Messages
		namespace Types {}
	}

	#if defined(DOXYGEN)
		/// @defgroup CompileOptions Compile Options
		/// preprocessor defines that control features of the library
	#endif
}
#endif // GS_h__
