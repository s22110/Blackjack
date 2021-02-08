#pragma once

#include<string>
#include<vector>

#include "Deck.h"

struct Dealer
{

public:

	std::string name = "Dealer";
	bool busted = false;

	void addCardToHand(Deck::Card card)
	{
		this->hand.push_back(card);

		if (card.face == 1)
		{
			card.value = 11;
		}
		else if (card.face >= 2 && card.face <= 9)
		{
			card.value = card.face;
		}
		else
		{
			card.value = 10;
		}
		this->score += card.value;
	}

	void reset()
	{
		this->busted = false;
		this->hand.clear();
		this->score = 0;
	}

	int getScore()
	{
		if (score > 21)
		{
			int sum = 0;
			int acesNo = 0;
			for (auto& card : this->hand)
			{
				if (card.value == 11)
				{
					acesNo++;
				}
				sum += card.value;
			}
			while (score > 21 && acesNo--)
			{
				score -= 10;
			}
			score = sum;
		}
		return score;
	}

	std::vector<Deck::Card> getHand()
	{
		return hand;
	}

private:
	std::vector<Deck::Card> hand;
	int score = 0;
};