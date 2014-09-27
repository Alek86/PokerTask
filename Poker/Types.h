#pragma once

#include <vector>

namespace Rank { enum Value
{
	Ace,
	King,
	Queen,
	Jack,
	C10,
	C9,
	C8,
	C7,
	C6,
	C5,
	C4,
	C3,
	C2
};}

namespace Suit { enum Value
{
	Diamonds,
	Clubs,
	Hearts,
	Spades
};}

struct Card
{
	Rank::Value rank;
	Suit::Value suit;
};

typedef std::vector<Card> Cards;