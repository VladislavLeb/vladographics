#include "stdafx.h"
#include "vladograpics.h"

std::ofstream OutLog;
COLORREF ActualCOLOR;
int isAnimation;

void vlado::BeginDraw()
{
	txBegin;
}

void vlado::EndDraw()
{
	txEnd();
}

void vlado::Init() // функция для инициализации окна и файла для хранения логов
{
	_txWindowStyle &= ~WS_CAPTION; // FullScreen: окно без заголовка, размером с экран
    int WinWidth = GetSystemMetrics (SM_CXSCREEN), WinHeight = GetSystemMetrics (SM_CYSCREEN);
    txCreateWindow (WinWidth, WinHeight);
	OutLog.open ("log.txt");
	isAnimation = 0;
}

void vlado::Line(int xFrom, int yFrom, int xTo, int yTo) // обертка для рисования линии
{
	txLine (xFrom, yFrom, xTo, yTo);
	if (!isAnimation)
		OutLog << "Line " << xFrom << " " << yFrom << " " << xTo << " " << yTo << std::endl;
}

void vlado::SetFillColor(COLORREF COLOR) // обертка для установления цвета заливки
{
	txSetFillColor (COLOR);
	ActualCOLOR = COLOR;
	if (!isAnimation)
		OutLog << "Fill_Color " << COLOR << std::endl;
}

void vlado::drawByMouse() // функция для рисования курсором мышки на окне
{
	vlado::SetFillColor (ActualCOLOR);
	vlado::SetColor (ActualCOLOR);
	int click = 0;
	while (!txGetAsyncKeyState (VK_ESCAPE))
	{
		if (vlado::MouseState () & 1)
		{
			vlado::Circle (vlado::MouseX (), vlado::MouseY (), 20);
		}
	}
}

int vlado::isKeyPressed(int button) 
{
	if (txGetAsyncKeyState (button))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void vlado::Clear()
{
	txClear ();
	if (!isAnimation)
		OutLog << "Clear" << std::endl;
}

void vlado::Circle(int x, int y, int r)
{
	txCircle (x, y, r);
	if (!isAnimation)
		OutLog << "Circle " << x << " " << y << " " << r << std::endl;
}

POINT vlado::MouseCoord()
{
	return txMousePos();
}

void vlado::UpdateWindow(int state)
{
	txUpdateWindow (state);
}

void vlado::SetColor(COLORREF COLOR)
{
	txSetColor (COLOR);
	ActualCOLOR = COLOR;
	if (!isAnimation)
		OutLog << "Color " << COLOR << std::endl;
}

int vlado::MouseX()
{
	return txMouseX();
}

int vlado::MouseY()
{
	return txMouseY();
}

unsigned vlado::MouseState()
{
	return txMouseButtons();
}

void vlado::Close()
{
	OutLog.close ();
}

void vlado::drawByFile(char s [])
{
	isAnimation = 1;
	std::string command;
	std::ifstream fin (s);
	if (!fin)
	{
		std::cout << "Are you joking? This file doesn't exist!" << std::endl;
		Sleep (1000);
	}
	vlado::BeginDraw();
	while (!fin.eof())
	{
		fin >> command;
		if (command == "Line")
		{
			int xFrom, yFrom, xTo, yTo;
			fin >> xFrom >> yFrom >> xTo >> yTo;
			vlado::Line (xFrom, yFrom, xTo, yTo);
		}
		if (command == "Circle")
		{
			int x, y, r;
			fin >> x >> y >> r;
			vlado::Circle (x, y, r);
		}
		if (command == "Color")
		{
			COLORREF COLOR;
			fin >> COLOR;
			vlado::SetColor (COLOR);
		}
		if (command == "Fill_Color")
		{
			COLORREF COLOR;
			fin >> COLOR;
			vlado::SetFillColor (COLOR);
		}
		if (command == "Clear")
		{
			txClear ();
		}
		//vlado::Sleep (50);
	}
	vlado::EndDraw();
	isAnimation = 0;
}

void vlado::Sleep(int time)
{
	txSleep(time);
}