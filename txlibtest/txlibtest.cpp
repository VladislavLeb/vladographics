// txlibtest.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "Human.h"
#include "HumanManager.h"
#include "Character.h"
#include <iostream>

#define PI 3.141592653

void askCommand(std::vector <Human> *, std::vector <Character> *);
void riseRightHand(std::vector <Human> *);
void doCommand(int, std::vector <Human> *, std::vector <Character> *);
void riseHand(int, std::vector <Human> *);
void testGraphics(int , int);
void reDraw(std::vector <Human> *);
void reDraw(std::vector <Character> *);
int askNumber();


int _tmain(int argc, _TCHAR* argv[])
{
	vlado::Init();

	std::vector <Human> PersonalHuman;
	std::vector <Character> MyCharacters;
	while (true)
	{
		reDraw (&PersonalHuman);
		askCommand (&PersonalHuman, &MyCharacters);
	//	vlado::UpdateWindow(0);
	}
	vlado::Close();
	return 0;
}

void reDraw(std::vector <Human> * PersonalHuman)
{
	for (auto human = PersonalHuman -> begin(); human != PersonalHuman -> end(); ++human) 
		human -> DrawHuman ();
}

void reDraw(std::vector <Character> * MyCharatcer)
{
	for (auto human = MyCharatcer -> begin(); human != MyCharatcer -> end(); ++human) 
		human -> Drawing ();
}

void riseHand(int number,std::vector <Human> * PersonalHuman)
{
	HumanManager * manager = new HumanManager;
	int tangle = 0;
	std::cout << "Enter the angle" << std::endl;
	std::cin >> tangle;
	double OldTangle = (double) PersonalHuman -> at (number).GetRightHandTangle();
	while (tangle != OldTangle)
	{
		vlado::Clear ();
		manager -> RightHandUp (&PersonalHuman -> at (number), OldTangle);
		OldTangle += (tangle > OldTangle ? 1 : -1);
		PersonalHuman -> at (number).SetRHandAngle (OldTangle);
		reDraw (PersonalHuman);
		vlado::Sleep (40);
	}
}

void doCommand(int command, std::vector <Human> * PersonalHuman, std::vector <Character> * MyCharacter)
{
	if (command < 1 || command > 8)
	{
		std::cout << "Are you serious? I tell you press 1 .. 8, not " << command
				  << std::endl << "Ok, i'll give you another try" << std::endl;
		Sleep (1000);
		askCommand (PersonalHuman, MyCharacter);
	}
	if (command == 1)
	{
		int number = askNumber ();
		PersonalHuman -> at (number).changeColor(); 
	}
	if (command == 2)
	{
		txClearConsole();
		std::cout << "NOTICE: All your animation automaticly sending to Disney!" << std::endl;
		vlado::AnimeCreator();
	}
	if (command == 3)
	{
		int number = askNumber ();
		riseHand (number, PersonalHuman);
	}
	if (command == 4)
	{
		std::cout << "OK, now enter the path to file and press ENTER" << std::endl;
		string path;
		std::cin >> path;
		vlado::readFromFile(path);
		vlado::drawByFile();
	}
	if (command == 5)
	{
		std::cout << "Press ESC to leave this mode" << std::endl;
		vlado::drawByMouse ();
	}
	if (command == 6)
	{
		std::cout << "Enter the name of character:" << std::endl;
		std::string name;
		std::cin >> name;
		auto it = std::find_if(MyCharacter -> begin(), MyCharacter -> end(), [&name](Character& obj) {return obj.GetName() == name;});
		if (it != MyCharacter -> end())
		{
		// found element. it is an iterator to the first matching element.
		// if you really need the index, you can also get it:
			auto index = std::distance(MyCharacter -> begin(), it);
			//MyCharacter -> at(index).loadFromFile();
			std::cout << "Press ESC to leave this mode" << std::endl;
			HumanManager * manager = new HumanManager;
			while (!vlado::isKeyPressed (VK_ESCAPE))
			{
				//vlado::Clear();
				manager -> attach (it -> GetX(), it -> GetY(), 
								   it -> GetXR(), it -> GetYR());
				if (manager -> isAttached)
				{
					std::cout << "ATTACHED" << std::endl;
					if (manager -> drag (&MyCharacter -> at(index))) 
					{
						vlado::Clear();
						reDraw (MyCharacter);
					}
				}
				
				vlado::Sleep (50);
			}
			vlado::SetIsDrawing();
			delete manager; 


		}
		

		/* int number = askNumber ();
		auto NUM = PersonalHuman -> begin () + number;
		std::cout << "Press ESC to leave this mode" << std::endl;
		HumanManager * manager = new HumanManager;
		while (!vlado::isKeyPressed (VK_ESCAPE))
		{
			//vlado::Clear();
			manager -> attach (NUM -> GetX(), NUM -> GetY(), 
							   NUM -> GetXR(), NUM -> GetYR());
			if (manager -> isAttached)
			{
				if (manager -> drag (&PersonalHuman -> at(number))) {vlado::Clear();}
			}
			reDraw (PersonalHuman);
			vlado::Sleep (50);
		}
		delete manager; 
		*/
	}
	if (command == 7)
	{
		int x, y, height;
		std::cout << "Enter the position and height of the Human" << std::endl;
		std::cin >> x >> y >> height;
		Human * HtoPush = new Human (x, y, height);
		PersonalHuman -> push_back (*HtoPush);
		delete HtoPush;
	}
	if (command == 8)
	{
		std::cout << "OK, now enter the path to file and press ENTER" << std::endl;
		string path;
		std::cin >> path;

		int i = 0;
		string CharacterName;
		while (path[i] != '.')
		{
			CharacterName += path[i];
			i++;
		}

		Character* ChToPush = new Character (CharacterName, path);
		MyCharacter -> push_back (*ChToPush);
		delete ChToPush;
		
	}
}

int askNumber()
{
	std::cout << "Chose number of human" << std::endl;
	int number = 0;
	std::cin >> number;
	return number;
}

void askCommand(std::vector <Human> * PersonalHuman, std::vector <Character> * MyCharacter)
{
	int command = 0;
	system ("CLS");
	std::cout << "If you want to change color enter the number 1 and press ENTER button" << std::endl;
	std::cout << "If you want to create your animation enter the number 2 and press ENTER button" << std::endl;
	std::cout << "If you want to raise his right hand enter the number 3 and press ENTER button" << std::endl;
	std::cout << "If you want to draw picture by log file enter the number 4 and press the butt" << std::endl;
	std::cout << "If you want to draw circle by mouse position enter the number 5 and press ENTER button" << std::endl;
	std::cout << "If you want to change position of character by mouse enter the number 6 and press ENTER button" << std::endl;
	std::cout << "If you want to create Human enter the number 7 and press ENTER button" << std::endl;
	std::cout << "If you want to add character from file enter the number 8 and press ENTER button" << std::endl;
	std::cin >> command;
	doCommand (command, PersonalHuman, MyCharacter);
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