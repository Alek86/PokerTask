#pragma once

#include <vector>
#include <array>

namespace Rank { enum Value
{
	C2 = 2,
	C3,
	C4,
	C5,
	C6,
	C7,
	C8,
	C9,
	C10,
	Jack,
	Queen,
	King,
	Ace,	
};}

namespace Suit { enum Value
{
	Diamonds,
	Clubs,
	Hearts,
	Spades
};}

namespace CompareResult { enum Value {
	FirstWon = 1,
	SecondWon = -1,
	BothWon = 0,
	BothLose = -2
};}

struct Card
{
	Rank::Value rank;
	Suit::Value suit;
};

typedef std::vector<Card> CardSet;

static const size_t NumOfCardsInHand = 5;

// Hand must be also sorted by Rank
typedef std::array<Card, NumOfCardsInHand> Hand;
