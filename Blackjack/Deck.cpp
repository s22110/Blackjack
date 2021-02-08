#include "Deck.h"

#include <string>
#include <vector>
#include <time.h>
#include <iostream>

using namespace Deck;

//Method creates deck of cards (52 cards A-K in four colors) * deck Qty
std::vector<Card> Deck::initializeDeck(int deckQty)
{
	std::vector<Card> deck;
	for (int i = 1; i <= deckQty; i++)
	{
		for (int suitValue = 1; suitValue <= 4; suitValue++)
		{
			for (int faceValue = 1; faceValue <= 13; faceValue++)
			{
				int cardValue = (suitValue * 100) + faceValue;

				Card card = Card(cardValue);
				deck.push_back(card);
			}
		}
	}
	return deck;
}

//Method for replacing cards in existing deck
void Deck::shuffleDeck(std::vector<Card>* deckPtr)
{
	srand(time(NULL));

	size_t cardQty = deckPtr->size();
	for (auto card : *deckPtr)
	{
		card._isGivenAway = false;

		int j = (rand() % cardQty);
		std::swap(card, deckPtr->at(j));
	}
}

//Gets one card from deck and sets flag that this card is given away
Card Deck::drawCard(std::vector<Card>* deckPtr)
{
	for (size_t i = 0; i < deckPtr->size(); i++)
	{
		Card card = deckPtr->at(i);
		bool isGivenAway = card._isGivenAway;

		if (!isGivenAway)
		{
			deckPtr->at(i)._isGivenAway = true;
			return card;
		}
	}
}