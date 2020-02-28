#pragma once
#include "vladograpics.h"
struct Commands
{
	string name;
	int x;
	int y;
	int x1;
	int y1;
	int r;
	COLORREF COLOR;
};
class Character
{
public:
	Character(std::string, std::string);
	~Character(void);
	void loadFromFile();
	void calculateRectangle();
	void Drawing();
	void SetX(int);
	void SetY(int);
	int GetX();
	int GetY();
	int GetXR();
	int GetYR();
	std::string GetName(); 
	void SetCoord(POINT);
private:
	int xLB, yLB, xRT, yRT, dx, dy;
	string name;
	int commandNumber;
	Commands AllCommands[1000];
	string path;
};

