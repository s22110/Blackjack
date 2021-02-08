#include "GameEngine.h"
#include "Deck.h"
#include "ConsoleHelpers.h"

#include <iostream>
#include <istream>
#include <vector>

using namespace Deck;
using namespace ConsoleHelpers;

//Game logic
void GameEngine::startGame(Player *playerPtr, int numberOfDecks)
{
	auto deck = initializeDeck(numberOfDecks);
	auto deckPtr = &deck;

	Dealer dealer;
	bool playAgain = false;
	do
	{
		shuffleDeck(deckPtr);

		auto dealerPtr = &dealer;

		clearScreen();
		askForBet(playerPtr);

		for (int i = 0; i < 2; i++)
		{
			auto playerCard = drawCard(deckPtr);
			playerPtr->addCardToHand(playerCard);

			auto dealerCard = drawCard(deckPtr);
			dealerPtr->addCardToHand(dealerCard);
		}

		bool blackjack = checkIfBlackjack(playerPtr->getScore(), playerPtr->getHand().size());

		if (!blackjack)
		{
			
			playerTurn(deckPtr, playerPtr);
			if (playerPtr->busted == true)
			{
				finishRound(dealerPtr, playerPtr);
			}
			else
			{
				dealerTurn(deckPtr, dealerPtr);

				finishRound(dealerPtr, playerPtr);
			}
		}
		else
		{
			playerPtr->isHandBlackjack = true;
			printHand(&playerPtr->getHand());

			dealerTurn(deckPtr, dealerPtr);

			finishRound(dealerPtr, playerPtr);
		}

		system("pause");
		clearScreen();

		if (playerPtr->chipsAmount > 0)
		{
			std::cout << "You have : $" << playerPtr->chipsAmount << std::endl;
			playAgain = askIfPlayAgain();
		}
		else
		{
			std::cout << "You have lost everything!" << std::endl;
			std::cout << "Be gone poor man and let others play!" << std::endl;
		}

		cleanAfterGame(dealerPtr, playerPtr);
	} while (playAgain && playerPtr->chipsAmount > 0);
}

//Ask user for bet and set it inside Player class
void GameEngine::askForBet(Player* playerPtr)
{
	int bet;
	do
	{
		bet = askUserForInt("Place your bet (min. $1)");
		if (bet < 1)
		{
			std::cout << "Minimum bet is 1" << std::endl << std::endl;
		}
		else if (bet > playerPtr->chipsAmount)
		{
			std::cout << "Slow down cowboy! You cannot afford bet that high." << std::endl << std::endl;
		}
		else
		{
			playerPtr->bet = bet;
			playerPtr->chipsAmount -= bet;
		}
	} while (bet < 1 || bet > playerPtr->chipsAmount);
}

//Player's turn logic. Loop will continue until player choose not to hit or get more than 21 points
void GameEngine::playerTurn(std::vector<Card>* deckPtr, Player* playerPtr)
{
	bool busted = false, isHitting = false;
	do
	{
		isHitting = askDrawNextCard(playerPtr);
		if (isHitting)
		{
			auto card = drawCard(deckPtr);
			playerPtr->addCardToHand(card);
		}
		busted = checkIfBusted(playerPtr->getScore());

		if (busted)
		{
			playerPtr->busted = true;
			break;
		}
	} while (isHitting);
}

//Dealer's turn logic. Dealer play until he gets 17 or more points
void GameEngine::dealerTurn(std::vector<Card>* deckPtr, Dealer* dealerPtr)
{
	std::cout << std::endl << "Dealer turn..." << std::endl;

	bool soft17 = false, busted = false;
	while (!soft17)
	{
		auto card = drawCard(deckPtr);
		dealerPtr->addCardToHand(card);

		soft17 = dealerPtr->getScore() >= 17;
		busted = checkIfBusted(dealerPtr->getScore());

		if (busted)
		{
			dealerPtr->busted = true;
			break;
		}
	}
	printHand(&dealerPtr->getHand());
}

//Method to check who won
void GameEngine::finishRound(Dealer* dealerPtr, Player* playerPtr)
{
	if (dealerPtr->busted == true || playerPtr->getScore() > dealerPtr->getScore())
	{
		if (playerPtr->isHandBlackjack == true)
		{
			double multipler = ceil(playerPtr->bet * 1.5);
			int winnings = playerPtr->bet += (int)multipler;

			std::cout << playerPtr->username << " have Blackjack!" << std::endl;
			std::cout << playerPtr->username << " won $" << winnings - playerPtr->bet << "!" << std::endl;

			playerPtr->payoutWinnings(winnings);
			playerPtr->resetBet();
		}
		else
		{
			int winnings = playerPtr->bet += playerPtr->bet;

			std::cout << playerPtr->username << "'s score: " << playerPtr->getScore() << std::endl;
			std::cout << "House score: " << dealerPtr->getScore() << std::endl;
			std::cout << playerPtr->username << " won $" << winnings - playerPtr->bet << std::endl;

			playerPtr->payoutWinnings(winnings);
			playerPtr->resetBet();
		}
	}
	else if (playerPtr->busted == true || playerPtr->getScore() < dealerPtr->getScore())
	{
		playerPtr->resetBet();

		if (playerPtr->busted == true)
		{
			std::cout << playerPtr->username << " busted!" << std::endl;
		}
		else
		{
			std::cout << playerPtr->username << "'s score: " << playerPtr->getScore() << std::endl;
			std::cout << "House score: " << dealerPtr->getScore() << std::endl;
			std::cout << "House won!" << std::endl;
		}
	}
	else
	{
		int winnings = playerPtr->bet;

		playerPtr->payoutWinnings(winnings);
		playerPtr->resetBet();

		std::cout << playerPtr->username << "'s score: " << playerPtr->getScore() << std::endl;
		std::cout << "House score: " << dealerPtr->getScore() << std::endl;
		std::cout << "Draw!" << std::endl;
	}
}

//Resets player and dealer before new game
void GameEngine::cleanAfterGame(Dealer* dealerPtr, Player* playerPtr)
{
	dealerPtr->reset();
	playerPtr->reset();
}

//Basically "Hit or Stand"
bool GameEngine::askDrawNextCard(Player* playerPtr)
{
	printHand(&playerPtr->getHand());
	std::cout << playerPtr->username << " score: " << playerPtr->getScore() << std::endl << std::endl;

	char userAnswer = askUserYesOrNo("Hit? [y/n]");
	if (userAnswer == 'y')
		return true;
	else
		return false;
}

//Checks if there is more than 21 points in hand
bool GameEngine::checkIfBusted(int score)
{
	if (score > 21)
		return true;
	else
		return false;
}

//Checks if first draw got player Blackjack
bool GameEngine::checkIfBlackjack(int score, int handSize)
{
	if (score == 21 && handSize == 2)
		return true;
	else
		return false;
}

//Asking player if he want to play next round (if he have enough money)
bool GameEngine::askIfPlayAgain()
{
	char answer = askUserYesOrNo("Play again? [y/n]");
	if (answer == 'y')
	{
		return true;
	}
	else return false;
}