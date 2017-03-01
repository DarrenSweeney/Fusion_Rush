#pragma once

//THIS FILE IS AUTO GENERATED, DO NOT MODIFY!!
//THIS FILE IS AUTO GENERATED, DO NOT MODIFY!!
//THIS FILE IS AUTO GENERATED, DO NOT MODIFY!!

#include "../GSTypedResponse.h"
#include "GSTypes.h"

namespace GameSparks
{
	namespace Api
	{
		namespace Responses
		{
			/*!
			\ingroup Multiplayer
			A response containing the challenge instance id that was accepted.
			*/
			class AcceptChallengeResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				AcceptChallengeResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				AcceptChallengeResponse(const AcceptChallengeResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The ID of the challenge
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetChallengeInstanceId () const
					{
						return m_Response.GetString("challengeInstanceId");
					}
			};
			/*!
			\ingroup Player
			A response containing the player's data.
			*/
			class AccountDetailsResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				AccountDetailsResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				AccountDetailsResponse(const AccountDetailsResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A JSON object containing the player's achievments
			/// </summary>
						gsstl::vector<gsstl::string> GetAchievements() const
						{
							return m_Response.GetStringList("achievements");
						}
			/// <summary>
			/// The amount of type 1 currency that the player holds
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency1 () const
					{
						return m_Response.GetLong("currency1");
					}
			/// <summary>
			/// The amount of type 2 currency that the player holds
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency2 () const
					{
						return m_Response.GetLong("currency2");
					}
			/// <summary>
			/// The amount of type 3 currency that the player holds
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency3 () const
					{
						return m_Response.GetLong("currency3");
					}
			/// <summary>
			/// The amount of type 4 currency that the player holds
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency4 () const
					{
						return m_Response.GetLong("currency4");
					}
			/// <summary>
			/// The amount of type 5 currency that the player holds
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency5 () const
					{
						return m_Response.GetLong("currency5");
					}
			/// <summary>
			/// The amount of type 6 currency that the player holds
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency6 () const
					{
						return m_Response.GetLong("currency6");
					}
			/// <summary>
			/// The player's display name
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetDisplayName () const
					{
						return m_Response.GetString("displayName");
					}
			/// <summary>
			/// A JSON object containing the player's external account details
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetExternalIds () const
					{
						return m_Response.GetGSDataObject("externalIds");
					}
			/// <summary>
			/// A JSON object containing the player's location
			/// </summary>
					// method type 2
					Types::Location GetLocation() const
					{
						return Types::Location(m_Response.GetGSDataObject("location").GetValue());
					}
			/// <summary>
			/// The amount of type 1 currency that the player holds which is currently reserved
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetReservedCurrency1 () const
					{
						return m_Response.GetGSDataObject("reservedCurrency1");
					}
			/// <summary>
			/// The amount of type 2 currency that the player holds which is currently reserved
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetReservedCurrency2 () const
					{
						return m_Response.GetGSDataObject("reservedCurrency2");
					}
			/// <summary>
			/// The amount of type 3 currency that the player holds which is currently reserved
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetReservedCurrency3 () const
					{
						return m_Response.GetGSDataObject("reservedCurrency3");
					}
			/// <summary>
			/// The amount of type 4 currency that the player holds which is currently reserved
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetReservedCurrency4 () const
					{
						return m_Response.GetGSDataObject("reservedCurrency4");
					}
			/// <summary>
			/// The amount of type 5 currency that the player holds which is currently reserved
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetReservedCurrency5 () const
					{
						return m_Response.GetGSDataObject("reservedCurrency5");
					}
			/// <summary>
			/// The amount of type 6 currency that the player holds which is currently reserved
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetReservedCurrency6 () const
					{
						return m_Response.GetGSDataObject("reservedCurrency6");
					}
			/// <summary>
			/// The player's id
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetUserId () const
					{
						return m_Response.GetString("userId");
					}
			/// <summary>
			/// A JSON object containing the virtual goods that the player owns
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetVirtualGoods () const
					{
						return m_Response.GetGSDataObject("virtualGoods");
					}
			};
			/*!
			\ingroup Analytics
			A response to an analytics request
			*/
			class AnalyticsResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				AnalyticsResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				AnalyticsResponse(const AnalyticsResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Leaderboards
			A response containing leaderboard data around the current player
			*/
			class AroundMeLeaderboardResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				AroundMeLeaderboardResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				AroundMeLeaderboardResponse(const AroundMeLeaderboardResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The leaderboard's challenge id
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetChallengeInstanceId () const
					{
						return m_Response.GetString("challengeInstanceId");
					}
			/// <summary>
			/// The leaderboard data
			/// </summary>
					// method type 1
					gsstl::vector<Types::LeaderboardData> GetData() const
					{
						gsstl::vector<Types::LeaderboardData> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("data");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::LeaderboardData(*it));
						}
						return result; 
					}
			/// <summary>
			/// The first item in the leaderboard data
			/// </summary>
					// method type 1
					gsstl::vector<Types::LeaderboardData> GetFirst() const
					{
						gsstl::vector<Types::LeaderboardData> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("first");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::LeaderboardData(*it));
						}
						return result; 
					}
			/// <summary>
			/// The last item in the leaderboard data
			/// </summary>
					// method type 1
					gsstl::vector<Types::LeaderboardData> GetLast() const
					{
						gsstl::vector<Types::LeaderboardData> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("last");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::LeaderboardData(*it));
						}
						return result; 
					}
			/// <summary>
			/// The leaderboard short code
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetLeaderboardShortCode () const
					{
						return m_Response.GetString("leaderboardShortCode");
					}
			/// <summary>
			/// True if the response contains a social leaderboard's data
			/// </summary>
					// method type 4
					Optional::t_BoolOptional GetSocial () const
					{
						return m_Response.GetBoolean("social");
					}
			};
			/*!
			\ingroup Authentication
			A response containing the auth token
			*/
			class AuthenticationResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				AuthenticationResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				AuthenticationResponse(const AuthenticationResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// 44b297a8-162a-4220-8c14-dad9a1946ad2
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetAuthToken () const
					{
						return m_Response.GetString("authToken");
					}
			/// <summary>
			/// The player's display name
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetDisplayName () const
					{
						return m_Response.GetString("displayName");
					}
			/// <summary>
			/// Indicates whether the player was created as part of this request
			/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNewPlayer () const
					{
						return m_Response.GetBoolean("newPlayer");
					}
			/// <summary>
			/// A summary of the player that would be switched to.  Only returned as part of an error response for a request where automatic switching is disabled.
			/// </summary>
					// method type 2
					Types::Player GetSwitchSummary() const
					{
						return Types::Player(m_Response.GetGSDataObject("switchSummary").GetValue());
					}
			/// <summary>
			/// The player's id
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetUserId () const
					{
						return m_Response.GetString("userId");
					}
			};
			/*!
			\ingroup Admin
			A response containing the individual responses for requests performed via a BatchAdminRequest
			*/
			class BatchAdminResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				BatchAdminResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				BatchAdminResponse(const BatchAdminResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A map of responses by player ID
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetResponses () const
					{
						return m_Response.GetGSDataObject("responses");
					}
			};
			/*!
			\ingroup Store
			A response containing details of the bought items
			*/
			class BuyVirtualGoodResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				BuyVirtualGoodResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				BuyVirtualGoodResponse(const BuyVirtualGoodResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A JSON object containing details of the bought items
			/// </summary>
					// method type 1
					gsstl::vector<Types::Boughtitem> GetBoughtItems() const
					{
						gsstl::vector<Types::Boughtitem> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("boughtItems");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Boughtitem(*it));
						}
						return result; 
					}
			/// <summary>
			/// How much currency type 1 was added
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency1Added () const
					{
						return m_Response.GetLong("currency1Added");
					}
			/// <summary>
			/// How much currency type 2 was added
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency2Added () const
					{
						return m_Response.GetLong("currency2Added");
					}
			/// <summary>
			/// How much currency type 3 was added
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency3Added () const
					{
						return m_Response.GetLong("currency3Added");
					}
			/// <summary>
			/// How much currency type 4 was added
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency4Added () const
					{
						return m_Response.GetLong("currency4Added");
					}
			/// <summary>
			/// How much currency type 5 was added
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency5Added () const
					{
						return m_Response.GetLong("currency5Added");
					}
			/// <summary>
			/// How much currency type 6 was added
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrency6Added () const
					{
						return m_Response.GetLong("currency6Added");
					}
			/// <summary>
			/// For a buy with currency request, how much currency was used
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetCurrencyConsumed () const
					{
						return m_Response.GetLong("currencyConsumed");
					}
			/// <summary>
			/// For a buy with currency request, which currency type was used
			/// </summary>
					// method type 4
					Optional::t_IntOptional GetCurrencyType () const
					{
						return m_Response.GetInt("currencyType");
					}
			/// <summary>
			/// The list of transactionIds, for this purchase, if they exist. This field is populated only for store buys
			/// </summary>
						gsstl::vector<gsstl::string> GetTransactionIds() const
						{
							return m_Response.GetStringList("transactionIds");
						}
			};
			/*!
			\ingroup Player
			A response listing cancelled bulk jobs
			*/
			class CancelBulkJobAdminResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				CancelBulkJobAdminResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				CancelBulkJobAdminResponse(const CancelBulkJobAdminResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON objects containing bulk jobs
			/// </summary>
					// method type 1
					gsstl::vector<Types::BulkJob> GetBulkJobs() const
					{
						gsstl::vector<Types::BulkJob> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("bulkJobs");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::BulkJob(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Player
			A response to a change user details request
			*/
			class ChangeUserDetailsResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ChangeUserDetailsResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ChangeUserDetailsResponse(const ChangeUserDetailsResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Multiplayer
			A response to a chat on challenge request
			*/
			class ChatOnChallengeResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ChatOnChallengeResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ChatOnChallengeResponse(const ChatOnChallengeResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The challenge instance id
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetChallengeInstanceId () const
					{
						return m_Response.GetString("challengeInstanceId");
					}
			};
			/*!
			\ingroup Store
			A response to a consume virtual goods response
			*/
			class ConsumeVirtualGoodResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ConsumeVirtualGoodResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ConsumeVirtualGoodResponse(const ConsumeVirtualGoodResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Multiplayer
			A response to a create challenge response
			*/
			class CreateChallengeResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				CreateChallengeResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				CreateChallengeResponse(const CreateChallengeResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The challenge instance id
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetChallengeInstanceId () const
					{
						return m_Response.GetString("challengeInstanceId");
					}
			};
			/*!
			\ingroup Teams
			A response containing the details of the team that was created
			*/
			class CreateTeamResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				CreateTeamResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				CreateTeamResponse(const CreateTeamResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The team members
			/// </summary>
					// method type 1
					gsstl::vector<Types::Player> GetMembers() const
					{
						gsstl::vector<Types::Player> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("members");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Player(*it));
						}
						return result; 
					}
			/// <summary>
			/// A summary of the owner
			/// </summary>
					// method type 2
					Types::Player GetOwner() const
					{
						return Types::Player(m_Response.GetGSDataObject("owner").GetValue());
					}
			/// <summary>
			/// The Id of the team
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamId () const
					{
						return m_Response.GetString("teamId");
					}
			/// <summary>
			/// The team name
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamName () const
					{
						return m_Response.GetString("teamName");
					}
			/// <summary>
			/// The team type
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamType () const
					{
						return m_Response.GetString("teamType");
					}
			};
			/*!
			\ingroup Multiplayer
			A response containing the challenge instance id of the challenge that was declined
			*/
			class DeclineChallengeResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				DeclineChallengeResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				DeclineChallengeResponse(const DeclineChallengeResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The challenge instance id
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetChallengeInstanceId () const
					{
						return m_Response.GetString("challengeInstanceId");
					}
			};
			/*!
			\ingroup Player
			A response to a dismiss message request
			*/
			class DismissMessageResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				DismissMessageResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				DismissMessageResponse(const DismissMessageResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Teams
			A response to a drop team request
			*/
			class DropTeamResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				DropTeamResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				DropTeamResponse(const DropTeamResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The team members
			/// </summary>
					// method type 1
					gsstl::vector<Types::Player> GetMembers() const
					{
						gsstl::vector<Types::Player> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("members");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Player(*it));
						}
						return result; 
					}
			/// <summary>
			/// A summary of the owner
			/// </summary>
					// method type 2
					Types::Player GetOwner() const
					{
						return Types::Player(m_Response.GetGSDataObject("owner").GetValue());
					}
			/// <summary>
			/// The Id of the team
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamId () const
					{
						return m_Response.GetString("teamId");
					}
			/// <summary>
			/// The team name
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamName () const
					{
						return m_Response.GetString("teamName");
					}
			/// <summary>
			/// The team type
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamType () const
					{
						return m_Response.GetString("teamType");
					}
			};
			/*!
			\ingroup Player
			A response to a send session request 
			*/
			class EndSessionResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				EndSessionResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				EndSessionResponse(const EndSessionResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Multiplayer
			A response to a find challenge request
			*/
			class FindChallengeResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				FindChallengeResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				FindChallengeResponse(const FindChallengeResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON objects representing the challenges.
			/// </summary>
					// method type 1
					gsstl::vector<Types::Challenge> GetChallengeInstances() const
					{
						gsstl::vector<Types::Challenge> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("challengeInstances");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Challenge(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Multiplayer
			A response to a find match request
			*/
			class FindMatchResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				FindMatchResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				FindMatchResponse(const FindMatchResponse& other)
					: GSTypedResponse(other)
				{
				}

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
			/// The id for this match instance
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetMatchId () const
					{
						return m_Response.GetString("matchId");
					}
			/// <summary>
			/// The opponents this player has been matched against
			/// </summary>
					// method type 1
					gsstl::vector<Types::Player> GetOpponents() const
					{
						gsstl::vector<Types::Player> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("opponents");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Player(*it));
						}
						return result; 
					}
			/// <summary>
			/// The peerId of this player within the match
			/// </summary>
					// method type 4
					Optional::t_IntOptional GetPeerId () const
					{
						return m_Response.GetInt("peerId");
					}
			/// <summary>
			/// The id of the current player
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetPlayerId () const
					{
						return m_Response.GetString("playerId");
					}
			/// <summary>
			/// The port to connect to for this match
			/// </summary>
					// method type 4
					Optional::t_IntOptional GetPort () const
					{
						return m_Response.GetInt("port");
					}
			};
			/*!
			\ingroup Multiplayer
			A response to a FindPendingMatchesRequest
			*/
			class FindPendingMatchesResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				FindPendingMatchesResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				FindPendingMatchesResponse(const FindPendingMatchesResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON objects containing pending matches
			/// </summary>
					// method type 1
					gsstl::vector<Types::PendingMatch> GetPendingMatches() const
					{
						gsstl::vector<Types::PendingMatch> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("pendingMatches");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::PendingMatch(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Misc
			A response containing the details of an error
			*/
			class GameSparksErrorResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				GameSparksErrorResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				GameSparksErrorResponse(const GameSparksErrorResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Multiplayer
			A response containing the details of a challenge
			*/
			class GetChallengeResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				GetChallengeResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				GetChallengeResponse(const GetChallengeResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A JSON object representing the challenge.
			/// </summary>
					// method type 2
					Types::Challenge GetChallenge() const
					{
						return Types::Challenge(m_Response.GetGSDataObject("challenge").GetValue());
					}
			};
			/*!
			\ingroup Misc
			A response containing the download URL for a downloadable item
			*/
			class GetDownloadableResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				GetDownloadableResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				GetDownloadableResponse(const GetDownloadableResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The date when the downloadable item was last modified
			/// </summary>
					// method type 4
					GameSparks::Core::GSDateTime::t_Optional GetLastModified () const
					{
						return m_Response.GetDate("lastModified");
					}
			/// <summary>
			/// The short code of the item
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetShortCode () const
					{
						return m_Response.GetString("shortCode");
					}
			/// <summary>
			/// The size of the item in bytes
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetSize () const
					{
						return m_Response.GetLong("size");
					}
			/// <summary>
			/// The download URL
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetUrl () const
					{
						return m_Response.GetString("url");
					}
			};
			/*!
			\ingroup Leaderboards
			A response containing leaderboard entry data for a given player
			*/
			class GetLeaderboardEntriesResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				GetLeaderboardEntriesResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				GetLeaderboardEntriesResponse(const GetLeaderboardEntriesResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The leaderboard entry data
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetResults () const
					{
						return m_Response.GetGSDataObject("results");
					}
			};
			/*!
			\ingroup Multiplayer
			A response containing the message data for a given message
			*/
			class GetMessageResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				GetMessageResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				GetMessageResponse(const GetMessageResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The message data
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetMessage () const
					{
						return m_Response.GetGSDataObject("message");
					}
			};
			/*!
			\ingroup Teams
			A response containing team data for teams that a player belong to
			*/
			class GetMyTeamsResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				GetMyTeamsResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				GetMyTeamsResponse(const GetMyTeamsResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The team data
			/// </summary>
					// method type 1
					gsstl::vector<Types::Team> GetTeams() const
					{
						gsstl::vector<Types::Team> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("teams");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Team(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Misc
			A response containing the requested property
			*/
			class GetPropertyResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				GetPropertyResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				GetPropertyResponse(const GetPropertyResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The property value
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetProperty () const
					{
						return m_Response.GetGSDataObject("property");
					}
			};
			/*!
			\ingroup Misc
			A response containing the requested property set
			*/
			class GetPropertySetResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				GetPropertySetResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				GetPropertySetResponse(const GetPropertySetResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The property set
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetPropertySet () const
					{
						return m_Response.GetGSDataObject("propertySet");
					}
			};
			/*!
			\ingroup Teams
			A response containing the details of the requested teams
			*/
			class GetTeamResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				GetTeamResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				GetTeamResponse(const GetTeamResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The team members
			/// </summary>
					// method type 1
					gsstl::vector<Types::Player> GetMembers() const
					{
						gsstl::vector<Types::Player> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("members");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Player(*it));
						}
						return result; 
					}
			/// <summary>
			/// A summary of the owner
			/// </summary>
					// method type 2
					Types::Player GetOwner() const
					{
						return Types::Player(m_Response.GetGSDataObject("owner").GetValue());
					}
			/// <summary>
			/// The Id of the team
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamId () const
					{
						return m_Response.GetString("teamId");
					}
			/// <summary>
			/// The team name
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamName () const
					{
						return m_Response.GetString("teamName");
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
			/// A JSON array of teams.
			/// </summary>
					// method type 1
					gsstl::vector<Types::Team> GetTeams() const
					{
						gsstl::vector<Types::Team> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("teams");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Team(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Misc
			A response containing a time sensitive URL to allow the game to upload a piece of player content to the GameSparks platform
			*/
			class GetUploadUrlResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				GetUploadUrlResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				GetUploadUrlResponse(const GetUploadUrlResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The time sensitive upload URL
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetUrl () const
					{
						return m_Response.GetString("url");
					}
			};
			/*!
			\ingroup Misc
			A reponse containing a time sensitive URL to a piece of content that was previously uploaded to the GameSparks platform by a player.
			*/
			class GetUploadedResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				GetUploadedResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				GetUploadedResponse(const GetUploadedResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The size of the file in bytes
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetSize () const
					{
						return m_Response.GetLong("size");
					}
			/// <summary>
			/// A time sensitive URL to a piece of content
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetUrl () const
					{
						return m_Response.GetString("url");
					}
			};
			/*!
			\ingroup Multiplayer
			A response to a player joining a challenge
			*/
			class JoinChallengeResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				JoinChallengeResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				JoinChallengeResponse(const JoinChallengeResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Multiplayer
			A response to a JoinPendingMatchRequest
			*/
			class JoinPendingMatchResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				JoinPendingMatchResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				JoinPendingMatchResponse(const JoinPendingMatchResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A JSON object containing the new pending match
			/// </summary>
					// method type 2
					Types::PendingMatch GetPendingMatch() const
					{
						return Types::PendingMatch(m_Response.GetGSDataObject("pendingMatch").GetValue());
					}
			};
			/*!
			\ingroup Teams
			A response to a player joining a team or a request for team data
			*/
			class JoinTeamResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				JoinTeamResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				JoinTeamResponse(const JoinTeamResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The team members
			/// </summary>
					// method type 1
					gsstl::vector<Types::Player> GetMembers() const
					{
						gsstl::vector<Types::Player> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("members");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Player(*it));
						}
						return result; 
					}
			/// <summary>
			/// A summary of the owner
			/// </summary>
					// method type 2
					Types::Player GetOwner() const
					{
						return Types::Player(m_Response.GetGSDataObject("owner").GetValue());
					}
			/// <summary>
			/// The Id of the team
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamId () const
					{
						return m_Response.GetString("teamId");
					}
			/// <summary>
			/// The team name
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamName () const
					{
						return m_Response.GetString("teamName");
					}
			/// <summary>
			/// The team type
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamType () const
					{
						return m_Response.GetString("teamType");
					}
			};
			/*!
			\ingroup Leaderboards
			A response containing leaderboard data
			*/
			class LeaderboardDataResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				LeaderboardDataResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				LeaderboardDataResponse(const LeaderboardDataResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The leaderboard's challenge id
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetChallengeInstanceId () const
					{
						return m_Response.GetString("challengeInstanceId");
					}
			/// <summary>
			/// The leaderboard data
			/// </summary>
					// method type 1
					gsstl::vector<Types::LeaderboardData> GetData() const
					{
						gsstl::vector<Types::LeaderboardData> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("data");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::LeaderboardData(*it));
						}
						return result; 
					}
			/// <summary>
			/// The first item in the leaderboard data
			/// </summary>
					// method type 1
					gsstl::vector<Types::LeaderboardData> GetFirst() const
					{
						gsstl::vector<Types::LeaderboardData> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("first");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::LeaderboardData(*it));
						}
						return result; 
					}
			/// <summary>
			/// The last item in the leaderboard data
			/// </summary>
					// method type 1
					gsstl::vector<Types::LeaderboardData> GetLast() const
					{
						gsstl::vector<Types::LeaderboardData> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("last");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::LeaderboardData(*it));
						}
						return result; 
					}
			/// <summary>
			/// The leaderboard short code
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetLeaderboardShortCode () const
					{
						return m_Response.GetString("leaderboardShortCode");
					}
			};
			/*!
			\ingroup Leaderboards
			A response containing leaderboard entry data for a given player
			*/
			class LeaderboardsEntriesResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				LeaderboardsEntriesResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				LeaderboardsEntriesResponse(const LeaderboardsEntriesResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The leaderboard entry data
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetResults () const
					{
						return m_Response.GetGSDataObject("results");
					}
			};
			/*!
			\ingroup Teams
			A response to a player leaving a team
			*/
			class LeaveTeamResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				LeaveTeamResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				LeaveTeamResponse(const LeaveTeamResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The team members
			/// </summary>
					// method type 1
					gsstl::vector<Types::Player> GetMembers() const
					{
						gsstl::vector<Types::Player> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("members");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Player(*it));
						}
						return result; 
					}
			/// <summary>
			/// A summary of the owner
			/// </summary>
					// method type 2
					Types::Player GetOwner() const
					{
						return Types::Player(m_Response.GetGSDataObject("owner").GetValue());
					}
			/// <summary>
			/// The Id of the team
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamId () const
					{
						return m_Response.GetString("teamId");
					}
			/// <summary>
			/// The team name
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamName () const
					{
						return m_Response.GetString("teamName");
					}
			/// <summary>
			/// The team type
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetTeamType () const
					{
						return m_Response.GetString("teamType");
					}
			};
			/*!
			\ingroup Player
			A reponse containing the game's achievments and an indication of whether the player has earned it
			*/
			class ListAchievementsResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ListAchievementsResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ListAchievementsResponse(const ListAchievementsResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON achievment objects
			/// </summary>
					// method type 1
					gsstl::vector<Types::Achievement> GetAchievements() const
					{
						gsstl::vector<Types::Achievement> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("achievements");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Achievement(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Player
			A response listing existing bulk jobs
			*/
			class ListBulkJobsAdminResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ListBulkJobsAdminResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ListBulkJobsAdminResponse(const ListBulkJobsAdminResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON objects containing bulk jobs
			/// </summary>
					// method type 1
					gsstl::vector<Types::BulkJob> GetBulkJobs() const
					{
						gsstl::vector<Types::BulkJob> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("bulkJobs");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::BulkJob(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Multiplayer
			A response containing challenges that are in the state that was specified in the request
			*/
			class ListChallengeResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ListChallengeResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ListChallengeResponse(const ListChallengeResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON objects representing the challenges.
			/// </summary>
					// method type 1
					gsstl::vector<Types::Challenge> GetChallengeInstances() const
					{
						gsstl::vector<Types::Challenge> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("challengeInstances");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Challenge(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Multiplayer
			A response containing the list of configured challenge types in the game
			*/
			class ListChallengeTypeResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ListChallengeTypeResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ListChallengeTypeResponse(const ListChallengeTypeResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON objects containing the challenge templates for the game
			/// </summary>
					// method type 1
					gsstl::vector<Types::ChallengeType> GetChallengeTemplates() const
					{
						gsstl::vector<Types::ChallengeType> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("challengeTemplates");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::ChallengeType(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Player
			A response containing the list of the current players game friends.
			*/
			class ListGameFriendsResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ListGameFriendsResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ListGameFriendsResponse(const ListGameFriendsResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON objects containing game friend data
			/// </summary>
					// method type 1
					gsstl::vector<Types::Player> GetFriends() const
					{
						gsstl::vector<Types::Player> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("friends");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Player(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Player
			A response containing a list of non game friends.
			*/
			class ListInviteFriendsResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ListInviteFriendsResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ListInviteFriendsResponse(const ListInviteFriendsResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON objects containing game friend data
			/// </summary>
					// method type 1
					gsstl::vector<Types::InvitableFriend> GetFriends() const
					{
						gsstl::vector<Types::InvitableFriend> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("friends");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::InvitableFriend(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Leaderboards
			A response containing a list of all leaderboards configured in the game.
			*/
			class ListLeaderboardsResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ListLeaderboardsResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ListLeaderboardsResponse(const ListLeaderboardsResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON object containing leaderboard meta data
			/// </summary>
					// method type 1
					gsstl::vector<Types::Leaderboard> GetLeaderboards() const
					{
						gsstl::vector<Types::Leaderboard> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("leaderboards");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Leaderboard(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Player
			A response containing the list of the current players messages / notifications.
			*/
			class ListMessageResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ListMessageResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ListMessageResponse(const ListMessageResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON objects containing player messages
			/// </summary>
						// method type 3.1 
						gsstl::vector<GameSparks::Core::GSData::t_Optional> GetMessageList() const
						{
							gsstl::vector<GameSparks::Core::GSData::t_Optional> result;
							gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("messageList");
							for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
							{
								result.push_back(GameSparks::Core::GSData::t_Optional(*it, true));
							}
							return result;
						}
			};
			/*!
			\ingroup Player
			A response containing  a summary of the list of the current players messages / notifications.
			*/
			class ListMessageSummaryResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ListMessageSummaryResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ListMessageSummaryResponse(const ListMessageSummaryResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON objects containing player message summaries
			/// </summary>
						// method type 3.1 
						gsstl::vector<GameSparks::Core::GSData::t_Optional> GetMessageList() const
						{
							gsstl::vector<GameSparks::Core::GSData::t_Optional> result;
							gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("messageList");
							for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
							{
								result.push_back(GameSparks::Core::GSData::t_Optional(*it, true));
							}
							return result;
						}
			};
			/*!
			\ingroup Teams
			A response to a list team messages request.
			*/
			class ListTeamChatResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ListTeamChatResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ListTeamChatResponse(const ListTeamChatResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Player
			A response listing transactions for the player
			*/
			class ListTransactionsResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ListTransactionsResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ListTransactionsResponse(const ListTransactionsResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON objects containing player transactions
			/// </summary>
					// method type 1
					gsstl::vector<Types::PlayerTransaction> GetTransactionList() const
					{
						gsstl::vector<Types::PlayerTransaction> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("transactionList");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::PlayerTransaction(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Store
			A response containing the list of configured virtual goods.
			*/
			class ListVirtualGoodsResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ListVirtualGoodsResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ListVirtualGoodsResponse(const ListVirtualGoodsResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of JSON objects containing virtual goods data
			/// </summary>
					// method type 1
					gsstl::vector<Types::VirtualGood> GetVirtualGoods() const
					{
						gsstl::vector<Types::VirtualGood> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("virtualGoods");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::VirtualGood(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Multiplayer
			A response to a log challenge event request 
			*/
			class LogChallengeEventResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				LogChallengeEventResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				LogChallengeEventResponse(const LogChallengeEventResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Player
			A response to a log event request 
			*/
			class LogEventResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				LogEventResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				LogEventResponse(const LogEventResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Multiplayer
			A response to a match details request
			*/
			class MatchDetailsResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				MatchDetailsResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				MatchDetailsResponse(const MatchDetailsResponse& other)
					: GSTypedResponse(other)
				{
				}

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
			/// The id for this match instance
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetMatchId () const
					{
						return m_Response.GetString("matchId");
					}
			/// <summary>
			/// The opponents this player has been matched against
			/// </summary>
					// method type 1
					gsstl::vector<Types::Player> GetOpponents() const
					{
						gsstl::vector<Types::Player> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("opponents");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::Player(*it));
						}
						return result; 
					}
			/// <summary>
			/// The peerId of this player within the match
			/// </summary>
					// method type 4
					Optional::t_IntOptional GetPeerId () const
					{
						return m_Response.GetInt("peerId");
					}
			/// <summary>
			/// The id of the current player
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetPlayerId () const
					{
						return m_Response.GetString("playerId");
					}
			/// <summary>
			/// The port to connect to for this match
			/// </summary>
					// method type 4
					Optional::t_IntOptional GetPort () const
					{
						return m_Response.GetInt("port");
					}
			};
			/*!
			\ingroup Multiplayer
			A response to a matchmaking request
			*/
			class MatchmakingResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				MatchmakingResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				MatchmakingResponse(const MatchmakingResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Misc
			A response to a push registration request 
			*/
			class PushRegistrationResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				PushRegistrationResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				PushRegistrationResponse(const PushRegistrationResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// An identifier for the successful registration.  Clients should store this value to be used in the event the player no longer wants to receive push notifications to this device.
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetRegistrationId () const
					{
						return m_Response.GetString("registrationId");
					}
			};
			/*!
			\ingroup Authentication
			A response to a registration request 
			*/
			class RegistrationResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				RegistrationResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				RegistrationResponse(const RegistrationResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// 44b297a8-162a-4220-8c14-dad9a1946ad2
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetAuthToken () const
					{
						return m_Response.GetString("authToken");
					}
			/// <summary>
			/// The player's display name
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetDisplayName () const
					{
						return m_Response.GetString("displayName");
					}
			/// <summary>
			/// Indicates whether the player was created as part of this request
			/// </summary>
					// method type 4
					Optional::t_BoolOptional GetNewPlayer () const
					{
						return m_Response.GetBoolean("newPlayer");
					}
			/// <summary>
			/// A summary of the player that would be switched to.  Only returned as part of an error response for a request where automatic switching is disabled.
			/// </summary>
					// method type 2
					Types::Player GetSwitchSummary() const
					{
						return Types::Player(m_Response.GetGSDataObject("switchSummary").GetValue());
					}
			/// <summary>
			/// The player's id
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetUserId () const
					{
						return m_Response.GetString("userId");
					}
			};
			/*!
			\ingroup Store
			A response containing details of the revoked items
			*/
			class RevokePurchaseGoodsResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				RevokePurchaseGoodsResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				RevokePurchaseGoodsResponse(const RevokePurchaseGoodsResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The map of revoked goods
			/// </summary>
					// method type 4
					GameSparks::Core::GSData::t_Optional GetRevokedGoods () const
					{
						return m_Response.GetGSDataObject("revokedGoods");
					}
			};
			/*!
			\ingroup Player
			A response acknowledging the scheduling of a bulk job
			*/
			class ScheduleBulkJobAdminResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				ScheduleBulkJobAdminResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				ScheduleBulkJobAdminResponse(const ScheduleBulkJobAdminResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// The count of players who would be affected by this job if it ran at the time it was submitted
			/// </summary>
					// method type 4
					Optional::t_LongOptional GetEstimatedCount () const
					{
						return m_Response.GetLong("estimatedCount");
					}
			/// <summary>
			/// The unique job ID, used to identify this job in future requests
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetJobId () const
					{
						return m_Response.GetString("jobId");
					}
			};
			/*!
			\ingroup Player
			A response to a send friend message request.
			*/
			class SendFriendMessageResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				SendFriendMessageResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				SendFriendMessageResponse(const SendFriendMessageResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Teams
			A response to a send team message request.
			*/
			class SendTeamChatMessageResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				SendTeamChatMessageResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				SendTeamChatMessageResponse(const SendTeamChatMessageResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Misc
			A response to a SocialDisconnectRequest
			*/
			class SocialDisconnectResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				SocialDisconnectResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				SocialDisconnectResponse(const SocialDisconnectResponse& other)
					: GSTypedResponse(other)
				{
				}

			};
			/*!
			\ingroup Misc
			A response containing the details of a the players social connections
			*/
			class SocialStatusResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				SocialStatusResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				SocialStatusResponse(const SocialStatusResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A list of social statuses.
			/// </summary>
					// method type 1
					gsstl::vector<Types::SocialStatus> GetStatuses() const
					{
						gsstl::vector<Types::SocialStatus> result;
						gsstl::vector<GameSparks::Core::GSData> dataList = m_Response.GetGSDataObjectList("statuses");
						for (gsstl::vector<GameSparks::Core::GSData>::iterator it = dataList.begin(); it != dataList.end(); ++it)
						{
							result.push_back(Types::SocialStatus(*it));
						}
						return result; 
					}
			};
			/*!
			\ingroup Multiplayer
			A response containing the challenge instance id that was withdrawn by a player
			*/
			class WithdrawChallengeResponse : public  GameSparks::Core::GSTypedResponse
			{
			public:
				WithdrawChallengeResponse(const GameSparks::Core::GSData& data)
					: GSTypedResponse(data)
				{

				}

				WithdrawChallengeResponse(const WithdrawChallengeResponse& other)
					: GSTypedResponse(other)
				{
				}

			/// <summary>
			/// A challenge instance id
			/// </summary>
					// method type 4
					Optional::t_StringOptional GetChallengeInstanceId () const
					{
						return m_Response.GetString("challengeInstanceId");
					}
			};
		}
	}
}


/*!
\addtogroup Admin
\addtogroup Analytics
\addtogroup Authentication
\addtogroup Leaderboards
\addtogroup Misc
\addtogroup Multiplayer
\addtogroup Player
\addtogroup Store
\addtogroup Teams
*/
