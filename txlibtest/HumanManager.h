#pragma once
#include "vladograpics.h"
#include "Human.h"
#include "Character.h"
class HumanManager
{
public:
	HumanManager(void);
	void attach(int, int, int, int);
	int drag(Human *);
	int drag(Character *);
	void RightHandUp(Human *, double);
	~HumanManager(void);
	int isAttached;
private:
	POINT MouseOld;
};

