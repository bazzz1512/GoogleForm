#include "CurlClass.h"
#include "SGlobal.h"
#include <thread>

CurlClass G_CCurlClass;

void CurlClass::ExecuteCurl() {
	SGlobal.AmountThreads++;
	while (true) {
		while (!SGlobal.ShouldStart) {
			std::this_thread::sleep_for(std::chrono::milliseconds(3));
		}
		while (SGlobal.ShouldStart && SGlobal.ShouldRun) {
			//		curl_easy_setopt(CCurlClass.curl, CURLOPT_POSTFIELDS, CCurlClass.PostData.PostDataStr.c_str());
			if (SGlobal.CheckBoxDebug)
			//			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "entry.444948769=ha&fvv=1&draftResponse=%5B%5B%5Bnull%2C795786708%2C%5B%22ad%22%5D%0D%0A%2C0%5D%0D%0A%5D%0D%0A%2Cnull%2C%224116965486144523552%22%5D%0D%0A&pageHistory=0%2C1&fbzx=4116965486144523552");
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "entry.1737744814_sentinel=&entry.1737744814=Argree&entry.1737744814=Also+Agree&fvv=1&draftResponse=%5Bnull%2Cnull%2C%22-3943645743380551133%22%5D%0D%0A&pageHistory=0&fbzx=-3943645743380551133");
			else {
				PostData.GetPostDataStr();
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, PostData.PostDataStr.c_str());
			}	
			res = curl_easy_perform(curl);
			/* Check for errors */
			if (res != CURLE_OK)
				fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
			SGlobal.TimesSent++;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

}

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
	return size * nmemb;
}

int CurlClass::ThreadExecuteCurl()
{
	CurlClass CCurlClass;
#define SKIP_PEER_VERIFICATION

	curl_global_init(CURL_GLOBAL_DEFAULT);

	CCurlClass.curl = curl_easy_init();
	CCurlClass.PostData.curl = CCurlClass.curl;
	if (CCurlClass.curl) {

		//Create string
#ifdef SKIP_PEER_VERIFICATION
		/*
		* If you want to connect to a site who isn't using a certificate that is
		* signed by one of the certs in the CA bundle you have, you can skip the
		* verification of the server's certificate. This makes the connection
		* A LOT LESS SECURE.
		*
		* If you have a CA cert for the server stored someplace else than in the
		* default bundle, then the CURLOPT_CAPATH option might come handy for
		* you.
		*/
		curl_easy_setopt(CCurlClass.curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
		/*
		* If the site you're connecting to uses a different host name that what
		* they have mentioned in their server certificate's commonName (or
		* subjectAltName) fields, libcurl will refuse to connect. You can skip
		* this check, but this will make the connection less secure.
		*/
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

		//		
		if (SGlobal.CheckBoxDebug)
//			curl_easy_setopt(CCurlClass.curl, CURLOPT_URL, "https://docs.google.com/forms/d/e/1FAIpQLSd0PlxcLOYgenk52MoECR_fDnAf1bqtQx_l1zDklHBcOjJvmQ/formResponse");
			curl_easy_setopt(CCurlClass.curl, CURLOPT_URL, "https://docs.google.com/forms/d/e/1FAIpQLSegmKXedXd7TCG0JQi2i-qsrbSDGL1yIJehQvXWfQ0TMMgOBQ/formResponse");
		else
			curl_easy_setopt(CCurlClass.curl, CURLOPT_URL, "https://docs.google.com/forms/d/e/1FAIpQLSck-EDtUfGmr2DsZFWrWl-IFybP9gVJ72XSgn0rjjIeppJ8UQ/formResponse");

		curl_easy_setopt(CCurlClass.curl, CURLOPT_FOLLOWLOCATION, TRUE);
		curl_easy_setopt(CCurlClass.curl, CURLOPT_POST, TRUE);
		curl_easy_setopt(CCurlClass.curl, CURLOPT_WRITEFUNCTION, write_data); //Debug messages

		CCurlClass.ExecuteCurl();


		/* always cleanup */
		curl_easy_cleanup(CCurlClass.curl);
	}

	curl_global_cleanup();
	//	std::cout << "Program Finished: \n" << s;
	return 0;
}

void CurlClass::StartThreads() {
	if (!SGlobal.Initialized) {
		for (int i = 1; i <= 100; ++i)
			SGlobal.threads.push_back(std::thread(&CurlClass::ThreadExecuteCurl, G_CCurlClass));
		SGlobal.Initialized = TRUE;
	}
	SGlobal.ShouldStart = TRUE;
}





