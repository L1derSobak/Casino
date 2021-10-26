#pragma once

class MoneyManager
{
public:
	MoneyManager();

	bool isCanMakeBet(int bet);
	void makeBet(int bet);
	int CalculateFinalBalance(bool isWin);
	int getBalance() { return Balance; }
	bool isCanContiuneGame();

	~MoneyManager();
private:
	int Balance;
	const int DefaultBalance = 7000; //�� ���� �� ��� ����, ����� �������! 
	int Bet;
	float procent = 1.5f;

	void CalculateBet(float procent, int bet);
};