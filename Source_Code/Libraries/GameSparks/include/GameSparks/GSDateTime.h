// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#ifndef GSDateTime_h__
#define GSDateTime_h__

#pragma once

#include <GameSparks/gsstl.h>
#include <GameSparks/GSOptional.h>
#include <GameSparks/GSLeakDetector.h>
#include <GameSparks/GSLinking.h>

namespace GameSparks
{
	namespace Core
	{
		/// Represents a point in time.
		/// \includelineno sampleExtra01DateTimeConversion.cpp
		class GS_API GSDateTime
		{
		public:
			typedef GameSparks::Optional::Optional<GSDateTime> t_Optional;

			GSDateTime();
			GSDateTime(int day, int month, int year, int hour, int minute, int second, bool isLocalTime);
			GSDateTime(time_t time, bool isLocalTime);
			GSDateTime(const gsstl::string& iso8601_str);
			static GSDateTime Now();

			GSDateTime ToLocalTime() const;
			GSDateTime ToGMTime() const;
			// Returns the DateTime object as a ISO 8601 string (eg. '2011-10-08T07:07:09Z') representation
			gsstl::string ToString() const;

			int GetDay() const;
			int GetMonth() const;
			int GetYear() const;
			int GetHour() const;
			int GetMinute() const;
			int GetSecond() const;
			bool IsLocalTime() const;

			/// caution: Those do NOT account for leap-seconds and DST switches
			/// add *seconds* seconds
			GSDateTime AddSeconds(int seconds);
			/// add 60 seconds
			GSDateTime AddMinutes(int minutes);
			/// add 60*60 seconds
			GSDateTime AddHours(int hours);
			/// add 24*60*60 seconds
			GSDateTime AddDays(int days);

			/// equality means, both time have to be equal and either both in UTC or both in local time. So timezone conversion will be attempted.
			bool operator == (const GSDateTime& o) const;
		private:
			time_t m_time;
			bool m_IsLocalTime;
            
            GS_LEAK_DETECTOR(GSDateTime)
		};

		/// \example sampleExtra01DateTimeConversion.cpp This is an example on how to use the GSDateTime class to convert dates to/from strings and to GMT/local time
	}
}
#endif // GSDateTime_h__
