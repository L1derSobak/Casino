
#include <iostream>
#include <clocale>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include "Game.h"

using namespace std;

void DrawMyIcon();
void MainMenu();
void setCurPos(int x, int y, char str[]);
void drawExitMessage();

const short eMessageXSize = 120;
short eMessageYSize = 12; //34
char exitMessage1[] = { "      _____                    _  _                   _         " };
char exitMessage2[] = { "   |  __ \\                  | || |                 | |      " };
char exitMessage3[] = { "   | |  \\/  ___    ___    __| || |__   _   _   ___ | |      " };
char exitMessage4[] = { " | | __  / _ \\  / _ \\  / _` || '_ \\ | | | | / _ \\| |   " };
char exitMessage5[] = { "  | |_\\ \\| (_) || (_) || (_| || |_) || |_| ||  __/|_|     " };
char exitMessage6[] = { "\\____/ \\___/  \\___/  \\__,_||_.__/  \\__, | \\___|(_) " };
char exitMessage7[] = { "                                         __/ |                " };
char exitMessage8[] = { "                                        |___/                 " };

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void DrawMyIcon()
{
	//1 num - background color, 2 num - text color
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4)); //1 - background, 2 - text background
	cout << "\n\n\t\t\t\t   Д о б р о   п о ж а л о в а т ь    в\n\n";
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));


	cout << "        /---/  /-/     /---\\       <------\\       /--/    /-----/    /--/      /--/  /---------\\" << endl;
	cout << "       /---/ /-/      /-/ \\-\\           >-->     /--/   /-/  /-/    /--/      /--/  /--/     \\--\\" << endl;
	cout << "      /---/<         /-------\\        <---<     /--/  /-/   /-/    /------------/  |--|       |--|" << endl;
	cout << "     /---/  \\-\\     /-/     \\-\\         >-->   /--/ /-/    /-/    /--/      /--/    \\--\\     /--/" << endl;
	cout << "    /---/    \\-\\   /-/       \\-\\   <------/   /-----/     /-/    /--/      /--/      \\---------/" << endl;


	cout << "\n\n\n";
	return;
}

void MainMenu()
{
	char c;
	short pos = 1;
	char menuPoint1[] = ">  >  21 очко  <  <", menuPoint2[] = ">  >  Выход  <  <", menuPoint3[] = "      21 очко      ", menuPoint4[] = "      Выход      ";
	char erase[1] = {};
	

	//Вывод полного меню
	//SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	setCurPos(100, 24, menuPoint1); //->  |
	setCurPos(100, 34, menuPoint4);

	//Анимация + управление стрелочками
	do {
		do
		{
			
			/*
			if (pos == 1)
			{
				setCurPos(100, 24, erase);
				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
				setCurPos(100, 24, menuPoint1);
				Sleep(500);
				setCurPos(100, 24, erase);
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
				setCurPos(100, 24, menuPoint1);
				Sleep(500);
			}
			else
			{
				setCurPos(100, 34, erase);
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
				setCurPos(100, 34, menuPoint2);
				Sleep(500);
				setCurPos(100, 34, erase);
				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
				setCurPos(100, 34, menuPoint2);
				Sleep(500);
			}
			//Sleep(99900);

			*/

		} while (!_kbhit());
		c = _getch();
		switch (c) {
		case 72:   //UP
			pos = 1;
			setCurPos(100, 24, erase);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			setCurPos(100, 24, menuPoint1);

			setCurPos(100, 34, erase);
			setCurPos(100, 34, menuPoint4);
			break;
		case 80:  //DOWN
			pos = 2;
			setCurPos(100, 24, erase);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			setCurPos(100, 24, menuPoint3);

			setCurPos(100, 34, erase);
			setCurPos(100, 34, menuPoint2);
			break;

		case 13: //Enter
			//char ends[] = { "END!" };
			//setCurPos(100, 36, ends);
			if (pos == 1)
				//cout << "End" << endl;
				StartMyGame();				
			else
			{
				drawExitMessage();
				exit(0);
			}				
			return;
			break;
		}
	} while (c != 27);
	drawExitMessage();
	exit(0);

	return;
}

void setCurPos(int x, int y, char str[])
{
	HANDLE hCon;
	COORD cPos;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	cPos.Y = y / 2; // UP->DOWN
	cPos.X = (x - strlen(str)) / 2; //LEFT->RIGHT
	SetConsoleCursorPosition(hCon, cPos);
	if (str == "3ras3")
	{
		printf("%c[2K\r", 27); //стереть строку 
		return;
	}
	else if (str == NULL)
	{
		return;
	}
	else
	{
		std::cout << str << std::endl;
		return;
	}


}

void drawExitMessage()
{
	system("cls");
	/*for (int i = 0; i < 8; i++)
	{
		setCurPos(eMessageXSize, eMessageYSize+2, exitMessage1);
	}*/
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 3));
	setCurPos(eMessageXSize, eMessageYSize, exitMessage1);
	setCurPos(eMessageXSize, eMessageYSize + 2, exitMessage2);
	setCurPos(eMessageXSize, eMessageYSize + 4, exitMessage3);
	setCurPos(eMessageXSize, eMessageYSize + 6, exitMessage4);
	setCurPos(eMessageXSize, eMessageYSize + 8, exitMessage5);
	setCurPos(eMessageXSize, eMessageYSize + 10, exitMessage6);
	setCurPos(eMessageXSize, eMessageYSize + 12, exitMessage7);
	setCurPos(eMessageXSize, eMessageYSize + 14, exitMessage8);
	Sleep(2500);
	return;
}