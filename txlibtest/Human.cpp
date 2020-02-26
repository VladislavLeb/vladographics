#include "stdafx.h"
#include "Human.h"


void Human::MoveTo ()
{
	int x, y;
	std::cout << "Enter x and y" << std::endl;
	std::cin >> x >> y;
	humanCoord.x = x;
	humanCoord.y = y;
	humanCoord.rightHandX = humanCoord.x + height * 2;
	humanCoord.rightHandY = humanCoord.y - height * 2;
	DrawHuman ();
}

void Human::rightHandUp(int tangle)
{
	humanCoord.rightHandX = (humanCoord.x + height) + height * cos (tangle);
	humanCoord.rightHandY = (humanCoord.y - height * 3) + height * sin (tangle);
	DrawHuman();
}

void Human::rightHandDown()
{
	humanCoord.rightHandX += 1;
	humanCoord.rightHandY += 1;
}

void Human::DrawHuman()
{
	vladoSetFillColor (TX_BLACK);
    vladoClear ();
	vladoSetColor(H_COLOR);
	vladoLine (humanCoord.x, humanCoord.y, humanCoord.x + height, humanCoord.y - height); // left foot
	vladoLine (humanCoord.x + height * 2, humanCoord.y, humanCoord.x + height, humanCoord.y - height); // right foot
	vladoLine (humanCoord.x + height, humanCoord.y - height, humanCoord.x + height, humanCoord.y - height * 3); // body
	vladoCircle (humanCoord.x + height, humanCoord.y - height * 3 - 30, 30); // head
	vladoLine (humanCoord.x + height, humanCoord.y - height * 3, humanCoord.x, humanCoord.y - height * 2); // left hand 
	vladoLine (humanCoord.x + height, humanCoord.y - height * 3, humanCoord.rightHandX, humanCoord.rightHandY); // right hand
}

Human::Human (int x, int y, int Height, int sizeX, int sizeY)
{
	srand (time (NULL));
	H_COLOR = RGB (rand(), rand(), rand());
	height = Height;
	humanCoord.x = x;
	humanCoord.y = y;
	humanCoord.rightHandX = humanCoord.x + height * 2;
	humanCoord.rightHandY = humanCoord.y - height * 2;
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
