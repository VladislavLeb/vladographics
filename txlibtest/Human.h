#pragma once
#include "vladograpics.h"
struct coord
{
	int x; 
	int y;
	int rightHandX;
	int rightHandY;
};

class Human
{
public:
	Human (int x, int y, int Height, int sizeX = 1, int sizeY = 1);
	~Human (void);
	int GetX ();
	int GetY ();
	void MoveTo ();
	void changeColor ();
	void rightHandUp (int);
	void rightHandDown ();
private:
	COLORREF H_COLOR;
	coord humanCoord;
	void DrawHuman ();
	int height;
};

