#pragma once
#include "URLHandler.h"
#include "json.hpp"
#include "Tweet.h"
#include <vector>

using namespace std;
using json = nlohmann::json;

// This is a class meant for handling Twitter's API specific requests. 
class TweetHandler : 
	public URLHandler
{
public:
	TweetHandler();
	TweetHandler(char * account_, int tweetsN_);
	TweetHandler(char * account_);
	virtual ~TweetHandler();

	void setAccountSource(char * account_);
	void setTweetsAmount(int tweetsN_);
	// Must be called before any other request, to get the token from Twitter.
	bool createTwitterToken();
	// To be called after setting new account and/or tweetsN.
	void updateURL();

	// To be called after creating the token.
	vector<Tweet> getTweetsList();

private:
	void initQuery();

	string APIKey;
	string APISecretKey;
	string account;
	int tweetsN;
	json TwitterAnswer;
	// The token received from Twitter will be saved here.
	string token;
	// List containing all the tweets as strings.
	vector<Tweet> tweetsList;
	// This is the page from the API where the object will get the tweets from.
	string query;
};