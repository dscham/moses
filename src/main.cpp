#pragma once
#include <Windows.h>
#include <string>
#include <random>
#include <functional>


DWORD timeout = 1000; // default timeout for each movement in ms

namespace std{
	default_random_engine randomEngine;
	uniform_int_distribution<int> randomDistanceDistribution(50, 150);
	auto randomDistance = bind(randomDistanceDistribution, randomEngine);
	uniform_int_distribution<int> randomDirectionDistribution(0, 1);
	auto randomDirection = bind(randomDirectionDistribution, randomEngine);
}

int generateMovement(long from) {
	if(std::randomDirection())
		return from + std::randomDistance();

	return from - std::randomDistance();
}

int main(int argc, char* argv[]) {
	POINT cursorPos;

	if (argc == 2) { // argument is timeout
		timeout = std::stoi(argv[1]);
	}
	
	bool running = 1;
	while(running) {
		GetCursorPos(&cursorPos);
		SetCursorPos(generateMovement(cursorPos.x), generateMovement(cursorPos.y));
		Sleep(timeout);
	}

	return 0;
}