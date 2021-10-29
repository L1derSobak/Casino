#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <clocale>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <cctype>
#include "Game.h"
#include "MoneyManager.h"
//#include "MoneyManager.h"

#pragma execution_character_set( "utf-8" )

HANDLE MyConsole = GetStdHandle(STD_OUTPUT_HANDLE); //GetStdHandle(STD_OUTPUT_HANDLE);

void setcur(int x, int y);
void drawTable();
void setcol(int backbrnCol, int textCol);
void setcol(int bothcol);
void drawCard(int number, int cPos);
void drawCard(char symbol, int cPos);
std::string spec_input_str();

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
enum GameEnd
{
	CANCEL_GAME = 0,
	ENG_WITHOUT_MONEY = 1
};

//Theme's cards variables
const int cardBackgroundColor = 8;
const int tableBackgroundColor = 0;
const int specialSymbolsColor = 4; //bubi, heart and also symbol of card
const int DefaultSymbolsColor = 15; //border of card like example
const int voidSymbolsColor = 0; //just void idk why i added it

//Playable cards variable
const int cardColorR = 4;
const int cardColorB = 0;
const int cardBackground = 8;
int  delayBLandG = 2000;
int cardNumber, printintMessagesY=22;
int cardPos = 0;
int cardHeight = 2;

//From DrawMethod
int whatNumberIs, XPos = 2;
char symbol = 'v';

//Main programm variables
char nulStr[]={"  "};
char mainPhrase[] = { "Тянуть карту?" };
char questionAnsy[] = { "1 - yes" };
char questionAnsn[] = { "0 - нет" };
char userInputp[] = { "Ваш выбор: " };
char voidStr[] = { "                                              " };
char borderSymbol = 'X';
char poleSymbol = '0';
bool isTen = false;

std::string spec_input_str()
{
	std::string number;
	while (number.size() == 0)
	{
		for (char c = 0; (c = _getch()) != 13;)
		{
			if (('0' <= c && c <= '9') || c == '-'
				|| ('a' <= c && c <= 'z') || c == '/')
			{
				number.push_back(c);
				std::cout << c;
			}
			else if (c == 8 && !number.empty())
			{
				number.pop_back();
				std::cout << "\b \b";
			}
			else if (c == 27)
			{
				number.clear();
				number.push_back('q');
				break;
			}
		}
	}
	std::cout << '\n';
	return number;
}

bool is_number(const std::string& s)
{
	return !s.empty() && (s.find_first_not_of("0123456789") == s.npos);
}

int tryToGetNumber()
{	
	std::string input;
	int whatNumber;
	setcur(2, 19); std::cout << voidStr;
	setcur(2, 19);
	input = spec_input_str();
	if (is_number(input))
	{
		whatNumber = std::stoi(input);		
		if (whatNumber != 0 && whatNumber != 1)
		{
			setcur(2, 20); std::cout << "Введите число 1 - да или 0 - нет";
			tryToGetNumber();
		}			
		else
			return whatNumber;
	}
	else
	{
		setcur(2, 20); std::cout << "Введите число 1 - да или 0 - нет";
		tryToGetNumber();
	}
	
}

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

void printFinalMessage(GameEnd endType)
{	
	for (int i = 15; i < 25; i++)
	{
		setcur(2, i); std::cout << voidStr;
	}
	setcur(90, 16); std::cout << voidStr;
	setcur(90, 16); std::cout << "┃ Баланс:             ┃";
	setcur(92, 20); std::cout << voidStr;
	drawTable();
	if (endType == 1)
	{
		setcol(0, 4); setcur(2, 16); std::cout << "К сожалению, у вас не хватает средств!";
		setcol(0, 4); setcur(2, 18); std::cout << "Возвращайтесь когда будете побогаче!";//:D
	}
	else
	{
		setcol(0, 2); setcur(2, 16); std::cout << "Спасибо вам за игру!";
		setcol(0, 2); setcur(2, 18); std::cout << "Возвращайтесь снова!!!";
	}
	
	Sleep(10000);
	exit(0);
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
	
}

void drawCard(char symbol, int cPos)
{		
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
}

void drawBalanceTable(int balance)
{
	setcur(90, 14); std::cout << "┎─────────────────────┒";
	setcur(90,15); std::cout << "┃                     ┃";
	setcur(90, 16); std::cout << "┃ Баланс:             ┃";
	setcur(90,16); std::cout << "┃ Баланс: "<<balance; setcur(112,16);std::cout<<"┃";
	setcur(90,17); std::cout << "┃                     ┃";
	setcur(90,18); std::cout << "┖─────────────────────┚";
}

void StartMyGame()//Основаная логика игры
{
	MoneyManager moneyManager;
	//
	int usersBet;
	bool isDigit;
	int counter;
	int falseCounter;
	std::string input;
	//MoneyManager* moneyManager = new MoneyManager();
	//moneyManager->DrawBalance();
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	printLogo();
	Sleep(delayBLandG);
	system("cls");
			
startGame:
	//Initialize variables
	XPos = 2;
	symbol = 'v';
	isTen = false;	
	isDigit = false;
	cardPos = 0;
	usersBet = 0;
	counter = 0;
	falseCounter = 0;
	input = "";
		
	drawTable();	
	drawBalanceTable(moneyManager.getBalance());
	//Ask for bet

	//Another draw
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

AskAgain:
	//
	setcur(2, 19); std::cout << voidStr;
	setcur(2, 20); std::cout << voidStr;
	//
	setcur(92, 20); std::cout << voidStr;
	setcur(92, 20); std::cout << "Ваша ставка: ";
	setcur(106, 20); 
	input = spec_input_str();
	if (is_number(input))
	{
		usersBet = std::stoi(input);
		if (moneyManager.isCanMakeBet(usersBet) == false)
		{
			setcur(80, 22); std::cout << voidStr;
			setcur(80, 23); std::cout << voidStr;
			setcur(80, 22); std::cout << "У вас недостаточно средств!";
			setcur(80, 23); std::cout << "Сделайте другую ставку!!!";
			goto AskAgain;
		}
		else
		{
			setcur(80, 22); std::cout << voidStr;
			setcur(80, 23); std::cout << voidStr;
			moneyManager.makeBet(usersBet);
			drawBalanceTable(moneyManager.getBalance());
		}
	}
	else
	{
		falseCounter++;
		setcur(80, 22); std::cout << voidStr;
		setcur(80, 23); std::cout << voidStr;
		//setcur(92, 22); std::cout << "Введите ставку в виде числа!";
		if (falseCounter <= 10)
		{
			setcur(80, 22); std::cout << "Введите, пожалуйста, число!";
		}
		else if (falseCounter <= 15 && falseCounter > 10)
		{
			setcur(80, 22); std::cout << "Уважаеый игрок, введите ЧИСЛО!";
		}
		else if (falseCounter <= 25 && falseCounter > 15)
		{
			setcur(80, 22); std::cout << "Я, конечно, всего лишь код, но моему";
			setcur(80, 23); std::cout << "удивлению нет предела... Нужно число...";
		}
		else
		{
			setcur(80, 22); std::cout << "Как же я жалею, что вы сели за мой стол";
			setcur(80, 23); std::cout << "С меня хватит! Я умываю руки!!!";
			Sleep(5000);
			exit(0);
		}
		goto AskAgain;
	}


	while (true)
	{
		//Try to get number from user
		choice = tryToGetNumber();
		setcur(2, 20); std::cout << voidStr;
		if (choice == 1)
		{
			cardPos++;
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
			if (count > 21)
			{
				moneyManager.CalculateFinalBalance(false);
				drawBalanceTable(moneyManager.getBalance());
				//moneyManager.getBalance();
				setcur(2, 15); std::cout << voidStr;
				setcur(2, 22); std::cout << "Вы проиграли! Вы набрали: " << count;
				setcur(2, 15); std::cout << "Хотите сыграть ещё раз?";
				setcur(2, 23); std::cout << voidStr;
				setcur(2, 19); std::cout << voidStr;
				setcur(2, 18); std::cout << "Ваш выбор: ";
				setcur(2, 19); choice = tryToGetNumber();
				//
				if (moneyManager.isCanContiuneGame() == true)
				{				
					if (choice == 1) goto startGame;
					else if(choice != 1 && choice != 0)
					{
						setcur(2, 20); std::cout << "Введите число 1 - да или 0 - нет";
						setcur(2, 19); std::cout << voidStr;
					}
					else break;
				}
				else
				{
					printFinalMessage(ENG_WITHOUT_MONEY);
				}
			}
			else if (count == 21)
			{
				moneyManager.CalculateFinalBalance(true);
				drawBalanceTable(moneyManager.getBalance());
				//std::cout << std::endl;
				setcur(2, 15); std::cout << voidStr;
				setcur(2, 22); std::cout << "*** Победа! Вы набрали 21 очко!!! ***";
				setcur(2, 15); std::cout << "Хотите сыграть ещё раз?";
				setcur(2, 23); std::cout << voidStr;
				setcur(2, 19); std::cout << voidStr;
				setcur(2, 18); std::cout << "Ваш выбор: ";
				setcur(2, 19); 	choice = tryToGetNumber();
				if (moneyManager.isCanContiuneGame() == true)
				{
					if (choice == 1) goto startGame;
					else if (choice != 1 && choice != 0)
					{
						setcur(2, 20); std::cout << "Введите число 1 - да или 0 - нет";
						setcur(2, 19); std::cout << voidStr;
					}
					else
					{
						printFinalMessage(CANCEL_GAME);
						break;
					}
				}
				else
				{
					printFinalMessage(ENG_WITHOUT_MONEY);
				}
			}
			else
			{
				setcur(2, 19); std::cout << voidStr;
				setcur(2, 23); std::cout << "У вас " << count << " очков";
			}
		}
		else if (choice == 0)
		{
			moneyManager.CalculateFinalBalance(false);
			drawBalanceTable(moneyManager.getBalance());
			setcur(2, 22); std::cout << "Вы закончили игру с колличеством очков: " << count;
			setcur(2, 23); std::cout << voidStr;
			setcur(2, 15); std::cout << "Хотите сыграть ещё раз?";			
			setcur(2, 19); std::cout << voidStr;
			setcur(2, 19); 
			choice = tryToGetNumber();
			if (choice == 1) goto startGame;
			else
			{
				printFinalMessage(CANCEL_GAME);
				break;
			}
		}
		else
		{
			setcur(2, 20); std::cout << "Введите число 1 - да или 0 - нет";			
		}
	}
		

	
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

