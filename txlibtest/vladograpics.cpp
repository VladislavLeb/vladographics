#include "stdafx.h"
#include "vladograpics.h"
#include <string>
std::ofstream OutLog;
COLORREF ActualCOLOR;
int AnimeComNum;
AnimCommands AnimeCommands[2000];

int isAnimation, isDrawing;

void vlado::BeginDraw()
{
	txBegin();
}

void vlado::EndDraw()
{
	txEnd();
}

void vlado::Init() // функция для инициализации окна и файла для хранения логов
{
	vlado::BeginDraw();
	_txWindowStyle &= ~WS_CAPTION; // FullScreen: окно без заголовка, размером с экран
    int WinWidth = GetSystemMetrics (SM_CXSCREEN), WinHeight = GetSystemMetrics (SM_CYSCREEN);
    txCreateWindow (WinWidth, WinHeight);
	srand ( time (NULL));
	ActualCOLOR = RGB (rand(), rand(), rand());
	isAnimation = 0;
	isDrawing = 0;
}

void vlado::Ellipse(int xFrom, int yFrom, int xTo, int yTo)
{
	txEllipse (xFrom, yFrom, xTo, yTo);
	if (!isAnimation && isDrawing)
		OutLog << "txEllipse (" << xFrom << ", " << yFrom << ", " << xTo << ", " << yTo << ");" << std::endl;
}

void vlado::Line(int xFrom, int yFrom, int xTo, int yTo) // обертка для рисования линии
{
	txLine (xFrom, yFrom, xTo, yTo);
	if (!isAnimation && isDrawing)
		OutLog << "txLine (" << xFrom << ", " << yFrom << ", " << xTo << ", " << yTo << ");" << std::endl;
}

void vlado::SetFillColor(COLORREF COLOR) // обертка для установления цвета заливки
{
	txSetFillColor (COLOR);
	if (!isAnimation && isDrawing)
		OutLog << "txSetFillColor (" << COLOR << ");" << std::endl;
}

void vlado::HelpDrawing()
{
	txClearConsole();
	std::cout << "If you want to change the color of the brush press 'tab'" << std::endl;
	std::cout << "If you want to change the size of the brush press '+' or '-'" << std::endl;
}

void vlado::AnimeCreator()
{
	std::cout << "Enter the name of you charter, logfile will be named the same:" << std::endl;
	std::string filename;
	std::cin >> filename;
	filename += ".txt";
	OutLog.open(filename);
	std::cout << "Okay. If you want to stop this mode press ESC" << std::endl;
	isDrawing = 1;
}

void vlado::SetIsDrawing()
{
	isDrawing = 0;
}

void vlado::drawByMouse() // функция для рисования курсором мышки на окне
{
	vlado::SetFillColor (ActualCOLOR);
	vlado::SetColor (ActualCOLOR);
	int click = 0, brushSize = 20;
	isDrawing = 1;
	char * filename = new char [255];
	txClearConsole();
	std::cout << "Enter the name of you charter, logfile will be named the same:" << std::endl;
	std::cin >> filename;
	OutLog.open (filename);
	vlado::HelpDrawing();
	while (!txGetAsyncKeyState (VK_ESCAPE))
	{
		if (txGetAsyncKeyState (VK_TAB))
		{
			int r, g, b;
			std::cout << "Enter the RGB color (3 number):" << std::endl;
			cin >> r >> g >> b;
			ActualCOLOR = RGB(r, g, b);
			vlado::HelpDrawing();
		}
		if (txGetAsyncKeyState (VK_OEM_PLUS))
		{
			brushSize++;
			Sleep(10);
		}
		if (txGetAsyncKeyState (VK_OEM_MINUS))
		{
			brushSize--;
			Sleep(10);
		}
		if (vlado::MouseState () & 1)
		{
			vlado::SetFillColor (ActualCOLOR);
			vlado::SetColor (ActualCOLOR);
			vlado::Circle (vlado::MouseX (), vlado::MouseY (), brushSize);
		}
		if (vlado::MouseState () & 2)
		{
			vlado::SetFillColor(TX_BLACK);
			vlado::SetColor (TX_BLACK);
			vlado::Circle (vlado::MouseX (), vlado::MouseY (), brushSize);
		}
	}
	OutLog.close();
}

int vlado::isKeyPressed(int button) 
{
	if (txGetAsyncKeyState (button))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void vlado::Clear()
{
	txClear ();
	if (!isAnimation)
		OutLog << "txClear ();" << std::endl;
}

void vlado::Circle(int x, int y, int r)
{
	txCircle (x, y, r);
	if (!isAnimation && isDrawing)
		OutLog << "txCircle (" << x << ", " << y << ", " << r << ");" << std::endl;
}

POINT vlado::MouseCoord()
{
	return txMousePos();
}

void vlado::UpdateWindow(int state)
{
	txUpdateWindow (state);
}

void vlado::SetColor(COLORREF COLOR)
{
	txSetColor (COLOR);
	if (!isAnimation && isDrawing)
		OutLog << "txSetColor (" << COLOR << ");" << std::endl;
}

int vlado::MouseX()
{
	return txMouseX();
}

int vlado::MouseY()
{
	return txMouseY();
}

unsigned vlado::MouseState()
{
	return txMouseButtons();
}

void vlado::Close()
{
	//OutLog.close ();
}

void vlado::GetArgs(int *args, std::ifstream *fin)
{
	std::string num = "";
	int i = 0;
	char letter = '~';
	while (letter != '(')
		fin -> get(letter);
	while (true)
	{
		fin -> get(letter);
		if (isdigit(letter))
		{
			num += letter;
		}
		if (letter == ' ' || letter == ')')
		{
			args[i] = std::atoi(num.c_str());
			num = "";
			i++;
		}
		if (letter == ';')
		{
			break;
		}
	}
}

void vlado::readFromFile(string s)
{
	/*isAnimation = 1;
	std::string command;
	std::ifstream fin;
	fin.open(s);
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
			//std::cout << args[0] << " " << args[1] << " " << args[2] << " " << args[3] << std::endl;
			vlado::Line (args[0], args[1], args[2], args[3]);
		}
		if (command == "txCircle")
		{
			const int count = 3;
			int args[count];
			vlado::GetArgs(args, &fin);
			//std::cout << args[0] << " " << args[1] << " " << args[2] << std::endl;
			vlado::Circle (args[0], args[1], args[2]);
		}
		if (command == "txSetColor")
		{
			const int count = 1;
			int args[count];
			vlado::GetArgs(args, &fin);
			//std::cout << args[0] << std::endl;
			vlado::SetColor (args[0]);
		}
		if (command == "txSetFillColor")
		{
			const int count = 1;
			int args[count];
			vlado::GetArgs(args, &fin);
			//std::cout << args[0] << std::endl;
			vlado::SetFillColor (args[0]);
		}
		if (command == "txEllipse")
		{
			const int count = 4;
			int args[count];
			vlado::GetArgs(args, &fin);
			//std::cout << args[0] << " " << args[1] << " " << args[2] << " " << args[3] << std::endl;
			vlado::Ellipse (args[0], args[1], args[2], args[3]);
		}
		if (command == "txClear")
		{
			vlado::Clear ();
		}
		//vlado::Sleep(10);
	}
	fin.close();
	std::cout << "STOOOOOPPPPPP"; */
	AnimeComNum = 0;
	std::string command;
	std::ifstream fin;
	fin.open(s);
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
			AnimeCommands[AnimeComNum].name = command;
			AnimeCommands[AnimeComNum].x = args[0];
			AnimeCommands[AnimeComNum].y = args[1];
			AnimeCommands[AnimeComNum].x1 = args[2];
			AnimeCommands[AnimeComNum].y1 = args[3];
			AnimeComNum++;
		}
		if (command == "txCircle")
		{
			const int count = 3;
			int args[count];
			vlado::GetArgs(args, &fin);
			AnimeCommands[AnimeComNum].name = command;
			AnimeCommands[AnimeComNum].x = args[0];
			AnimeCommands[AnimeComNum].y = args[1];
			AnimeCommands[AnimeComNum].r = args[2];
			AnimeComNum++;
		}
		if (command == "txSetColor")
		{
			const int count = 1;
			int args[count];
			vlado::GetArgs(args, &fin);
			AnimeCommands[AnimeComNum].name = command;
			AnimeCommands[AnimeComNum].COLOR = args[0];
			AnimeComNum++;
		}
		if (command == "txSetFillColor")
		{
			const int count = 1;
			int args[count];
			vlado::GetArgs(args, &fin);
			AnimeCommands[AnimeComNum].name = command;
			AnimeCommands[AnimeComNum].COLOR = args[0];
			AnimeComNum++;
		}
		if (command == "txEllipse")
		{
			const int count = 4;
			int args[count];
			vlado::GetArgs(args, &fin);
			
			AnimeCommands[AnimeComNum].name = command;
			AnimeCommands[AnimeComNum].x = args[0];
			AnimeCommands[AnimeComNum].y = args[1];
			AnimeCommands[AnimeComNum].x1 = args[2];
			AnimeCommands[AnimeComNum].y1 = args[3];

			AnimeComNum++;
		}
		if (command == "txClear")
		{
			AnimeCommands[AnimeComNum].name = command;
			AnimeComNum++;
			vlado::Clear ();
		}
	}
	fin.close();
}

void vlado::drawByFile()
{
	for (int i = 0; i < AnimeComNum; i++)
	{	//	vlado::SetFillColor(TX_BLACK);
		//vlado::Clear();
		if (AnimeCommands[i].name == "txLine")
		{
			//std::cout << args[0] << " " << args[1] << " " << args[2] << " " << args[3] << std::endl;
			vlado::Line (AnimeCommands[i].x, AnimeCommands[i].y, AnimeCommands[i].x1, AnimeCommands[i].y1);
		//	std::cout << AnimeCommands[i].x << " " << AnimeCommands[i].y << " " << AnimeCommands[i].x1 << " " << AnimeCommands[i].y1 << std::endl;
		}
		if (AnimeCommands[i].name == "txCircle")
		{
			vlado::Circle(AnimeCommands[i].x, AnimeCommands[i].y, AnimeCommands[i].r);
		}
		if (AnimeCommands[i].name == "txSetColor")
		{
			vlado::SetFillColor(AnimeCommands[i].COLOR);
		}
		if (AnimeCommands[i].name == "txSetFillColor")
		{
			vlado::SetFillColor(AnimeCommands[i].COLOR);
		}
		if (AnimeCommands[i].name == "txEllipse")
		{
			vlado::Ellipse (AnimeCommands[i].x, AnimeCommands[i].y, AnimeCommands[i].x1, AnimeCommands[i].y1);
			//std::cout << AnimeCommands[i].x << " " << AnimeCommands[i].y << " " << AnimeCommands[i].x1 << " " << AnimeCommands[i].y1 << std::endl;
		}
		if (AnimeCommands[i].name == "txClear")
		{
			vlado::Clear ();
		}
		vlado::Sleep(2);
	}
	isAnimation = 0;
}

void vlado::Sleep(int time)
{
	txSleep(time);
}