#pragma once

#include "./IGSPlatform.h"

#ifndef IW_SDK
#	error "This file is meant for inclusion in marmalade projects only."
#endif /* IW_SDK */

#include <s3eDevice.h>
#include <IwDebug.h>

namespace GameSparks
{
	namespace Core
	{
		/// IGSPlatform implementation for [Marmalade](https://www.madewithmarmalade.com/)
		class MarmaladePlatform : public IGSPlatform
		{
			public:
				MarmaladePlatform(const gsstl::string& apikey, const gsstl::string& secret, bool usePreviewServer, bool verboseLogging=false, size_t maxLogEntriesToKeep=0)
				: IGSPlatform(apikey, secret, usePreviewServer, verboseLogging), m_maxLogEntriesToKeep(maxLogEntriesToKeep) {}

				//Gets a unique identifier for the device
				virtual gsstl::string GetDeviceId() const
				{
					return s3eDeviceGetString(S3E_DEVICE_UNIQUE_ID);
				}

				//IOS or AND or WP8 - Required for in app purchases
				virtual gsstl::string GetDeviceOS() const
				{
					// http://api.madewithmarmalade.com/group__deviceapigroup.html#ga35cf28487294cc1c7cee7b4a73e122db
					return s3eDeviceGetString(S3E_DEVICE_OS);
				}

				//Will be used in analytics reports
				virtual gsstl::string GetPlatform() const
				{
					// http://api.madewithmarmalade.com/group__deviceapigroup.html#ga42c616710c895108e5f31a7e2787b77d
					return s3eDeviceGetString(S3E_DEVICE_ARCHITECTURE);
				}

				//Will be used in analytics reports
				virtual gsstl::string GetSDK() const
				{
					return "GameSparks SDK C++ 1.0 for Marmalade";
				}

				//Will be used in analytics reports
				virtual gsstl::string GetDeviceType() const
				{
					// http://api.madewithmarmalade.com/group__deviceapigroup.html#gaf67bd64343f477244ca9e8a821020db0
					return s3eDeviceGetString(S3E_DEVICE_CLASS);
				}

				//Receives debugging information from the API
				virtual void DebugMsg(const gsstl::string& message) const
				{
					IwTrace(GameSparks, ("%s", message.c_str()));
                    
                    if(m_maxLogEntriesToKeep > 0)
                    {
                        MarmaladePlatform* self = const_cast<MarmaladePlatform*>(this); // not to nice!
                        
                        while(self->m_log.size() >= m_maxLogEntriesToKeep)
                            self->m_log.pop_front();
                        
                        self->m_log.push_back(message);
                    }
				}
            
                gsstl::string getLog() const
                {
                    gsstl::string ret;
                    for( Log::const_iterator i = m_log.begin(); i != m_log.end(); ++i )
                        ret += *i + "\n";
                    
                    return ret;
                }
            private:
                typedef gsstl::list<gsstl::string> Log;
                Log m_log;
                size_t m_maxLogEntriesToKeep;
		};
	}
}
