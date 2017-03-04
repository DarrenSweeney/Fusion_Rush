// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#ifndef GSMessage_h__
#define GSMessage_h__

#pragma once

#include "GSTypedResponse.h"
#include "GSObject.h"
#include "./gsstl.h"
#include <GameSparks/GSLeakDetector.h>

using namespace GameSparks::Core;
using namespace GameSparks::Optional;

namespace GameSparks
{
	namespace Core
	{
		class GS;
	}

	namespace Api
	{
		namespace Messages
		{
			/// base class for all messages
			class GSMessage : public GSTypedResponse
			{
				public:
					/// construct from GSData
					GSMessage(const GSData& message) 
					: GSTypedResponse(message)
					{

					}

					/// get the id of this message
					t_StringOptional GetMessageId() const
					{
						return m_Response.GetString(MESSAGE_ID_KEY);
					}

				protected:
					/// @internal
					const static gsstl::string MESSAGE_ID_KEY; ///< key name to access the message id
				private:
			};
		}
	}
}
#endif // GSMessage_h__
