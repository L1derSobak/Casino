//Казино
#include "MainMenu.h"
#include "Game.h"
#include <conio.h>
#include <Windows.h>
#include <iostream>

#pragma execution_character_set( "utf-8" )

using namespace std;

int main()
{
	
	//setlocale(LC_ALL, "Rus");
	system("mode con cols=120 lines=25");
	wstring conName = L"GRAND CASINO";
	SetConsoleTitle(conName.c_str());
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	

	//printLogo();
	//StartMyGame();
	//Debugging();
	// 
	// Set UTF-8
	//SetConsoleOutputCP(65001);
	//SetConsoleCP(65001);
	// 
	//printf("Testing unicode -- English -- Ελληνικά -- Español -- Русский. aäbcdefghijklmnoöpqrsßtuüvwxyz\n");
	//cout<<"Testing unicode -- English -- Ελληνικά -- Español -- Русский. aäbcdefghijklmnoöpqrsßtuüvwxyz\n";
	
	/*cout << "╔══════════╗" << endl;
	cout << "║Д         ║" << endl;
	cout << "║   ╔══╗   ║" << endl;
	cout << "║   ║╔╗║   ║" << endl;
	cout << "║   ║║║║   ║" << endl;
	cout << "║   ║║║║   ║" << endl;
	cout << "║  ╔╝╚╝╚╗  ║" << endl;
	cout << "║  ╚════╝  ║" << endl;
	cout << "║         Д║" << endl;
	cout << "╚══════════╝" << endl;
	*/
	DrawMyIcon();
	MainMenu();
	cin.get();
	return 0;
}
