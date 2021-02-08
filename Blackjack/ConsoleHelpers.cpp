#include "ConsoleHelpers.h"

#include <string>
#include <iostream>
#include<Windows.h>

using namespace ConsoleHelpers;

//Methods asking user for different types of variables
int ConsoleHelpers::askUserForInt(const std::string prompt)
{
	auto userAnswer = std::string{};
	int newFreshInt = 0;
	bool isIntegeer = false;
	do
	{
		if (!prompt.empty())
		{
			std::cout << prompt << ": ";
		}

		std::getline(std::cin, userAnswer);
		try
		{
			newFreshInt = stoi(userAnswer);
			isIntegeer = true;
			return newFreshInt;
		}
		catch (const std::exception&)
		{
			return isIntegeer = false;
		}
	} while (!isIntegeer || userAnswer.empty() || newFreshInt < 0);
}
char ConsoleHelpers::askUserYesOrNo(std::string prompt)
{
	char value;
	do
	{
		if (!prompt.empty())
		{
			std::cout << prompt << ": ";
		}

		std::cin >> value;
		value = tolower(value);

	} while (value != 'y' && value != 'n');

	return value;
}
std::string ConsoleHelpers::askUserForStringInput(const std::string prompt)
{
	auto userInput = std::string{};
	do
	{
		if (!prompt.empty())
		{
			std::cout << prompt << ": ";
		}
		else
		{
			std::cout << "Enter text: ";
		}
		std::getline(std::cin, userInput);
	} while (userInput.empty());

	return userInput;
}

//Prints given set of cards
void ConsoleHelpers::printHand(std::vector<Deck::Card>* hand)
{
	for (auto& card : *hand)
	{
		std::string cardPrint;

		switch (card.face)
		{
		case 1:
			cardPrint = "A";
			break;
		case 2:
			cardPrint = "2";
			break;
		case 3:
			cardPrint = "3";
			break;
		case 4:
			cardPrint = "4";
			break;
		case 5:
			cardPrint = "5";
			break;
		case 6:
			cardPrint = "6";
			break;
		case 7:
			cardPrint = "7";
			break;
		case 8:
			cardPrint = "8";
			break;
		case 9:
			cardPrint = "9";
			break;
		case 10:
			cardPrint = "10";
			break;
		case 11:
			cardPrint = "J";
			break;
		case 12:
			cardPrint = "Q";
			break;
		case 13:
			cardPrint = "K";
			break;
		default:
			break;
		}

		switch (card.suit)
		{
		case 1:
			cardPrint += "C";
			break;
		case 2:
			cardPrint += "D";
			break;
		case 3:
			cardPrint += "H";
			break;
		case 4:
			cardPrint += "S";
			break;
		default:
			break;
		}

		std::cout << "| " << cardPrint << " |";
	}
	std::cout << std::endl << std::endl;
}

//Found @https://www.cplusplus.com/articles/4z18T05o/, clears screen from previous messages
void ConsoleHelpers::clearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}