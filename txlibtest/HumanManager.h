#pragma once
#include "vladograpics.h"
#include "Human.h"

class HumanManager
{
public:
	HumanManager(void);
	void attach(int, int, int, int);
	void drag(Human *);
	void RightHandUp(Human *, double);
	~HumanManager(void);
	int isAttached;
private:
	POINT MouseOld;
};

