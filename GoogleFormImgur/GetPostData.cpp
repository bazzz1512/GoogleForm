#include "GetPostData.h"

std::string AStrHuizen[9]{
	"DKH 't Strijdschip",
	"Gallinarium",
	"Homeros",
	"Idéfix",
	"Οἶκος Optimus",
	"Omega",
	"Phalleina",
	"Philomela",
	"Phoenix"
};

std::string AStrJaar[3]{
	"Gymnasium-4",
	"Gymnasium-5",
	"Gymnasium-6"
};

std::string AStrVerbeteringActiviteiten[]{
	"Alles",
	"Wat niet",
	"De hele mikmak"
};

std::string AStrVerbeteringHuizenuur[]{
	"Alles",
	"Wat niet",
	"De hele mikmak",
	""
};

std::string AStrVerbeteringTutor[]{
	"Alles",
	"Wat niet",
	"De hele mikmak",
	""
};

std::string AStrOpmerkingen[]{
	"Alles",
	"Wat niet",
	"De hele mikmak",
	""
};


void CPostData::GetRandomFBZX() {
	CPostData::RandomFBZX = std::to_string(((long int)rand()*(LONG_MAX - LONG_MIN) / (long int)LONG_MAX - LONG_MIN));
}

void CPostData::CompleteEndString() {
	CPostData::EndStringCompleted = CPostData::EndStringUncompleted + CPostData::RandomFBZX;
}

std::string CPostData::StrGetRandNum() {
	int randNum = rand() % (3 - 1 + 1) + 1;
	return std::to_string(randNum);
}

void gen_random(char *s, const int len) {
	static const char alphanum[] =
		"0123456789";

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	s[len] = 0;
}

int gen_randomint(int min, int max) {
	return rand() % (max - min + 1) + min;
}

void CPostData::GetPostDataStr() {
//	GetRandomFBZX();
	char randomnumber[20];
	gen_random(randomnumber, 19);
	RandomFBZX = randomnumber;
	CompleteEndString();
	std::string sb = "[[[null,1331226644,[\"" + AStrHuizen[gen_randomint(0,8)] + "\"]\r\n"
		",0]\r\n"
		",[null,1573624780,[\"" + AStrJaar[gen_randomint(0,2)] +"\"]\r\n"
		",0]\r\n"
		",[null,1026073671,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,1221645985,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,1654303147,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,1496779464,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,634098067,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,1759584021,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,999980218,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,1904099267,[\"Als je iets mocht veranderen aan de activiteiten, wat zou dat dan zijn en hoe zou je het anders willen?\"]\r\n" //Als je iets mocht veranderen aan de activiteiten, wat zou dat dan zijn en hoe zou je het anders willen?
		",0]\r\n"
		",[null,727468834,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,1326867202,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,986542467,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,1529998233,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,1709232691,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		", [null, 849045148, [\"Als je iets mocht veranderen aan je Huizenuur, wat zou dat dan zijn en hoe zou je het anders willen?\"]\r\n" //Als je iets mocht veranderen aan je Huizenuur, wat zou dat dan zijn en hoe zou je het anders willen?
		",0]\r\n"
		",[null,849045148,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,51591311,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,1405407033,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,1084000977,[\"te klein\"]\r\n"
		",0]\r\n"
		",[null,18332793,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,60836006,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,81530456,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,1905987581,[\"" + StrGetRandNum() + "\"]\r\n"
		",0]\r\n"
		",[null,257611018,[\"Als je iets mocht veranderen aan je het contact met je tutor, wat zou dat dan zijn en hoe zou je het anders willen?\"]\r\n" //Als je iets mocht veranderen aan je het contact met je tutor, wat zou dat dan zijn en hoe zou je het anders willen?
		",0]\r\n"
		"]\r\n"
		",null,\"" + RandomFBZX + "\"]\r\n";

	std::string StrOutput;
	if (CPostData::curl) {
		char *output = curl_easy_escape(CPostData::curl, sb.c_str(), 0);
		if (output) {
			StrOutput = output;
			curl_free(output);
		}
	}

	PostDataStr = BaseString + StrOutput + EndStringCompleted;

}