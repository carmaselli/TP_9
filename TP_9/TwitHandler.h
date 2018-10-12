#pragma once
#include <string>
#include <curl/curl.h>

using namespace std;

class TwitHandler
{
public:
	TwitHandler();
	TwitHandler(char * accaunt, int twitsN);
	TwitHandler(char * accaunt);
	~TwitHandler();

	void setAccountSource(char * accaunt);
	void getToken();

public:
	string APIKey;
	string APISecretKey;
	// URL that will be sent to Twitter for the request.
	string query;
	// The token received from Twitter will be saved here.
	string token;
	// The curl response will be saved here to see if there was an error while sending the request.
	CURLcode res;
	// Request configurations will he saved here.
	CURL * curl;

};