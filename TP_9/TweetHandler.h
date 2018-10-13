#pragma once
#include "URLHandler.h"
#include "json.hpp"

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
	void getToken();
	void isOk();
	Error getError();

private:
	string APIKey;
	string APISecretKey;
	string accaunt;
	int tweetsN;
	json parser;
};