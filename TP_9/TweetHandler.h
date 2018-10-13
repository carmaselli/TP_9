#pragma once
#include "URLHandler.h"
#include "json.hpp"
#include <vector>

using namespace std;
using json = nlohmann::json;

// This is a class meant for handling Twitter's API specific requests. 
class TweetHandler : 
	public URLHandler
{
public:
	TweetHandler();
	TweetHandler(char * accaunt_, int tweetsN_);
	TweetHandler(char * accaunt_);
	virtual ~TweetHandler();

	void setAccountSource(char * accaunt_);
	void setTweetsAmount(int tweetsN_);
	void setUpTwitterToken();
	void getTweetsList();

private:
	string APIKey;
	string APISecretKey;
	string accaunt;
	int tweetsN;
	json parser;
	// The token received from Twitter will be saved here.
	string token;
	// List containing all the tweets as strings.
	vector<string>  tweetsList;
};