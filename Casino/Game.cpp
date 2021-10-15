
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <clocale>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "Game.h"

#pragma execution_character_set( "utf-8" )

HANDLE MyConsole = GetStdHandle(STD_OUTPUT_HANDLE); //GetStdHandle(STD_OUTPUT_HANDLE);

void setcur(int x, int y);
void drawTable();
void setcol(int backbrnCol, int textCol);
void setcol(int bothcol);
void drawCard(int number, int cPos);
void drawCard(char symbol, int cPos);

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

const int cardBackgroundColor = 8;
const int tableBackgroundColor = 0;
const int specialSymbolsColor = 4; //bubi, heart and also symbol of card
const int DefaultSymbolsColor = 15; //border of card like example
const int voidSymbolsColor = 0; //just void idk why i added it
//
const int cardColorR = 4;
const int cardColorB = 0;
const int cardBackground = 8;
//
int cardNumber, delayBLandG = 2000, printintMessagesY=22;
int cardPos = 0;
int cardHeight = 2;
//From DrawMethod
int whatNumberIs, XPos = 2;
char symbol = 'v';
//
char nulStr[]={"  "};
char mainPhrase[] = { "Тянуть карту?" };
char questionAnsy[] = { "1 - yes" };
char questionAnsn[] = { "0 - нет" };
char userInputp[] = { "Ваш выбор: " };
char voidStr[] = { "                                              " };
char borderSymbol = 'X';
char poleSymbol = '0';
bool isTen = false;

void setcol(int backbrnCol, int textCol)
{
	SetConsoleTextAttribute(MyConsole, (WORD)((backbrnCol << 4) | textCol)); //1 - background, 2 - text background
}

void setcol(int bothcol)
{
	SetConsoleTextAttribute(MyConsole, (WORD)((bothcol << 4) | bothcol)); //1 - background, 2 - text background
}

void printLogo()
{
	system("cls");
	//SetConsoleTextAttribute(MyConsole, (WORD)((0 << 4) | 15)); //1 - background, 2 - text background

	std::cout << "\t\t\t\t                              " << std::endl;
	std::cout << "\t\t\t\t               /-\\     /|          " << std::endl;
	std::cout << "\t\t\t\t                 /    / |          " << std::endl;
	std::cout << "\t\t\t\t                /       |          " << std::endl;
	std::cout << "\t\t\t\t               /___     |          " << std::endl;
	std::cout << "\t\t\t\t                             " << std::endl;
	std::cout << "\t\t\t\t             /\\  \\|  |/  /\\         " << std::endl;
	std::cout << "\t\t\t\t             \\/   |  |\\  \\/         " << std::endl;
	std::cout << "\t\t\t\t                              " << std::endl;	

	//1 layer
	std::cout << "\t\t\t\t       ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|----------|";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "    ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout<<"|----------|"<< std::endl;

	//2 layer
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "\t\t\t\t       ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|";
	//<T up>
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | specialSymbolsColor));
	std::cout << "---";
	//</T up>
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "       |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "    ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|/|/\\      |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "         " << std::endl;

	//3 layer
	std::cout << "\t\t\t\t       ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout<<"| ";
	//<T middle>
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | specialSymbolsColor));
	std::cout<<"|";
	//</T middle>
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout<<"        |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "    ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "| |\\/      |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "       " << std::endl;

	//4 layer
	std::cout << "\t\t\t\t       ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "| ";
	//<T down>
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | specialSymbolsColor));
	std::cout << "|";
	//</T down>
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "        |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "    "; 
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|          |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "    " << std::endl;

	//5 layer
	std::cout << "\t\t\t\t       ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|    ";
	//Heart up
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | specialSymbolsColor));
	std::cout << "/V\\";
	//Heart up
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "   |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "    ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|    ";
	//bubi up
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | specialSymbolsColor));
	std::cout << "/\\";
	//bubi up
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "    |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "          " << std::endl;

	//6 layer
	std::cout << "\t\t\t\t       ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|    ";
	//Heart middle
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | specialSymbolsColor));
	std::cout << "\\ /";
	//Heart middle
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "   |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "    ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|   ";
	//bubi middle
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | specialSymbolsColor));
	std::cout << "<  >";
	//bubi middle
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "   |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "          " << std::endl;

	//7 layer
	std::cout << "\t\t\t\t       ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|     ";
	//Heart down
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | specialSymbolsColor));
	std::cout << "V";
	//Heart down
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "  ";	
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "  |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "    ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|    ";
	//bubi down
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | specialSymbolsColor));
	std::cout << "\\/";
	//bubi down
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "    |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "       " << std::endl;

	//8 layer
	std::cout << "\t\t\t\t       ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|        ";
	//T up
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | specialSymbolsColor));
	std::cout << "|";
	//T up
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << " |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "    ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|          |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "        " << std::endl;

	//9 layer
	std::cout << "\t\t\t\t       ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|        ";
	//T middle
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | specialSymbolsColor));
	std::cout << "|";
	//T middle
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << " |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "    ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|      /\\| |";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "        " << std::endl;

	//10 layer
	std::cout << "\t\t\t\t       ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|       ";
	//T down
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | specialSymbolsColor));
	std::cout << "---";
	//T down
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "    ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|      \\/|/|";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "         " << std::endl;

	//11 layer
	std::cout << "\t\t\t\t       ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|----------|";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "    ";
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackgroundColor << 4) | voidSymbolsColor));
	std::cout << "|----------|";
	SetConsoleTextAttribute(MyConsole, (WORD)((tableBackgroundColor << 4) | DefaultSymbolsColor));
	std::cout << "                   " << std::endl;


	
}

void drawTable()
{
	setcur(0, 0); setcol(6); 
	for (int i = 0; i < 120; i++)
	{
		std::cout << borderSymbol;
	}
	for (int i = 1; i < 14; i++)
	{
		setcur(0, i); std::cout << borderSymbol;
		setcur(119, i); std::cout << borderSymbol;
	}
	for (int i = 1; i < 119; i++)
	{
		setcur(i, 13); std::cout << borderSymbol;
	}


	setcol(2);
	for (int i = 1; i < 119; i++)
	{
		for (int j = 1; j < 13; j++)
		{
			setcur(i, j); std::cout << poleSymbol;
		}
	}
	setcol(tableBackgroundColor, DefaultSymbolsColor);	
}

void drawmethod(int position, int number)
{
	//14X120		
	switch (position)
	{
	case 1:
		XPos = 2;
		break;
	case 2:
		XPos = 15;
		break;
	case 3:
		XPos = 28;
		break;
	case 4:
		XPos = 41;
		break;		
	case 5:
		XPos = 54;
		break;
	case 6:
		XPos = 67;
		break;
	default:
		XPos = 80;
		break;
	}
		
	whatNumberIs = number;
	if (whatNumberIs == 10)
	{
		whatNumberIs = rand() % 4;
		switch (whatNumberIs)
		{
		case 0:
			symbol = 't';
			whatNumberIs = 10;
			break;
		case 1:
			symbol = 'B';//ENG SYMBOL
			break;
		case 2:
			symbol = 'D';//ENG SYMBOL
			break;
		case 3:
			symbol = 'K';//ENG SYMBOL
			break;
		}
	}
	else if (whatNumberIs == 11)
		symbol = 'T';	
	else
		symbol = 'v';
		
	short useColor = rand() % 2 ? cardColorR : cardColorB;
	SetConsoleTextAttribute(MyConsole, (WORD)((cardBackground << 4) | useColor));
	//Выбор рисовки карты
	if (symbol == 't') //10
	{
		drawCard(10, XPos);
	}
	else if (symbol == 'T')//Туз
	{
		drawCard('T', XPos);
	}
	else
	{
		if (symbol == 'v')//цифры
		{
			drawCard(whatNumberIs, XPos);
		}
		else//Остальное
		{
			drawCard(symbol, XPos);
		}		
		
	}
	SetConsoleTextAttribute(MyConsole, (WORD)((0 << 4) | 15));
}

void drawCard(int number, int cPos)
{
	//10x8
		/*
╔════╗╔╗╔══╗╔══╗──╔══╗
╚═╗╔═╝║║║╔═╝║╔╗║──║╔╗║
──║║──║╚╝║──║╚╝╚╗─║║║║
──║║──║╔╗║──║╔═╗║─║║║║
──║║──║║║╚═╗║╚═╝║╔╝╚╝╚╗
──╚╝──╚╝╚══╝╚═══╝╚════╝
─╔╦══╗╔══╗╔══╗╔══╗
╔╝║╔╗║║╔╗║║╔╗║╚═╗║
╚╗║║║║║╚╝║║╚╝║──║║
─║║║║║╚═╗║║╔╗║──║║
─║║╚╝║╔═╝║║╚╝║──║║
─╚╩══╝╚══╝╚══╝──╚╝
╔══╗╔══╗╔╗╔╗╔══╗╔══╗
║╔═╝║╔═╝║║║║╚═╗║╚═╗║
║╚═╗║╚═╗║╚╝║╔═╝║╔═╝║
║╔╗║╚═╗║╚═╗║╚═╗║║╔═╝
║╚╝║╔═╝║──║║╔═╝║║╚═╗
╚══╝╚══╝──╚╝╚══╝╚══╝
─╔╗
╔╝║
╚╗║
─║║
─║║
─╚╝

	*/
	switch (number)
	{
	case 2:
		//2
		setcur(cPos, cardHeight); std::cout << "╔══════════╗";
		setcur(cPos, cardHeight + 1); std::cout << "║2         ║";
		setcur(cPos, cardHeight + 2); std::cout << "║   ╔══╗   ║";
		setcur(cPos, cardHeight + 3); std::cout << "║   ╚═╗║   ║";
		setcur(cPos, cardHeight + 4); std::cout << "║   ╔═╝║   ║";
		setcur(cPos, cardHeight + 5); std::cout << "║   ║╔═╝   ║";
		setcur(cPos, cardHeight + 6); std::cout << "║   ║╚═╗   ║";
		setcur(cPos, cardHeight + 7); std::cout << "║   ╚══╝   ║";
		setcur(cPos, cardHeight + 8); std::cout << "║         2║";
		setcur(cPos, cardHeight + 9); std::cout << "╚══════════╝";
		break;
	case 3:
		//3
		setcur(cPos, cardHeight); std::cout << "╔══════════╗";
		setcur(cPos, cardHeight + 1); std::cout << "║3         ║";
		setcur(cPos, cardHeight + 2); std::cout << "║   ╔══╗   ║";
		setcur(cPos, cardHeight + 3); std::cout << "║   ╚═╗║   ║";
		setcur(cPos, cardHeight + 4); std::cout << "║   ╔═╝║   ║";
		setcur(cPos, cardHeight + 5); std::cout << "║   ╚═╗║   ║";
		setcur(cPos, cardHeight + 6); std::cout << "║   ╔═╝║   ║";
		setcur(cPos, cardHeight + 7); std::cout << "║   ╚══╝   ║";
		setcur(cPos, cardHeight + 8); std::cout << "║         3║";
		setcur(cPos, cardHeight + 9); std::cout << "╚══════════╝";
		break;
	case 4:
		//4
		setcur(cPos, cardHeight); std::cout << "╔══════════╗";
		setcur(cPos, cardHeight + 1); std::cout << "║4         ║";
		setcur(cPos, cardHeight + 2); std::cout << "║   ╔╗╔╗   ║";
		setcur(cPos, cardHeight + 3); std::cout << "║   ║║║║   ║";
		setcur(cPos, cardHeight + 4); std::cout << "║   ║╚╝║   ║";
		setcur(cPos, cardHeight + 5); std::cout << "║   ╚═╗║   ║";
		setcur(cPos, cardHeight + 6); std::cout << "║     ║║   ║";
		setcur(cPos, cardHeight + 7); std::cout << "║     ╚╝   ║";
		setcur(cPos, cardHeight + 8); std::cout << "║         4║";
		setcur(cPos, cardHeight + 9); std::cout << "╚══════════╝";
		break;
	case 5:
		//5
		setcur(cPos, cardHeight); std::cout << "╔══════════╗";
		setcur(cPos, cardHeight + 1); std::cout << "║5         ║";
		setcur(cPos, cardHeight + 2); std::cout << "║   ╔══╗   ║";
		setcur(cPos, cardHeight + 3); std::cout << "║   ║╔═╝   ║";
		setcur(cPos, cardHeight + 4); std::cout << "║   ║╚═╗   ║";
		setcur(cPos, cardHeight + 5); std::cout << "║   ╚═╗║   ║";
		setcur(cPos, cardHeight + 6); std::cout << "║   ╔═╝║   ║";
		setcur(cPos, cardHeight + 7); std::cout << "║   ╚══╝   ║";
		setcur(cPos, cardHeight + 8); std::cout << "║         5║";
		setcur(cPos, cardHeight + 9); std::cout << "╚══════════╝";
		break;
	case 6:
		//6
		setcur(cPos, cardHeight); std::cout << "╔══════════╗";
		setcur(cPos, cardHeight + 1); std::cout << "║6         ║";
		setcur(cPos, cardHeight + 2); std::cout << "║   ╔══╗   ║";
		setcur(cPos, cardHeight + 3); std::cout << "║   ║╔═╝   ║";
		setcur(cPos, cardHeight + 4); std::cout << "║   ║╚═╗   ║";
		setcur(cPos, cardHeight + 5); std::cout << "║   ║╔╗║   ║";
		setcur(cPos, cardHeight + 6); std::cout << "║   ║╚╝║   ║";
		setcur(cPos, cardHeight + 7); std::cout << "║   ╚══╝   ║";
		setcur(cPos, cardHeight + 8); std::cout << "║         6║";
		setcur(cPos, cardHeight + 9); std::cout << "╚══════════╝";
		break;
	case 7:
		//7
		setcur(cPos, cardHeight); std::cout << "╔══════════╗";
		setcur(cPos, cardHeight + 1); std::cout << "║7         ║";
		setcur(cPos, cardHeight + 2); std::cout << "║   ╔══╗   ║";
		setcur(cPos, cardHeight + 3); std::cout << "║   ╚═╗║   ║";
		setcur(cPos, cardHeight + 4); std::cout << "║     ║║   ║";
		setcur(cPos, cardHeight + 5); std::cout << "║     ║║   ║";
		setcur(cPos, cardHeight + 6); std::cout << "║     ║║   ║";
		setcur(cPos, cardHeight + 7); std::cout << "║     ║║   ║";
		setcur(cPos, cardHeight + 8); std::cout << "║         7║";
		setcur(cPos, cardHeight + 9); std::cout << "╚══════════╝";
		break;
	case 8:
		//8
		setcur(cPos, cardHeight); std::cout << "╔══════════╗";
		setcur(cPos, cardHeight + 1); std::cout << "║8         ║";
		setcur(cPos, cardHeight + 2); std::cout << "║   ╔══╗   ║";
		setcur(cPos, cardHeight + 3); std::cout << "║   ║╔╗║   ║";
		setcur(cPos, cardHeight + 4); std::cout << "║   ║╚╝║   ║";
		setcur(cPos, cardHeight + 5); std::cout << "║   ║╔╗║   ║";
		setcur(cPos, cardHeight + 6); std::cout << "║   ║╚╝║   ║";
		setcur(cPos, cardHeight + 7); std::cout << "║   ╚══╝   ║";
		setcur(cPos, cardHeight + 8); std::cout << "║         8║";
		setcur(cPos, cardHeight + 9); std::cout << "╚══════════╝";
		break;
	case 9:
		//9
		setcur(cPos, cardHeight); std::cout << "╔══════════╗";
		setcur(cPos, cardHeight + 1); std::cout << "║9         ║";
		setcur(cPos, cardHeight + 2); std::cout << "║   ╔══╗   ║";
		setcur(cPos, cardHeight + 3); std::cout << "║   ║╔╗║   ║";
		setcur(cPos, cardHeight + 4); std::cout << "║   ║╚╝║   ║";
		setcur(cPos, cardHeight + 5); std::cout << "║   ╚═╗║   ║";
		setcur(cPos, cardHeight + 6); std::cout << "║   ╔═╝║   ║";
		setcur(cPos, cardHeight + 7); std::cout << "║   ╚══╝   ║";
		setcur(cPos, cardHeight + 8); std::cout << "║         9║";
		setcur(cPos, cardHeight + 9); std::cout << "╚══════════╝";
		break;
	case 10:
		//10
		setcur(cPos, cardHeight); std::cout << "╔══════════╗";
		setcur(cPos, cardHeight + 1); std::cout << "║10        ║";
		setcur(cPos, cardHeight + 2); std::cout << "║   ╔╦══╗  ║";
		setcur(cPos, cardHeight + 3); std::cout << "║  ╔╝║╔╗║  ║";
		setcur(cPos, cardHeight + 4); std::cout << "║  ╚╗║║║║  ║";
		setcur(cPos, cardHeight + 5); std::cout << "║   ║║║║║  ║";
		setcur(cPos, cardHeight + 6); std::cout << "║   ║║╚╝║  ║";
		setcur(cPos, cardHeight + 7); std::cout << "║   ╚╩══╝  ║";
		setcur(cPos, cardHeight + 8); std::cout << "║        10║";
		setcur(cPos, cardHeight + 9); std::cout << "╚══════════╝";
		break;
	default:
		break;
	}
	return;
	//2
	setcur(cPos, 4); std::cout <<  "╔══════════╗";
	setcur(cPos, 5); std::cout <<  "║2         ║";
	setcur(cPos, 6); std::cout <<  "║   ╔══╗   ║";
	setcur(cPos, 7); std::cout <<  "║   ╚═╗║   ║";
	setcur(cPos, 8); std::cout <<  "║   ╔═╝║   ║";
	setcur(cPos, 9); std::cout <<  "║   ║╔═╝   ║";
	setcur(cPos, 10); std::cout << "║   ║╚═╗   ║";
	setcur(cPos, 11); std::cout << "║   ╚══╝   ║";
	setcur(cPos, 12); std::cout << "║         2║";
	setcur(cPos, 13); std::cout << "╚══════════╝";

	//3
	setcur(cPos, 4); std::cout <<  "╔══════════╗";
	setcur(cPos, 5); std::cout <<  "║3         ║";
	setcur(cPos, 6); std::cout <<  "║   ╔══╗   ║";
	setcur(cPos, 7); std::cout <<  "║   ╚═╗║   ║";
	setcur(cPos, 8); std::cout <<  "║   ╔═╝║   ║";
	setcur(cPos, 9); std::cout <<  "║   ╚═╗║   ║";
	setcur(cPos, 10); std::cout << "║   ╔═╝║   ║";
	setcur(cPos, 11); std::cout << "║   ╚══╝   ║";
	setcur(cPos, 12); std::cout << "║         3║";
	setcur(cPos, 13); std::cout << "╚══════════╝";

	//4
	setcur(cPos, 4); std::cout <<  "╔══════════╗";
	setcur(cPos, 5); std::cout <<  "║4         ║";
	setcur(cPos, 6); std::cout <<  "║   ╔╗╔╗   ║";
	setcur(cPos, 7); std::cout <<  "║   ║║║║   ║";
	setcur(cPos, 8); std::cout <<  "║   ║╚╝║   ║";
	setcur(cPos, 9); std::cout <<  "║   ╚═╗║   ║";
	setcur(cPos, 10); std::cout << "║     ║║   ║";
	setcur(cPos, 11); std::cout << "║     ╚╝   ║";
	setcur(cPos, 12); std::cout << "║         4║";
	setcur(cPos, 13); std::cout << "╚══════════╝";

	//5
	setcur(cPos, 4); std::cout <<  "╔══════════╗";
	setcur(cPos, 5); std::cout <<  "║5         ║";
	setcur(cPos, 6); std::cout <<  "║   ╔══╗   ║";
	setcur(cPos, 7); std::cout <<  "║   ║╔═╝   ║";
	setcur(cPos, 8); std::cout <<  "║   ║╚═╗   ║";
	setcur(cPos, 9); std::cout <<  "║   ╚═╗║   ║";
	setcur(cPos, 10); std::cout << "║   ╔═╝║   ║";
	setcur(cPos, 11); std::cout << "║   ╚══╝   ║";
	setcur(cPos, 12); std::cout << "║         5║";
	setcur(cPos, 13); std::cout << "╚══════════╝";

	//6
	setcur(cPos, 4); std::cout <<  "╔══════════╗";
	setcur(cPos, 5); std::cout <<  "║6         ║";
	setcur(cPos, 6); std::cout <<  "║   ╔══╗   ║";
	setcur(cPos, 7); std::cout <<  "║   ║╔═╝   ║";
	setcur(cPos, 8); std::cout <<  "║   ║╚═╗   ║";
	setcur(cPos, 9); std::cout <<  "║   ║╔╗║   ║";
	setcur(cPos, 10); std::cout << "║   ║╚╝║   ║";
	setcur(cPos, 11); std::cout << "║   ╚══╝   ║";
	setcur(cPos, 12); std::cout << "║         6║";
	setcur(cPos, 13); std::cout << "╚══════════╝";

	//7
	setcur(cPos, 4); std::cout <<  "╔══════════╗";
	setcur(cPos, 5); std::cout <<  "║7         ║";
	setcur(cPos, 6); std::cout <<  "║   ╔══╗   ║";
	setcur(cPos, 7); std::cout <<  "║   ╚═╗║   ║";
	setcur(cPos, 8); std::cout <<  "║     ║║   ║";
	setcur(cPos, 9); std::cout <<  "║     ║║   ║";
	setcur(cPos, 10); std::cout << "║     ║║   ║";
	setcur(cPos, 11); std::cout << "║     ╚╝   ║";
	setcur(cPos, 12); std::cout << "║         7║";
	setcur(cPos, 13); std::cout << "╚══════════╝";

	//8
	setcur(cPos, 4); std::cout <<  "╔══════════╗";
	setcur(cPos, 5); std::cout <<  "║8         ║";
	setcur(cPos, 6); std::cout <<  "║   ╔══╗   ║";
	setcur(cPos, 7); std::cout <<  "║   ║╔╗║   ║";
	setcur(cPos, 8); std::cout <<  "║   ║╚╝║   ║";
	setcur(cPos, 9); std::cout <<  "║   ║╔╗║   ║";
	setcur(cPos, 10); std::cout << "║   ║╚╝║   ║";
	setcur(cPos, 11); std::cout << "║   ╚══╝   ║";
	setcur(cPos, 12); std::cout << "║         8║";
	setcur(cPos, 13); std::cout << "╚══════════╝";

	//9
	setcur(cPos, 4); std::cout <<  "╔══════════╗";
	setcur(cPos, 5); std::cout <<  "║9         ║";
	setcur(cPos, 6); std::cout <<  "║   ╔══╗   ║";
	setcur(cPos, 7); std::cout <<  "║   ║╔╗║   ║";
	setcur(cPos, 8); std::cout <<  "║   ║╚╝║   ║";
	setcur(cPos, 9); std::cout <<  "║   ╚═╗║   ║";
	setcur(cPos, 10); std::cout << "║   ╔═╝║   ║";
	setcur(cPos, 11); std::cout << "║   ╚══╝   ║";
	setcur(cPos, 12); std::cout << "║         9║";
	setcur(cPos, 13); std::cout << "╚══════════╝";

	//10
	setcur(cPos, 4); std::cout <<  "╔══════════╗";
	setcur(cPos, 5); std::cout <<  "║10        ║";
	setcur(cPos, 6); std::cout <<  "║   ╔╦══╗  ║";
	setcur(cPos, 7); std::cout <<  "║  ╔╝║╔╗║  ║";
	setcur(cPos, 8); std::cout <<  "║  ╚╗║║║║  ║";
	setcur(cPos, 9); std::cout <<  "║   ║║║║║  ║";
	setcur(cPos, 10); std::cout << "║   ║║╚╝║  ║";
	setcur(cPos, 11); std::cout << "║   ╚╩══╝  ║";
	setcur(cPos, 12); std::cout << "║        10║";
	setcur(cPos, 13); std::cout << "╚══════════╝";

}

void drawCard(char symbol, int cPos)
{
	
	/*
	╔════╗╔╗╔══╗╔══╗──╔══╗
	╚═╗╔═╝║║║╔═╝║╔╗║──║╔╗║
	──║║──║╚╝║──║╚╝╚╗─║║║║
	──║║──║╔╗║──║╔═╗║─║║║║
	──║║──║║║╚═╗║╚═╝║╔╝╚╝╚╗
	──╚╝──╚╝╚══╝╚═══╝╚════╝
	*/
	switch (symbol)
	{
	case 'B':
		//В
		setcur(cPos, cardHeight); std::cout << "╔══════════╗";
		setcur(cPos, cardHeight + 1); std::cout << "║В         ║";
		setcur(cPos, cardHeight + 2); std::cout << "║   ╔══╗   ║";
		setcur(cPos, cardHeight + 3); std::cout << "║   ║╔╗║   ║";
		setcur(cPos, cardHeight + 4); std::cout << "║   ║╚╝╚╗  ║";
		setcur(cPos, cardHeight + 5); std::cout << "║   ║╔═╗║  ║";
		setcur(cPos, cardHeight + 6); std::cout << "║   ║╚═╝║  ║";
		setcur(cPos, cardHeight + 7); std::cout << "║   ╚═══╝  ║";
		setcur(cPos, cardHeight + 8); std::cout << "║         В║";
		setcur(cPos, cardHeight + 9); std::cout << "╚══════════╝";
		break;

	case 'D':
		//Д
		setcur(cPos, cardHeight); std::cout << "╔══════════╗";
		setcur(cPos, cardHeight + 1); std::cout << "║Д         ║";
		setcur(cPos, cardHeight + 2); std::cout << "║   ╔══╗   ║";
		setcur(cPos, cardHeight + 3); std::cout << "║   ║╔╗║   ║";
		setcur(cPos, cardHeight + 4); std::cout << "║   ║║║║   ║";
		setcur(cPos, cardHeight + 5); std::cout << "║   ║║║║   ║";
		setcur(cPos, cardHeight + 6); std::cout << "║  ╔╝╚╝╚╗  ║";
		setcur(cPos, cardHeight + 7); std::cout << "║  ╚════╝  ║";
		setcur(cPos, cardHeight + 8); std::cout << "║         Д║";
		setcur(cPos, cardHeight + 9); std::cout << "╚══════════╝";
		break;

	case 'K':
		//К
		setcur(cPos, cardHeight); std::cout << "╔══════════╗";
		setcur(cPos, cardHeight + 1); std::cout << "║К         ║";
		setcur(cPos, cardHeight + 2); std::cout << "║  ╔╗╔══╗  ║";
		setcur(cPos, cardHeight + 3); std::cout << "║  ║║║╔═╝  ║";
		setcur(cPos, cardHeight + 4); std::cout << "║  ║╚╝║    ║";
		setcur(cPos, cardHeight + 5); std::cout << "║  ║╔╗║    ║";
		setcur(cPos, cardHeight + 6); std::cout << "║  ║║║╚═╗  ║";
		setcur(cPos, cardHeight + 7); std::cout << "║  ╚╝╚══╝  ║";
		setcur(cPos, cardHeight + 8); std::cout << "║         К║";
		setcur(cPos, cardHeight + 9); std::cout << "╚══════════╝";

		break;

	case 'T':
		//Т
		setcur(cPos, cardHeight); std::cout << "╔══════════╗";
		setcur(cPos, cardHeight + 1); std::cout << "║Т         ║";
		setcur(cPos, cardHeight + 2); std::cout << "║  ╔════╗  ║";
		setcur(cPos, cardHeight + 3); std::cout << "║  ╚═╗╔═╝  ║";
		setcur(cPos, cardHeight + 4); std::cout << "║    ║║    ║";
		setcur(cPos, cardHeight + 5); std::cout << "║    ║║    ║";
		setcur(cPos, cardHeight + 6); std::cout << "║    ║║    ║";
		setcur(cPos, cardHeight + 7); std::cout << "║    ╚╝    ║";
		setcur(cPos, cardHeight + 8); std::cout << "║         Т║";
		setcur(cPos, cardHeight + 9); std::cout << "╚══════════╝";
		break;
	}
	return;





	//В
	setcur(cPos, 4); std::cout <<  "╔══════════╗";
	setcur(cPos, 5); std::cout <<  "║В         ║";
	setcur(cPos, 6); std::cout <<  "║   ╔══╗   ║";
	setcur(cPos, 7); std::cout <<  "║   ║╔╗║   ║";
	setcur(cPos, 8); std::cout <<  "║   ║╚╝╚╗  ║";
	setcur(cPos, 9); std::cout <<  "║   ║╔═╗║  ║";
	setcur(cPos, 10); std::cout << "║   ║╚═╝║  ║";
	setcur(cPos, 11); std::cout << "║   ╚═══╝  ║";
	setcur(cPos, 12); std::cout << "║         В║";
	setcur(cPos, 13); std::cout << "╚══════════╝";

	//Д
	setcur(cPos, 4); std::cout <<  "╔══════════╗";
	setcur(cPos, 5); std::cout <<  "║Д         ║";
	setcur(cPos, 6); std::cout <<  "║   ╔══╗   ║";
	setcur(cPos, 7); std::cout <<  "║   ║╔╗║   ║";
	setcur(cPos, 8); std::cout <<  "║   ║║║║   ║";
	setcur(cPos, 9); std::cout <<  "║   ║║║║   ║";
	setcur(cPos, 10); std::cout << "║  ╔╝╚╝╚╗  ║";
	setcur(cPos, 11); std::cout << "║  ╚════╝  ║";
	setcur(cPos, 12); std::cout << "║         Д║";
	setcur(cPos, 13); std::cout << "╚══════════╝";

	//К
	setcur(cPos, 4); std::cout <<  "╔══════════╗";
	setcur(cPos, 5); std::cout <<  "║К         ║";
	setcur(cPos, 6); std::cout <<  "║  ╔╗╔══╗  ║";
	setcur(cPos, 7); std::cout <<  "║  ║║║╔═╝  ║";
	setcur(cPos, 8); std::cout <<  "║  ║╚╝║    ║";
	setcur(cPos, 9); std::cout <<  "║  ║╔╗║    ║";
	setcur(cPos, 10); std::cout << "║  ║║║╚═╗  ║";
	setcur(cPos, 11); std::cout << "║  ╚╝╚══╝  ║";
	setcur(cPos, 12); std::cout << "║         К║";
	setcur(cPos, 13); std::cout << "╚══════════╝";

	//Т
	setcur(cPos, 4); std::cout <<  "╔══════════╗";
	setcur(cPos, 5); std::cout <<  "║Т         ║";
	setcur(cPos, 6); std::cout <<  "║  ╔════╗  ║";
	setcur(cPos, 7); std::cout <<  "║  ╚═╗╔═╝  ║";
	setcur(cPos, 8); std::cout <<  "║    ║║    ║";
	setcur(cPos, 9); std::cout <<  "║    ║║    ║";
	setcur(cPos, 10); std::cout << "║    ║║    ║";
	setcur(cPos, 11); std::cout << "║    ╚╝    ║";
	setcur(cPos, 12); std::cout << "║         Т║";
	setcur(cPos, 13); std::cout << "╚══════════╝";
}

void StartMyGame()//Основаная логика игры
{
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	printLogo();
	Sleep(delayBLandG);
	system("cls");
		
startGame:
	XPos = 2;
	symbol = 'v';
	isTen = false;
	drawTable();
	cardPos = 0;
	setcur(2, 15); std::cout << voidStr << std::endl;
	setcur(2, 15); std::cout << mainPhrase << std::endl;
	setcur(2, 16); std::cout << questionAnsy << std::endl;
	setcur(2, 17); std::cout << questionAnsn << std::endl;
	setcur(2, 18); std::cout << userInputp << std::endl;

	setcur(2, 22); std::cout << voidStr;
	setcur(2, 23); std::cout << voidStr;
	std::srand(unsigned(std::time(0))); //Генерация случайного числа с испоьзованием текущего времени
	std::vector<int> cards = { 11, 11, 11, 11, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,
					  5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8,
					  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
					  10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9 };
	int choice, playcard, count = 0; //Выбор игрока, выпавшая карта, счётчик очков	
	while (true)
	{
		cardPos++;
		setcur(2, 19); std::cout << voidStr;
		setcur(2, 19); std::cin >> choice;
		setcur(2, 20); std::cout << voidStr;
		if (choice == 1)
		{
			setcur(2, 22); std::cout << voidStr;
			std::random_shuffle(cards.begin(), cards.end());
			playcard = cards[cards.size() - 1]; //Определяем карту
			cards.erase(cards.begin() + cards.size() - 1); //Рабочее стирание

			drawmethod(cardPos, playcard);
			

			//==================================================
			//Красивый и адекватный вывод выпавшей карты:
			setcur(2, 22);
			//Дисклеймер: английские символы
			//t - 10
			//B - Валет
			//D - Дама
			//K - Король
			//T - Туз
			//v - цифра
			//std::cout << "Вы вытянули: " << playcard;
			switch (symbol)
			{
			case 'v':
				std::cout << "Вы вытянули: " << playcard;
				break;
			case 't':
				std::cout << "Вы вытянули: 10";
				break;
			case 'B':
				std::cout << "Вы вытянули: Валет";
				break;
			case 'D':
				std::cout << "Вы вытянули: Дама";
				break;
			case 'K':
				std::cout << "Вы вытянули: Король";
				break;
			case 'T':
				std::cout << "Вы вытянули: Туз";
				break;
			default:
				break;
			}
			count += playcard;
			//==================================================
			//count += playcard;
			//drawmethod(cardPos, playcard);
			//drawCardBackside(playcard);
			if (count > 21)
			{
				setcur(2, 15); std::cout << voidStr;
				setcur(2, 22); std::cout << "Вы проиграли! Вы набрали: " << count;
				setcur(2, 15); std::cout << "Хотите сыграть ещё раз?";
				setcur(2, 23); std::cout << voidStr;
				//std::cout << "1 - yes" << std::endl;
				//std::cout << "0 - нет" << std::endl;
				setcur(2, 19); std::cout << voidStr;
				setcur(2, 18); std::cout << "Ваш выбор: ";
				setcur(2, 19); std::cin >> choice;
				if (choice == 1) goto startGame;
				else if(choice != 1 && choice != 0)
				{
					setcur(2, 20); std::cout << "Введите число 1 - да или 0 - нет";
					setcur(2, 19); std::cout << voidStr;
				}
				else break;
			}
			else if (count == 21)
			{
				//std::cout << std::endl;
				setcur(2, 15); std::cout << voidStr;
				setcur(2, 22); std::cout << "*** Победа! Вы набрали 21 очко!!! ***";
				setcur(2, 15); std::cout << "Хотите сыграть ещё раз?";
				setcur(2, 23); std::cout << voidStr;
				//std::cout << "1 - yes" << std::endl;
				//std::cout << "0 - нет" << std::endl;
				setcur(2, 19); std::cout << voidStr;
				setcur(2, 18); std::cout << "Ваш выбор: ";
				setcur(2, 19); std::cin >> choice;
				if (choice == 1) goto startGame;
				else if (choice != 1 && choice != 0)
				{
					setcur(2, 20); std::cout << "Введите число 1 - да или 0 - нет";
					setcur(2, 19); std::cout << voidStr;
				}
				else	break;
			}
			else
			{
				setcur(2, 19); std::cout << voidStr;
				setcur(2, 23); std::cout << "У вас " << count << " очков";
			}
		}
		else if (choice == 0)
		{
			setcur(2, 22); std::cout << "Вы закончили игру с колличеством очков: " << count;
			setcur(2, 23); std::cout << voidStr;
			setcur(2, 15); std::cout << "Хотите сыграть ещё раз?";
			//std::cout << "1 - yes" << std::endl;
			//std::cout << "0 - нет" << std::endl;
			//std::cout << "Ваш выбор: ";
			setcur(2, 19); std::cout << voidStr;
			setcur(2, 19); std::cin >> choice;
			if (choice == 1) goto startGame;
			else break;
		}
		else
		{
			setcur(2, 20); std::cout << "Введите число 1 - да или 0 - нет";			
		}
	}
		

	
}

void Debugging()
{
	std::srand(unsigned(std::time(0))); //Генерация случайного числа с испоьзованием текущего времени
	std::vector<int> cards = { 11, 11, 11, 11, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4,
					  5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8,
					  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
					  10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9 };
	int playcard, count = 0; //Выбор игрока, выпавшая карта, счётчик очков //choice, 
	std::random_shuffle(cards.begin(), cards.end());

	outvector(1,cards);
	playcard = cards[cards.size() - 1];
	std::cout << playcard << std::endl;
	cards.erase(cards.begin() + cards.size()-1); //Рабочее стирание
	outvector(2,cards);
}

void outvector(int count, std::vector<int> vec)
{
	std::cout << count << std::endl;
	for (int i = 0; i <= vec.size() - 1; i++)
	{
		std::cout << vec[i] << "|";
	}
	std::cout << "---\n" << std::endl;
}

void setcur(int x, int y)
{
	COORD curPos;
	curPos.X = x;
	curPos.Y = y;
	SetConsoleCursorPosition(MyConsole, curPos);
}

