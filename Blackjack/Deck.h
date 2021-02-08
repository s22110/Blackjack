#pragma once
#include<string>
#include<vector>

namespace Deck
{
	struct Card
	{
	public:
		int value = 0, face = 0, suit = 0;
		bool _isGivenAway = false;

		Card(int value)
		{
			face = value % 100;
			suit = value / 100;

			if (face == 1)
			{
				this->value = 1;
			}
			else if (face >= 2 && face <= 9)
			{
				this->value = face;
			}
			else
			{
				this->value = 10;
			}
		}
	};

	std::vector<Card> initializeDeck(int deckQty);
	void shuffleDeck(std::vector<Card>* deckPtr);
	Card drawCard(std::vector<Card>* deckPtr);
};

