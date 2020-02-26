// txlibtest.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "Human.h"
#include <iostream>
 
void askCommand(Human *);
void doCommand(Human *, int);
void raiseHand(Human *);

int _tmain(int argc, _TCHAR* argv[])
{
	Init();

	Human PersonalHuman (50, 756, 50);

	while (true)
	{
		askCommand (&PersonalHuman);
	}
	
	vladoClose();
	return 0;
}


void raiseHand(Human *PersonalHuman)
{
	int i = 10, tangleHand = 0;
	while (i--)
	{
		tangleHand += (tangleHand == 360 ? 1 : -360);
		PersonalHuman -> rightHandUp (tangleHand);
		Sleep (50);
	}
}

void doCommand(Human *PersonalHuman, int command)
{
	if (command < 1 || command > 4)
	{
		std::cout << "Are you serious? I tell you press 1 or 2, not " << command
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
		drawByFile(path);
		delete [] path;
	}
}

void askCommand(Human *PersonalHuman)
{
	int command;
	system ("CLS");
	std::cout << "If you want change color enter the number 1 and press ENTER button" << std::endl;
	std::cout << "If you want move to new coord enter the number 2 and press ENTER button" << std::endl;
	std::cout << "If you want raise his right hand enter the number 3 and press ENTER button" << std::endl;
	std::cout << "If you want to draw picture by log file enter the number 4 and press the butt" << std::endl;
	std::cin >> command;
	doCommand(PersonalHuman, command);
}
