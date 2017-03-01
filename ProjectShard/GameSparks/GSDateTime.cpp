// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.

#if defined(WINAPI_FAMILY)
#define __STDC_WANT_SECURE_LIB__ 0
#define sprintf_s(buf, size, fmt, ...) sprintf(buf, fmt, __VA_ARGS__)
#define swprintf_s(buf, size, fmt, ...) swprintf(buf, size, fmt, __VA_ARGS__)
char * strptime(const char *buf, const char *fmt, struct tm *tm);
#endif

#if defined(__ORBIS__ )
char * strptime(const char *buf, const char *fmt, struct tm *tm);
#endif

#include <GameSparks/GSDateTime.h>

#include <ctime>
#include <google/timesupport.h>

using namespace GameSparks::Core;

GameSparks::Core::GSDateTime::GSDateTime()
	: m_time(0)
    , m_IsLocalTime(false)
{
}

GameSparks::Core::GSDateTime::GSDateTime(int day, int month, int year, int hour, int minute, int second, bool isLocalTime)
	: m_time(0)
	, m_IsLocalTime(isLocalTime)
{
	struct tm t;
	memset(&t, 0, sizeof(tm));

	t.tm_mday = day;
	t.tm_mon = month - 1;
	t.tm_year = year - 1900;
	t.tm_hour = hour;
	t.tm_min = minute;
	t.tm_sec = second;
	t.tm_wday = 0;
	t.tm_yday = 0;
	t.tm_isdst = 0;

	m_time = mktime(&t);
}

GameSparks::Core::GSDateTime::GSDateTime(time_t time, bool isLocalTime)
	: m_time(time)
	, m_IsLocalTime(isLocalTime)
{
}

GameSparks::Core::GSDateTime::GSDateTime(const gsstl::string& iso8601_str)
	: m_time(0)
	, m_IsLocalTime(false)
{
	struct tm t;
	memset(&t, 0, sizeof(tm));
	strptime(iso8601_str.c_str(), "%Y-%m-%dT%H:%M:%SZ", &t);
    m_time = _mkgmtime(&t);
}

bool GameSparks::Core::GSDateTime::operator == (const GSDateTime& o) const
{
	return m_time == o.m_time && m_IsLocalTime == o.m_IsLocalTime;
}

GameSparks::Core::GSDateTime GameSparks::Core::GSDateTime::Now()
{
	time_t now;
	time(&now);
	GSDateTime result(now, false);
	return result;
}

GameSparks::Core::GSDateTime GameSparks::Core::GSDateTime::ToLocalTime() const
{
	if (m_IsLocalTime)
	{
		return *this;
	}
	else
	{
		tm* tmobj = localtime(&m_time);
		GSDateTime result(mktime(tmobj), true);
		return result;

	}
}

GameSparks::Core::GSDateTime GameSparks::Core::GSDateTime::ToGMTime() const
{
	if (m_IsLocalTime)
	{
		tm* tmobj = gmtime(&m_time);
		GSDateTime result(_mkgmtime(tmobj), false);
		return result;
	}
	else
	{
		return *this;
	}
}

gsstl::string GameSparks::Core::GSDateTime::ToString() const
{
	return FormatW3CTime(m_time, m_IsLocalTime);
}

int GameSparks::Core::GSDateTime::GetDay() const
{
	if (m_IsLocalTime) return localtime(&m_time)->tm_mday;
	else return gmtime(&m_time)->tm_mday;
}

int GameSparks::Core::GSDateTime::GetMonth() const
{
	if (m_IsLocalTime) return localtime(&m_time)->tm_mon + 1;
	else return gmtime(&m_time)->tm_mon + 1;
}

int GameSparks::Core::GSDateTime::GetYear() const
{
	// http://www.cplusplus.com/reference/ctime/tm/ (years since 1900)
	if (m_IsLocalTime) return localtime(&m_time)->tm_year + 1900;
	else return gmtime(&m_time)->tm_year + 1900;
}

int GameSparks::Core::GSDateTime::GetHour() const
{
	if (m_IsLocalTime) return localtime(&m_time)->tm_hour;
	else return gmtime(&m_time)->tm_hour;
}

int GameSparks::Core::GSDateTime::GetMinute() const
{
	if (m_IsLocalTime) return localtime(&m_time)->tm_min;
	else return gmtime(&m_time)->tm_min;
}

int GameSparks::Core::GSDateTime::GetSecond() const
{
	if (m_IsLocalTime) return localtime(&m_time)->tm_sec;
	else return gmtime(&m_time)->tm_sec;
}

bool GameSparks::Core::GSDateTime::IsLocalTime() const
{
	return m_IsLocalTime;
}

GSDateTime GameSparks::Core::GSDateTime::AddSeconds(int seconds)
{
	return GSDateTime(m_time + seconds, m_IsLocalTime);
}

GSDateTime GameSparks::Core::GSDateTime::AddMinutes(int minutes)
{
	return AddSeconds(minutes * 60);
}

GSDateTime GameSparks::Core::GSDateTime::AddHours(int hours)
{
	return AddMinutes(hours * 60);
}

GSDateTime GameSparks::Core::GSDateTime::AddDays(int days)
{
	return AddHours(days * 24);
}
