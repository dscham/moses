#pragma once
#include <Windows.h>
#include <string>
#include <random>
#include <functional>

const LPCSTR title = "Moses Oida";
bool clicking = false;

namespace std{
	default_random_engine randomEngine;
	uniform_int_distribution<int> randomDistanceDistribution(10, 100);
	auto randomDistance = bind(randomDistanceDistribution, randomEngine);
	uniform_int_distribution<int> randomDirectionDistribution(1, 8);
	auto randomDirection = bind(randomDirectionDistribution, randomEngine);
	uniform_int_distribution<int> randomTimeoutDistribution(1, 10);
	auto randomTimeout = bind(randomTimeoutDistribution, randomEngine);
	uniform_int_distribution<int> randomClickDistribution(0, 1);
	auto randomClick = bind(randomClickDistribution, randomEngine);
}

void moveMouse() {
	INPUT input[1] = {};
	ZeroMemory(input, sizeof input);

	input[0].type = INPUT_MOUSE;
	input[0].mi.dwFlags = MOUSEEVENTF_MOVE;

	const int xMove = std::randomDistance();
	const int yMove = std::randomDistance();

	switch(std::randomDirection()) {
		case 1:
			input[0].mi.dx = xMove;
			input[0].mi.dy = 0;
			break;
		case 2:
			input[0].mi.dx = 0;
			input[0].mi.dy = yMove;
			break;
		case 3:
			input[0].mi.dx = -xMove;
			input[0].mi.dy = 0;
			break;
		case 4:
			input[0].mi.dx = 0;
			input[0].mi.dy = -yMove;
			break;
		case 5:
			input[0].mi.dx = xMove;
			input[0].mi.dy = yMove;
			break;
		case 6:
			input[0].mi.dx = -xMove;
			input[0].mi.dy = yMove;
			break;
		case 7:
			input[0].mi.dx = xMove;
			input[0].mi.dy = -yMove;
			break;
		case 8:
			input[0].mi.dx = -xMove;
			input[0].mi.dy = -yMove;
			break;
	}

	SendInput(ARRAYSIZE(input), input, sizeof INPUT);
	printf("Mousemove sent. {x: %d, y: %d}.\r\n", xMove, yMove);

	if (std::randomClick() && clicking) {
		INPUT input[1] = {};
		ZeroMemory(input, sizeof input);

		input[0].type = INPUT_MOUSE;
		input[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;

		SendInput(ARRAYSIZE(input), input, sizeof INPUT);
		printf("Mouse middle down sent.\r\n");

		Sleep(150);

		input[0].type = INPUT_MOUSE;
		input[0].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;

		SendInput(ARRAYSIZE(input), input, sizeof INPUT);
		printf("Mouse middle up sent.\r\n");
	}
}

int main(int argc, char* argv[]) {
	SetConsoleTitleA(title);

	if (argc == 2) {
		clicking = argv[1];
	}

	bool running = 1;
	while (running) {
		moveMouse();

		const int timeout = std::randomTimeout();
		printf("Next in: %d seconds\r\n", timeout);
		Sleep( timeout * 1000);
	}
}