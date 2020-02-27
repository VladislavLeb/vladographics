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
	int GetXR ();
	int GetYR ();
	int GetHeight();
	int GetRightHandTangle();
	void SetRHandXY(POINT);
	void SetRHandAngle(int);
	void SetX (int);
	void SetY (int);
	void SetCoord(POINT);
	void MoveTo ();
	void changeColor ();
	void DrawHuman ();
private:
	COLORREF H_COLOR;
	coord humanCoord;
	int height;
	int RightHandTangle;
	int headSize;
};

