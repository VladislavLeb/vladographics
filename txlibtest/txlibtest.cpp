// txlibtest.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "Human.h"
#include "HumanManager.h"
#include <iostream>
 
void askCommand(Human *);
void doCommand(Human *, int);
void raiseHand(Human *);
void testGraphics(int , int);


int _tmain(int argc, _TCHAR* argv[])
{
	vlado::Init();

	Human PersonalHuman (50, 756, 50);

	while (true)
	{
		askCommand (&PersonalHuman);
	//	vlado::UpdateWindow(0);
	}
	
	vlado::Close();
	return 0;
}


void raiseHand(Human *PersonalHuman)
{
	HumanManager * manager = new HumanManager;
	int  tangle;
	std::cout << "Enter the angle" << std::endl;
	std::cin >> tangle;
	manager -> RightHandUp (PersonalHuman, (double)tangle);
}

void doCommand(Human *PersonalHuman, int command)
{
	if (command < 1 || command > 6)
	{
		std::cout << "Are you serious? I tell you press 1 .. 6, not " << command
				  << std::endl << "Ok, i'll give you another try" << std::endl;
		Sleep (1000);
		askCommand(PersonalHuman);
	}
	if (command == 1)
	{
		PersonalHuman -> changeColor (); 
	}
	if (command == 2)
	{
		PersonalHuman -> MoveTo ();
	}
	if (command == 3)
	{
		raiseHand (PersonalHuman);
	}
	if (command == 4)
	{
		std::cout << "OK, now enter the path to file and press ENTER" << std::endl;
		char *path = new char[255];
		std::cin >> path;
		vlado::drawByFile(path);
		delete [] path;
	}
	if (command == 5)
	{
		std::cout << "Press ESC to leave this mode" << std::endl;
		vlado::drawByMouse();
	}
	if (command == 6)
	{
		std::cout << "Press ESC to leave this mode" << std::endl;
		HumanManager * manager = new HumanManager;
		vlado::BeginDraw();
		while (!vlado::isKeyPressed (VK_ESCAPE))
		{
			manager -> attach (PersonalHuman -> GetX(), PersonalHuman -> GetY(), 
							   PersonalHuman -> GetXR(), PersonalHuman -> GetYR());
			if (manager -> isAttached)
			{
				manager -> drag (PersonalHuman);
			}
			vlado::Sleep(20);
		}
		vlado::EndDraw();
		delete manager; 
		/* 
		vlado::SetFillColor (TX_BLACK);
		vlado::Clear ();
		int x = 60, y = 500, isAttach = 0;
		testGraphics (x, y);
		int mouseOldX = vlado::MouseX(), mouseOldY = vlado::MouseY();
		while (true)
		{
			if (vlado::MouseState() & 1 
				&& vlado::MouseX() > x && vlado::MouseX() < x + 100
				&& vlado::MouseY() < y && vlado::MouseY() > y - 150 - 60) 
				isAttach = 1; 
			else 
				isAttach = 0;
			
			if (isAttach)
			{
				std::cout << "ATTACH" << std::endl;
				vlado::SetColor (RGB (90, 200, 30));
				x = vlado::MouseX();
				y = vlado::MouseY();
			}
			
			if (mouseOldX != vlado::MouseX() || mouseOldY != vlado::MouseY())
			{
				std::cout << "DRAG" << std::endl;
				testGraphics (x, y);
			}

			mouseOldX = vlado::MouseX();
			mouseOldY = vlado::MouseY();

			txSleep();
		} 
		*/
	}
}

void askCommand(Human *PersonalHuman)
{
	int command = 0;
	system ("CLS");
	std::cout << "If you want change color enter the number 1 and press ENTER button" << std::endl;
	std::cout << "If you want move to new coord enter the number 2 and press ENTER button" << std::endl;
	std::cout << "If you want raise his right hand enter the number 3 and press ENTER button" << std::endl;
	std::cout << "If you want to draw picture by log file enter the number 4 and press the butt" << std::endl;
	std::cout << "If you want to draw circle by mouse position enter the number 5 and press ENTER button" << std::endl;
	std::cout << "If you want to change position of Human by mouse enter the number 6 and press ENTER button" << std::endl;
	std::cin >> command;
	doCommand(PersonalHuman, command);
}

void testGraphics(int x, int y)
{
	int height = 50, headSize = 30;
	int rightHandX = x + height * 2;
	int rightHandY = y - height * 2;
	vlado::SetFillColor (TX_BLACK);
	vlado::Clear ();
	vlado::Line (x, y, x + height, y - height); // left foot
	vlado::Line (x + height * 2, y, x + height, y - height); // right foot
	vlado::Line (x + height, y - height, x + height, y - height * 3); // body
	vlado::Circle (x + height, y - height * 3 - headSize, headSize); // head
	vlado::Line (x + height, y - height * 3, x, y - height * 2); // left hand 
	vlado::Line (x + height, y - height * 3, rightHandX, rightHandY); // right hand
}