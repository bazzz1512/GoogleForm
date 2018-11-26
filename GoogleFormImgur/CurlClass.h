#pragma once
#include <stdio.h>
#include <curl/curl.h>
#include "GetPostData.h"



class CurlClass {
public:
	CURL* curl;
	CURLcode res;
	CPostData PostData;

	void ExecuteCurl();
	void StartThreads();
	int ThreadExecuteCurl();
	CurlClass() : PostData(curl) {}
};

extern CurlClass G_CCurlClass;


