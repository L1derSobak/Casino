//Казино
#include "MainMenu.h"
#include "Game.h"
#include <conio.h>
#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	//Задаём базовые конфигурации
	system("mode con cols=120 lines=25");
	wstring conName = L"GRAND CASINO";
	SetConsoleTitle(conName.c_str());
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	DrawMyIcon();
	MainMenu();
	cin.get();
	return 0;
}
