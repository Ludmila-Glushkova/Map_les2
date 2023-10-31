#pragma once
#include <windows.h>


class consoleParameter
{
private:
	static HANDLE hStdOut;

public:
	static void setPos(int x, int y)
	{
		COORD p;
		p.X = x;
		p.Y = y;
		SetConsoleCursorPosition(hStdOut, p);
	}
};
