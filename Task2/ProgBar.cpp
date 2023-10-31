#include <iostream>
#include "ProgBar.h"
#include "ConsParam.h"
#include <thread>

using namespace std::chrono_literals;


ProgBar::ProgBar(int x, int y, int wid) : X(x), Y(y), WidBar(wid) {}

void ProgBar::Start() {

	const char sym = '-';
	for (int i = X; i < WidBar + X; ++i)
	{
		consoleParameter::setPos(i, Y);
		std::cout << sym;
		std::this_thread::sleep_for(400ms);
	}
}
HANDLE consoleParameter::hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);