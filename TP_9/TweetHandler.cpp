#include "TweetHandler.h"

#define API_KEY "7s8uvgQnJqjJDqA6JsLIFp90FcOaoR5Ic41LWyHOic0Ht3SRJ6"
#define API_SECRET_KEY "7s8uvgQnJqjJDqA6JsLIFp90FcOaoR5Ic41LWyHOic0Ht3SRJ6"


TweetHandler::TweetHandler() : tweetsList(), TwitterAnswer()
{
	APIKey = API_KEY;
	APISecretKey = API_SECRET_KEY;
}

TweetHandler::TweetHandler(char * account_, int tweetsN_) : tweetsList(), TwitterAnswer()
{
	APIKey = API_KEY;
	APISecretKey = API_SECRET_KEY;
	setAccountSource(account_);
	setTweetsAmount(tweetsN_);

	updateURL();
}

TweetHandler::TweetHandler(char * account_) : tweetsList(), TwitterAnswer()
{
	APIKey = API_KEY;
	APISecretKey = API_SECRET_KEY;
	setAccountSource(account_);
	setTweetsAmount(0);

	updateURL();
}


TweetHandler::~TweetHandler()
{
}

void TweetHandler::setAccountSource(char * account_)
{
	account = account_;
}

void TweetHandler::setTweetsAmount(int tweetsN_)
{
	tweetsN = tweetsN_;
}

bool TweetHandler::createTwitterToken()
{
	string password = APIKey + ":" + APISecretKey;
	return easyPerform((char *)password.c_str());		// Executing an easyPerform to get the token using a password.
}

void TweetHandler::updateURL()
{
	initQuery();
	setURL((char *)query.c_str());						// Setting URL with parent method.
}

vector<Tweet> TweetHandler::getTweetsList()
{
	if (token.empty())
	{
		return vector<Tweet>();						// If the token was not initialised, an empty vector is returned.
	}
	else
	{
		string aux = "Authorisation: Bearer ";
		aux += token;
		setUpMultiPerform((char *)aux.c_str());				// Setting up multi perform with the authentication header as specified by Twitter, using the token.
		multiPerform();

		TwitterAnswer = json::parse(response);				// Parsing Twitter's response as a JSON object.
		try
		{
			for (auto tweet : TwitterAnswer)
			{

			}
		}
		catch (exception& e)
		{

		}
	}
}

void TweetHandler::initQuery()
{
	query = string("https://api.twitter.com/1.1/statuses/user_timeline.json") + "?" + "screen_name=" + account;

	if (tweetsN != 0)
	{
		query += string("&") + "count=" + to_string(tweetsN);
	}
}
