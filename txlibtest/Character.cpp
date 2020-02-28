#include "stdafx.h"
#include "Character.h"


Character::Character(std::string Name, std::string Path)
{
	name = Name;
	path = Path;
	commandNumber = 0;
	std::cout << "You add the character named: " << name << std::endl;
	//loadFromFile();
	calculateRectangle();
	//dx = 20;
	//dy = - 20;
	//vlado::SetFillColor(TX_BLACK);
	//vlado::Clear();
	/*while (true)
	{
		dx++;
		dy++;
		vlado::SetFillColor(TX_BLACK);
	    vlado::Clear();
		Drawing();
		vlado::Sleep(50);
	}*/
	Drawing();
}

void Character::Drawing()
{
	//vlado::SetFillColor(TX_BLACK);
	//vlado::Clear();
	for (int i = 0; i < commandNumber; i++)
	{
		if (AllCommands[i].name == "txLine")
		{
			//std::cout << args[0] << " " << args[1] << " " << args[2] << " " << args[3] << std::endl;
			vlado::Line (AllCommands[i].x, AllCommands[i].y, AllCommands[i].x1, AllCommands[i].y1);
		//	std::cout << AllCommands[i].x << " " << AllCommands[i].y << " " << AllCommands[i].x1 << " " << AllCommands[i].y1 << std::endl;
		}
		if (AllCommands[i].name == "txCircle")
		{
			vlado::Circle(AllCommands[i].x, AllCommands[i].y, AllCommands[i].r);
		}
		if (AllCommands[i].name == "txSetColor")
		{
			vlado::SetFillColor(AllCommands[i].COLOR);
		}
		if (AllCommands[i].name == "txSetFillColor")
		{
			vlado::SetFillColor(AllCommands[i].COLOR);
		}
		if (AllCommands[i].name == "txEllipse")
		{
			vlado::Ellipse (AllCommands[i].x, AllCommands[i].y, AllCommands[i].x1, AllCommands[i].y1);
			//std::cout << AllCommands[i].x << " " << AllCommands[i].y << " " << AllCommands[i].x1 << " " << AllCommands[i].y1 << std::endl;
		}
		if (AllCommands[i].name == "txClear")
		{
			vlado::Clear ();
		}
	}
	//std::cout << args[0] + dx << " " << args[1] + dy << " " << args[2] + dx << " " << args[3] + dy << std::endl;
//	fin.close(); 
	//vlado::Ellipse(xLB, yLB, xRT, yRT);
}

void Character::SetCoord(POINT FROM)
{
	xRT += FROM.x - xLB;
	yRT += FROM.y - yLB;
	dx = FROM.x - xLB;
	dy = FROM.y - yLB;
	xLB += dx;
	yLB  += dy;
	//std::cout << commandNumber;
	for (int i = 0; i < commandNumber; i++)
	{
		if (AllCommands[i].name == "txEllipse")
		{
			AllCommands[i].x += dx;
			AllCommands[i].y += dy;
			AllCommands[i].x1 += dx;
			AllCommands[i].y1 += dy;
		}
		if (AllCommands[i].name == "txLine")
		{
			AllCommands[i].x += dx;
			AllCommands[i].y += dy;
			AllCommands[i].x1 += dx;
			AllCommands[i].y1 += dy;
		}
		if (AllCommands[i].name == "txCircle")
		{
			AllCommands[i].x += dx;
			AllCommands[i].y += dy;
		}
	}
}

int Character::GetX()
{
	return xLB;
}

int Character::GetY()
{
	return yLB;
}

int Character::GetXR()
{
	return xRT;
}

int Character::GetYR()
{
	return yRT;
}

string Character::GetName()
{
	return name;
}

void Character::calculateRectangle()
{
	int xLMin = 9999, yLMax = 0, xRMax = 0, yRMin = 9999;
	std::string command;
	std::ifstream fin;
	fin.open(path);
	if (!fin)
	{
		std::cout << "Are you joking? This file doesn't exist!" << std::endl;
		Sleep (1000);
	}
	while (fin >> command)
	{
		if (command == "txLine")
		{
			const int count = 4;
			int args[count];
			vlado::GetArgs(args, &fin);
			AllCommands[commandNumber].name = command;
			AllCommands[commandNumber].x = args[0];
			AllCommands[commandNumber].y = args[1];
			AllCommands[commandNumber].x1 = args[2];
			AllCommands[commandNumber].y1 = args[3];
			commandNumber++;
		//	std::cout << args[0] << " " << args[1] << " " << args[2] << " " << args[3] << std::endl;
	//		vlado::Line (args[0], args[1], args[2], args[3]);
			if (args[0] < xLMin) xLMin = args[0];
			if (args[0] > xRMax) xRMax = args[0];
			if (args[2] < xLMin) xLMin = args[2];
			if (args[2] > xRMax) xRMax = args[2];
			if (args[1] < yRMin) yRMin = args[1];
			if (args[1] > yLMax) yLMax = args[1];
			if (args[3] < yRMin) yRMin = args[3];
			if (args[3] > yLMax) yLMax = args[3];
		}
		if (command == "txCircle")
		{
			const int count = 3;
			int args[count];
			vlado::GetArgs(args, &fin);
			AllCommands[commandNumber].name = command;
			AllCommands[commandNumber].x = args[0];
			AllCommands[commandNumber].y = args[1];
			AllCommands[commandNumber].r = args[2];
			commandNumber++;
		//	std::cout << args[0] << " " << args[1] << " " << args[2] << std::endl;
			//vlado::Circle (args[0], args[1], args[2]);
			if (args[0] < xLMin) xLMin = args[0];
			if (args[0] + args[2] > xRMax) xRMax = args[0];
			if (args[1] < yRMin) yRMin = args[1];
			if (args[1] + args[2] > yLMax) yLMax = args[1];
		}
		if (command == "txSetColor")
		{
			const int count = 1;
			int args[count];
			vlado::GetArgs(args, &fin);
			AllCommands[commandNumber].name = command;
			AllCommands[commandNumber].COLOR = args[0];
			commandNumber++;
		//	std::cout << args[0] << std::endl;
			//vlado::SetColor (args[0]);
		}
		if (command == "txSetFillColor")
		{
			const int count = 1;
			int args[count];
			vlado::GetArgs(args, &fin);
			AllCommands[commandNumber].name = command;
			AllCommands[commandNumber].COLOR = args[0];
			commandNumber++;
		//	std::cout << args[0] << std::endl;
			//vlado::SetFillColor (args[0]);
		}
		if (command == "txEllipse")
		{
			const int count = 4;
			int args[count];
			vlado::GetArgs(args, &fin);
			//std::cout << args[0] << " " << args[1] << " " << args[2] << " " << args[3] << std::endl;
			//Commands[0] = "txEllpise (" + args[0] + ', ' + args[1] + ', ' + args[2] + ', ' + args[3] + ');';
			//cout << Commands[0];
			
			AllCommands[commandNumber].name = command;
			AllCommands[commandNumber].x = args[0];
			AllCommands[commandNumber].y = args[1];
			AllCommands[commandNumber].x1 = args[2];
			AllCommands[commandNumber].y1 = args[3];

			commandNumber++;
		//	vlado::Sleep(5000);
		//	vlado::Ellipse (args[0], args[1], args[2], args[3]);
			if (args[0] < xLMin) xLMin = args[0];
			if (args[0] > xRMax) xRMax = args[0];
			if (args[2] < xLMin) xLMin = args[2];
			if (args[2] > xRMax) xRMax = args[2];
			if (args[1] < yRMin) yRMin = args[1];
			if (args[1] > yLMax) yLMax = args[1];
			if (args[3] < yRMin) yRMin = args[3];
			if (args[3] > yLMax) yLMax = args[3];
		}
		if (command == "txClear")
		{

			vlado::Clear ();
		}
	}
	xLB = xLMin;
	yLB = yLMax;
	xRT = xRMax;
	yRT = yRMin;
	//std::cout << xLB << " " << yLB << " " << xRT << " " << yRT << std::endl;
	POINT START = {xLB, yLB};
	SetCoord(START);
	fin.close();
}

void Character::loadFromFile()
{
	//std::cout << path << std::endl;
	//vlado::drawByFile(path);
}

Character::~Character(void)
{
}
