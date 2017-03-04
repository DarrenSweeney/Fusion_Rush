// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#ifndef GSData_h__
#define GSData_h__

#pragma once

#include "IGSData.h"
#include "GSOptional.h"
#include "GSDateTime.h"
#include "GSLinking.h"

namespace GameSparks
{
	namespace Core
	{
		/// You can think of this as a convenient C++ wrapper around cJSON.
		/// This class is used to construct json objects in memory.
		class GS_API GSData : public IGSData
		{
			public:
				/// optional GSData
				typedef GameSparks::Optional::Optional<GSData> t_Optional;

				/// construct an empty GSData object
				GSData();

				/// copy-constructor
				GSData(const GSData& other);

				/// construct a GSData object from a cJSON object
				GSData(cJSON* data);

				/// destructor
				virtual ~GSData();

				/// assingment operator
				GSData& operator=(GSData other);

				/// returns true, if this GSData objects contains the given key. false otherwise.
				/// @param key the key to check for
				virtual bool ContainsKey(const gsstl::string& key) const;
				
				/// try to retrieve the string names name from this GSData object
				virtual Optional::t_StringOptional GetString(const gsstl::string& name) const;

				/// get an optional int
				virtual Optional::t_IntOptional GetInt(const gsstl::string& name) const;

				/// get an optional long
				virtual Optional::t_LongOptional GetLong(const gsstl::string& name) const;
				
				/// get an optional long long - note that full integer precission is only 53 bits
				virtual Optional::t_LongLongOptional GetLongLong(const gsstl::string& name) const;

				/// get an optional long
				virtual Optional::t_LongOptional GetNumber(const gsstl::string& name) const;

				/// get an optional double
				virtual Optional::t_DoubleOptional GetDouble(const gsstl::string& name) const;

				/// get an optional float
				virtual Optional::t_FloatOptional GetFloat(const gsstl::string& name) const;

				/// get an optional boolean
				virtual Optional::t_BoolOptional GetBoolean(const gsstl::string& name) const;

				/// get an optional embedded object
				virtual t_Optional GetGSDataObject(const gsstl::string& name) const;

				/// get an optional date
				virtual GSDateTime::t_Optional GetDate(const gsstl::string& name) const;

				/// get a list of strings
				virtual gsstl::vector<gsstl::string> GetStringList(const gsstl::string& name) const;

				/// get a list of floats
				virtual gsstl::vector<float> GetFloatList(const gsstl::string& name) const;

				/// get a list of doubles
				virtual gsstl::vector<double> GetDoubleList(const gsstl::string& name) const;

				/// get a list of ints
				virtual gsstl::vector<int> GetIntList(const gsstl::string& name) const;

				/// get a list of longs
				virtual gsstl::vector<long> GetLongList(const gsstl::string& name) const;
				
				/// get a list of long longs - note that full integer precission is only 53 bits
				virtual gsstl::vector<long long> GetLongLongList(const gsstl::string& name) const;

				/// get a list of GSData-objects
				virtual gsstl::vector<GSData> GetGSDataObjectList(const gsstl::string& name) const;

				/// get the internal cJSON object. be careful when using this
				virtual cJSON* GetBaseData() const;

				/// serialize this GSData object to json
				virtual gsstl::string GetJSON() const;

				/// get a list of keys of this GSData object in lexicographically sorted
				virtual gsstl::vector<gsstl::string> GetKeys();
			protected:
				cJSON* m_Data;
            
            private:
	            GS_LEAK_DETECTOR(GSData)
		};
	}	
}
#endif // GSData_h__
