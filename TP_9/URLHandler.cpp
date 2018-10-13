#include "URLHandler.h"

URLHandler::URLHandler() : err()
{
}


URLHandler::~URLHandler()
{
}

bool URLHandler::easyPerform()
{
	curl = curl_easy_init();		// Initialising curl.
	response = "";					// Initialising response string.
	
	if (curl)						// As long as everything was ok...
	{
		return basicEasyPerform();
	}
	else
	{
		err.setErrType(ErrType::ERR_WHILE_CURL_INIT);
		curl_easy_cleanup(curl);
		return false;
	}
}

bool URLHandler::easyPerform(char * password)
{
	curl = curl_easy_init();		// Initialising curl.
	response = "";					// Initialising response string.

	if (curl)						// as long as everything was ok...
	{
		curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);							// Basic authentication by HTTP.
		curl_easy_setopt(curl, CURLOPT_USERPWD, password);

		struct curl_slist * list = NULL;													// List for setting up a header.
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);									// Telling CURL we're sending coded URLs and in	UTF8 format. This automatically codes our password.
		list = curl_slist_append(list, "Content-Type: application/x-www-form-urlencoded;charset=UTF-8");

		string data = "grant_type=client_credentials";
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());							// Telling CURL we're working with credentials.

		return basicEasyPerform();
	}
	else
	{
		err.setErrType(ErrType::ERR_WHILE_CURL_INIT);
		curl_easy_cleanup(curl);
		return false;
	}
}

bool URLHandler::setUpMultiPerform()
{
	curl = curl_easy_init();								// Initialising curl.
	multiHandle = curl_multi_init();						// Initialising multiHandle.
	response = "";											// Initialising response string.
	stillReceiving = 0;

	if (curl != NULL && multiHandle != NULL)				// As long as everything is ok...
	{
		return basicSetUpMultiPerform();
	}
	else
	{
		err.setErrType(ErrType::ERR_WHILE_CURL_INIT);
		curl_easy_cleanup(curl);
		return false;
	}
}

bool URLHandler::setUpMultiPerform(char * header)
{
	curl = curl_easy_init();								// Initialising curl.
	multiHandle = curl_multi_init();						// Initialising multiHandle.
	response = "";											// Initialising response string.
	stillReceiving = 0;

	if (curl != NULL && multiHandle != NULL)				// As long as everything is ok...
	{
		struct curl_slist * list = NULL;													// List for setting up a header.
		list = curl_slist_append(list, header);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);									// Telling curl we're adding a header.

		return basicSetUpMultiPerform();
	}
	else
	{
		err.setErrType(ErrType::ERR_WHILE_CURL_INIT);
		curl_easy_cleanup(curl);
		return false;
	}
}

bool URLHandler::multiPerform()
{
	multiRes = curl_multi_perform(multiHandle, &stillReceiving);
	if (multiRes != CURLE_OK)
	{
		err.setErrType(ErrType::ERR_WHILE_MULTI_PERFORM);
		curl_easy_cleanup(curl);
		return false;
	}
}

bool URLHandler::isStillReceiving()
{
	return stillReceiving;
}

bool URLHandler::basicEasyPerform()
{
	curl_easy_setopt(curl, CURLOPT_URL, URL);											// Setting URL we will connect to.
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);									// Telling CURL to follow redirection in case page we visit redirects us somewhere else.
	curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);		// Telling CURL to work with either HTTP or HTTPS.

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->curlCallback);					// Specifying callback function to be called when curl has to write the response.
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);								// Specifying "response" as the parameter to be passed to callback function as user data.

	easyRes = curl_easy_perform(curl);														// Performing in blocking mode.
	if (easyRes != CURLE_OK)
	{
		err.setErrType(ErrType::ERR_WHILE_EASY_PERFORM);
		curl_easy_cleanup(curl);
		return false;
	}

	curl_easy_cleanup(curl);
	return true;
}

bool URLHandler::basicSetUpMultiPerform()
{
	curl_multi_add_handle(multiHandle, curl);			// Attaching easy handle to multi handle to perform non blocking.

	curl_easy_setopt(curl, CURLOPT_URL, URL);											// Setting URL we will connect to.
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);									// Telling CURL to follow redirection in case page we visit redirects us somewhere else.
	curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);		// Telling CURL to work with either HTTP or HTTPS.

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->curlCallback);					// Specifying callback function to be called when curl has to write the response.
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);								// Specifying "response" as the parameter to be passed to callback function as user data.

	return true;
}
