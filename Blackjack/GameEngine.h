#pragma once

#include<vector>

#include "Player.h"
#include "Dealer.h"
#include "Deck.h"

namespace GameEngine
{
	bool askDrawNextCard(Player* player);
	bool checkIfBusted(int score);
	bool checkIfBlackjack(int score, int handSize);
	bool askIfPlayAgain();

	void askForBet(Player* playerPtr);
	void startGame(Player* playerPtr, int numberOfDecks);
	void playerTurn(std::vector<Deck::Card>* deckPtr, Player* playerPtr);
	void dealerTurn(std::vector<Deck::Card>* deckPtr, Dealer* dealerPtr);
	void finishRound(Dealer* dealerPtr, Player* playerPtr);
	void cleanAfterGame(Dealer* dealerPtr, Player* playerPtr);
};

