#pragma once
#include <fstream>
#include "TXLib.h"

namespace vlado
{
	void Sleep(int);
	void Init();
	void BeginDraw();
	void EndDraw();
	void Line(int, int, int, int);
	void SetFillColor(COLORREF);
	void Clear();
	void Circle(int, int, int);
	void SetColor(COLORREF);
	void Close();
	void UpdateWindow(int);
	void drawByFile(char []);
	int MouseX();
	int MouseY();
	POINT MouseCoord();
	unsigned MouseState();
	void drawByMouse();
	int isKeyPressed(int);
}
extern COLORREF ActualCOLOR;
extern int isAnimation;
extern std::ofstream outLog;