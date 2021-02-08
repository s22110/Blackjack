#include <iostream>
#include "GameEngine.h"
#include "ConsoleHelpers.h"

using namespace std;
using namespace GameEngine;
using namespace ConsoleHelpers;

void showMainMenu();
void playGame();
void showRules();

int main()
{
	showMainMenu();

    return 0;
}

void showMainMenu()
{
	int userChoice = 0;
	do
	{
		clearScreen();
		cout << "Welcome in Blackjack game!" << endl << endl;
		cout << "[1] Play game" << endl;
		cout << "[2] Rules" << endl;
		cout << "[3] Exit" << endl;
		cout << endl << endl;

		userChoice = askUserForInt("Choose option");
		switch (userChoice)
		{
		case 1:
			playGame();
			break;
		case 2:
			showRules();
			break;
		case 3:
			break;
		default:
			break;
		}
	} while (userChoice != 3);
}

void playGame()
{
	auto playerName = askUserForStringInput("Enter your name");
	auto player = Player(playerName);
	auto* playerPtr = &player;

	int decksNo = 0;
	do
	{
		decksNo = askUserForInt("How many deck you want to play with? [max 6 decks]");
	} while (decksNo < 1 && decksNo > 6);
	
	clearScreen();
	startGame(playerPtr, decksNo);
}

void showRules()
{
	clearScreen();
	cout << "Rules: " << endl << endl;
	cout << "1) The goal of blackjack is to beat the dealer's hand without going over 21." << endl;
	cout << "2) Face cards are worth 10. Aces are worth 1 or 11, whichever makes a better hand." << endl;
	cout << "3) Each player starts with two cards." << endl;
	cout << "4) To 'Hit' is to ask for another card." << endl;
	cout << "5) If you go over 21 you bust, and the dealer wins regardless of the dealer's hand." << endl;
	cout << "6) If you are dealt 21 from the start (Ace & 10), you got a blackjack." << endl;
	cout << "7) Blackjack means you win 1.5 the amount of your bet." << endl;
	cout << "8) Dealer will hit until his/her cards total 17 or higher." << endl;

	system("pause");
}
