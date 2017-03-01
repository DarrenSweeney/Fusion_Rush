#pragma once

//THIS FILE IS AUTO GENERATED, DO NOT MODIFY!!
//THIS FILE IS AUTO GENERATED, DO NOT MODIFY!!
//THIS FILE IS AUTO GENERATED, DO NOT MODIFY!!

#include "../GSObject.h"
#include "../GSTypedResponse.h"
#include "../GSTypedRequest.h"
#include "GSResponses.h"

namespace GameSparks
{
	namespace Api
	{
		namespace Requests
		{
			/*!
			\ingroup Multiplayer
			Accepts a challenge that has been issued to the current player.
			*/
			class AcceptChallengeRequest : public GameSparks::Core::GSTypedRequest < AcceptChallengeRequest, GameSparks::Api::Responses::AcceptChallengeResponse >
			{
			public:
				AcceptChallengeRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".AcceptChallengeRequest")
				{

				}
			


			/// <summary>
			/// The ID of the challenge
			/// </summary>
			AcceptChallengeRequest& SetChallengeInstanceId( const gsstl::string& challengeInstanceId )
			{
				m_Request.AddString("challengeInstanceId", challengeInstanceId);
				return *this;
			}
			/// <summary>
			/// An optional message to send with the challenge
			/// </summary>
			AcceptChallengeRequest& SetMessage( const gsstl::string& message )
			{
				m_Request.AddString("message", message);
				return *this;
			}
			};
			
			/*!
			\ingroup Player
			Retrieves the details of the current authenticated player.
			*/
			class AccountDetailsRequest : public GameSparks::Core::GSTypedRequest < AccountDetailsRequest, GameSparks::Api::Responses::AccountDetailsResponse >
			{
			public:
				AccountDetailsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".AccountDetailsRequest")
				{

				}
			


			};
			
			/*!
			\ingroup Store
			Processes the receipt from an Amazon in app purchase.
			The GameSparks platform will validate the amazonUserId and receiptId with Amazon using the Amazon Purchase Secret configured against the game.
			The receiptId in the data will be recorded and the request will be rejected if the receiptId has previously been processed, this prevents replay attacks.
			Once verfied, the players account will be credited with the Virtual Good, or Virtual Currency the purchase contains. The virtual good will be looked up by matching the productId in the receipt with the 'Amazon Product Id' configured against the virtual good.
			*/
			class AmazonBuyGoodsRequest : public GameSparks::Core::GSTypedRequest < AmazonBuyGoodsRequest, GameSparks::Api::Responses::BuyVirtualGoodResponse >
			{
			public:
				AmazonBuyGoodsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".AmazonBuyGoodsRequest")
				{

				}
			


			/// <summary>
			/// The userId obtained from the UserData within a PurchaseResponse
			/// </summary>
			AmazonBuyGoodsRequest& SetAmazonUserId( const gsstl::string& amazonUserId )
			{
				m_Request.AddString("amazonUserId", amazonUserId);
				return *this;
			}
			/// <summary>
			/// The receiptId obtained from the Receipt within a PurchaseResponse
			/// </summary>
			AmazonBuyGoodsRequest& SetReceiptId( const gsstl::string& receiptId )
			{
				m_Request.AddString("receiptId", receiptId);
				return *this;
			}
			/// <summary>
			/// If set to true, the transactionId from this receipt will not be globally valdidated, this will mean replays between players are possible.
			/// It will only validate the transactionId has not been used by this player before.
			/// </summary>
			AmazonBuyGoodsRequest& SetUniqueTransactionByPlayer( bool uniqueTransactionByPlayer )
			{
				m_Request.AddBoolean("uniqueTransactionByPlayer", uniqueTransactionByPlayer);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows an Amazon access token to be used as an authentication mechanism.
			Once authenticated the platform can determine the current players details from the Amazon platform and store them within GameSparks.
			If the Amazon user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthentictionRequest or RegistrationRequest AND the Amazon user is not already registered with the game, the Amazon user will be linked to the current player.
			If the current player has not authenticated and the Amazon user is not known, a new player will be created using the Amazon details and the session will be authenticated against the new player.
			If the Amazon user is already known, the session will switch to being the previously created user.
			*/
			class AmazonConnectRequest : public GameSparks::Core::GSTypedRequest < AmazonConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				AmazonConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".AmazonConnectRequest")
				{

				}
			


			/// <summary>
			/// The access token is used by the client to make authenticated requests on behalf of the end user.
			/// </summary>
			AmazonConnectRequest& SetAccessToken( const gsstl::string& accessToken )
			{
				m_Request.AddString("accessToken", accessToken);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			AmazonConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			AmazonConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			AmazonConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			AmazonConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			AmazonConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
			}
			};
			
			/*!
			\ingroup Analytics
			Records some custom analytical data.
			Simple analytics, where you just need to track the number of times something happened, just take a key parameter. We'll record the players id against the data to allow you to report on averages per user
			Timed analytics allow you to send start and end timer requests, and with this data GameSparks can track the length of time something takes.
			If an end request is sent without a matching start timer the request will fail silently and your analytics data might not contain what you expect.
			If both start and end are supplied, the request will be treated as a start timer.
			An additional data payload can be attached to the event for advanced reporting. This data can be a string, number or JSON object.
			If a second start timer is created using a key that has already had a start timer created without an end, the previous one will be marked as abandoned.
			*/
			class AnalyticsRequest : public GameSparks::Core::GSTypedRequest < AnalyticsRequest, GameSparks::Api::Responses::AnalyticsResponse >
			{
			public:
				AnalyticsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".AnalyticsRequest")
				{

				}
			


			/// <summary>
			/// Custom data payload
			/// </summary>
			AnalyticsRequest& SetData( const GameSparks::Core::GSRequestData& data )
			{
				m_Request.AddObject("data", data);
				return *this;
			}
			/// <summary>
			/// Use the value true to indicate it's an end timer
			/// </summary>
			AnalyticsRequest& SetEnd( bool end )
			{
				m_Request.AddBoolean("end", end);
				return *this;
			}
			/// <summary>
			/// The key you want to track this analysis with.
			/// </summary>
			AnalyticsRequest& SetKey( const gsstl::string& key )
			{
				m_Request.AddString("key", key);
				return *this;
			}
			/// <summary>
			/// Use the value true to indicate it's a start timer
			/// </summary>
			AnalyticsRequest& SetStart( bool start )
			{
				m_Request.AddBoolean("start", start);
				return *this;
			}
			};
			
			/*!
			\ingroup Leaderboards
			Returns leaderboard data that is adjacent to the currently signed in player's position within the given leaderboard.
			*/
			class AroundMeLeaderboardRequest : public GameSparks::Core::GSTypedRequest < AroundMeLeaderboardRequest, GameSparks::Api::Responses::AroundMeLeaderboardResponse >
			{
			public:
				AroundMeLeaderboardRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".AroundMeLeaderboardRequest")
				{

				}
			


			/// <summary>
			/// The challenge instance to get the leaderboard data for
			/// </summary>
			AroundMeLeaderboardRequest& SetChallengeInstanceId( const gsstl::string& challengeInstanceId )
			{
				m_Request.AddString("challengeInstanceId", challengeInstanceId);
				return *this;
			}
			/// <summary>
			/// An optional filter on the customIds.
			/// If this request does not contain a custonIdFilter or if it is a partial filter, 
			/// the leaderboard entries around the highest score for the given constraints will be returned.
			/// </summary>
			AroundMeLeaderboardRequest& SetCustomIdFilter( const GameSparks::Core::GSRequestData& customIdFilter )
			{
				m_Request.AddObject("customIdFilter", customIdFilter);
				return *this;
			}
			/// <summary>
			/// The default behaviour on a social request is to error if the player has no friends (NOTSOCIAL).  Set this flag to suppress that error and return the player's leaderboard entry instead.
			/// </summary>
			AroundMeLeaderboardRequest& SetDontErrorOnNotSocial( bool dontErrorOnNotSocial )
			{
				m_Request.AddBoolean("dontErrorOnNotSocial", dontErrorOnNotSocial);
				return *this;
			}
			/// <summary>
			/// The number of items to return in a page (default=50)
			/// </summary>
			AroundMeLeaderboardRequest& SetEntryCount( long entryCount )
			{
				m_Request.AddNumber("entryCount", entryCount);
				return *this;
			}
			/// <summary>
			/// A friend id or an array of friend ids to use instead of the player's social friends
			/// </summary>
			AroundMeLeaderboardRequest& SetFriendIds( gsstl::vector<gsstl::string> friendIds )
			{
				m_Request.AddStringList("friendIds", friendIds);
				return *this;
			}
			/// <summary>
			/// Number of entries to include from head of the list
			/// </summary>
			AroundMeLeaderboardRequest& SetIncludeFirst( long includeFirst )
			{
				m_Request.AddNumber("includeFirst", includeFirst);
				return *this;
			}
			/// <summary>
			/// Number of entries to include from tail of the list
			/// </summary>
			AroundMeLeaderboardRequest& SetIncludeLast( long includeLast )
			{
				m_Request.AddNumber("includeLast", includeLast);
				return *this;
			}
			/// <summary>
			/// Returns the leaderboard excluding the player's social friends
			/// </summary>
			AroundMeLeaderboardRequest& SetInverseSocial( bool inverseSocial )
			{
				m_Request.AddBoolean("inverseSocial", inverseSocial);
				return *this;
			}
			/// <summary>
			/// The short code of the leaderboard
			/// </summary>
			AroundMeLeaderboardRequest& SetLeaderboardShortCode( const gsstl::string& leaderboardShortCode )
			{
				m_Request.AddString("leaderboardShortCode", leaderboardShortCode);
				return *this;
			}
			/// <summary>
			/// If True returns a leaderboard of the player's social friends
			/// </summary>
			AroundMeLeaderboardRequest& SetSocial( bool social )
			{
				m_Request.AddBoolean("social", social);
				return *this;
			}
			/// <summary>
			/// The IDs of the teams you are interested in
			/// </summary>
			AroundMeLeaderboardRequest& SetTeamIds( gsstl::vector<gsstl::string> teamIds )
			{
				m_Request.AddStringList("teamIds", teamIds);
				return *this;
			}
			/// <summary>
			/// The type of team you are interested in
			/// </summary>
			AroundMeLeaderboardRequest& SetTeamTypes( gsstl::vector<gsstl::string> teamTypes )
			{
				m_Request.AddStringList("teamTypes", teamTypes);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Provides authentication using a username/password combination.
			The username will have been previously created using a RegistrationRequest.
			*/
			class AuthenticationRequest : public GameSparks::Core::GSTypedRequest < AuthenticationRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				AuthenticationRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".AuthenticationRequest")
				{

				}
			


			/// <summary>
			/// The previously registered password
			/// </summary>
			AuthenticationRequest& SetPassword( const gsstl::string& password )
			{
				m_Request.AddString("password", password);
				return *this;
			}
			/// <summary>
			/// The previously registered player name
			/// </summary>
			AuthenticationRequest& SetUserName( const gsstl::string& userName )
			{
				m_Request.AddString("userName", userName);
				return *this;
			}
			};
			
			/*!
			\ingroup Admin
			Performs a request for multiple players.
			*/
			class BatchAdminRequest : public GameSparks::Core::GSTypedRequest < BatchAdminRequest, GameSparks::Api::Responses::BatchAdminResponse >
			{
			public:
				BatchAdminRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".BatchAdminRequest")
				{

				}
			


			/// <summary>
			/// The players to run the request for.
			/// </summary>
			BatchAdminRequest& SetPlayerIds( gsstl::vector<gsstl::string> playerIds )
			{
				m_Request.AddStringList("playerIds", playerIds);
				return *this;
			}
			/// <summary>
			/// The request to be run for each player.
			/// </summary>
			BatchAdminRequest& SetRequest( const GameSparks::Core::GSRequestData& request )
			{
				m_Request.AddObject("request", request);
				return *this;
			}
			};
			
			/*!
			\ingroup Store
			Purchases a virtual good with an in game currency. Once purchased the virtual good will be added to the players account.
			*/
			class BuyVirtualGoodsRequest : public GameSparks::Core::GSTypedRequest < BuyVirtualGoodsRequest, GameSparks::Api::Responses::BuyVirtualGoodResponse >
			{
			public:
				BuyVirtualGoodsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".BuyVirtualGoodsRequest")
				{

				}
			


			/// <summary>
			/// Which virtual currency to use. (1 to 6)
			/// </summary>
			BuyVirtualGoodsRequest& SetCurrencyType( long currencyType )
			{
				m_Request.AddNumber("currencyType", currencyType);
				return *this;
			}
			/// <summary>
			/// The number of items to purchase
			/// </summary>
			BuyVirtualGoodsRequest& SetQuantity( long quantity )
			{
				m_Request.AddNumber("quantity", quantity);
				return *this;
			}
			/// <summary>
			/// The short code of the virtual good to be purchased
			/// </summary>
			BuyVirtualGoodsRequest& SetShortCode( const gsstl::string& shortCode )
			{
				m_Request.AddString("shortCode", shortCode);
				return *this;
			}
			};
			
			/*!
			\ingroup Admin
			Cancel one or more bulk jobs.
			*/
			class CancelBulkJobAdminRequest : public GameSparks::Core::GSTypedRequest < CancelBulkJobAdminRequest, GameSparks::Api::Responses::CancelBulkJobAdminResponse >
			{
			public:
				CancelBulkJobAdminRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".CancelBulkJobAdminRequest")
				{

				}
			


			/// <summary>
			/// The IDs of existing bulk jobs to cancel
			/// </summary>
			CancelBulkJobAdminRequest& SetBulkJobIds( gsstl::vector<gsstl::string> bulkJobIds )
			{
				m_Request.AddStringList("bulkJobIds", bulkJobIds);
				return *this;
			}
			};
			
			/*!
			\ingroup Player
			Change the display name of the currently signed in Player.
			*/
			class ChangeUserDetailsRequest : public GameSparks::Core::GSTypedRequest < ChangeUserDetailsRequest, GameSparks::Api::Responses::ChangeUserDetailsResponse >
			{
			public:
				ChangeUserDetailsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ChangeUserDetailsRequest")
				{

				}
			


			/// <summary>
			/// The new display name to set in the player data.
			/// </summary>
			ChangeUserDetailsRequest& SetDisplayName( const gsstl::string& displayName )
			{
				m_Request.AddString("displayName", displayName);
				return *this;
			}
			/// <summary>
			/// The new language code to set in the player data.
			/// </summary>
			ChangeUserDetailsRequest& SetLanguage( const gsstl::string& language )
			{
				m_Request.AddString("language", language);
				return *this;
			}
			/// <summary>
			/// The new password to set in the player data.
			/// </summary>
			ChangeUserDetailsRequest& SetNewPassword( const gsstl::string& newPassword )
			{
				m_Request.AddString("newPassword", newPassword);
				return *this;
			}
			/// <summary>
			/// The player's existing password. If supplied it will be checked against the password stored in the player data. This allows you re-authenticate the player making the change.
			/// </summary>
			ChangeUserDetailsRequest& SetOldPassword( const gsstl::string& oldPassword )
			{
				m_Request.AddString("oldPassword", oldPassword);
				return *this;
			}
			/// <summary>
			/// The new userName with which this player will sign in.  If the player currently authenticates using device authentication this will upgrade their account and require them to use username and password authentication from now on.
			/// </summary>
			ChangeUserDetailsRequest& SetUserName( const gsstl::string& userName )
			{
				m_Request.AddString("userName", userName);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Sends a message to all players involved in the challenge. The current player must be involved in the challenge for the message to be sent.
			As the message is sent to all players, the current player will also see details of the message in the response. Read the section on response message aggregation for a description of this.
			*/
			class ChatOnChallengeRequest : public GameSparks::Core::GSTypedRequest < ChatOnChallengeRequest, GameSparks::Api::Responses::ChatOnChallengeResponse >
			{
			public:
				ChatOnChallengeRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ChatOnChallengeRequest")
				{

				}
			


			/// <summary>
			/// The ID of the challenge
			/// </summary>
			ChatOnChallengeRequest& SetChallengeInstanceId( const gsstl::string& challengeInstanceId )
			{
				m_Request.AddString("challengeInstanceId", challengeInstanceId);
				return *this;
			}
			/// <summary>
			/// An optional message to send with the challenge
			/// </summary>
			ChatOnChallengeRequest& SetMessage( const gsstl::string& message )
			{
				m_Request.AddString("message", message);
				return *this;
			}
			};
			
			/*!
			\ingroup Store
			Consumes a given amount of the specified virtual good.
			*/
			class ConsumeVirtualGoodRequest : public GameSparks::Core::GSTypedRequest < ConsumeVirtualGoodRequest, GameSparks::Api::Responses::ConsumeVirtualGoodResponse >
			{
			public:
				ConsumeVirtualGoodRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ConsumeVirtualGoodRequest")
				{

				}
			


			/// <summary>
			/// The amount of virtual goods to be consumed
			/// </summary>
			ConsumeVirtualGoodRequest& SetQuantity( long quantity )
			{
				m_Request.AddNumber("quantity", quantity);
				return *this;
			}
			/// <summary>
			/// The short code of the virtual good to be consumed
			/// </summary>
			ConsumeVirtualGoodRequest& SetShortCode( const gsstl::string& shortCode )
			{
				m_Request.AddString("shortCode", shortCode);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Issues a challenge to a group of players from the currently signed in player.
			The endTime field must be present unless the challenge template has an achievement set in the 'First to Achievement' field.
			The usersToChallenge field must be present for this request if the acessType is PRIVATE (which is the default).
			*/
			class CreateChallengeRequest : public GameSparks::Core::GSTypedRequest < CreateChallengeRequest, GameSparks::Api::Responses::CreateChallengeResponse >
			{
			public:
				CreateChallengeRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".CreateChallengeRequest")
				{

				}
			


			/// <summary>
			/// Who can join this challenge. Either PUBLIC, PRIVATE or FRIENDS
			/// </summary>
			CreateChallengeRequest& SetAccessType( const gsstl::string& accessType )
			{
				m_Request.AddString("accessType", accessType);
				return *this;
			}
			/// <summary>
			/// Whether this challenge should automatically start when a new player joins and maxPlayers is reached
			/// </summary>
			CreateChallengeRequest& SetAutoStartJoinedChallengeOnMaxPlayers( bool autoStartJoinedChallengeOnMaxPlayers )
			{
				m_Request.AddBoolean("autoStartJoinedChallengeOnMaxPlayers", autoStartJoinedChallengeOnMaxPlayers);
				return *this;
			}
			/// <summary>
			/// An optional message to include with the challenge
			/// </summary>
			CreateChallengeRequest& SetChallengeMessage( const gsstl::string& challengeMessage )
			{
				m_Request.AddString("challengeMessage", challengeMessage);
				return *this;
			}
			/// <summary>
			/// The short code of the challenge
			/// </summary>
			CreateChallengeRequest& SetChallengeShortCode( const gsstl::string& challengeShortCode )
			{
				m_Request.AddString("challengeShortCode", challengeShortCode);
				return *this;
			}
			/// <summary>
			/// The ammount of currency type 1 that the player is wagering on this challenge
			/// </summary>
			CreateChallengeRequest& SetCurrency1Wager( long currency1Wager )
			{
				m_Request.AddNumber("currency1Wager", currency1Wager);
				return *this;
			}
			/// <summary>
			/// The amount of currency type 2 that the player is wagering on this challenge
			/// </summary>
			CreateChallengeRequest& SetCurrency2Wager( long currency2Wager )
			{
				m_Request.AddNumber("currency2Wager", currency2Wager);
				return *this;
			}
			/// <summary>
			/// The amount of currency type 3 that the player is wagering on this challenge
			/// </summary>
			CreateChallengeRequest& SetCurrency3Wager( long currency3Wager )
			{
				m_Request.AddNumber("currency3Wager", currency3Wager);
				return *this;
			}
			/// <summary>
			/// The amount of currency type 4 that the player is wagering on this challenge
			/// </summary>
			CreateChallengeRequest& SetCurrency4Wager( long currency4Wager )
			{
				m_Request.AddNumber("currency4Wager", currency4Wager);
				return *this;
			}
			/// <summary>
			/// The amount of currency type 5 that the player is wagering on this challenge
			/// </summary>
			CreateChallengeRequest& SetCurrency5Wager( long currency5Wager )
			{
				m_Request.AddNumber("currency5Wager", currency5Wager);
				return *this;
			}
			/// <summary>
			/// The amount of currency type 6 that the player is wagering on this challenge
			/// </summary>
			CreateChallengeRequest& SetCurrency6Wager( long currency6Wager )
			{
				m_Request.AddNumber("currency6Wager", currency6Wager);
				return *this;
			}
			/// <summary>
			/// Criteria for who can and cannot find and join this challenge (when the accessType is PUBLIC or FRIENDS).
			/// Currently supports a field <i>segments</i> that contains segment type against single (where that segment value is required) or multiple (where one of the specified values is required) segment values.
			/// For each segment type a player must have one of the specified values in order to be considered eligible.
			/// </summary>
			CreateChallengeRequest& SetEligibilityCriteria( const GameSparks::Core::GSRequestData& eligibilityCriteria )
			{
				m_Request.AddObject("eligibilityCriteria", eligibilityCriteria);
				return *this;
			}
			/// <summary>
			/// The time at which this challenge will end
			/// </summary>
			CreateChallengeRequest& SetEndTime( const GameSparks::Core::GSDateTime& endTime )
			{
				m_Request.AddDate("endTime", endTime);
				return *this;
			}
			/// <summary>
			/// The latest time that players can join this challenge
			/// </summary>
			CreateChallengeRequest& SetExpiryTime( const GameSparks::Core::GSDateTime& expiryTime )
			{
				m_Request.AddDate("expiryTime", expiryTime);
				return *this;
			}
			/// <summary>
			/// The maximum number of attempts 
			/// </summary>
			CreateChallengeRequest& SetMaxAttempts( long maxAttempts )
			{
				m_Request.AddNumber("maxAttempts", maxAttempts);
				return *this;
			}
			/// <summary>
			/// The maximum number of players that are allowed to join this challenge
			/// </summary>
			CreateChallengeRequest& SetMaxPlayers( long maxPlayers )
			{
				m_Request.AddNumber("maxPlayers", maxPlayers);
				return *this;
			}
			/// <summary>
			/// The minimum number of players that are allowed to join this challenge
			/// </summary>
			CreateChallengeRequest& SetMinPlayers( long minPlayers )
			{
				m_Request.AddNumber("minPlayers", minPlayers);
				return *this;
			}
			/// <summary>
			/// If True  no messaging is triggered
			/// </summary>
			CreateChallengeRequest& SetSilent( bool silent )
			{
				m_Request.AddBoolean("silent", silent);
				return *this;
			}
			/// <summary>
			/// The time at which this challenge will begin
			/// </summary>
			CreateChallengeRequest& SetStartTime( const GameSparks::Core::GSDateTime& startTime )
			{
				m_Request.AddDate("startTime", startTime);
				return *this;
			}
			/// <summary>
			/// A player id or an array of player ids who will recieve this challenge
			/// </summary>
			CreateChallengeRequest& SetUsersToChallenge( gsstl::vector<gsstl::string> usersToChallenge )
			{
				m_Request.AddStringList("usersToChallenge", usersToChallenge);
				return *this;
			}
			};
			
			/*!
			\ingroup Teams
			Allows a new team to be created.
			*/
			class CreateTeamRequest : public GameSparks::Core::GSTypedRequest < CreateTeamRequest, GameSparks::Api::Responses::CreateTeamResponse >
			{
			public:
				CreateTeamRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".CreateTeamRequest")
				{

				}
			


			/// <summary>
			/// An optional teamId to use
			/// </summary>
			CreateTeamRequest& SetTeamId( const gsstl::string& teamId )
			{
				m_Request.AddString("teamId", teamId);
				return *this;
			}
			/// <summary>
			/// A display name to use
			/// </summary>
			CreateTeamRequest& SetTeamName( const gsstl::string& teamName )
			{
				m_Request.AddString("teamName", teamName);
				return *this;
			}
			/// <summary>
			/// The type of team to be created
			/// </summary>
			CreateTeamRequest& SetTeamType( const gsstl::string& teamType )
			{
				m_Request.AddString("teamType", teamType);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Declines a challenge that has been issued to the current player.
			*/
			class DeclineChallengeRequest : public GameSparks::Core::GSTypedRequest < DeclineChallengeRequest, GameSparks::Api::Responses::DeclineChallengeResponse >
			{
			public:
				DeclineChallengeRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".DeclineChallengeRequest")
				{

				}
			


			/// <summary>
			/// The ID of the challenge
			/// </summary>
			DeclineChallengeRequest& SetChallengeInstanceId( const gsstl::string& challengeInstanceId )
			{
				m_Request.AddString("challengeInstanceId", challengeInstanceId);
				return *this;
			}
			/// <summary>
			/// An optional message to send with the challenge
			/// </summary>
			DeclineChallengeRequest& SetMessage( const gsstl::string& message )
			{
				m_Request.AddString("message", message);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows a device id to be used to create an anonymous profile in the game.
			This allows the player to be tracked and have data stored against them before using FacebookConnectRequest to create a full profile.
			DeviceAuthenticationRequest should not be used in conjunction with RegistrationRequest as the two accounts will not be merged.
			*/
			class DeviceAuthenticationRequest : public GameSparks::Core::GSTypedRequest < DeviceAuthenticationRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				DeviceAuthenticationRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".DeviceAuthenticationRequest")
				{

				}
			


			/// <summary>
			/// A unique device identifier. Each platform has it's own method for getting a unique id
			/// </summary>
			DeviceAuthenticationRequest& SetDeviceId( const gsstl::string& deviceId )
			{
				m_Request.AddString("deviceId", deviceId);
				return *this;
			}
			/// <summary>
			/// The device model
			/// </summary>
			DeviceAuthenticationRequest& SetDeviceModel( const gsstl::string& deviceModel )
			{
				m_Request.AddString("deviceModel", deviceModel);
				return *this;
			}
			/// <summary>
			/// The device name
			/// </summary>
			DeviceAuthenticationRequest& SetDeviceName( const gsstl::string& deviceName )
			{
				m_Request.AddString("deviceName", deviceName);
				return *this;
			}
			/// <summary>
			/// An indicator of the device platform, should be IOS, ANDROID, WP8 or W8
			/// </summary>
			DeviceAuthenticationRequest& SetDeviceOS( const gsstl::string& deviceOS )
			{
				m_Request.AddString("deviceOS", deviceOS);
				return *this;
			}
			/// <summary>
			/// The device type
			/// </summary>
			DeviceAuthenticationRequest& SetDeviceType( const gsstl::string& deviceType )
			{
				m_Request.AddString("deviceType", deviceType);
				return *this;
			}
			/// <summary>
			/// An optional displayname for the player
			/// </summary>
			DeviceAuthenticationRequest& SetDisplayName( const gsstl::string& displayName )
			{
				m_Request.AddString("displayName", displayName);
				return *this;
			}
			/// <summary>
			/// The device type
			/// </summary>
			DeviceAuthenticationRequest& SetOperatingSystem( const gsstl::string& operatingSystem )
			{
				m_Request.AddString("operatingSystem", operatingSystem);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request reates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			DeviceAuthenticationRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			};
			
			/*!
			\ingroup Player
			Allows a message to be dismissed. Once dismissed the message will no longer appear in either ListMessageResponse or ListMessageSummaryResponse.
			*/
			class DismissMessageRequest : public GameSparks::Core::GSTypedRequest < DismissMessageRequest, GameSparks::Api::Responses::DismissMessageResponse >
			{
			public:
				DismissMessageRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".DismissMessageRequest")
				{

				}
			


			/// <summary>
			/// The messageId of the message to dismiss
			/// </summary>
			DismissMessageRequest& SetMessageId( const gsstl::string& messageId )
			{
				m_Request.AddString("messageId", messageId);
				return *this;
			}
			};
			
			/*!
			\ingroup Teams
			Allows a player to drop a team.
			*/
			class DropTeamRequest : public GameSparks::Core::GSTypedRequest < DropTeamRequest, GameSparks::Api::Responses::DropTeamResponse >
			{
			public:
				DropTeamRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".DropTeamRequest")
				{

				}
			


			/// <summary>
			/// The team owner to find, used in combination with teamType. If not supplied the current players id will be used
			/// </summary>
			DropTeamRequest& SetOwnerId( const gsstl::string& ownerId )
			{
				m_Request.AddString("ownerId", ownerId);
				return *this;
			}
			/// <summary>
			/// The teamId to find (may be null if teamType supplied)
			/// </summary>
			DropTeamRequest& SetTeamId( const gsstl::string& teamId )
			{
				m_Request.AddString("teamId", teamId);
				return *this;
			}
			/// <summary>
			/// The teamType to find, used in combination with the current player, or the player defined by ownerId
			/// </summary>
			DropTeamRequest& SetTeamType( const gsstl::string& teamType )
			{
				m_Request.AddString("teamType", teamType);
				return *this;
			}
			};
			
			/*!
			\ingroup Analytics
			Records the end of the current player's active session.
			The SDK will automatically create a new session ID when the application is started, this method can be useful to call when the app goes into the background to allow reporting on player session length.
			*/
			class EndSessionRequest : public GameSparks::Core::GSTypedRequest < EndSessionRequest, GameSparks::Api::Responses::EndSessionResponse >
			{
			public:
				EndSessionRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".EndSessionRequest")
				{

				}
			


			};
			
			/*!
			\ingroup Authentication
			Allows either a Facebook access token, or a Facebook authorization code to be used as an authentication mechanism.
			Once authenticated the platform can determine the current players details from the Facebook platform and store them within GameSparks.
			GameSparks will determine the player's friends and whether any of them are currently registered with the game.
			If the Facebook user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthenticationRequest or RegistrationRequest AND the Facebook user is not already registered with the game, the Facebook user will be linked to the current player.
			If the current player has not authenticated and the Facebook user is not known, a new player will be created using the Facebook details and the session will be authenticated against the new player.
			If the Facebook user is already known, the session will switch to being the previously created user.
			*/
			class FacebookConnectRequest : public GameSparks::Core::GSTypedRequest < FacebookConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				FacebookConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".FacebookConnectRequest")
				{

				}
			


			/// <summary>
			/// The access token is used by the client to make authenticated requests on behalf of the end user.
			/// It has a longer lifetime than the authorization code, typically on the order of minutes or hours.
			/// When the access token expires, attempts to use it will fail, and a new access token must be obtained via a refresh token.
			/// </summary>
			FacebookConnectRequest& SetAccessToken( const gsstl::string& accessToken )
			{
				m_Request.AddString("accessToken", accessToken);
				return *this;
			}
			/// <summary>
			/// An authorization code is a short-lived token representing the user's access grant, created by the authorization server and passed to the client application via the browser.
			/// The client application sends the authorization code to the authorization server to obtain an access token and, optionally, a refresh token.
			/// </summary>
			FacebookConnectRequest& SetCode( const gsstl::string& code )
			{
				m_Request.AddString("code", code);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			FacebookConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			FacebookConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			FacebookConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			FacebookConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			FacebookConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Allows a player to find challenges that they are eligible to join.
			*/
			class FindChallengeRequest : public GameSparks::Core::GSTypedRequest < FindChallengeRequest, GameSparks::Api::Responses::FindChallengeResponse >
			{
			public:
				FindChallengeRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".FindChallengeRequest")
				{

				}
			


			/// <summary>
			/// The type of challenge to find, either PUBLIC or FRIENDS.  Defaults to FRIENDS
			/// </summary>
			FindChallengeRequest& SetAccessType( const gsstl::string& accessType )
			{
				m_Request.AddString("accessType", accessType);
				return *this;
			}
			/// <summary>
			/// The number of challenges to return (MAX=50)
			/// </summary>
			FindChallengeRequest& SetCount( long count )
			{
				m_Request.AddNumber("count", count);
				return *this;
			}
			/// <summary>
			/// Optional.  Allows the current player's eligibility to be overridden by what is provided here.
			/// </summary>
			FindChallengeRequest& SetEligibility( const GameSparks::Core::GSRequestData& eligibility )
			{
				m_Request.AddObject("eligibility", eligibility);
				return *this;
			}
			/// <summary>
			/// The offset to start from when returning challenges (used for paging)
			/// </summary>
			FindChallengeRequest& SetOffset( long offset )
			{
				m_Request.AddNumber("offset", offset);
				return *this;
			}
			/// <summary>
			/// Optional shortCodes to filter the results by challenge type
			/// </summary>
			FindChallengeRequest& SetShortCode( gsstl::vector<gsstl::string> shortCode )
			{
				m_Request.AddStringList("shortCode", shortCode);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			@Deprecated. Use MatchmakingRequest instead.
			Find a match for this player, using the given skill and matchShortCode.
			Players looking for a match using the same matchShortCode will be considered for a match, based on the matchConfig.
			Each player must match the other for the match to be found.
			*/
			class FindMatchRequest : public GameSparks::Core::GSTypedRequest < FindMatchRequest, GameSparks::Api::Responses::FindMatchResponse >
			{
			public:
				FindMatchRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".FindMatchRequest")
				{

				}
			


			/// <summary>
			/// The action to take on the already in-flight request for this match. Currently supported actions are: 'cancel'
			/// </summary>
			FindMatchRequest& SetAction( const gsstl::string& action )
			{
				m_Request.AddString("action", action);
				return *this;
			}
			/// <summary>
			/// Optional. Players will be grouped based on the distinct value passed in here, only players in the same group can be matched together
			/// </summary>
			FindMatchRequest& SetMatchGroup( const gsstl::string& matchGroup )
			{
				m_Request.AddString("matchGroup", matchGroup);
				return *this;
			}
			/// <summary>
			/// The shortCode of the match type this player is registering for
			/// </summary>
			FindMatchRequest& SetMatchShortCode( const gsstl::string& matchShortCode )
			{
				m_Request.AddString("matchShortCode", matchShortCode);
				return *this;
			}
			/// <summary>
			/// The skill of the player looking for a match
			/// </summary>
			FindMatchRequest& SetSkill( long skill )
			{
				m_Request.AddNumber("skill", skill);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Find other pending matches that will match this player's previously submitted MatchmakingRequest.
			Used for manual matching of players, where you want control over which pending match should be chosen.
			Each player must match the other for the pending match to be found.
			*/
			class FindPendingMatchesRequest : public GameSparks::Core::GSTypedRequest < FindPendingMatchesRequest, GameSparks::Api::Responses::FindPendingMatchesResponse >
			{
			public:
				FindPendingMatchesRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".FindPendingMatchesRequest")
				{

				}
			


			/// <summary>
			/// Optional. The matchGroup of the match this player previously registeredfor
			/// </summary>
			FindPendingMatchesRequest& SetMatchGroup( const gsstl::string& matchGroup )
			{
				m_Request.AddString("matchGroup", matchGroup);
				return *this;
			}
			/// <summary>
			/// The shortCode of the match this player previously registered for
			/// </summary>
			FindPendingMatchesRequest& SetMatchShortCode( const gsstl::string& matchShortCode )
			{
				m_Request.AddString("matchShortCode", matchShortCode);
				return *this;
			}
			/// <summary>
			/// Optional. The maximum number of pending matches to return (default=10)
			/// </summary>
			FindPendingMatchesRequest& SetMaxMatchesToFind( long maxMatchesToFind )
			{
				m_Request.AddNumber("maxMatchesToFind", maxMatchesToFind);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows an Apple account that has GameCenter to be used as an authentication mechanism.
			The request must supply the GameCenter user details, such as the player id and username.
			If the GameCenter user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthentictionRequest or RegistrationRequest AND the GameCenter user is not already registered with the game, the GameCenter user will be linked to the current player.
			If the current player has not authenticated and the GameCenter user is not known, a new player will be created using the GameCenter details and the session will be authenticated against the new player.
			If the GameCenter user is already known, the session will switch to being the previously created user.
			This API call requires the output details from GKLocalPlayer.generateIdentityVerificationSignatureWithCompletionHandler on your iOS device
			*/
			class GameCenterConnectRequest : public GameSparks::Core::GSTypedRequest < GameCenterConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				GameCenterConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GameCenterConnectRequest")
				{

				}
			


			/// <summary>
			/// The display of the current player from GameCenter. This will be used as the displayName of the gamesparks player if created (or syncDisplayname is true)
			/// </summary>
			GameCenterConnectRequest& SetDisplayName( const gsstl::string& displayName )
			{
				m_Request.AddString("displayName", displayName);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			GameCenterConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			GameCenterConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// The game center id of the current player. This value obtained be obtained from GKLocalPlayer playerID
			/// </summary>
			GameCenterConnectRequest& SetExternalPlayerId( const gsstl::string& externalPlayerId )
			{
				m_Request.AddString("externalPlayerId", externalPlayerId);
				return *this;
			}
			/// <summary>
			/// The url from where we will download the public key. This value should be obtained from generateIdentityVerificationSignatureWithCompletionHandler. 
			/// </summary>
			GameCenterConnectRequest& SetPublicKeyUrl( const gsstl::string& publicKeyUrl )
			{
				m_Request.AddString("publicKeyUrl", publicKeyUrl);
				return *this;
			}
			/// <summary>
			/// The salt is needed in order to prevent request forgery. This value should be obtained from generateIdentityVerificationSignatureWithCompletionHandler and should be base64 encoded using [salt base64Encoding]
			/// </summary>
			GameCenterConnectRequest& SetSalt( const gsstl::string& salt )
			{
				m_Request.AddString("salt", salt);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			GameCenterConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// The signature is needed to validate that the request is genuine and that we can save the player. This value should be obtained from generateIdentityVerificationSignatureWithCompletionHandler and should be base64 encoded using [signature base64Encoding]
			/// </summary>
			GameCenterConnectRequest& SetSignature( const gsstl::string& signature )
			{
				m_Request.AddString("signature", signature);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			GameCenterConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			GameCenterConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
			}
			/// <summary>
			/// The timestamp is needed to validate the request signature. This value should be obtained from generateIdentityVerificationSignatureWithCompletionHandler
			/// </summary>
			GameCenterConnectRequest& SetTimestamp( long timestamp )
			{
				m_Request.AddNumber("timestamp", timestamp);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Gets the details of a challenge. The current player must be involved in the challenge for the request to succeed.
			*/
			class GetChallengeRequest : public GameSparks::Core::GSTypedRequest < GetChallengeRequest, GameSparks::Api::Responses::GetChallengeResponse >
			{
			public:
				GetChallengeRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GetChallengeRequest")
				{

				}
			


			/// <summary>
			/// The ID of the challenge
			/// </summary>
			GetChallengeRequest& SetChallengeInstanceId( const gsstl::string& challengeInstanceId )
			{
				m_Request.AddString("challengeInstanceId", challengeInstanceId);
				return *this;
			}
			/// <summary>
			/// An optional message to send with the challenge
			/// </summary>
			GetChallengeRequest& SetMessage( const gsstl::string& message )
			{
				m_Request.AddString("message", message);
				return *this;
			}
			};
			
			/*!
			\ingroup Misc
			Returns a secure, time sensitive url to allow the game to download a piece of downloadable content stored in the GameSparks platform.
			*/
			class GetDownloadableRequest : public GameSparks::Core::GSTypedRequest < GetDownloadableRequest, GameSparks::Api::Responses::GetDownloadableResponse >
			{
			public:
				GetDownloadableRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GetDownloadableRequest")
				{

				}
			


			/// <summary>
			/// The short code of the Downloadable item
			/// </summary>
			GetDownloadableRequest& SetShortCode( const gsstl::string& shortCode )
			{
				m_Request.AddString("shortCode", shortCode);
				return *this;
			}
			};
			
			/*!
			\ingroup Leaderboards
			Get the leaderboard entry data for the current player or a given player. 
			For each leaderboard it returns the hichest score the player has
			*/
			class GetLeaderboardEntriesRequest : public GameSparks::Core::GSTypedRequest < GetLeaderboardEntriesRequest, GameSparks::Api::Responses::GetLeaderboardEntriesResponse >
			{
			public:
				GetLeaderboardEntriesRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GetLeaderboardEntriesRequest")
				{

				}
			


			/// <summary>
			/// The challenge leaderboards to return entries for
			/// </summary>
			GetLeaderboardEntriesRequest& SetChallenges( gsstl::vector<gsstl::string> challenges )
			{
				m_Request.AddStringList("challenges", challenges);
				return *this;
			}
			/// <summary>
			/// Returns the leaderboard excluding the player's social friends
			/// </summary>
			GetLeaderboardEntriesRequest& SetInverseSocial( bool inverseSocial )
			{
				m_Request.AddBoolean("inverseSocial", inverseSocial);
				return *this;
			}
			/// <summary>
			/// The list of leaderboards shortcodes
			/// </summary>
			GetLeaderboardEntriesRequest& SetLeaderboards( gsstl::vector<gsstl::string> leaderboards )
			{
				m_Request.AddStringList("leaderboards", leaderboards);
				return *this;
			}
			/// <summary>
			/// The player id. Leave out to use the current player id
			/// </summary>
			GetLeaderboardEntriesRequest& SetPlayer( const gsstl::string& player )
			{
				m_Request.AddString("player", player);
				return *this;
			}
			/// <summary>
			/// Set to true to include the player's game friends
			/// </summary>
			GetLeaderboardEntriesRequest& SetSocial( bool social )
			{
				m_Request.AddBoolean("social", social);
				return *this;
			}
			/// <summary>
			/// The types of team to apply this request to
			/// </summary>
			GetLeaderboardEntriesRequest& SetTeamTypes( gsstl::vector<gsstl::string> teamTypes )
			{
				m_Request.AddStringList("teamTypes", teamTypes);
				return *this;
			}
			};
			
			/*!
			\ingroup Player
			Returns the full details of a message.
			*/
			class GetMessageRequest : public GameSparks::Core::GSTypedRequest < GetMessageRequest, GameSparks::Api::Responses::GetMessageResponse >
			{
			public:
				GetMessageRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GetMessageRequest")
				{

				}
			


			/// <summary>
			/// The messageId of the message retreive
			/// </summary>
			GetMessageRequest& SetMessageId( const gsstl::string& messageId )
			{
				m_Request.AddString("messageId", messageId);
				return *this;
			}
			};
			
			/*!
			\ingroup Teams
			Get the teams that the player is in. Can be filtered on team type and also on those teams that the player owns.
			*/
			class GetMyTeamsRequest : public GameSparks::Core::GSTypedRequest < GetMyTeamsRequest, GameSparks::Api::Responses::GetMyTeamsResponse >
			{
			public:
				GetMyTeamsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GetMyTeamsRequest")
				{

				}
			


			/// <summary>
			/// Set to true to only get teams owned by the player
			/// </summary>
			GetMyTeamsRequest& SetOwnedOnly( bool ownedOnly )
			{
				m_Request.AddBoolean("ownedOnly", ownedOnly);
				return *this;
			}
			/// <summary>
			/// The type of teams to get
			/// </summary>
			GetMyTeamsRequest& SetTeamTypes( gsstl::vector<gsstl::string> teamTypes )
			{
				m_Request.AddStringList("teamTypes", teamTypes);
				return *this;
			}
			};
			
			/*!
			\ingroup Misc
			Get the property for the given short Code.
			*/
			class GetPropertyRequest : public GameSparks::Core::GSTypedRequest < GetPropertyRequest, GameSparks::Api::Responses::GetPropertyResponse >
			{
			public:
				GetPropertyRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GetPropertyRequest")
				{

				}
			


			/// <summary>
			/// The shortCode of the property to return.
			/// </summary>
			GetPropertyRequest& SetPropertyShortCode( const gsstl::string& propertyShortCode )
			{
				m_Request.AddString("propertyShortCode", propertyShortCode);
				return *this;
			}
			};
			
			/*!
			\ingroup Misc
			Get the property set for the given short Code.
			*/
			class GetPropertySetRequest : public GameSparks::Core::GSTypedRequest < GetPropertySetRequest, GameSparks::Api::Responses::GetPropertySetResponse >
			{
			public:
				GetPropertySetRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GetPropertySetRequest")
				{

				}
			


			/// <summary>
			/// The shortCode of the property set to return.
			/// </summary>
			GetPropertySetRequest& SetPropertySetShortCode( const gsstl::string& propertySetShortCode )
			{
				m_Request.AddString("propertySetShortCode", propertySetShortCode);
				return *this;
			}
			};
			
			/*!
			\ingroup Teams
			Allows the details of a team to be retrieved.
			*/
			class GetTeamRequest : public GameSparks::Core::GSTypedRequest < GetTeamRequest, GameSparks::Api::Responses::GetTeamResponse >
			{
			public:
				GetTeamRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GetTeamRequest")
				{

				}
			


			/// <summary>
			/// The team owner to find, used in combination with teamType. If not supplied the current players id will be used
			/// </summary>
			GetTeamRequest& SetOwnerId( const gsstl::string& ownerId )
			{
				m_Request.AddString("ownerId", ownerId);
				return *this;
			}
			/// <summary>
			/// The teamId to find (may be null if teamType supplied)
			/// </summary>
			GetTeamRequest& SetTeamId( const gsstl::string& teamId )
			{
				m_Request.AddString("teamId", teamId);
				return *this;
			}
			/// <summary>
			/// The teamType to find, used in combination with the current player, or the player defined by ownerId
			/// </summary>
			GetTeamRequest& SetTeamType( const gsstl::string& teamType )
			{
				m_Request.AddString("teamType", teamType);
				return *this;
			}
			};
			
			/*!
			\ingroup Misc
			Returns a secure, time sensitive URL to allow the game to upload a piece of player content to the GameSparks platform.
			*/
			class GetUploadUrlRequest : public GameSparks::Core::GSTypedRequest < GetUploadUrlRequest, GameSparks::Api::Responses::GetUploadUrlResponse >
			{
			public:
				GetUploadUrlRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GetUploadUrlRequest")
				{

				}
			


			/// <summary>
			/// Optional meta data which is stored against the player's uploaded content
			/// </summary>
			GetUploadUrlRequest& SetUploadData( const GameSparks::Core::GSRequestData& uploadData )
			{
				m_Request.AddObject("uploadData", uploadData);
				return *this;
			}
			};
			
			/*!
			\ingroup Misc
			Returns a secure, time sensitive URL to a piece of content that was previously uploaded to the GameSparks platform by a player.
			*/
			class GetUploadedRequest : public GameSparks::Core::GSTypedRequest < GetUploadedRequest, GameSparks::Api::Responses::GetUploadedResponse >
			{
			public:
				GetUploadedRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GetUploadedRequest")
				{

				}
			


			/// <summary>
			/// The system generated id of the uploaded item
			/// </summary>
			GetUploadedRequest& SetUploadId( const gsstl::string& uploadId )
			{
				m_Request.AddString("uploadId", uploadId);
				return *this;
			}
			};
			
			/*!
			\ingroup Store
			Processes the response from a Google Play in app purchase flow.
			The GameSparks platform will validate the signature and signed data with the Google Play Public Key configured against the game.
			The orderId in the data will be recorded and the request will be rejected if the orderId has previously been processed, this prevents replay attacks.
			Once verfied, the players account will be credited with the Virtual Good, or Virtual Currency the purchase contains. The virtual good will be looked up by matching the productId in the signed data with the 'Google Product ID' configured against the virtual good.
			It is critical that the signedData is sent exactly as it is returned form google, including any whitespace. Any modification of the signedData will cause the verification process to fail.
			*/
			class GooglePlayBuyGoodsRequest : public GameSparks::Core::GSTypedRequest < GooglePlayBuyGoodsRequest, GameSparks::Api::Responses::BuyVirtualGoodResponse >
			{
			public:
				GooglePlayBuyGoodsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GooglePlayBuyGoodsRequest")
				{

				}
			


			/// <summary>
			/// The value obtained from data.getStringExtra("INAPP_DATA_SIGNATURE");
			/// </summary>
			GooglePlayBuyGoodsRequest& SetSignature( const gsstl::string& signature )
			{
				m_Request.AddString("signature", signature);
				return *this;
			}
			/// <summary>
			/// The value obtained from data.getStringExtra("INAPP_PURCHASE_DATA")
			/// </summary>
			GooglePlayBuyGoodsRequest& SetSignedData( const gsstl::string& signedData )
			{
				m_Request.AddString("signedData", signedData);
				return *this;
			}
			/// <summary>
			/// If set to true, the transactionId from this receipt will not be globally valdidated, this will mean replays between players are possible.
			/// It will only validate the transactionId has not been used by this player before.
			/// </summary>
			GooglePlayBuyGoodsRequest& SetUniqueTransactionByPlayer( bool uniqueTransactionByPlayer )
			{
				m_Request.AddBoolean("uniqueTransactionByPlayer", uniqueTransactionByPlayer);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows either a Google Play access code or an access token to be used as an authentication mechanism.
			The access code needs to have at least the https://www.googleapis.com/auth/games scope.
			For more details about Google OAuth 2.0 scopes refer to this: https://developers.google.com/identity/protocols/googlescopes#gamesConfigurationv1configuration
			If the Google Play user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthentictionRequest or RegistrationRequest AND the Google Play user is not already registered with the game, the Google Play user will be linked to the current player.
			If the current player has not authenticated and the Google Play user is not known, a new player will be created using the Google Play details and the session will be authenticated against the new player.
			If the Google Play user is already known, the session will switch to being the previously created user.
			*/
			class GooglePlayConnectRequest : public GameSparks::Core::GSTypedRequest < GooglePlayConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				GooglePlayConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GooglePlayConnectRequest")
				{

				}
			


			/// <summary>
			/// The access token is used when using the service id and certificate.
			/// </summary>
			GooglePlayConnectRequest& SetAccessToken( const gsstl::string& accessToken )
			{
				m_Request.AddString("accessToken", accessToken);
				return *this;
			}
			/// <summary>
			/// The access code is used by the client to make authenticated requests on behalf of the end user. Requires clientId and clientsecret to be set
			/// </summary>
			GooglePlayConnectRequest& SetCode( const gsstl::string& code )
			{
				m_Request.AddString("code", code);
				return *this;
			}
			/// <summary>
			/// The display of the current player from Google Play. This will be used as the displayName of the gamesparks player if created (or syncDisplayname is true)
			/// </summary>
			GooglePlayConnectRequest& SetDisplayName( const gsstl::string& displayName )
			{
				m_Request.AddString("displayName", displayName);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			GooglePlayConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			GooglePlayConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// Did you request the plus.login scope when you got the access code or authorisation token from Google? If this is true, we will fetch the user's google+ account and friends
			/// </summary>
			GooglePlayConnectRequest& SetGooglePlusScope( bool googlePlusScope )
			{
				m_Request.AddBoolean("googlePlusScope", googlePlusScope);
				return *this;
			}
			/// <summary>
			/// Did you request the profile scope when you got the access code or authorisation token from Google? If this is true, we will fetch the user info by calling https://www.googleapis.com/oauth2/v1/userinfo?alt=json 
			/// </summary>
			GooglePlayConnectRequest& SetProfileScope( bool profileScope )
			{
				m_Request.AddBoolean("profileScope", profileScope);
				return *this;
			}
			/// <summary>
			/// Only required when the access code has been granted using an explicit redirectUri, for example when using the mechanism described in https://developers.google.com/+/web/signin/server-side-flow
			/// </summary>
			GooglePlayConnectRequest& SetRedirectUri( const gsstl::string& redirectUri )
			{
				m_Request.AddString("redirectUri", redirectUri);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			GooglePlayConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			GooglePlayConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			GooglePlayConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows either a Google Plus access code or an authentication token to be used as an authentication mechanism.
			Once authenticated the platform can determine the current players details from the Google Plus platform and store them within GameSparks.
			GameSparks will determine the player's friends and whether any of them are currently registered with the game.
			If the Google Plus user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthentictionRequest or RegistrationRequest AND the Google Plus user is not already registered with the game, the Google Plus user will be linked to the current player.
			If the current player has not authenticated and the Google Plus user is not known, a new player will be created using the Google Plus details and the session will be authenticated against the new player.
			If the Google Plus user is already known, the session will switch to being the previously created user.
			*/
			class GooglePlusConnectRequest : public GameSparks::Core::GSTypedRequest < GooglePlusConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				GooglePlusConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".GooglePlusConnectRequest")
				{

				}
			


			/// <summary>
			/// The access token is used when using the service id and certificate.
			/// </summary>
			GooglePlusConnectRequest& SetAccessToken( const gsstl::string& accessToken )
			{
				m_Request.AddString("accessToken", accessToken);
				return *this;
			}
			/// <summary>
			/// The access code is used by the client to make authenticated requests on behalf of the end user. Requires clientId and clientsecret to be set
			/// </summary>
			GooglePlusConnectRequest& SetCode( const gsstl::string& code )
			{
				m_Request.AddString("code", code);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			GooglePlusConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			GooglePlusConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// Only required when the access code has been granted using an explicit redirectUri, for example when using the mechanism described in https://developers.google.com/+/web/signin/server-side-flow
			/// </summary>
			GooglePlusConnectRequest& SetRedirectUri( const gsstl::string& redirectUri )
			{
				m_Request.AddString("redirectUri", redirectUri);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			GooglePlusConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			GooglePlusConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			GooglePlusConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
			}
			};
			
			/*!
			\ingroup Store
			Processes a transaction receipt from an App Store in app purchase.
			The GameSparks platform will validate the receipt with Apple and process the response. The transaction_id in the response will be recorded and the request will be rejected if the transaction_id has previously been processed, this prevents replay attacks.
			Once verified, the players account will be credited with the Virtual Good, or Virtual Currency the purchase contains. The virtual good will be looked up by matching the product_id in the response with the 'IOS Product ID' configured against the virtual good.
			*/
			class IOSBuyGoodsRequest : public GameSparks::Core::GSTypedRequest < IOSBuyGoodsRequest, GameSparks::Api::Responses::BuyVirtualGoodResponse >
			{
			public:
				IOSBuyGoodsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".IOSBuyGoodsRequest")
				{

				}
			


			/// <summary>
			/// The receipt obtained from SKPaymentTransaction. transactionReceipt
			/// </summary>
			IOSBuyGoodsRequest& SetReceipt( const gsstl::string& receipt )
			{
				m_Request.AddString("receipt", receipt);
				return *this;
			}
			/// <summary>
			/// Should the sandbox account be used
			/// </summary>
			IOSBuyGoodsRequest& SetSandbox( bool sandbox )
			{
				m_Request.AddBoolean("sandbox", sandbox);
				return *this;
			}
			/// <summary>
			/// If set to true, the transactionId from this receipt will not be globally valdidated, this will mean replays between players are possible.
			/// It will only validate the transactionId has not been used by this player before.
			/// </summary>
			IOSBuyGoodsRequest& SetUniqueTransactionByPlayer( bool uniqueTransactionByPlayer )
			{
				m_Request.AddBoolean("uniqueTransactionByPlayer", uniqueTransactionByPlayer);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Allows a player to join an open challenge.
			*/
			class JoinChallengeRequest : public GameSparks::Core::GSTypedRequest < JoinChallengeRequest, GameSparks::Api::Responses::JoinChallengeResponse >
			{
			public:
				JoinChallengeRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".JoinChallengeRequest")
				{

				}
			


			/// <summary>
			/// The ID of the challenge
			/// </summary>
			JoinChallengeRequest& SetChallengeInstanceId( const gsstl::string& challengeInstanceId )
			{
				m_Request.AddString("challengeInstanceId", challengeInstanceId);
				return *this;
			}
			/// <summary>
			/// Optional.  Allows the current player's eligibility to be overridden by what is provided here.
			/// </summary>
			JoinChallengeRequest& SetEligibility( const GameSparks::Core::GSRequestData& eligibility )
			{
				m_Request.AddObject("eligibility", eligibility);
				return *this;
			}
			/// <summary>
			/// An optional message to send with the challenge
			/// </summary>
			JoinChallengeRequest& SetMessage( const gsstl::string& message )
			{
				m_Request.AddString("message", message);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Requests to join a pending match (found via FindPendingMatchesRequest).
			*/
			class JoinPendingMatchRequest : public GameSparks::Core::GSTypedRequest < JoinPendingMatchRequest, GameSparks::Api::Responses::JoinPendingMatchResponse >
			{
			public:
				JoinPendingMatchRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".JoinPendingMatchRequest")
				{

				}
			


			/// <summary>
			/// Optional. The matchGroup of the match this player previously registeredfor
			/// </summary>
			JoinPendingMatchRequest& SetMatchGroup( const gsstl::string& matchGroup )
			{
				m_Request.AddString("matchGroup", matchGroup);
				return *this;
			}
			/// <summary>
			/// The shortCode of the match this player previously registered for
			/// </summary>
			JoinPendingMatchRequest& SetMatchShortCode( const gsstl::string& matchShortCode )
			{
				m_Request.AddString("matchShortCode", matchShortCode);
				return *this;
			}
			/// <summary>
			/// The pending match ID to join
			/// </summary>
			JoinPendingMatchRequest& SetPendingMatchId( const gsstl::string& pendingMatchId )
			{
				m_Request.AddString("pendingMatchId", pendingMatchId);
				return *this;
			}
			};
			
			/*!
			\ingroup Teams
			Allows a player to join a team of a team to be retrieved.
			*/
			class JoinTeamRequest : public GameSparks::Core::GSTypedRequest < JoinTeamRequest, GameSparks::Api::Responses::JoinTeamResponse >
			{
			public:
				JoinTeamRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".JoinTeamRequest")
				{

				}
			


			/// <summary>
			/// The team owner to find, used in combination with teamType. If not supplied the current players id will be used
			/// </summary>
			JoinTeamRequest& SetOwnerId( const gsstl::string& ownerId )
			{
				m_Request.AddString("ownerId", ownerId);
				return *this;
			}
			/// <summary>
			/// The teamId to find (may be null if teamType supplied)
			/// </summary>
			JoinTeamRequest& SetTeamId( const gsstl::string& teamId )
			{
				m_Request.AddString("teamId", teamId);
				return *this;
			}
			/// <summary>
			/// The teamType to find, used in combination with the current player, or the player defined by ownerId
			/// </summary>
			JoinTeamRequest& SetTeamType( const gsstl::string& teamType )
			{
				m_Request.AddString("teamType", teamType);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows a Kongregate account to be used as an authentication mechanism.
			Once authenticated the platform can determine the current players details from the Kongregate platform and store them within GameSparks.
			If the Kongregate user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthentictionRequest or RegistrationRequest AND the Kongregate user is not already registered with the game, the Kongregate user will be linked to the current player.
			If the current player has not authenticated and the Kongregate user is not known, a new player will be created using the Kongregate details and the session will be authenticated against the new player.
			If the Kongregate user is already known, the session will switch to being the previously created user.
			*/
			class KongregateConnectRequest : public GameSparks::Core::GSTypedRequest < KongregateConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				KongregateConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".KongregateConnectRequest")
				{

				}
			


			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			KongregateConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			KongregateConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// The gameAuthToken, together with the userID are used by the client to make authenticated requests on behalf of the end user.
			/// </summary>
			KongregateConnectRequest& SetGameAuthToken( const gsstl::string& gameAuthToken )
			{
				m_Request.AddString("gameAuthToken", gameAuthToken);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			KongregateConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			KongregateConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			KongregateConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
			}
			/// <summary>
			/// The userID, together with the gameAuthToken are used by the client to make authenticated requests on behalf of the end user.
			/// </summary>
			KongregateConnectRequest& SetUserId( const gsstl::string& userId )
			{
				m_Request.AddString("userId", userId);
				return *this;
			}
			};
			
			/*!
			\ingroup Leaderboards
			Returns the top data for either the specified global leaderboard or the specified challenges leaderboard. The data is sorted as defined in the rules specified in the leaderboard configuration.
			The response contains the top of the leaderboard, and returns the number of entries as defined in the entryCount parameter.
			If a shortCode is supplied, the response will contain the global leaderboard data. If a challengeInstanceId is supplied, the response will contain the leaderboard data for the challenge.
			*/
			class LeaderboardDataRequest : public GameSparks::Core::GSTypedRequest < LeaderboardDataRequest, GameSparks::Api::Responses::LeaderboardDataResponse >
			{
			public:
				LeaderboardDataRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".LeaderboardDataRequest")
				{

				}
			


			/// <summary>
			/// The challenge instance to get the leaderboard data for
			/// </summary>
			LeaderboardDataRequest& SetChallengeInstanceId( const gsstl::string& challengeInstanceId )
			{
				m_Request.AddString("challengeInstanceId", challengeInstanceId);
				return *this;
			}
			/// <summary>
			/// The default behaviour on a social request is to error if the player has no friends (NOTSOCIAL).  Set this flag to suppress that error and return the player's leaderboard entry instead.
			/// </summary>
			LeaderboardDataRequest& SetDontErrorOnNotSocial( bool dontErrorOnNotSocial )
			{
				m_Request.AddBoolean("dontErrorOnNotSocial", dontErrorOnNotSocial);
				return *this;
			}
			/// <summary>
			/// The number of items to return in a page (default=50)
			/// </summary>
			LeaderboardDataRequest& SetEntryCount( long entryCount )
			{
				m_Request.AddNumber("entryCount", entryCount);
				return *this;
			}
			/// <summary>
			/// A friend id or an array of friend ids to use instead of the player's social friends
			/// </summary>
			LeaderboardDataRequest& SetFriendIds( gsstl::vector<gsstl::string> friendIds )
			{
				m_Request.AddStringList("friendIds", friendIds);
				return *this;
			}
			/// <summary>
			/// Number of entries to include from head of the list
			/// </summary>
			LeaderboardDataRequest& SetIncludeFirst( long includeFirst )
			{
				m_Request.AddNumber("includeFirst", includeFirst);
				return *this;
			}
			/// <summary>
			/// Number of entries to include from tail of the list
			/// </summary>
			LeaderboardDataRequest& SetIncludeLast( long includeLast )
			{
				m_Request.AddNumber("includeLast", includeLast);
				return *this;
			}
			/// <summary>
			/// Returns the leaderboard excluding the player's social friends
			/// </summary>
			LeaderboardDataRequest& SetInverseSocial( bool inverseSocial )
			{
				m_Request.AddBoolean("inverseSocial", inverseSocial);
				return *this;
			}
			/// <summary>
			/// The short code of the leaderboard
			/// </summary>
			LeaderboardDataRequest& SetLeaderboardShortCode( const gsstl::string& leaderboardShortCode )
			{
				m_Request.AddString("leaderboardShortCode", leaderboardShortCode);
				return *this;
			}
			/// <summary>
			/// The offset into the set of leaderboards returned
			/// </summary>
			LeaderboardDataRequest& SetOffset( long offset )
			{
				m_Request.AddNumber("offset", offset);
				return *this;
			}
			/// <summary>
			/// If True returns a leaderboard of the player's social friends
			/// </summary>
			LeaderboardDataRequest& SetSocial( bool social )
			{
				m_Request.AddBoolean("social", social);
				return *this;
			}
			/// <summary>
			/// The IDs of the teams you are interested in
			/// </summary>
			LeaderboardDataRequest& SetTeamIds( gsstl::vector<gsstl::string> teamIds )
			{
				m_Request.AddStringList("teamIds", teamIds);
				return *this;
			}
			/// <summary>
			/// The type of team you are interested in
			/// </summary>
			LeaderboardDataRequest& SetTeamTypes( gsstl::vector<gsstl::string> teamTypes )
			{
				m_Request.AddStringList("teamTypes", teamTypes);
				return *this;
			}
			};
			
			/*!
			\ingroup Leaderboards
			Get the leaderboard entry data for the current player or a given player.
			For each leaderboard it returns the array of leaderboard entries that the player has.
			*/
			class LeaderboardsEntriesRequest : public GameSparks::Core::GSTypedRequest < LeaderboardsEntriesRequest, GameSparks::Api::Responses::LeaderboardsEntriesResponse >
			{
			public:
				LeaderboardsEntriesRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".LeaderboardsEntriesRequest")
				{

				}
			


			/// <summary>
			/// The challenge leaderboards to return entries for
			/// </summary>
			LeaderboardsEntriesRequest& SetChallenges( gsstl::vector<gsstl::string> challenges )
			{
				m_Request.AddStringList("challenges", challenges);
				return *this;
			}
			/// <summary>
			/// Returns the leaderboard excluding the player's social friends
			/// </summary>
			LeaderboardsEntriesRequest& SetInverseSocial( bool inverseSocial )
			{
				m_Request.AddBoolean("inverseSocial", inverseSocial);
				return *this;
			}
			/// <summary>
			/// The list of leaderboards shortcodes
			/// </summary>
			LeaderboardsEntriesRequest& SetLeaderboards( gsstl::vector<gsstl::string> leaderboards )
			{
				m_Request.AddStringList("leaderboards", leaderboards);
				return *this;
			}
			/// <summary>
			/// The player id. Leave out to use the current player id
			/// </summary>
			LeaderboardsEntriesRequest& SetPlayer( const gsstl::string& player )
			{
				m_Request.AddString("player", player);
				return *this;
			}
			/// <summary>
			/// Set to true to include the player's game friends
			/// </summary>
			LeaderboardsEntriesRequest& SetSocial( bool social )
			{
				m_Request.AddBoolean("social", social);
				return *this;
			}
			/// <summary>
			/// The types of team to apply this request to
			/// </summary>
			LeaderboardsEntriesRequest& SetTeamTypes( gsstl::vector<gsstl::string> teamTypes )
			{
				m_Request.AddStringList("teamTypes", teamTypes);
				return *this;
			}
			};
			
			/*!
			\ingroup Teams
			Allows a player to leave a team.
			*/
			class LeaveTeamRequest : public GameSparks::Core::GSTypedRequest < LeaveTeamRequest, GameSparks::Api::Responses::LeaveTeamResponse >
			{
			public:
				LeaveTeamRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".LeaveTeamRequest")
				{

				}
			


			/// <summary>
			/// The team owner to find, used in combination with teamType. If not supplied the current players id will be used
			/// </summary>
			LeaveTeamRequest& SetOwnerId( const gsstl::string& ownerId )
			{
				m_Request.AddString("ownerId", ownerId);
				return *this;
			}
			/// <summary>
			/// The teamId to find (may be null if teamType supplied)
			/// </summary>
			LeaveTeamRequest& SetTeamId( const gsstl::string& teamId )
			{
				m_Request.AddString("teamId", teamId);
				return *this;
			}
			/// <summary>
			/// The teamType to find, used in combination with the current player, or the player defined by ownerId
			/// </summary>
			LeaveTeamRequest& SetTeamType( const gsstl::string& teamType )
			{
				m_Request.AddString("teamType", teamType);
				return *this;
			}
			};
			
			/*!
			\ingroup Player
			Retrieves a list of the configured achievements in the game, along with whether the current player has earned the achievement.
			*/
			class ListAchievementsRequest : public GameSparks::Core::GSTypedRequest < ListAchievementsRequest, GameSparks::Api::Responses::ListAchievementsResponse >
			{
			public:
				ListAchievementsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ListAchievementsRequest")
				{

				}
			


			};
			
			/*!
			\ingroup Admin
			Lists existing bulk jobs.
			*/
			class ListBulkJobsAdminRequest : public GameSparks::Core::GSTypedRequest < ListBulkJobsAdminRequest, GameSparks::Api::Responses::ListBulkJobsAdminResponse >
			{
			public:
				ListBulkJobsAdminRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ListBulkJobsAdminRequest")
				{

				}
			


			/// <summary>
			/// The IDs of existing bulk jobs to get details for
			/// </summary>
			ListBulkJobsAdminRequest& SetBulkJobIds( gsstl::vector<gsstl::string> bulkJobIds )
			{
				m_Request.AddStringList("bulkJobIds", bulkJobIds);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Returns a list of challenges in the state defined in the 'state' field.
			The response can be further filtered by passing a shortCode field which will limit the returned lists to challenges of that short code.
			Valid states are:
			WAITING : The challenge has been issued and accepted and is waiting for the start date.
			RUNNING : The challenge is active.
			ISSUED : The challenge has been issued by the current player and is waiting to be accepted.
			RECEIVED : The challenge has been issued to the current player and is waiting to be accepted.
			COMPLETE : The challenge has completed.
			DECLINED : The challenge has been issued by the current player and has been declined.
			*/
			class ListChallengeRequest : public GameSparks::Core::GSTypedRequest < ListChallengeRequest, GameSparks::Api::Responses::ListChallengeResponse >
			{
			public:
				ListChallengeRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ListChallengeRequest")
				{

				}
			


			/// <summary>
			/// The number of items to return in a page (default=50)
			/// </summary>
			ListChallengeRequest& SetEntryCount( long entryCount )
			{
				m_Request.AddNumber("entryCount", entryCount);
				return *this;
			}
			/// <summary>
			/// The offset (page number) to start from (default=0)
			/// </summary>
			ListChallengeRequest& SetOffset( long offset )
			{
				m_Request.AddNumber("offset", offset);
				return *this;
			}
			/// <summary>
			/// The type of challenge to return
			/// </summary>
			ListChallengeRequest& SetShortCode( const gsstl::string& shortCode )
			{
				m_Request.AddString("shortCode", shortCode);
				return *this;
			}
			/// <summary>
			/// The state of the challenged to be returned
			/// </summary>
			ListChallengeRequest& SetState( const gsstl::string& state )
			{
				m_Request.AddString("state", state);
				return *this;
			}
			/// <summary>
			/// The states of the challenges to be returned
			/// </summary>
			ListChallengeRequest& SetStates( gsstl::vector<gsstl::string> states )
			{
				m_Request.AddStringList("states", states);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Returns the list of configured challenge types.
			*/
			class ListChallengeTypeRequest : public GameSparks::Core::GSTypedRequest < ListChallengeTypeRequest, GameSparks::Api::Responses::ListChallengeTypeResponse >
			{
			public:
				ListChallengeTypeRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ListChallengeTypeRequest")
				{

				}
			


			};
			
			/*!
			\ingroup Player
			Returns the list of the current players game friends.
			A Game friend is someone in their social network who also plays the game.
			Against each friend, an indicator is supplied to show whether the friend is currently connected to the GameSparks service
			*/
			class ListGameFriendsRequest : public GameSparks::Core::GSTypedRequest < ListGameFriendsRequest, GameSparks::Api::Responses::ListGameFriendsResponse >
			{
			public:
				ListGameFriendsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ListGameFriendsRequest")
				{

				}
			


			};
			
			/*!
			\ingroup Player
			Returns the list of the current players friends in their social network, who are not yet playing this game.
			This is dependent on the security and privacy policies of the social network.
			For example, Facebook's policies prevent this friend list being provided, whereas Twitter will supply a list of users who are not playing the game.
			*/
			class ListInviteFriendsRequest : public GameSparks::Core::GSTypedRequest < ListInviteFriendsRequest, GameSparks::Api::Responses::ListInviteFriendsResponse >
			{
			public:
				ListInviteFriendsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ListInviteFriendsRequest")
				{

				}
			


			};
			
			/*!
			\ingroup Leaderboards
			Returns a list of all leaderboards configured in the game.
			*/
			class ListLeaderboardsRequest : public GameSparks::Core::GSTypedRequest < ListLeaderboardsRequest, GameSparks::Api::Responses::ListLeaderboardsResponse >
			{
			public:
				ListLeaderboardsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ListLeaderboardsRequest")
				{

				}
			


			};
			
			/*!
			\ingroup Player
			Returns the list of the current players messages / notifications.
			The list only contains un-dismissed messages, to dismiss a message see DismissMessageRequest Read the section on Messages to the the complete list of messages and their meaning.
			*/
			class ListMessageRequest : public GameSparks::Core::GSTypedRequest < ListMessageRequest, GameSparks::Api::Responses::ListMessageResponse >
			{
			public:
				ListMessageRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ListMessageRequest")
				{

				}
			


			/// <summary>
			/// The number of items to return in a page (default=50)
			/// </summary>
			ListMessageRequest& SetEntryCount( long entryCount )
			{
				m_Request.AddNumber("entryCount", entryCount);
				return *this;
			}
			/// <summary>
			/// An optional filter that limits the message types returned
			/// </summary>
			ListMessageRequest& SetInclude( const gsstl::string& include )
			{
				m_Request.AddString("include", include);
				return *this;
			}
			/// <summary>
			/// The offset (page number) to start from (default=0)
			/// </summary>
			ListMessageRequest& SetOffset( long offset )
			{
				m_Request.AddNumber("offset", offset);
				return *this;
			}
			};
			
			/*!
			\ingroup Player
			Returns a summary of the list of the current players messages / notifications.
			The list only contains un-dismissed messages, to dismiss a message see DismissMessageRequest.
			The full message can be retrieved using GetMessageRequest Read the section on Messages to see the complete list of messages and their meanings.
			*/
			class ListMessageSummaryRequest : public GameSparks::Core::GSTypedRequest < ListMessageSummaryRequest, GameSparks::Api::Responses::ListMessageSummaryResponse >
			{
			public:
				ListMessageSummaryRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ListMessageSummaryRequest")
				{

				}
			


			/// <summary>
			/// The number of items to return in a page (default=50)
			/// </summary>
			ListMessageSummaryRequest& SetEntryCount( long entryCount )
			{
				m_Request.AddNumber("entryCount", entryCount);
				return *this;
			}
			/// <summary>
			/// The offset (page number) to start from (default=0)
			/// </summary>
			ListMessageSummaryRequest& SetOffset( long offset )
			{
				m_Request.AddNumber("offset", offset);
				return *this;
			}
			};
			
			/*!
			\ingroup Teams
			Get a list of the messages sent to the team (by players using SendTeamChatMessageRequest).
			*/
			class ListTeamChatRequest : public GameSparks::Core::GSTypedRequest < ListTeamChatRequest, GameSparks::Api::Responses::ListTeamChatResponse >
			{
			public:
				ListTeamChatRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ListTeamChatRequest")
				{

				}
			


			/// <summary>
			/// The number of messages to return (default=50)
			/// </summary>
			ListTeamChatRequest& SetEntryCount( long entryCount )
			{
				m_Request.AddNumber("entryCount", entryCount);
				return *this;
			}
			/// <summary>
			/// The offset (nth message) to start from (default=0)
			/// </summary>
			ListTeamChatRequest& SetOffset( long offset )
			{
				m_Request.AddNumber("offset", offset);
				return *this;
			}
			/// <summary>
			/// The team owner to find, used in combination with teamType. If not supplied the current players id will be used
			/// </summary>
			ListTeamChatRequest& SetOwnerId( const gsstl::string& ownerId )
			{
				m_Request.AddString("ownerId", ownerId);
				return *this;
			}
			/// <summary>
			/// The teamId to find (may be null if teamType supplied)
			/// </summary>
			ListTeamChatRequest& SetTeamId( const gsstl::string& teamId )
			{
				m_Request.AddString("teamId", teamId);
				return *this;
			}
			/// <summary>
			/// The teamType to find, used in combination with the current player, or the player defined by ownerId
			/// </summary>
			ListTeamChatRequest& SetTeamType( const gsstl::string& teamType )
			{
				m_Request.AddString("teamType", teamType);
				return *this;
			}
			};
			
			/*!
			\ingroup Player
			Returns a list of the current player's transaction history.
			*/
			class ListTransactionsRequest : public GameSparks::Core::GSTypedRequest < ListTransactionsRequest, GameSparks::Api::Responses::ListTransactionsResponse >
			{
			public:
				ListTransactionsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ListTransactionsRequest")
				{

				}
			


			/// <summary>
			/// Optional date constraint to list transactions from
			/// </summary>
			ListTransactionsRequest& SetDateFrom( const GameSparks::Core::GSDateTime& dateFrom )
			{
				m_Request.AddDate("dateFrom", dateFrom);
				return *this;
			}
			/// <summary>
			/// Optional date constraint to list transactions to
			/// </summary>
			ListTransactionsRequest& SetDateTo( const GameSparks::Core::GSDateTime& dateTo )
			{
				m_Request.AddDate("dateTo", dateTo);
				return *this;
			}
			/// <summary>
			/// The number of items to return in a page (default=50)
			/// </summary>
			ListTransactionsRequest& SetEntryCount( long entryCount )
			{
				m_Request.AddNumber("entryCount", entryCount);
				return *this;
			}
			/// <summary>
			/// An optional filter that limits the transaction types returned
			/// </summary>
			ListTransactionsRequest& SetInclude( const gsstl::string& include )
			{
				m_Request.AddString("include", include);
				return *this;
			}
			/// <summary>
			/// The offset (page number) to start from (default=0)
			/// </summary>
			ListTransactionsRequest& SetOffset( long offset )
			{
				m_Request.AddNumber("offset", offset);
				return *this;
			}
			};
			
			/*!
			\ingroup Store
			Returns the list of configured virtual goods.
			*/
			class ListVirtualGoodsRequest : public GameSparks::Core::GSTypedRequest < ListVirtualGoodsRequest, GameSparks::Api::Responses::ListVirtualGoodsResponse >
			{
			public:
				ListVirtualGoodsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ListVirtualGoodsRequest")
				{

				}
			


			/// <summary>
			/// A filter to only include goods with the given tags. Each good must have all the provided tags.
			/// </summary>
			ListVirtualGoodsRequest& SetTags( gsstl::vector<gsstl::string> tags )
			{
				m_Request.AddStringList("tags", tags);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Allows a user defined event to be triggered. The event will be posted to the challenge specified.
			This call differs from most as it does not have a fixed format. The @class, challengeInstanceId and eventKey attributes are common, but the rest of the attributes are as defined in the Event object configured in the dev portal.
			The example below shows a request to en event with a short code of HS with 2 attributes, 'HS' & 'GL'.
			*/
			class LogChallengeEventRequest : public GameSparks::Core::GSTypedRequest < LogChallengeEventRequest, GameSparks::Api::Responses::LogChallengeEventResponse >
			{
			public:
				LogChallengeEventRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".LogChallengeEventRequest")
				{

				}
			

				LogChallengeEventRequest& SetEventAttribute(const gsstl::string& key, long value)
				{
					m_Request.AddNumber(key, value);
					return *this;
				}

				LogChallengeEventRequest& SetEventAttribute(const gsstl::string& key, int value)
				{
					m_Request.AddNumber(key, value);
					return *this;
				}

				LogChallengeEventRequest& SetEventAttribute(const gsstl::string& key, const gsstl::string& value)
				{
					m_Request.AddString(key, value);
					return *this;
				}

				LogChallengeEventRequest& SetEventAttribute(const gsstl::string& key, const GameSparks::Core::GSRequestData& value)
				{
					m_Request.AddObject(key, value);
					return *this;
				}

				LogChallengeEventRequest& SetEventAttribute(const gsstl::string& key, gsstl::vector<GameSparks::Core::GSData> value)
				{
					m_Request.AddObjectList(key, value);
					return *this;
				}

				LogChallengeEventRequest& SetEventAttribute(const gsstl::string& key, gsstl::vector<gsstl::string> value)
				{
					m_Request.AddStringList(key, value);
					return *this;
				}

				LogChallengeEventRequest& SetEventAttribute(const gsstl::string& key, gsstl::vector<long> value)
				{
					m_Request.AddNumberList(key, value);
					return *this;
				}

				LogChallengeEventRequest& SetEventAttribute(const gsstl::string& key, gsstl::vector<int> value)
				{
					m_Request.AddNumberList(key, value);
					return *this;
				}

			/// <summary>
			/// The ID challenge instance to target
			/// </summary>
			LogChallengeEventRequest& SetChallengeInstanceId( const gsstl::string& challengeInstanceId )
			{
				m_Request.AddString("challengeInstanceId", challengeInstanceId);
				return *this;
			}
			/// <summary>
			/// The short code of the event to trigger
			/// </summary>
			LogChallengeEventRequest& SetEventKey( const gsstl::string& eventKey )
			{
				m_Request.AddString("eventKey", eventKey);
				return *this;
			}
			};
			
			/*!
			\ingroup Player
			Allows a user defined event to be triggered.
			This call differs from most as it does not have a fixed format. The @class and eventKey attributes are common, but the rest of the attributes are as defined in the Event object configured in the dev portal.
			The example below shows a request to an event with a short code of HS with 2 attributes, 'HS' & 'GL'.
			*/
			class LogEventRequest : public GameSparks::Core::GSTypedRequest < LogEventRequest, GameSparks::Api::Responses::LogEventResponse >
			{
			public:
				LogEventRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".LogEventRequest")
				{

				}
			

				LogEventRequest& SetEventAttribute(const gsstl::string& key, long value)
				{
					m_Request.AddNumber(key, value);
					return *this;
				}

				LogEventRequest& SetEventAttribute(const gsstl::string& key, int value)
				{
					m_Request.AddNumber(key, value);
					return *this;
				}

				LogEventRequest& SetEventAttribute(const gsstl::string& key, const gsstl::string& value)
				{
					m_Request.AddString(key, value);
					return *this;
				}

				LogEventRequest& SetEventAttribute(const gsstl::string& key, const GameSparks::Core::GSRequestData& value)
				{
					m_Request.AddObject(key, value);
					return *this;
				}

				LogEventRequest& SetEventAttribute(const gsstl::string& key, gsstl::vector<GameSparks::Core::GSData> value)
				{
					m_Request.AddObjectList(key, value);
					return *this;
				}

				LogEventRequest& SetEventAttribute(const gsstl::string& key, gsstl::vector<gsstl::string> value)
				{
					m_Request.AddStringList(key, value);
					return *this;
				}

				LogEventRequest& SetEventAttribute(const gsstl::string& key, gsstl::vector<long> value)
				{
					m_Request.AddNumberList(key, value);
					return *this;
				}

				LogEventRequest& SetEventAttribute(const gsstl::string& key, gsstl::vector<int> value)
				{
					m_Request.AddNumberList(key, value);
					return *this;
				}

			/// <summary>
			/// The short code of the event to trigger
			/// </summary>
			LogEventRequest& SetEventKey( const gsstl::string& eventKey )
			{
				m_Request.AddString("eventKey", eventKey);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Find the details of an existing match this player belongs to, using the matchId
			*/
			class MatchDetailsRequest : public GameSparks::Core::GSTypedRequest < MatchDetailsRequest, GameSparks::Api::Responses::MatchDetailsResponse >
			{
			public:
				MatchDetailsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".MatchDetailsRequest")
				{

				}
			


			/// <summary>
			/// The matchId to find the details of
			/// </summary>
			MatchDetailsRequest& SetMatchId( const gsstl::string& matchId )
			{
				m_Request.AddString("matchId", matchId);
				return *this;
			}
			/// <summary>
			/// Adds realtime server details if the match has been created using Cloud Code and it has not been realtime enabled
			/// </summary>
			MatchDetailsRequest& SetRealtimeEnabled( bool realtimeEnabled )
			{
				m_Request.AddBoolean("realtimeEnabled", realtimeEnabled);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Register this player for matchmaking, using the given skill and matchShortCode.
			Players looking for a match using the same matchShortCode will be considered for a match, based on the matchConfig.
			Each player must match the other for the match to be found.
			If the matchShortCode points to a match with realtime enabled, in order to minimise latency, the location of Players and their proximity to one another takes precedence over their reciprocal skill values.
			*/
			class MatchmakingRequest : public GameSparks::Core::GSTypedRequest < MatchmakingRequest, GameSparks::Api::Responses::MatchmakingResponse >
			{
			public:
				MatchmakingRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".MatchmakingRequest")
				{

				}
			


			/// <summary>
			/// The action to take on the already in-flight request for this match. Currently supported actions are: 'cancel'
			/// </summary>
			MatchmakingRequest& SetAction( const gsstl::string& action )
			{
				m_Request.AddString("action", action);
				return *this;
			}
			/// <summary>
			/// The query that will be applied to the PendingMatch collection
			/// </summary>
			MatchmakingRequest& SetCustomQuery( const GameSparks::Core::GSRequestData& customQuery )
			{
				m_Request.AddObject("customQuery", customQuery);
				return *this;
			}
			/// <summary>
			/// A JSON Map of any data that will be associated to the pending match
			/// </summary>
			MatchmakingRequest& SetMatchData( const GameSparks::Core::GSRequestData& matchData )
			{
				m_Request.AddObject("matchData", matchData);
				return *this;
			}
			/// <summary>
			/// Optional. Players will be grouped based on the distinct value passed in here, only players in the same group can be matched together
			/// </summary>
			MatchmakingRequest& SetMatchGroup( const gsstl::string& matchGroup )
			{
				m_Request.AddString("matchGroup", matchGroup);
				return *this;
			}
			/// <summary>
			/// The shortCode of the match type this player is registering for
			/// </summary>
			MatchmakingRequest& SetMatchShortCode( const gsstl::string& matchShortCode )
			{
				m_Request.AddString("matchShortCode", matchShortCode);
				return *this;
			}
			/// <summary>
			/// A JSON Map of any data that will be associated to this user in a pending match
			/// </summary>
			MatchmakingRequest& SetParticipantData( const GameSparks::Core::GSRequestData& participantData )
			{
				m_Request.AddObject("participantData", participantData);
				return *this;
			}
			/// <summary>
			/// The skill of the player looking for a match
			/// </summary>
			MatchmakingRequest& SetSkill( long skill )
			{
				m_Request.AddNumber("skill", skill);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows a PSN account to be used as an authentication mechanism.
			Once authenticated the platform can determine the current players details from the PSN platform and store them within GameSparks.
			GameSparks will determine the player's friends and whether any of them are currently registered with the game.
			If the PSN user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthentictionRequest or RegistrationRequest AND the PSN user is not already registered with the game, the PSN user will be linked to the current player.
			If the current player has not authenticated and the PSN user is not known, a new player will be created using the PSN details and the session will be authenticated against the new player.
			If the PSN user is already known, the session will switch to being the previously created user.
			*/
			class PSNConnectRequest : public GameSparks::Core::GSTypedRequest < PSNConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				PSNConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".PSNConnectRequest")
				{

				}
			


			/// <summary>
			/// The authorization code obtained from PSN, as described here https://ps4.scedev.net/resources/documents/SDK/latest/NpAuth-Reference/0008.html
			/// </summary>
			PSNConnectRequest& SetAuthorizationCode( const gsstl::string& authorizationCode )
			{
				m_Request.AddString("authorizationCode", authorizationCode);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			PSNConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			PSNConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// When using the authorization code obtained from PlayStation®4/PlayStation®Vita/PlayStation®3, this is not required.
			/// When using the authorization code obtained with the PC authentication gateway, set the URI issued from the Developer Network website.
			/// </summary>
			PSNConnectRequest& SetRedirectUri( const gsstl::string& redirectUri )
			{
				m_Request.AddString("redirectUri", redirectUri);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			PSNConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			PSNConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			PSNConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
			}
			};
			
			/*!
			\ingroup Store
			Processes an update of entitlement in PlayStation network.
			The GameSparks platform will update the 'use_count' for an entitlement (by default 'use_count' is 1).
			The request will be rejected if entitlement 'use_limit' is 0
			GampSparks platform by default will use internally saved PSN user access token
			*/
			class PsnBuyGoodsRequest : public GameSparks::Core::GSTypedRequest < PsnBuyGoodsRequest, GameSparks::Api::Responses::BuyVirtualGoodResponse >
			{
			public:
				PsnBuyGoodsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".PsnBuyGoodsRequest")
				{

				}
			


			/// <summary>
			/// The authorization code obtained from PSN, as described here https://ps4.scedev.net/resources/documents/SDK/latest/NpAuth-Reference/0008.html
			/// </summary>
			PsnBuyGoodsRequest& SetAuthorizationCode( const gsstl::string& authorizationCode )
			{
				m_Request.AddString("authorizationCode", authorizationCode);
				return *this;
			}
			/// <summary>
			/// Specify the entitlement label of the entitlement to update. (Not an entitlement ID).
			/// </summary>
			PsnBuyGoodsRequest& SetEntitlementLabel( const gsstl::string& entitlementLabel )
			{
				m_Request.AddString("entitlementLabel", entitlementLabel);
				return *this;
			}
			/// <summary>
			/// When using the authorization code obtained from PlayStation®4/PlayStation®Vita/PlayStation®3, this is not required.
			/// When using the authorization code obtained with the PC authentication gateway, set the URI issued from the Developer Network website.
			/// </summary>
			PsnBuyGoodsRequest& SetRedirectUri( const gsstl::string& redirectUri )
			{
				m_Request.AddString("redirectUri", redirectUri);
				return *this;
			}
			/// <summary>
			/// If set to true, the transactionId from this receipt will not be globally valdidated, this will mean replays between players are possible.
			/// It will only validate the transactionId has not been used by this player before.
			/// </summary>
			PsnBuyGoodsRequest& SetUniqueTransactionByPlayer( bool uniqueTransactionByPlayer )
			{
				m_Request.AddBoolean("uniqueTransactionByPlayer", uniqueTransactionByPlayer);
				return *this;
			}
			/// <summary>
			/// Optional - specify the quantity of the entitlement to use. Default = 1
			/// </summary>
			PsnBuyGoodsRequest& SetUseCount( long useCount )
			{
				m_Request.AddNumber("useCount", useCount);
				return *this;
			}
			};
			
			/*!
			\ingroup Misc
			Registers the current device for push notifications. Currently GameSparks supports iOS, GCM & Microsoft Push notifications.
			Supply the device type, and the push notification identifier for the device.
			*/
			class PushRegistrationRequest : public GameSparks::Core::GSTypedRequest < PushRegistrationRequest, GameSparks::Api::Responses::PushRegistrationResponse >
			{
			public:
				PushRegistrationRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".PushRegistrationRequest")
				{

				}
			


			/// <summary>
			/// The type of id, valid values are ios, android, wp8, w8, kindle or viber
			/// </summary>
			PushRegistrationRequest& SetDeviceOS( const gsstl::string& deviceOS )
			{
				m_Request.AddString("deviceOS", deviceOS);
				return *this;
			}
			/// <summary>
			/// The push notification identifier for the device
			/// </summary>
			PushRegistrationRequest& SetPushId( const gsstl::string& pushId )
			{
				m_Request.AddString("pushId", pushId);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows a QQ access token to be used as an authentication mechanism.
			Once authenticated the platform can determine the current players details from the QQ platform and store them within GameSparks.
			If the QQ user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthenticationRequest or RegistrationRequest AND the QQ user is not already registered with the game, the QQ user will be linked to the current player.
			If the current player has not authenticated and the QQ user is not known, a new player will be created using the QQ details and the session will be authenticated against the new player.
			If the QQ user is already known, the session will switch to being the previously created user.
			*/
			class QQConnectRequest : public GameSparks::Core::GSTypedRequest < QQConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				QQConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".QQConnectRequest")
				{

				}
			


			/// <summary>
			/// The access token is used by the client to make authenticated requests on behalf of the end user.
			/// When the access token expires, attempts to use it will fail, and a new access token must be obtained using the refresh token.
			/// </summary>
			QQConnectRequest& SetAccessToken( const gsstl::string& accessToken )
			{
				m_Request.AddString("accessToken", accessToken);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			QQConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			QQConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			QQConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			QQConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			QQConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows a new player to be created using a username, password display name.
			*/
			class RegistrationRequest : public GameSparks::Core::GSTypedRequest < RegistrationRequest, GameSparks::Api::Responses::RegistrationResponse >
			{
			public:
				RegistrationRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".RegistrationRequest")
				{

				}
			


			/// <summary>
			/// A display name to use
			/// </summary>
			RegistrationRequest& SetDisplayName( const gsstl::string& displayName )
			{
				m_Request.AddString("displayName", displayName);
				return *this;
			}
			/// <summary>
			/// The previously registered password
			/// </summary>
			RegistrationRequest& SetPassword( const gsstl::string& password )
			{
				m_Request.AddString("password", password);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			RegistrationRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// The previously registered player name
			/// </summary>
			RegistrationRequest& SetUserName( const gsstl::string& userName )
			{
				m_Request.AddString("userName", userName);
				return *this;
			}
			};
			
			/*!
			\ingroup Admin
			Revokes the purchase of a good. The items aquired will be removed from remaining items of the player.
			*/
			class RevokePurchaseGoodsRequest : public GameSparks::Core::GSTypedRequest < RevokePurchaseGoodsRequest, GameSparks::Api::Responses::RevokePurchaseGoodsResponse >
			{
			public:
				RevokePurchaseGoodsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".RevokePurchaseGoodsRequest")
				{

				}
			


			/// <summary>
			/// The playerId for which to revoke the transaction
			/// </summary>
			RevokePurchaseGoodsRequest& SetPlayerId( const gsstl::string& playerId )
			{
				m_Request.AddString("playerId", playerId);
				return *this;
			}
			/// <summary>
			/// The store type for which to revoke these transactions
			/// </summary>
			RevokePurchaseGoodsRequest& SetStoreType( const gsstl::string& storeType )
			{
				m_Request.AddString("storeType", storeType);
				return *this;
			}
			/// <summary>
			/// The list of transactionIds to revoke
			/// </summary>
			RevokePurchaseGoodsRequest& SetTransactionIds( gsstl::vector<gsstl::string> transactionIds )
			{
				m_Request.AddStringList("transactionIds", transactionIds);
				return *this;
			}
			};
			
			/*!
			\ingroup Admin
			Schedules a bulk job to be run against multiple players.
			*/
			class ScheduleBulkJobAdminRequest : public GameSparks::Core::GSTypedRequest < ScheduleBulkJobAdminRequest, GameSparks::Api::Responses::ScheduleBulkJobAdminResponse >
			{
			public:
				ScheduleBulkJobAdminRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ScheduleBulkJobAdminRequest")
				{

				}
			


			/// <summary>
			/// Optional data to be passed into the script
			/// </summary>
			ScheduleBulkJobAdminRequest& SetData( const GameSparks::Core::GSRequestData& data )
			{
				m_Request.AddObject("data", data);
				return *this;
			}
			/// <summary>
			/// The short code of the cloud code module to be executed against each player
			/// </summary>
			ScheduleBulkJobAdminRequest& SetModuleShortCode( const gsstl::string& moduleShortCode )
			{
				m_Request.AddString("moduleShortCode", moduleShortCode);
				return *this;
			}
			/// <summary>
			/// The query to be run against the player collection to identify which players to execute the cloud code for
			/// </summary>
			ScheduleBulkJobAdminRequest& SetPlayerQuery( const GameSparks::Core::GSRequestData& playerQuery )
			{
				m_Request.AddObject("playerQuery", playerQuery);
				return *this;
			}
			/// <summary>
			/// An optional date and time for this job to be run
			/// </summary>
			ScheduleBulkJobAdminRequest& SetScheduledTime( const GameSparks::Core::GSDateTime& scheduledTime )
			{
				m_Request.AddDate("scheduledTime", scheduledTime);
				return *this;
			}
			/// <summary>
			/// The script to be executed against each player
			/// </summary>
			ScheduleBulkJobAdminRequest& SetScript( const gsstl::string& script )
			{
				m_Request.AddString("script", script);
				return *this;
			}
			};
			
			/*!
			\ingroup Player
			Sends a message to one or more game friend(s). A game friend is someone in the players social network who also plays the game.
			*/
			class SendFriendMessageRequest : public GameSparks::Core::GSTypedRequest < SendFriendMessageRequest, GameSparks::Api::Responses::SendFriendMessageResponse >
			{
			public:
				SendFriendMessageRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".SendFriendMessageRequest")
				{

				}
			


			/// <summary>
			/// One or more friend ID's. This can be supplied as a single string, or a JSON array
			/// </summary>
			SendFriendMessageRequest& SetFriendIds( gsstl::vector<gsstl::string> friendIds )
			{
				m_Request.AddStringList("friendIds", friendIds);
				return *this;
			}
			/// <summary>
			/// The message to send
			/// </summary>
			SendFriendMessageRequest& SetMessage( const gsstl::string& message )
			{
				m_Request.AddString("message", message);
				return *this;
			}
			};
			
			/*!
			\ingroup Teams
			Send a message to all the players who are member of the given team
			*/
			class SendTeamChatMessageRequest : public GameSparks::Core::GSTypedRequest < SendTeamChatMessageRequest, GameSparks::Api::Responses::SendTeamChatMessageResponse >
			{
			public:
				SendTeamChatMessageRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".SendTeamChatMessageRequest")
				{

				}
			


			/// <summary>
			/// The message to send
			/// </summary>
			SendTeamChatMessageRequest& SetMessage( const gsstl::string& message )
			{
				m_Request.AddString("message", message);
				return *this;
			}
			/// <summary>
			/// The team owner to find, used in combination with teamType. If not supplied the current players id will be used
			/// </summary>
			SendTeamChatMessageRequest& SetOwnerId( const gsstl::string& ownerId )
			{
				m_Request.AddString("ownerId", ownerId);
				return *this;
			}
			/// <summary>
			/// The teamId to find (may be null if teamType supplied)
			/// </summary>
			SendTeamChatMessageRequest& SetTeamId( const gsstl::string& teamId )
			{
				m_Request.AddString("teamId", teamId);
				return *this;
			}
			/// <summary>
			/// The teamType to find, used in combination with the current player, or the player defined by ownerId
			/// </summary>
			SendTeamChatMessageRequest& SetTeamType( const gsstl::string& teamType )
			{
				m_Request.AddString("teamType", teamType);
				return *this;
			}
			};
			
			/*!
			\ingroup Player
			Allows a player's internal profile to be disconnected from an external system to which it is linked.  Any friends linked as result of this connection will be removed.
			*/
			class SocialDisconnectRequest : public GameSparks::Core::GSTypedRequest < SocialDisconnectRequest, GameSparks::Api::Responses::SocialDisconnectResponse >
			{
			public:
				SocialDisconnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".SocialDisconnectRequest")
				{

				}
			


			/// <summary>
			/// The external system from which to disconnect this profile.
			/// </summary>
			SocialDisconnectRequest& SetSystemId( const gsstl::string& systemId )
			{
				m_Request.AddString("systemId", systemId);
				return *this;
			}
			};
			
			/*!
			\ingroup Leaderboards
			Returns leaderboard data that only contains entries of players that are game friends with the current player.
			The GameSparks platform will attempt to return players both ahead and behind the current player, where data is available.
			The entry count defines how many player should be returned both ahead and behind. The numer of results may vary if there are not enough friends either ahead or behind.
			*/
			class SocialLeaderboardDataRequest : public GameSparks::Core::GSTypedRequest < SocialLeaderboardDataRequest, GameSparks::Api::Responses::LeaderboardDataResponse >
			{
			public:
				SocialLeaderboardDataRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".SocialLeaderboardDataRequest")
				{

				}
			


			/// <summary>
			/// The challenge instance to get the leaderboard data for
			/// </summary>
			SocialLeaderboardDataRequest& SetChallengeInstanceId( const gsstl::string& challengeInstanceId )
			{
				m_Request.AddString("challengeInstanceId", challengeInstanceId);
				return *this;
			}
			/// <summary>
			/// The default behaviour on a social request is to error if the player has no friends (NOTSOCIAL).  Set this flag to suppress that error and return the player's leaderboard entry instead.
			/// </summary>
			SocialLeaderboardDataRequest& SetDontErrorOnNotSocial( bool dontErrorOnNotSocial )
			{
				m_Request.AddBoolean("dontErrorOnNotSocial", dontErrorOnNotSocial);
				return *this;
			}
			/// <summary>
			/// The number of items to return in a page (default=50)
			/// </summary>
			SocialLeaderboardDataRequest& SetEntryCount( long entryCount )
			{
				m_Request.AddNumber("entryCount", entryCount);
				return *this;
			}
			/// <summary>
			/// A friend id or an array of friend ids to use instead of the player's social friends
			/// </summary>
			SocialLeaderboardDataRequest& SetFriendIds( gsstl::vector<gsstl::string> friendIds )
			{
				m_Request.AddStringList("friendIds", friendIds);
				return *this;
			}
			/// <summary>
			/// Number of entries to include from head of the list
			/// </summary>
			SocialLeaderboardDataRequest& SetIncludeFirst( long includeFirst )
			{
				m_Request.AddNumber("includeFirst", includeFirst);
				return *this;
			}
			/// <summary>
			/// Number of entries to include from tail of the list
			/// </summary>
			SocialLeaderboardDataRequest& SetIncludeLast( long includeLast )
			{
				m_Request.AddNumber("includeLast", includeLast);
				return *this;
			}
			/// <summary>
			/// Returns the leaderboard excluding the player's social friends
			/// </summary>
			SocialLeaderboardDataRequest& SetInverseSocial( bool inverseSocial )
			{
				m_Request.AddBoolean("inverseSocial", inverseSocial);
				return *this;
			}
			/// <summary>
			/// The short code of the leaderboard
			/// </summary>
			SocialLeaderboardDataRequest& SetLeaderboardShortCode( const gsstl::string& leaderboardShortCode )
			{
				m_Request.AddString("leaderboardShortCode", leaderboardShortCode);
				return *this;
			}
			/// <summary>
			/// The offset into the set of leaderboards returned
			/// </summary>
			SocialLeaderboardDataRequest& SetOffset( long offset )
			{
				m_Request.AddNumber("offset", offset);
				return *this;
			}
			/// <summary>
			/// If True returns a leaderboard of the player's social friends
			/// </summary>
			SocialLeaderboardDataRequest& SetSocial( bool social )
			{
				m_Request.AddBoolean("social", social);
				return *this;
			}
			/// <summary>
			/// The IDs of the teams you are interested in
			/// </summary>
			SocialLeaderboardDataRequest& SetTeamIds( gsstl::vector<gsstl::string> teamIds )
			{
				m_Request.AddStringList("teamIds", teamIds);
				return *this;
			}
			/// <summary>
			/// The type of team you are interested in
			/// </summary>
			SocialLeaderboardDataRequest& SetTeamTypes( gsstl::vector<gsstl::string> teamTypes )
			{
				m_Request.AddStringList("teamTypes", teamTypes);
				return *this;
			}
			};
			
			/*!
			\ingroup Misc
			Returns detials of the current social connections of this player. Each connection .
			*/
			class SocialStatusRequest : public GameSparks::Core::GSTypedRequest < SocialStatusRequest, GameSparks::Api::Responses::SocialStatusResponse >
			{
			public:
				SocialStatusRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".SocialStatusRequest")
				{

				}
			


			};
			
			/*!
			\ingroup Store
			Processes a 'orderid' from a Steam.
			The GameSparks platform will validate the 'orderid' with Steam and process the response. The 'orderid' from the response will be recorded and the request will be rejected, if the 'orderid' has previously been processed, this prevents replay attacks.
			Once verified, the players account will be credited with the Virtual Good, or Virtual Currency the purchase contains. The virtual good will be looked up by matching the 'itemid' in the response with the 'Steam Product ID' configured against the virtual good.
			*/
			class SteamBuyGoodsRequest : public GameSparks::Core::GSTypedRequest < SteamBuyGoodsRequest, GameSparks::Api::Responses::BuyVirtualGoodResponse >
			{
			public:
				SteamBuyGoodsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".SteamBuyGoodsRequest")
				{

				}
			


			/// <summary>
			/// Unique 64-bit ID for order
			/// </summary>
			SteamBuyGoodsRequest& SetOrderId( const gsstl::string& orderId )
			{
				m_Request.AddString("orderId", orderId);
				return *this;
			}
			/// <summary>
			/// If set to true, the transactionId from this receipt will not be globally valdidated, this will mean replays between players are possible.
			/// It will only validate the transactionId has not been used by this player before.
			/// </summary>
			SteamBuyGoodsRequest& SetUniqueTransactionByPlayer( bool uniqueTransactionByPlayer )
			{
				m_Request.AddBoolean("uniqueTransactionByPlayer", uniqueTransactionByPlayer);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows a Steam sessionTicket to be used as an authentication mechanism.
			Once authenticated the platform can determine the current players details from the Steam platform and store them within GameSparks.
			GameSparks will determine the player's friends and whether any of them are currently registered with the game.
			If the Steam user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthentictionRequest or RegistrationRequest AND the Steam user is not already registered with the game, the Steam user will be linked to the current player.
			If the current player has not authenticated and the Steam user is not known, a new player will be created using the Steam details and the session will be authenticated against the new player.
			If the Steam user is already known, the session will switch to being the previously created user.
			*/
			class SteamConnectRequest : public GameSparks::Core::GSTypedRequest < SteamConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				SteamConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".SteamConnectRequest")
				{

				}
			


			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			SteamConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			SteamConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			SteamConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// The hex encoded UTF-8 string representation of the ticket acquired calling the Steam SDKs GetAuthSessionTicket.
			/// </summary>
			SteamConnectRequest& SetSessionTicket( const gsstl::string& sessionTicket )
			{
				m_Request.AddString("sessionTicket", sessionTicket);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			SteamConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			SteamConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows a Twitch account to be used as an authentication mechanism.
			Once authenticated the platform can determine the current players details from the Twitch platform and store them within GameSparks.
			If the Twitch user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthentictionRequest or RegistrationRequest AND the Twitch user is not already registered with the game, the Twitch user will be linked to the current player.
			If the current player has not authenticated and the Twitch user is not known, a new player will be created using the Twitch details and the session will be authenticated against the new player.
			If the Twitch user is already known, the session will switch to being the previously created user.
			*/
			class TwitchConnectRequest : public GameSparks::Core::GSTypedRequest < TwitchConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				TwitchConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".TwitchConnectRequest")
				{

				}
			


			/// <summary>
			/// The access token is used by the client to make authenticated requests on behalf of the end user.
			/// </summary>
			TwitchConnectRequest& SetAccessToken( const gsstl::string& accessToken )
			{
				m_Request.AddString("accessToken", accessToken);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			TwitchConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			TwitchConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			TwitchConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			TwitchConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			TwitchConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows a Twitter account to be used as an authentication mechanism.
			Once authenticated the platform can determine the current players details from the Twitter platform and store them within GameSparks.
			GameSparks will determine the player's friends and whether any of them are currently registered with the game.
			If the Twitter user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthentictionRequest or RegistrationRequest AND the Twitter user is not already registered with the game, the Twitter user will be linked to the current player.
			If the current player has not authenticated and the Twitter user is not known, a new player will be created using the Twitter details and the session will be authenticated against the new player.
			If the Twitter user is already known, the session will switch to being the previously created user.
			*/
			class TwitterConnectRequest : public GameSparks::Core::GSTypedRequest < TwitterConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				TwitterConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".TwitterConnectRequest")
				{

				}
			


			/// <summary>
			/// The accessSecret is obtained at the same time as the accessToken, and is required to sign requests to Twitter's services that require the accessToken.
			/// </summary>
			TwitterConnectRequest& SetAccessSecret( const gsstl::string& accessSecret )
			{
				m_Request.AddString("accessSecret", accessSecret);
				return *this;
			}
			/// <summary>
			/// The accessToken represents a player's permission to share access to their account with your application.
			/// To obtain an accessToken for the player see https://dev.twitter.com/docs/auth/obtaining-access-tokens.
			/// Currently, Twitter accessTokens do not expire but they can be revoked by the player.
			/// </summary>
			TwitterConnectRequest& SetAccessToken( const gsstl::string& accessToken )
			{
				m_Request.AddString("accessToken", accessToken);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			TwitterConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			TwitterConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			TwitterConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			TwitterConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			TwitterConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows a Viber account to be used as an authentication mechanism.
			Once authenticated the platform can determine the current players details from the Viber platform and store them within GameSparks.
			A successful authentication will also register the player to receive Viber push notifications.
			GameSparks will determine the player's friends and whether any of them are currently registered with the game.
			If the Viber user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthentictionRequest or RegistrationRequest AND the Viber user is not already registered with the game, the Viber user will be linked to the current player.
			If the current player has not authenticated and the Viber user is not known, a new player will be created using the Viber details and the session will be authenticated against the new player.
			If the Viber user is already known, the session will switch to being the previously created user.
			*/
			class ViberConnectRequest : public GameSparks::Core::GSTypedRequest < ViberConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				ViberConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".ViberConnectRequest")
				{

				}
			


			/// <summary>
			/// The accessToken represents a player's permission to share access to their account with your application.
			/// </summary>
			ViberConnectRequest& SetAccessToken( const gsstl::string& accessToken )
			{
				m_Request.AddString("accessToken", accessToken);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			ViberConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Does not automatocally register this user for push notifications. Defaults to false.
			/// </summary>
			ViberConnectRequest& SetDoNotRegisterForPush( bool doNotRegisterForPush )
			{
				m_Request.AddBoolean("doNotRegisterForPush", doNotRegisterForPush);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			ViberConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			ViberConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			ViberConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			ViberConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows a WeChat access token to be used as an authentication mechanism.
			Once authenticated the platform can determine the current players details from the WeChat platform and store them within GameSparks.
			If the WeChat user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthenticationRequest or RegistrationRequest AND the WeChat user is not already registered with the game, the WeChat user will be linked to the current player.
			If the current player has not authenticated and the WeChat user is not known, a new player will be created using the WeChat details and the session will be authenticated against the new player.
			If the WeChat user is already known, the session will switch to being the previously created user.
			*/
			class WeChatConnectRequest : public GameSparks::Core::GSTypedRequest < WeChatConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				WeChatConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".WeChatConnectRequest")
				{

				}
			


			/// <summary>
			/// The access token sould be obtained from WeChat
			/// It is used by the client to make authenticated requests on behalf of the end user.
			/// </summary>
			WeChatConnectRequest& SetAccessToken( const gsstl::string& accessToken )
			{
				m_Request.AddString("accessToken", accessToken);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			WeChatConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			WeChatConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// The open ID corresponding to the WeChat user
			/// </summary>
			WeChatConnectRequest& SetOpenId( const gsstl::string& openId )
			{
				m_Request.AddString("openId", openId);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			WeChatConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			WeChatConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			WeChatConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
			}
			};
			
			/*!
			\ingroup Store
			Processes a transaction receipt from a windows store purchase.
			The GameSparks platform will validate the receipt using the signature embedded in the xml. The Id in the xml will be recorded and the request will be rejected if the Id has previously been processed, this prevents replay attacks.
			Once verified, the players account will be credited with the Virtual Good, or Virtual Currency the purchase contains. The virtual good will be looked up by matching the productId in the xml with the 'WP8 Product ID' configured against the virtual good.
			*/
			class WindowsBuyGoodsRequest : public GameSparks::Core::GSTypedRequest < WindowsBuyGoodsRequest, GameSparks::Api::Responses::BuyVirtualGoodResponse >
			{
			public:
				WindowsBuyGoodsRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".WindowsBuyGoodsRequest")
				{

				}
			


			/// <summary>
			/// Allows you to specify the platform
			/// </summary>
			WindowsBuyGoodsRequest& SetPlatform( const gsstl::string& platform )
			{
				m_Request.AddString("platform", platform);
				return *this;
			}
			/// <summary>
			/// The xml reciept returned from the windows phone 8 store
			/// </summary>
			WindowsBuyGoodsRequest& SetReceipt( const gsstl::string& receipt )
			{
				m_Request.AddString("receipt", receipt);
				return *this;
			}
			/// <summary>
			/// If set to true, the transactionId from this receipt will not be globally valdidated, this will mean replays between players are possible.
			/// It will only validate the transactionId has not been used by this player before.
			/// </summary>
			WindowsBuyGoodsRequest& SetUniqueTransactionByPlayer( bool uniqueTransactionByPlayer )
			{
				m_Request.AddBoolean("uniqueTransactionByPlayer", uniqueTransactionByPlayer);
				return *this;
			}
			};
			
			/*!
			\ingroup Multiplayer
			Withdraws a challenge previously issued by the current player.
			This can only be done while the challenge is in the ISSUED state. Once it's been accepted the challenge can not be withdrawn.
			*/
			class WithdrawChallengeRequest : public GameSparks::Core::GSTypedRequest < WithdrawChallengeRequest, GameSparks::Api::Responses::WithdrawChallengeResponse >
			{
			public:
				WithdrawChallengeRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".WithdrawChallengeRequest")
				{

				}
			


			/// <summary>
			/// The ID of the challenge
			/// </summary>
			WithdrawChallengeRequest& SetChallengeInstanceId( const gsstl::string& challengeInstanceId )
			{
				m_Request.AddString("challengeInstanceId", challengeInstanceId);
				return *this;
			}
			/// <summary>
			/// An optional message to send with the challenge
			/// </summary>
			WithdrawChallengeRequest& SetMessage( const gsstl::string& message )
			{
				m_Request.AddString("message", message);
				return *this;
			}
			};
			
			/*!
			\ingroup Authentication
			Allows an Xbox Live Shared Token String to be used as an authentication mechanism.
			Once authenticated the platform can determine the current players details from the Xbox Live and store them within GameSparks.
			GameSparks will determine the player's friends and whether any of them are currently registered with the game.
			If the Xbox user is already linked to a player, the current session will switch to the linked player.
			If the current player has previously created an account using either DeviceAuthentictionRequest or RegistrationRequest AND the Xbox user is not already registered with the game, the Xbox user will be linked to the current player.
			If the current player has not authenticated and the Xbox user is not known, a new player will be created using the Xbox details and the session will be authenticated against the new player.
			If the Xbox user is already known, the session will switch to being the previously created user.
			*/
			class XBOXLiveConnectRequest : public GameSparks::Core::GSTypedRequest < XBOXLiveConnectRequest, GameSparks::Api::Responses::AuthenticationResponse >
			{
			public:
				XBOXLiveConnectRequest(Core::GS& gsInstance)
					: GSTypedRequest(gsInstance, ".XBOXLiveConnectRequest")
				{

				}
			


			/// <summary>
			/// Indicates that the server should not try to link the external profile with the current player.  If false, links the external profile to the currently signed in player.  If true, creates a new player and links the external profile to them.  Defaults to false.
			/// </summary>
			XBOXLiveConnectRequest& SetDoNotLinkToCurrentPlayer( bool doNotLinkToCurrentPlayer )
			{
				m_Request.AddBoolean("doNotLinkToCurrentPlayer", doNotLinkToCurrentPlayer);
				return *this;
			}
			/// <summary>
			/// Indicates whether the server should return an error if an account switch would have occurred, rather than switching automatically.  Defaults to false.
			/// </summary>
			XBOXLiveConnectRequest& SetErrorOnSwitch( bool errorOnSwitch )
			{
				m_Request.AddBoolean("errorOnSwitch", errorOnSwitch);
				return *this;
			}
			/// <summary>
			/// An optional segment configuration for this request.
			/// If this request creates a new player on the gamesparks platform, the segments of the new player will match the values provided
			/// </summary>
			XBOXLiveConnectRequest& SetSegments( const GameSparks::Core::GSRequestData& segments )
			{
				m_Request.AddObject("segments", segments);
				return *this;
			}
			/// <summary>
			/// The access token is used by the client to make authenticated requests on behalf of the end user.
			/// It has a longer lifetime than the authorization code, typically on the order of minutes or hours.
			/// When the access token expires, attempts to use it will fail, and a new access token must be obtained via a refresh token.
			/// </summary>
			XBOXLiveConnectRequest& SetStsTokenString( const gsstl::string& stsTokenString )
			{
				m_Request.AddString("stsTokenString", stsTokenString);
				return *this;
			}
			/// <summary>
			/// Indicates that the server should switch to the supplied profile if it isalready associated to a player. Defaults to false.
			/// </summary>
			XBOXLiveConnectRequest& SetSwitchIfPossible( bool switchIfPossible )
			{
				m_Request.AddBoolean("switchIfPossible", switchIfPossible);
				return *this;
			}
			/// <summary>
			/// Indicates that the associated players displayName should be kept in syn with this profile when it's updated by the external provider.
			/// </summary>
			XBOXLiveConnectRequest& SetSyncDisplayName( bool syncDisplayName )
			{
				m_Request.AddBoolean("syncDisplayName", syncDisplayName);
				return *this;
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



