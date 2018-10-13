#pragma once

#include <string>
#include <curl/curl.h>
#include "Error.h"

using namespace std;

// This is a class meant for handling URL requests using libcurl library.
class URLHandler
{
public:
	URLHandler();
	virtual ~URLHandler();

private:
	// Callback function to register curl's response.
	static size_t curlCallback(void *contents, size_t size, size_t nmemb, void *userp);
	// This handles all of the errors occurred during connection.
	Error err;
	// URL that will be sent to Twitter for the request.
	string query;
	// The token received from Twitter will be saved here.
	string token;
	// The curl response will be saved here to see if there was an error while sending the request.
	CURLcode res;
	// Request configurations will he saved here.
	CURL * curl;
	// This variable is necessary for using curl_multi_perform() (the non blocking way of emitting requests). Many easy handles will be attached to it.
	CURLM * multiHandle;
	// String containing response form API.
	string response;

};

