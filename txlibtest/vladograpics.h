#pragma once
#include <fstream>
#include "TXLib.h"
struct AnimCommands
{
	string name;
	int x;
	int y;
	int x1;
	int y1;
	int r;
	COLORREF COLOR;
};
namespace vlado
{
	void Sleep(int);
	void Init();
	void BeginDraw();
	void EndDraw();
	void Line(int, int, int, int);
	void Ellipse(int, int, int, int);
	void SetFillColor(COLORREF);
	void Clear();
	void AnimeCreator();
	void Circle(int, int, int);
	void SetColor(COLORREF);
	void Close();
	void UpdateWindow(int);
	void drawByFile();
	void SetIsDrawing();
	void readFromFile(std::string s);
	int MouseX();
	int MouseY();
	void HelpDrawing();
	void GetArgs(int *, std::ifstream *);
	POINT MouseCoord();
	unsigned MouseState();
	void drawByMouse();
	int isKeyPressed(int);

}
extern	int AnimeComNum;
extern	AnimCommands AnimeCommands[2000];
extern COLORREF ActualCOLOR;
extern int isDrawing;
extern int isAnimation;
extern std::ofstream OutLog;