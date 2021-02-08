#pragma once

#include "Deck.h"

#include<string>
#include<vector>

namespace ConsoleHelpers
{
	int askUserForInt(const std::string prompt);
	char askUserYesOrNo(std::string prompt);
	std::string askUserForStringInput(const std::string prompt);

	void printHand(std::vector<Deck::Card> *hand);
	void clearScreen();
};

