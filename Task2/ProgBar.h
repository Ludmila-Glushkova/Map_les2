#pragma once
#include <mutex>

class ProgBar {

private:
	int X;
	int Y;
	int WidBar;

public:
	ProgBar(int x, int y, int wid);

	void Start();
};
