#include "stdafx.h"
#include "Human.h"
#include <math.h>
#define PI 3.141592653
void Human::MoveTo ()
{
	int x, y;
	std::cout << "Enter x and y" << std::endl;
	std::cin >> x >> y;
	humanCoord.x = x;
	humanCoord.y = y;
	DrawHuman ();
}

int Human::GetRightHandTangle()
{
	return RightHandTangle;
}

void Human::SetRHandXY(POINT P)
{
	humanCoord.rightHandX = P.x;
	humanCoord.rightHandY = P.y;
}

int Human::GetHeight()
{
	return height;
}

void Human::DrawHuman()
{
	//vlado::UpdateWindow(1);
	//vlado::BeginDraw();
	vlado::SetFillColor (TX_BLACK);
    vlado::Clear ();
	vlado::SetColor (H_COLOR);
	vlado::Line (humanCoord.x, humanCoord.y, humanCoord.x + height, humanCoord.y - height); // left foot
	vlado::Line (humanCoord.x + height * 2, humanCoord.y, humanCoord.x + height, humanCoord.y - height); // right foot
	vlado::Line (humanCoord.x + height, humanCoord.y - height, humanCoord.x + height, humanCoord.y - height * 3); // body
	vlado::Circle (humanCoord.x + height, humanCoord.y - height * 3 - headSize, headSize); // head
	vlado::Line (humanCoord.x + height, humanCoord.y - height * 3, humanCoord.x, humanCoord.y - height * 2); // left hand 
	vlado::Line (humanCoord.x + height, humanCoord.y - height * 3, humanCoord.rightHandX, humanCoord.rightHandY); // right hand
	//vlado::Sleep (50);  
	//vlado::EndDraw();
}

void Human::SetX(int x)
{
	humanCoord.x = x;
}

void Human::SetY(int y)
{
	humanCoord.y = y;
}

void Human::SetCoord(POINT P)
{
	humanCoord.x = P.x;
	humanCoord.y = P.y;
	double RHAngle = (RightHandTangle * PI) / 180;
	humanCoord.rightHandX = (humanCoord.x + height) + height * cos (RHAngle);
	humanCoord.rightHandY = (humanCoord.y - height * 3) + height * sin (RHAngle);
}

void Human::SetRHandAngle(int angle)
{
	RightHandTangle = angle;
}

Human::Human (int x, int y, int Height, int sizeX, int sizeY)
{
	srand (time (NULL));
	H_COLOR = RGB (rand(), rand(), rand());
	height = Height;
	headSize = 30;
	humanCoord.x = x;
	humanCoord.y = y;
	humanCoord.rightHandX = humanCoord.x + height * 2;
	humanCoord.rightHandY = humanCoord.y - height * 2;
	RightHandTangle = 45;
	DrawHuman ();
}

int Human::GetX ()
{
	return humanCoord.x;
}

int Human::GetY ()
{
	return humanCoord.y;
}

int Human::GetXR ()
{
	return humanCoord.x + height * 2;
}

int Human::GetYR ()
{
	return humanCoord.y - height * 3 - headSize * 2;
}

void Human::changeColor ()
{
	int r, g, b;
	std::cout << "Enter RGB color" << std::endl;
	std::cin >> r >> g >> b;
	H_COLOR = RGB (r, g, b);
	DrawHuman ();
}

Human::~Human (void)
{
}
