// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#ifndef IGSData_h__
#define IGSData_h__

#pragma once

#include <cjson/cJSON.h>
#include <GameSparks/GSLeakDetector.h>

namespace GameSparks
{
	namespace Core
	{
		/// base class for GSData objects
		class IGSData
		{
            GS_LEAK_DETECTOR(IGSData)
		public:

			/// access the internal cJSON object
			virtual const cJSON* GetBaseData() const = 0;
		};
	}

}
#endif // IGSData_h__
