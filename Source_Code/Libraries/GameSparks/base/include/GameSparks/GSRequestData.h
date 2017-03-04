// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#ifndef GSRequestData_h__
#define GSRequestData_h__

#pragma once

#include "GSData.h"
#include "GSLinking.h"
#include <GameSparks/GSDateTime.h>

namespace GameSparks
{
	namespace Core
	{
		/// a mutable version of GSData
		class GS_API GSRequestData : public GSData
		{
			public:
				GSRequestData() : GSData() {}

				GSRequestData(const GSData& wrapper) : GSData(wrapper) {}

				GSRequestData(const GSRequestData& other)
				: GSData(other.m_Data) {}

				GSRequestData(cJSON* data) : GSData(data){}

				GSRequestData& AddString(const gsstl::string& paramName, const gsstl::string& value)
				{
					return Add(paramName, value);
				}

				GSRequestData& AddObject(const gsstl::string& paramName, const GSData& value)
				{
					return Add(paramName, value);
				}

				GSRequestData& AddDate(const gsstl::string& paramName, const GSDateTime& date)
				{
					return Add(paramName, date.ToString());
				}

				GSRequestData& AddNumber(const gsstl::string& paramName, float value)
				{
					return Add(paramName, value);
				}

				GSRequestData& AddNumber(const gsstl::string& paramName, double value)
				{
					return Add(paramName, value);
				}

				GSRequestData& AddNumber(const gsstl::string& paramName, int value)
				{
					return Add(paramName, value);
				}
	            
	            GSRequestData& AddNumber(const gsstl::string& paramName, long value)
	            {
	                return Add(paramName, value);
	            }
				
				GSRequestData& AddNumber(const gsstl::string& paramName, long long value)
				{
					return Add(paramName, value);
                }

				GSRequestData& AddBoolean(const gsstl::string& paramName, bool value)
				{
					return Add(paramName, value);
				}

				GSRequestData& AddStringList(const gsstl::string& paramName, const gsstl::vector<gsstl::string>& value)
				{
					return Add(paramName, value);
				}

				GSRequestData& AddObjectList(const gsstl::string& paramName, const gsstl::vector<GSData>& value)
				{
					return Add(paramName, value);
				}

				template <typename NativeNumberType>
				GSRequestData& AddNumberList(const gsstl::string& paramName, const gsstl::vector<NativeNumberType>& value)
				{
					return Add(paramName, value);
				}
			private:
				GS_LEAK_DETECTOR(GSRequestData)

				/* conversions from native datatypes to cJSON obejcts */
				cJSON* createFromNative(const gsstl::string& value) { return cJSON_CreateString(value.c_str()); }
				cJSON* createFromNative(bool value) { return cJSON_CreateBool(value); }
				cJSON* createFromNative(int value) { return cJSON_CreateNumber(value); }
				cJSON* createFromNative(long value) { return cJSON_CreateNumber(value); }
				cJSON* createFromNative(long long value) { return cJSON_CreateNumber(static_cast<double>(value)); }
				cJSON* createFromNative(float value) { return cJSON_CreateNumber(value); }
				cJSON* createFromNative(double value) { return cJSON_CreateNumber(value); }
				cJSON* createFromNative(const GSData& value) { return cJSON_Duplicate(value.GetBaseData(), 1); }
				cJSON* createFromNative(const gsstl::vector<int>& value) { return cJSON_CreateIntArray(&value[0], static_cast<int>(value.size())); }
				cJSON* createFromNative(const gsstl::vector<long long>& value) { return cJSON_CreateLongLongArray(&value[0], static_cast<int>(value.size())); }
				cJSON* createFromNative(const gsstl::vector<float>& value) { return cJSON_CreateFloatArray(&value[0], static_cast<int>(value.size())); }
				cJSON* createFromNative(const gsstl::vector<double>& value) { return cJSON_CreateDoubleArray(&value[0], static_cast<int>(value.size())); }

				// convert vector of ContainedType
				template <typename ContainedType>
				cJSON* createFromNative(const gsstl::vector<ContainedType>& value)
				{
					cJSON* json_array = cJSON_CreateArray();
					for (typename gsstl::vector<ContainedType>::const_iterator it = value.begin(); it != value.end(); ++it)
					{
						cJSON_AddItemToArray(json_array, createFromNative(*it));
					}
					return json_array;
				}

				// add or replace value named paramName
				template <typename T>
				GSRequestData& Add(const gsstl::string& paramName, T value)
				{
					cJSON* node = createFromNative(value);

					if (cJSON_GetObjectItem(m_Data, paramName.c_str()))
						cJSON_ReplaceItemInObject(m_Data, paramName.c_str(), node);
					else
						cJSON_AddItemToObject(m_Data, paramName.c_str(), node);

					return *this;
				}
		};
	}
}
#endif // GSRequestData_h__
