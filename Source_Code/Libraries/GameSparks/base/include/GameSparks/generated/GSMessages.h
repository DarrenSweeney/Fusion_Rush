#pragma once

//THIS FILE IS AUTO GENERATED, DO NOT MODIFY!!
//THIS FILE IS AUTO GENERATED, DO NOT MODIFY!!
//THIS FILE IS AUTO GENERATED, DO NOT MODIFY!!

#include "../GSMessage.h"
#include "../gsstl.h"
#include "GSTypes.h"

namespace GameSparks
{
	namespace Api
	{
		namespace Messages
		{

			/*!
			\ingroup Player
			Message sent to a player when they have been awarded an achievement within the game.
			This message may be triggered by a leaderboard or a script.
			The player may have gained a virtual good or virtual currency as a result of gaining the award.
			*/
			class AchievementEarnedMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".AchievementEarnedMessage";
					}

					AchievementEarnedMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// The name of achievement.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetAchievementName () const
					{
						return m_Response.GetString("achievementName");
					}
				/// <summary>
				/// The short code of the achievement.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetAchievementShortCode () const
					{
						return m_Response.GetString("achievementShortCode");
					}
				/// <summary>
				/// The amount of type 1 currency earned.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetCurrency1Earned () const
					{
						return m_Response.GetString("currency1Earned");
					}
				/// <summary>
				/// The amount of type 2 currency earned.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetCurrency2Earned () const
					{
						return m_Response.GetString("currency2Earned");
					}
				/// <summary>
				/// The amount of type 2 currency earned.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetCurrency3Earned () const
					{
						return m_Response.GetString("currency3Earned");
					}
				/// <summary>
				/// The amount of type 4 currency earned.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetCurrency4Earned () const
					{
						return m_Response.GetString("currency4Earned");
					}
				/// <summary>
				/// The amount of type 5 currency earned.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetCurrency5Earned () const
					{
						return m_Response.GetString("currency5Earned");
					}
				/// <summary>
				/// The amount of type 6 currency earned.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetCurrency6Earned () const
					{
						return m_Response.GetString("currency6Earned");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The name of the virtual good that was earned.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetVirtualGoodEarned () const
					{
						return m_Response.GetString("virtualGoodEarned");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that the challenge has been accepted.
			*/
			class ChallengeAcceptedMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeAcceptedMessage";
					}

					ChallengeAcceptedMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// A player message included in this message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMessage () const
					{
						return m_Response.GetString("message");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The name of the player whose actions generated this message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetWho () const
					{
						return m_Response.GetString("who");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that a player has posted a score in to the challenge's leaderboard.
			*/
			class ChallengeChangedMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeChangedMessage";
					}

					ChallengeChangedMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// The leaderboard data associated with this challenge.
				/// </summary>
					// method type 2
					Types::LeaderboardData GetLeaderboardData() const
					{
						return Types::LeaderboardData(m_Response.GetGSDataObject("leaderboardData").GetValue());
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// Indicates which player has changed the challenge
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetWho () const
					{
						return m_Response.GetString("who");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message containing general chat between players involved in the challenge.
			*/
			class ChallengeChatMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeChatMessage";
					}

					ChallengeChatMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// A player message included in this message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMessage () const
					{
						return m_Response.GetString("message");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The name of the player whose actions generated this message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetWho () const
					{
						return m_Response.GetString("who");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that a player has declined the challenge.
			*/
			class ChallengeDeclinedMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeDeclinedMessage";
					}

					ChallengeDeclinedMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// A player message included in this message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMessage () const
					{
						return m_Response.GetString("message");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The name of the player whose actions generated this message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetWho () const
					{
						return m_Response.GetString("who");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that the challenge result is a draw.
			This message is sent to all the players who have drawn in the current challenge
			*/
			class ChallengeDrawnMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeDrawnMessage";
					}

					ChallengeDrawnMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// The leaderboard data associated with this challenge.
				/// </summary>
					// method type 2
					Types::LeaderboardData GetLeaderboardData() const
					{
						return Types::LeaderboardData(m_Response.GetGSDataObject("leaderboardData").GetValue());
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that the challenge expiry date has passed.
			*/
			class ChallengeExpiredMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeExpiredMessage";
					}

					ChallengeExpiredMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that a challenge has been issued.
			*/
			class ChallengeIssuedMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeIssuedMessage";
					}

					ChallengeIssuedMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// A player message included in this message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMessage () const
					{
						return m_Response.GetString("message");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The name of the player whose actions generated this message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetWho () const
					{
						return m_Response.GetString("who");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that the challenge has been joined.
			*/
			class ChallengeJoinedMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeJoinedMessage";
					}

					ChallengeJoinedMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// A player message included in this message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMessage () const
					{
						return m_Response.GetString("message");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The name of the player whose actions generated this message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetWho () const
					{
						return m_Response.GetString("who");
					}
			};
			

			/*!
			\ingroup Multiplayer
			@Deprecated
			A message indicating that the challenge has reached its end time but was not yet started.
			This message is no longer used. Instead, a ChallengeExpiredMessage will be triggered.
			*/
			class ChallengeLapsedMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeLapsedMessage";
					}

					ChallengeLapsedMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that the challenge has been lost.
			This message is sent to all the players in the challenge who have lost
			*/
			class ChallengeLostMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeLostMessage";
					}

					ChallengeLostMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// The leaderboard data associated with this challenge.
				/// </summary>
					// method type 2
					Types::LeaderboardData GetLeaderboardData() const
					{
						return Types::LeaderboardData(m_Response.GetGSDataObject("leaderboardData").GetValue());
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The winning players name
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetWinnerName () const
					{
						return m_Response.GetString("winnerName");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that the challenge has started
			*/
			class ChallengeStartedMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeStartedMessage";
					}

					ChallengeStartedMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that the current player has taken a turn with this challenge.
			*/
			class ChallengeTurnTakenMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeTurnTakenMessage";
					}

					ChallengeTurnTakenMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The name of the player whoe has taken their turn.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetWho () const
					{
						return m_Response.GetString("who");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that there is a challenge waiting for the player.
			*/
			class ChallengeWaitingMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeWaitingMessage";
					}

					ChallengeWaitingMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that the challenging player has withdrawn this challenge.
			*/
			class ChallengeWithdrawnMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeWithdrawnMessage";
					}

					ChallengeWithdrawnMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// A player message included in this message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMessage () const
					{
						return m_Response.GetString("message");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The name of the player whose actions generated this message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetWho () const
					{
						return m_Response.GetString("who");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that the challenge has been won.
			This message is only sent to the individual player who has won the challenge
			*/
			class ChallengeWonMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ChallengeWonMessage";
					}

					ChallengeWonMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// An object representing the challenge.
				/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
				/// <summary>
				/// The amount of type 1 currency the player has won.
				/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency1Won () const
					{
						return m_Response.GetLong("currency1Won");
					}
				/// <summary>
				/// The amount of type 2 currency the player has won.
				/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency2Won () const
					{
						return m_Response.GetLong("currency2Won");
					}
				/// <summary>
				/// The amount of type 3 currency the player has won.
				/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency3Won () const
					{
						return m_Response.GetLong("currency3Won");
					}
				/// <summary>
				/// The amount of type 4 currency the player has won.
				/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency4Won () const
					{
						return m_Response.GetLong("currency4Won");
					}
				/// <summary>
				/// The amount of type 5 currency the player has won.
				/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency5Won () const
					{
						return m_Response.GetLong("currency5Won");
					}
				/// <summary>
				/// The amount of type 6 currency the player has won.
				/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency6Won () const
					{
						return m_Response.GetLong("currency6Won");
					}
				/// <summary>
				/// The leaderboard data associated with this challenge.
				/// </summary>
					// method type 2
					Types::LeaderboardData GetLeaderboardData() const
					{
						return Types::LeaderboardData(m_Response.GetGSDataObject("leaderboardData").GetValue());
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The winning player's name.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetWinnerName () const
					{
						return m_Response.GetString("winnerName");
					}
			};
			

			/*!
			\ingroup Player
			A message sent from a player to one of his social network friends.
			*/
			class FriendMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".FriendMessage";
					}

					FriendMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// The player's id who is sending the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetFromId () const
					{
						return m_Response.GetString("fromId");
					}
				/// <summary>
				/// The player's message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMessage () const
					{
						return m_Response.GetString("message");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The name of the player who is sending the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetWho () const
					{
						return m_Response.GetString("who");
					}
			};
			

			/*!
			\ingroup Leaderboards
			This message is sent to players when their rank in a global leaderboard changes such that they are knocked out of the configured 'Top N'.
			*/
			class GlobalRankChangedMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".GlobalRankChangedMessage";
					}

					GlobalRankChangedMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// The game id that this message relates to.
				/// </summary>
					// method type 4
					Optional::t_LongOptional GetGameId () const
					{
						return m_Response.GetLong("gameId");
					}
				/// <summary>
				/// The leaderboard's name.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetLeaderboardName () const
					{
						return m_Response.GetString("leaderboardName");
					}
				/// <summary>
				/// The leaderboard shortcode.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetLeaderboardShortCode () const
					{
						return m_Response.GetString("leaderboardShortCode");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// The score details of the player whose score the receiving player has passed.
				/// </summary>
					// method type 2
					Types::LeaderboardData GetThem() const
					{
						return Types::LeaderboardData(m_Response.GetGSDataObject("them").GetValue());
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The score details of the receiving player.
				/// </summary>
					// method type 2
					Types::LeaderboardData GetYou() const
					{
						return Types::LeaderboardData(m_Response.GetGSDataObject("you").GetValue());
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that a match has been found
			*/
			class MatchFoundMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".MatchFoundMessage";
					}

					MatchFoundMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// The accessToken used to authenticate this player for this match
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetAccessToken () const
					{
						return m_Response.GetString("accessToken");
					}
				/// <summary>
				/// The host to connect to for this match
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetHost () const
					{
						return m_Response.GetString("host");
					}
				/// <summary>
				/// MatchData is arbitrary data that can be stored in a Match instance by a Cloud Code script.
				/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetMatchData () const
					{
						return m_Response.GetGSDataObject("matchData");
					}
				/// <summary>
				/// The group the player was assigned in the matchmaking request
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMatchGroup () const
					{
						return m_Response.GetString("matchGroup");
					}
				/// <summary>
				/// The id for this match instance
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMatchId () const
					{
						return m_Response.GetString("matchId");
					}
				/// <summary>
				/// The shortCode of the match type this message for
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMatchShortCode () const
					{
						return m_Response.GetString("matchShortCode");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// The participants in this match
				/// </summary>
					// method type 1
					gsstl::vector<Types::Participant> GetParticipants() const
					{
						gsstl::vector<Types::Participant> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("participants");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Participant(*it));
						}
						return result; 
					}
				/// <summary>
				/// The port to connect to for this match
				/// </summary>
					// method type 4
					Optional::t_IntOptional GetPort () const
					{
						return m_Response.GetInt("port");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that no suitable match was found during the configured time
			*/
			class MatchNotFoundMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".MatchNotFoundMessage";
					}

					MatchNotFoundMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// MatchData is arbitrary data that can be stored in a Match instance by a Cloud Code script.
				/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetMatchData () const
					{
						return m_Response.GetGSDataObject("matchData");
					}
				/// <summary>
				/// The group the player was assigned in the matchmaking request
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMatchGroup () const
					{
						return m_Response.GetString("matchGroup");
					}
				/// <summary>
				/// The shortCode of the match type this message for
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMatchShortCode () const
					{
						return m_Response.GetString("matchShortCode");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A JSON Map of any data that was associated to this user
				/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetParticipantData () const
					{
						return m_Response.GetGSDataObject("participantData");
					}
				/// <summary>
				/// The participants in this match
				/// </summary>
					// method type 1
					gsstl::vector<Types::Participant> GetParticipants() const
					{
						gsstl::vector<Types::Participant> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("participants");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Participant(*it));
						}
						return result; 
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
			};
			

			/*!
			\ingroup Multiplayer
			A message indicating that there has been an update to a pending match request, but it is not yet complete
			*/
			class MatchUpdatedMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".MatchUpdatedMessage";
					}

					MatchUpdatedMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// The players that joined this match
				/// </summary>
					// method type 3 
						gsstl::vector<gsstl::string> GetAddedPlayers() const
						{
							return m_Response.GetStringList("addedPlayers");
						}
				/// <summary>
				/// MatchData is arbitrary data that can be stored in a Match instance by a Cloud Code script.
				/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetMatchData () const
					{
						return m_Response.GetGSDataObject("matchData");
					}
				/// <summary>
				/// The group the player was assigned in the matchmaking request
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMatchGroup () const
					{
						return m_Response.GetString("matchGroup");
					}
				/// <summary>
				/// The id for this match instance
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMatchId () const
					{
						return m_Response.GetString("matchId");
					}
				/// <summary>
				/// The shortCode of the match type this message for
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMatchShortCode () const
					{
						return m_Response.GetString("matchShortCode");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// The participants in this match
				/// </summary>
					// method type 1
					gsstl::vector<Types::Participant> GetParticipants() const
					{
						gsstl::vector<Types::Participant> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("participants");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Participant(*it));
						}
						return result; 
					}
				/// <summary>
				/// The players that left this match
				/// </summary>
					// method type 3 
						gsstl::vector<gsstl::string> GetRemovedPlayers() const
						{
							return m_Response.GetStringList("removedPlayers");
						}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
			};
			

			/*!
			\ingroup Leaderboards
			A message indicating that the player has achieved a new high score in the game.
			*/
			class NewHighScoreMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".NewHighScoreMessage";
					}

					NewHighScoreMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// The new leaderboard data associated with this message.
				/// </summary>
					// method type 2
					Types::LeaderboardData GetLeaderboardData() const
					{
						return Types::LeaderboardData(m_Response.GetGSDataObject("leaderboardData").GetValue());
					}
				/// <summary>
				/// The leaderboard's name.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetLeaderboardName () const
					{
						return m_Response.GetString("leaderboardName");
					}
				/// <summary>
				/// The leaderboard shortcode.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetLeaderboardShortCode () const
					{
						return m_Response.GetString("leaderboardShortCode");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// The ranking information for the new score.
				/// </summary>
					// method type 2
					Types::LeaderboardRankDetails GetRankDetails() const
					{
						return Types::LeaderboardRankDetails(m_Response.GetGSDataObject("rankDetails").GetValue());
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
			};
			

			/*!
			\ingroup Leaderboards
			A message indicating that the player's team has achieved a new high score in the game.
			*/
			class NewTeamScoreMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".NewTeamScoreMessage";
					}

					NewTeamScoreMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// The new leaderboard data associated with this message.
				/// </summary>
					// method type 2
					Types::LeaderboardData GetLeaderboardData() const
					{
						return Types::LeaderboardData(m_Response.GetGSDataObject("leaderboardData").GetValue());
					}
				/// <summary>
				/// The leaderboard's name.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetLeaderboardName () const
					{
						return m_Response.GetString("leaderboardName");
					}
				/// <summary>
				/// The leaderboard shortcode.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetLeaderboardShortCode () const
					{
						return m_Response.GetString("leaderboardShortCode");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// The ranking information for the new score.
				/// </summary>
					// method type 2
					Types::LeaderboardRankDetails GetRankDetails() const
					{
						return Types::LeaderboardRankDetails(m_Response.GetGSDataObject("rankDetails").GetValue());
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
			};
			

			/*!
			\ingroup Misc
			A message sent from a Cloud Code script to one or more players.
			See the Spark.sendMessage function in the Cloud Code - Java Script API documentation.
			*/
			class ScriptMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".ScriptMessage";
					}

					ScriptMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// JSON data sent from a Cloud Code script.
				/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetData () const
					{
						return m_Response.GetGSDataObject("data");
					}
				/// <summary>
				/// The extension code used wen creating this script message
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetExtCode () const
					{
						return m_Response.GetString("extCode");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
			};
			

			/*!
			\ingroup Misc
			A message sent to sockets when disconnectOthers() has been called.
			*/
			class SessionTerminatedMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".SessionTerminatedMessage";
					}

					SessionTerminatedMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// Used to automatically re-authenticate a client during socket connect.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetAuthToken () const
					{
						return m_Response.GetString("authToken");
					}
			};
			

			/*!
			\ingroup Leaderboards
			This message is sent to players when their rank in a leaderboard changes with respect to the rank of their social network friends.
			*/
			class SocialRankChangedMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".SocialRankChangedMessage";
					}

					SocialRankChangedMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// The game id that this message relates to.
				/// </summary>
					// method type 4
					Optional::t_LongOptional GetGameId () const
					{
						return m_Response.GetLong("gameId");
					}
				/// <summary>
				/// The leaderboard's name.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetLeaderboardName () const
					{
						return m_Response.GetString("leaderboardName");
					}
				/// <summary>
				/// The leaderboard shortcode.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetLeaderboardShortCode () const
					{
						return m_Response.GetString("leaderboardShortCode");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// The score details of the player whose score the receiving player has passed.
				/// </summary>
					// method type 2
					Types::LeaderboardData GetThem() const
					{
						return Types::LeaderboardData(m_Response.GetGSDataObject("them").GetValue());
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The score details of the receiving player.
				/// </summary>
					// method type 2
					Types::LeaderboardData GetYou() const
					{
						return Types::LeaderboardData(m_Response.GetGSDataObject("you").GetValue());
					}
			};
			

			/*!
			\ingroup Teams
			A message sent from a player to an entire team.
			*/
			class TeamChatMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".TeamChatMessage";
					}

					TeamChatMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// The identifier for this message as it appears in the chat history.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetChatMessageId () const
					{
						return m_Response.GetString("chatMessageId");
					}
				/// <summary>
				/// The player's id who is sending the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetFromId () const
					{
						return m_Response.GetString("fromId");
					}
				/// <summary>
				/// The message to send to the team.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetMessage () const
					{
						return m_Response.GetString("message");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// The id of the owner
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetOwnerId () const
					{
						return m_Response.GetString("ownerId");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// The id of the team
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamId () const
					{
						return m_Response.GetString("teamId");
					}
				/// <summary>
				/// The team type
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamType () const
					{
						return m_Response.GetString("teamType");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The name of the player who is sending the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetWho () const
					{
						return m_Response.GetString("who");
					}
			};
			

			/*!
			\ingroup Teams
			This message is sent to players when their rank in a global leaderboard changes such that they are knocked out of the configured 'Top N'.
			*/
			class TeamRankChangedMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".TeamRankChangedMessage";
					}

					TeamRankChangedMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// The game id that this message relates to.
				/// </summary>
					// method type 4
					Optional::t_LongOptional GetGameId () const
					{
						return m_Response.GetLong("gameId");
					}
				/// <summary>
				/// The leaderboard's name.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetLeaderboardName () const
					{
						return m_Response.GetString("leaderboardName");
					}
				/// <summary>
				/// The leaderboard shortcode.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetLeaderboardShortCode () const
					{
						return m_Response.GetString("leaderboardShortCode");
					}
				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// The score details of the team whose score the receiving team's players have passed.
				/// </summary>
					// method type 2
					Types::LeaderboardData GetThem() const
					{
						return Types::LeaderboardData(m_Response.GetGSDataObject("them").GetValue());
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The score details of the receiving team.
				/// </summary>
					// method type 2
					Types::LeaderboardData GetYou() const
					{
						return Types::LeaderboardData(m_Response.GetGSDataObject("you").GetValue());
					}
			};
			

			/*!
			\ingroup Misc
			A message indicating that the asynchronous upload task trigger by the player is now complete.
			*/
			class UploadCompleteMessage : public GSMessage
			{
				public:
					// used by SetListener to register message creation functions
					static const char* GetTypeName()
					{
						return ".UploadCompleteMessage";
					}

					UploadCompleteMessage(const GSData& data)
					: GSMessage(data)
					{

					}
				public:

				/// <summary>
				/// Flag indicating whether this message could be sent as a push notification or not.
				/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNotification () const
					{
						return m_Response.GetBoolean("notification");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSubTitle () const
					{
						return m_Response.GetString("subTitle");
					}
				/// <summary>
				/// A textual summary describing the message's purpose.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetSummary () const
					{
						return m_Response.GetString("summary");
					}
				/// <summary>
				/// A textual title for the message.
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetTitle () const
					{
						return m_Response.GetString("title");
					}
				/// <summary>
				/// The upload data (if supplied as part of GetUploadUrlRequest) of UploadData objects
				/// </summary>
					// method type 2
					Types::UploadData GetUploadData() const
					{
						return Types::UploadData(m_Response.GetGSDataObject("uploadData").GetValue());
					}
				/// <summary>
				/// The id of the upload
				/// </summary>
					// method type 4
					Optional::t_StringOptional GetUploadId () const
					{
						return m_Response.GetString("uploadId");
					}
			};
			
		}
	}
}	



/*!
\addtogroup Leaderboards
\addtogroup Misc
\addtogroup Multiplayer
\addtogroup Player
\addtogroup Teams
*/