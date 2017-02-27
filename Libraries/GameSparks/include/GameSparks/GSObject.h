// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#ifndef GSObject_h__
#define GSObject_h__

#pragma once

#include "GSRequestData.h"
#include "GSOptional.h"
#include "GSLinking.h"
#include <cjson/cJSON.h>
#include <GameSparks/GSLeakDetector.h>

namespace GameSparks
{
	namespace Core
	{
		class GSRequest;

		/// Basically GSData with additional type information
		class GS_API GSObject : public GSRequestData
		{
			public:

				typedef GameSparks::Optional::Optional<GSObject> t_Optional;
				
				GSObject(cJSON* data)
					: GSRequestData(data)
				{
		
				}
		
				GSObject(const GSData& wrapper)
					: GSRequestData(wrapper)
				{

				}

				GSObject(const GSObject& other)
					: GSRequestData(other.m_Data)
				{

				}
				

				~GSObject()
				{
				}
		
				GSObject(const gsstl::string& type)
				{
					AddString("@class", type);
				}
		
				/// Create a new instance of the given type ("@class")
				Optional::t_StringOptional GetType() const
				{
					return GetString("@class");
				}
		
				static GSObject FromJSON(const gsstl::string& json)
				{
					cJSON* root = cJSON_Parse(json.c_str());
					GSObject result(root);
					cJSON_Delete(root);
					return result;
				}
		
			protected:
				GSObject()
					: GSRequestData()
				{
					
				}

				friend class GSRequest;
	            
	            GS_LEAK_DETECTOR(GSObject)
		};
	}
}
#endif // GSObject_h__
