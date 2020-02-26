#pragma once
#include <fstream>
#include "TXLib.h"


void Init();
void vladoLine(int, int, int, int);
void vladoSetFillColor(COLORREF);
void vladoClear();
void vladoCircle(int, int, int);
void vladoSetColor(COLORREF);
void vladoClose();
void drawByFile(char []);
static std::ofstream outLog;