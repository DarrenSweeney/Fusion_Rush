// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#ifndef GSTypedRequest_h__
#define GSTypedRequest_h__

#pragma once

#include "GSRequest.h"
#include "GSTypedResponse.h"
#include <GameSparks/GSLeakDetector.h>
#include <cassert>

namespace GameSparks
{
	namespace Core
	{
		/*!
			Wraps a GSRequest but can be parameterized by the concrete RequestType and ResponseType.
			This is the base class for all built-in Requests.

			@tparam RequestType the concrete type of the request
			@tparam ResponseType the concrete type of the response
		*/
		template<typename RequestType, typename ResponseType>
		class GSTypedRequest 
		{
            GS_LEAK_DETECTOR(GSTypedRequest)

			public:

				#if defined(GS_USE_STD_FUNCTION)
					/// the response callback as a std::function, in case all the compilers you need to support have support for C++11.
					/// this also supports C++11 lambdas
					typedef gsstl::function<void(GS&, const ResponseType&)> t_ResponseCallback;
				#else
					/// response callback as a c-style function pointer.
					/// In case you need to support ancient compilers.
					typedef void(*t_ResponseCallback)(GS&, const ResponseType&);
				#endif /* GS_USE_STD_FUNCTION */

				/// the wrapped request
				GSRequest m_Request;

				/// constructor.
				GSTypedRequest(GS& gsInstance)
					: m_Request(gsInstance, ".LogEventRequest")
				{

				}

				/// constructor with request type
				GSTypedRequest(GS& gsInstance, const gsstl::string& type)
					: m_Request(gsInstance, type)
				{
				}

				virtual RequestType& SetScriptData(const GSRequestData& data)
				{
					m_Request.AddObject("scriptData", data);
					return static_cast<RequestType&>(*this);
				}

				/// send this request to the server. Use thus for fire and forget Requests.
				virtual void Send()
				{
					m_Request.Send();
				}
            
                bool HasUserData() const
                {
                    return m_Request.HasUserData();
                }
            
                void SetUserData(void* userData)
                {
                    m_Request.SetUserData(userData);
                }
            
				/// send this request with a response-callback and optional timeout (in seconds)
				/// callback will be called in case of success and error. you have to examine the passed response
				/// to find out if the request failed.
				virtual void Send(t_ResponseCallback callback, Seconds timeoutSeconds=10)
				{
					m_Request.Send(new Callbacks(callback, callback, m_Request.m_userData), timeoutSeconds);
				}

				/// send this request with a successCallback, errorCallback and optional timeout (in seconds)
				virtual void Send(t_ResponseCallback successCallback, t_ResponseCallback errorCallback, Seconds timeoutSeconds=10)
				{
					m_Request.Send(new Callbacks(successCallback, errorCallback, m_Request.m_userData), timeoutSeconds);
				}

				/// marks this request as durable. Note, that the timeoutSeconds parameter for Send() is not respected
				/// for requests that have been restored from the persistent queue.
				GSTypedRequest<RequestType, ResponseType>& SetDurable(bool value)
				{
					m_Request.m_Durable = value;
					return *this;
				}

				private:
					class Callbacks : public GSRequest::BaseCallbacks
					{
						public:
							Callbacks(t_ResponseCallback onSuccess, t_ResponseCallback onError, void* userData)
                            :m_onSuccess(onSuccess), m_onError(onError) { m_userData = userData; }

							virtual void OnSucess(GS& gsInstance, const GSObject& response)
							{
								if ( m_onSuccess )
                                {
                                    ResponseType typedResponse(response); // the constructor of ResponseType takes a GSObject
                                    typedResponse.m_userData = m_userData;
                                    m_onSuccess( gsInstance, typedResponse );
                                }
							}

							virtual void OnError (GS& gsInstance, const GSObject& response)
							{
								if ( m_onError )
                                {
                                    ResponseType typedResponse(response); // the constructor of ResponseType takes a GSObject
                                    typedResponse.m_userData = m_userData;
                                    m_onError( gsInstance, typedResponse );
                                }
							}

							virtual Callbacks* Clone() const
							{
								return new Callbacks( m_onSuccess, m_onError, m_userData );
							}
						private:
							t_ResponseCallback m_onSuccess;
							t_ResponseCallback m_onError;
					};
		};
	}
}
#endif // GSTypedRequest_h__
