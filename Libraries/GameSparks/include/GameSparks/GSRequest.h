// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#ifndef GSRequest_h__
#define GSRequest_h__

#pragma once

#include "GSObject.h"
#include "./gsstl.h"
#include "GSDateTime.h"
#include "GSTime.h"
#include "GSLinking.h"

namespace GameSparks
{
	namespace Core
	{
		class GS;

		/// A request to GameSparks
		class GS_API GSRequest : public GSObject
		{
			public:
				#if defined(GS_USE_STD_FUNCTION)
					typedef gsstl::function<void (GS&, const GSObject&)> t_Callback;
				#else
					typedef void(*t_Callback)(GS&, const GSObject&);
				#endif /* GS_USE_STD_FUNCTION */

				bool operator==(const GSRequest& other) const;

                bool HasCallbacks() const
                {
                    return m_callbacks;
                }

                void SetCallbacks(const t_Callback& successCallback, const t_Callback& errorCallback)
                {
                    m_callbacks = new Callbacks(successCallback, errorCallback, m_userData);
                }
            
                void SetCallback(const t_Callback& successCallback)
                {
                    m_callbacks = new Callbacks(successCallback, t_Callback(), m_userData);
                }
            
                bool HasUserData() const
                {
                    return m_userData != 0;
                }
            
                void SetUserData(void* userData)
                {
                    m_userData = userData;
                }

				const void* GetUserData() const
				{
					return m_userData;
				}
			private:
				// TODO: check if this works/is needed
				bool GetDurable() const { return m_Durable; }
				void SetDurable(bool durable) { m_Durable = durable; }
			private:
				friend class GS;

				GSRequest(GS& gsInstance, const gsstl::string& requestType);
				GSRequest(GS& gsInstance, cJSON* data);
				GSRequest(); // dummy default constructor for VC12 std::list - do not call, it will create an invalid object!

				GS& GetGSInstance() const { return *m_GSInstance; }

				void Complete(const GSObject& response);			

				GSObject m_Response;

				GS* m_GSInstance; ///< this is a pointer, so that the auto-generated assignment operator works

				bool m_Durable;
				Seconds m_CancelSeconds;          ///< decrementing timer for requests waiting to be send
				Seconds m_WaitForResponseSeconds; ///< decrementing timer for requests waiting to be answered
				Seconds m_DurableRetrySeconds;    ///< decrementing timer for requests waiting to be re-send
				Seconds m_ResponseTimeout;		  ///< used to override the default timeouts

				/*
					This class is here so that it can be implemented in GSTypedRequest.
					We need to hold a pointer to the base class, because the concrete
					implementations hold templated (specialized) function pointers.

					This whole construct is needed, because we cannot depend on stl-function
					We need to support raw function pointers as well.
				*/
				struct BaseCallbacks
				{
                    BaseCallbacks() : m_userData() {}
                    virtual ~BaseCallbacks() {}
					virtual void OnSucess(GS& gsInstance, const GSObject& response) = 0;
					virtual void OnError (GS& gsInstance, const GSObject& response) = 0;
					virtual BaseCallbacks* Clone() const = 0;
                    void* m_userData;
                    GS_LEAK_DETECTOR(BaseCallbacks)
				};

				/* iff all the members behave the way one would expect them to,
					the auto-generated copy-constructors and assignment operators
					behave as one would expect them to. By implementing this thin
					pointer wrapper, we spare us the burden of maintaining the CCs
					and AOs of GSRequest.
				*/
				class GS_API BaseCallbacksPtr
				{
					public:
						// constructor						
						BaseCallbacksPtr(BaseCallbacks* callbacks=0)
						: ptr(callbacks) {}

						// destructor
						virtual ~BaseCallbacksPtr()
						{
							delete ptr;
						}

						// copy constructor (this is the interesting part)
						BaseCallbacksPtr(const BaseCallbacksPtr& other)
						: ptr( other.ptr ? other.ptr->Clone() : 0) {}

						// assignment operator
						BaseCallbacksPtr& operator=(BaseCallbacksPtr other)
						{
							swap(*this, other); // copy and swap idom
							return *this;
						}

						// pointer access operator
						BaseCallbacks* operator-> ()
						{
							return ptr;
						}

						// conversion to bool (e.g. wrapped pointer not null)
						operator bool () const
						{
							return ptr != 0;
						}
					private:
						static void swap(BaseCallbacksPtr& first, BaseCallbacksPtr& second)
						{
							// We'd prefer to use stl-swap, but cannot depend on having the stl.
							BaseCallbacks* tmp = first.ptr;
							first.ptr = second.ptr;
							second.ptr = tmp;
						}

						BaseCallbacks* ptr;
                    
                        GS_LEAK_DETECTOR(BaseCallbacksPtr)
				};
            
                class Callbacks : public BaseCallbacks
                {
                    public:
                        Callbacks(t_Callback onSuccess, t_Callback onError, void* userData)
                        :m_onSuccess(onSuccess), m_onError(onError) { m_userData = userData; }
                
                        virtual void OnSucess(GS& gsInstance, const GSObject& response)
                        {
                            if ( m_onSuccess ) m_onSuccess( gsInstance, response );
                        }
                
                        virtual void OnError (GS& gsInstance, const GSObject& response)
                        {
                            if ( m_onError ) m_onError( gsInstance, response );
                        }
                
                        virtual Callbacks* Clone() const
                        {
                            return new Callbacks( m_onSuccess, m_onError, m_userData );
                        }
                    
                    private:
                        t_Callback m_onSuccess;
                        t_Callback m_onError;
                };

				// TODO: check if the type cound be changed to Seconds
				void Send(const BaseCallbacksPtr& callbacks, Seconds timeoutSeconds);
				void Send();

				BaseCallbacksPtr m_callbacks;

				template<typename RequestType, typename ResponseType>
				friend class GSTypedRequest;
            
                void* m_userData;
            
                GS_LEAK_DETECTOR(GSRequest)
		};
	}
}
#endif // GSRequest_h__
