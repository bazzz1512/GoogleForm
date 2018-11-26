#pragma once
#include <iostream>
#include <vector>
#include <thread>



struct GlobalStruct {
	bool ShouldStart = false;
	bool ShouldRun = true;
	int TimesSent = 0;
	std::vector<std::thread> threads;
	int AmountThreads = 0;
	bool CheckBoxDebug = false;
	bool Initialized =	false;
};

extern GlobalStruct SGlobal;