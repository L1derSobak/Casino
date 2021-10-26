#include "MoneyManager.h"

MoneyManager::MoneyManager()
{
	Balance = DefaultBalance;
}

bool MoneyManager::isCanMakeBet(int bet)
{
	return Balance - bet >= 0 ? true : false;
}

void MoneyManager::makeBet(int bet)
{
	Bet = bet;
	Balance -= Bet;
}

int MoneyManager::CalculateFinalBalance(bool isWin)
{
	if (isWin == true)
		CalculateBet(procent, Bet);	
	return Balance;
}

bool MoneyManager::isCanContiuneGame()
{
	return Balance <= 0 ? false : true;
}

void MoneyManager::CalculateBet(float procent, int bet)
{
	//Bet += Bet*procent;
	Bet *= procent;
	Balance += Bet;
}

MoneyManager::~MoneyManager()
{
}
