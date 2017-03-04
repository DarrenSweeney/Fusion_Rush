// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#include "GameSparks/GSData.h"
#include <math.h>
#include <cassert>

namespace GameSparks{ namespace Core {

GSData::GSData()
{
	m_Data = cJSON_CreateObject();
}

GSData::GSData(const GSData& other)
{
	m_Data = cJSON_Duplicate(other.m_Data, 1);
}

GSData::GSData(cJSON* data)
{
	m_Data = cJSON_Duplicate(data, 1);
	// whatever here makes sense (o:
}

GSData::~GSData()
{
	cJSON_Delete(m_Data);
}

GSData& GSData::operator=(GSData other)
{
    cJSON_Delete(m_Data);
	m_Data = cJSON_Duplicate(other.m_Data, 1);
	return *this;
}

bool GSData::ContainsKey(const gsstl::string& key) const
{
	return (cJSON_GetObjectItem(m_Data, key.c_str()) != 0);
}

Optional::t_StringOptional GSData::GetString(const gsstl::string& name) const
{
	cJSON* item = cJSON_GetObjectItem(m_Data, name.c_str());
	if (item != NULL && item->type == cJSON_String)
		return Optional::t_StringOptional(gsstl::string(item->valuestring), true);
	else
		return Optional::t_StringOptional(gsstl::string(), false);
}

Optional::t_IntOptional GSData::GetInt(const gsstl::string& name) const
{
	cJSON* item = cJSON_GetObjectItem(m_Data, name.c_str());
	if (item != NULL && item->type == cJSON_Number)
		return Optional::t_IntOptional(item->valueint, true);
	else
		return Optional::t_IntOptional(0, false);
}

Optional::t_LongOptional GSData::GetLong(const gsstl::string& name) const
{
	cJSON* item = cJSON_GetObjectItem(m_Data, name.c_str());
	if (item != NULL && item->type == cJSON_Number)
		return Optional::t_LongOptional(item->valueint, true);
	else
		return Optional::t_LongOptional(0, false);
}

Optional::t_LongLongOptional GSData::GetLongLong(const gsstl::string& name) const
 {
 	cJSON* item = cJSON_GetObjectItem(m_Data, name.c_str());
	if (item != NULL && item->type == cJSON_Number)
		return Optional::t_LongLongOptional(llround(item->valuedouble), true);
 	else
		return Optional::t_LongLongOptional(0, false);
}

Optional::t_LongOptional GSData::GetNumber(const gsstl::string& name) const
{
	cJSON* item = cJSON_GetObjectItem(m_Data, name.c_str());
	if (item != NULL && item->type == cJSON_Number)
		return Optional::t_LongOptional(item->valueint, true);
	else
		return Optional::t_LongOptional(0, false);
}

Optional::t_DoubleOptional GSData::GetDouble(const gsstl::string& name) const
{
	cJSON* item = cJSON_GetObjectItem(m_Data, name.c_str());
	if (item != NULL && item->type == cJSON_Number)
		return Optional::t_DoubleOptional(item->valuedouble, true);
	else
		return Optional::t_DoubleOptional((double)0, false);
}

Optional::t_FloatOptional GSData::GetFloat(const gsstl::string& name) const
{
	cJSON* item = cJSON_GetObjectItem(m_Data, name.c_str());
	if (item != NULL && item->type == cJSON_Number)
		return Optional::t_FloatOptional(static_cast<float>(item->valuedouble), true);
	else
		return Optional::t_FloatOptional((float)0, false);
}

Optional::t_BoolOptional GSData::GetBoolean(const gsstl::string& name) const
{
	cJSON* item = cJSON_GetObjectItem(m_Data, name.c_str());
	if (item != NULL && item->type == cJSON_True)
		return Optional::t_BoolOptional(true, true);
	else if (item != NULL && item->type == cJSON_False)
		return Optional::t_BoolOptional(false, true);
	else
		return Optional::t_BoolOptional(false, false);
}

GSData::t_Optional GSData::GetGSDataObject(const gsstl::string& name) const
{
	cJSON* item = cJSON_GetObjectItem(m_Data, name.c_str());
	if (item != NULL && item->type == cJSON_Object)
		return t_Optional(GSData(item), true);
	else
		return t_Optional(GSData(), false);
}

GSDateTime::t_Optional GSData::GetDate(const gsstl::string& name) const
{
	Optional::t_StringOptional dateString = GetString(name);
	if (dateString.HasValue())
	{
		return GSDateTime::t_Optional(GSDateTime(dateString.GetValue()), true);
	}
	else
	{
		return GSDateTime::t_Optional(GSDateTime(), false);
	}
}

gsstl::vector<gsstl::string> GSData::GetStringList(const gsstl::string& name) const
{
	gsstl::vector<gsstl::string> result;
	cJSON* arr = cJSON_GetObjectItem(m_Data, name.c_str());
	if (arr != NULL && arr->type == cJSON_Array)
	{
		for (int i = 0; i < cJSON_GetArraySize(arr); ++i)
		{
			cJSON* item = cJSON_GetArrayItem(arr, i);
			if (item != NULL && item->type == cJSON_String)
			{
				result.push_back(gsstl::string(item->valuestring));
			}
		}
	}
	return result;
}

gsstl::vector<float> GSData::GetFloatList(const gsstl::string& name) const
{
	gsstl::vector<float> result;
	cJSON* arr = cJSON_GetObjectItem(m_Data, name.c_str());
	if (arr != NULL && arr->type == cJSON_Array)
	{
		for (int i = 0; i < cJSON_GetArraySize(arr); ++i)
		{
			cJSON* item = cJSON_GetArrayItem(arr, i);
			if (item != NULL && item->type == cJSON_Number)
			{
				result.push_back((float)item->valuedouble);
			}
		}
	}
	return result;
}

gsstl::vector<double> GSData::GetDoubleList(const gsstl::string& name) const
{
	gsstl::vector<double> result;
	cJSON* arr = cJSON_GetObjectItem(m_Data, name.c_str());
	if (arr != NULL && arr->type == cJSON_Array)
	{
		for (int i = 0; i < cJSON_GetArraySize(arr); ++i)
		{
			cJSON* item = cJSON_GetArrayItem(arr, i);
			if (item != NULL && item->type == cJSON_Number)
			{
				result.push_back(item->valuedouble);
			}
		}
	}
	return result;
}

gsstl::vector<int> GSData::GetIntList(const gsstl::string& name) const
{
	gsstl::vector<int> result;
	cJSON* arr = cJSON_GetObjectItem(m_Data, name.c_str());
	if (arr != NULL && arr->type == cJSON_Array)
	{
		for (int i = 0; i < cJSON_GetArraySize(arr); ++i)
		{
			cJSON* item = cJSON_GetArrayItem(arr, i);
			if (item != NULL && item->type == cJSON_Number)
			{
				result.push_back(item->valueint);
			}
		}
	}
	return result;
}

gsstl::vector<long> GSData::GetLongList(const gsstl::string& name) const
{
	gsstl::vector<long> result;
	cJSON* arr = cJSON_GetObjectItem(m_Data, name.c_str());
	if (arr != NULL && arr->type == cJSON_Array)
	{
		for (int i = 0; i < cJSON_GetArraySize(arr); ++i)
		{
			cJSON* item = cJSON_GetArrayItem(arr, i);
			if (item != NULL && item->type == cJSON_Number)
			{
				result.push_back((long)item->valueint);
			}
		}
	}
	return result;
}

gsstl::vector<long long> GSData::GetLongLongList(const gsstl::string& name) const
{
	gsstl::vector<long long> result;
	cJSON* arr = cJSON_GetObjectItem(m_Data, name.c_str());
	if (arr != NULL && arr->type == cJSON_Array)
	{
		for (int i = 0; i < cJSON_GetArraySize(arr); ++i)
		{
			cJSON* item = cJSON_GetArrayItem(arr, i);
			if (item != NULL && item->type == cJSON_Number)
			{
				result.push_back(static_cast<long long>(round(item->valuedouble)));
			}
		}
	}
	return result;
}

gsstl::vector<GSData> GSData::GetGSDataObjectList(const gsstl::string& name) const
{
	gsstl::vector<GSData> result;
	cJSON* arr = cJSON_GetObjectItem(m_Data, name.c_str());
	if (arr != NULL && arr->type == cJSON_Array)
	{
		for (int i = 0; i < cJSON_GetArraySize(arr); ++i)
		{
			result.push_back(GSData(cJSON_GetArrayItem(arr, i)));
		}
	}
	return result;
}

cJSON* GSData::GetBaseData() const
{
	return m_Data;
}

gsstl::string GSData::GetJSON() const
{
	char* asText = cJSON_Print(m_Data);
	gsstl::string result(asText);
	free(asText);
	return result;
}

gsstl::vector<gsstl::string> GSData::GetKeys()
{
	gsstl::vector<gsstl::string> keys;
	
	if (!m_Data)
	{
		return keys;
	}

	assert(m_Data->type == cJSON_Object);
	if (m_Data->type != cJSON_Object)
	{
		return keys;
	}

	for (cJSON *c = m_Data->child; c != 0; c = c->next)
	{
		assert(c->string);
		if (c->string)
		{
			keys.push_back(c->string);
		}
	}

	gsstl::sort(keys.begin(), keys.end());

	return keys;
}

}} // namespace GameSparks{ namespace Core {
