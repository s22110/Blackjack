#pragma once

#include<string>
#include<vector>

#include "Deck.h"

class Player
{

public:

	std::string username;
	bool busted = false, isHandBlackjack = false;
	int bet = 0, chipsAmount = 0;

	Player(std::string username)
	{
		this->username = username;
		chipsAmount += 500;
	}

	void addCardToHand(Deck::Card card)
	{
		this->hand.push_back(card);

		if (card.face == 1)
		{
			card.value = 11;
			acesNo++;

		}
		else if (card.face >= 2 && card.face <= 9)
		{
			card.value = card.face;
		}
		else
		{
			card.value = 10;
		}
		score += card.value;
	}

	void resetBet()
	{
		this->bet = 0;
	}

	void reset()
	{
		this->acesNo = 0;
		this->busted = false;
		this->hand.clear();
		this->isHandBlackjack = false;
	}

	void payoutWinnings(int winning)
	{
		this->chipsAmount += winning;
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
		return this->hand;
	}

private:
	std::vector<Deck::Card> hand;
	int score, acesNo = 0;
};