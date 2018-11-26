#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <curl/curl.h>

extern std::string AStrHuizen[9];
extern std::string AStrJaar[3];



class CPostData {
public:
	void GetPostDataStr();
	std::string PostDataStr;
	CURL* curl;
	CPostData(CURL* curl) : curl(curl) {}


private:
	void GetRandomFBZX();
	void CompleteEndString();
	std::string StrGetRandNum();
	std::string RandomFBZX;
	std::string UltimateBaseString = "entry.1563850579=1&entry.338432268=1&entry.1775340028=1&entry.36340669=1&entry.1800239883=1&entry.165142798=";
	std::string BaseString = "entry.1563850579=1&entry.338432268=1&entry.1775340028=1&entry.36340669=1&entry.1800239883=1&entry.165142798=&fvv=1&draftResponse=";
	std::string BaseStringWithResponse = "entry.1563850579=1&entry.338432268=1&entry.1775340028=1&entry.36340669=1&entry.1800239883=1&entry.165142798=Als+je+nog+andere+opmerkingen+of+suggesties+hebt%2C+kun+je+die+hieronder+kwijt&fvv=1&draftResponse=";
	std::string BaseStringEnd = "&fvv=1&draftResponse=";
	std::string EndStringUncompleted = "&pageHistory=0%2C1%2C2%2C3%2C4&fbzx=";
	std::string EndStringCompleted;
};