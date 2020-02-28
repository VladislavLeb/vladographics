#include "stdafx.h"
#include "HumanManager.h"
#define PI 3.141592653

HumanManager::HumanManager(void)
{
	isAttached = 0;
}

void HumanManager::attach(int x, int y, int xl, int yl)
{
	if (!isAttached && vlado::MouseState() & 1 
		&& vlado::MouseX() > x && vlado::MouseX() < xl
		&& vlado::MouseY() < y && vlado::MouseY() > yl)
	{
		MouseOld = vlado::MouseCoord();
		isAttached = 1;
	}
	if (isAttached && !vlado::MouseState() & 1)
	{
		isAttached = 0;
	}
}

void HumanManager::RightHandUp(Human * PersonalHuman, double tangle)
{
	POINT RightHand;
	double MoveTangle = (tangle * PI) / 180;
	RightHand.x = (PersonalHuman -> GetX () + PersonalHuman -> GetHeight()) + PersonalHuman -> GetHeight() * cos (MoveTangle);
	RightHand.y = (PersonalHuman -> GetY () - PersonalHuman -> GetHeight() * 3) + PersonalHuman -> GetHeight() * sin (MoveTangle);
	PersonalHuman -> SetRHandXY (RightHand);
}

int HumanManager::drag(Human * PersonalHuman)
{
	int ShouldIRedraw = 0;
	POINT HumanCoord = {PersonalHuman -> GetX(), PersonalHuman -> GetY()};
	POINT MouseNew = vlado::MouseCoord();
	POINT HumanGoTo = {HumanCoord.x + MouseNew.x - MouseOld.x,
					   HumanCoord.y + MouseNew.y - MouseOld.y};
	PersonalHuman -> SetCoord (HumanGoTo);
	if (MouseOld.x != MouseNew.x ||
		MouseOld.y != MouseNew.y)
	{
		ShouldIRedraw = 1;	
	}
	else
	{
		ShouldIRedraw = 0;
	}
	MouseOld.x = MouseNew.x; 
	MouseOld.y = MouseNew.y; 
	return (ShouldIRedraw);
}

int HumanManager::drag(Character * character)
{
	int ShouldIRedraw = 0;
	POINT HumanCoord = {character -> GetX(), character -> GetY()};
	POINT MouseNew = vlado::MouseCoord();
	POINT HumanGoTo = {HumanCoord.x + MouseNew.x - MouseOld.x,
					   HumanCoord.y + MouseNew.y - MouseOld.y};
	character -> SetCoord (HumanGoTo);
	if (MouseOld.x != MouseNew.x ||
		MouseOld.y != MouseNew.y)
	{
		ShouldIRedraw = 1;	
	}
	else
	{
		ShouldIRedraw = 0;
	}
	MouseOld.x = MouseNew.x; 
	MouseOld.y = MouseNew.y; 
	return (ShouldIRedraw);
}

HumanManager::~HumanManager(void)
{
}
