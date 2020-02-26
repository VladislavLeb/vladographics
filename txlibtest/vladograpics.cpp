#include "stdafx.h"
#include "vladograpics.h"

void Init()
{
	_txWindowStyle &= ~WS_CAPTION; // FullScreen: окно без заголовка, размером с экран
    int WinHeight = GetSystemMetrics (SM_CXSCREEN), WinWidth = GetSystemMetrics (SM_CYSCREEN);
    txCreateWindow (WinHeight, WinWidth);
	outLog.open("log.txt");
}

void vladoLine(int xFrom, int yFrom, int xTo, int yTo)
{
	txLine(xFrom, yFrom, xTo, yTo);
	outLog << "Line " << xFrom << " " << yFrom << " " << xTo << " " << yTo << std::endl;
}

void vladoSetFillColor(COLORREF COLOR)
{
	txSetFillColor (COLOR);
	outLog << "Fill_Color " << COLOR << std::endl;
}

void vladoClear()
{
	txClear();
	outLog << "Clear" << std::endl;
}

void vladoCircle(int x, int y, int r)
{
	txCircle(x, y, r);
	outLog << "Circle " << x << " " << y << " " << r << std::endl;
}

void vladoSetColor(COLORREF COLOR)
{
	txSetColor(COLOR);
	outLog << "Color " << COLOR << std::endl;
}

void vladoClose()
{
	outLog.close();
}

void drawByFile(char s [])
{
	std::string command;
	std::ifstream fin (s);
	if (!fin)
	{
		std::cout << "Are you joking? This file doesn't exist!" << std::endl;
		Sleep(1000);
	}
	while (fin)
	{
		fin >> command;
		if (command == "Line")
		{
			int xFrom, yFrom, xTo, yTo;
			fin >> xFrom >> yFrom >> xTo >> yTo;
			vladoLine (xFrom, yFrom, xTo, yTo);
		}
		if (command == "Circle")
		{
			int x, y, r;
			fin >> x >> y >> r;
			vladoCircle (x, y, r);
		}
		if (command == "Color")
		{
			COLORREF COLOR;
			fin >> COLOR;
			vladoSetColor (COLOR);
		}
		if (command == "Fill_Color")
		{
			COLORREF COLOR;
			fin >> COLOR;
			vladoSetFillColor (COLOR);
		}
		if (command == "Clear")
		{
			txClear();
		}
	}
}