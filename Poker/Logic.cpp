#include "Logic.h"

#include <algorithm>

namespace
{
    int GetRankInt(const Card& card)
    {
        return static_cast<int>(card.rank);
    }

	bool IsFound(const Hand& cards, Rank::Value rank)
	{
		return std::find_if(
			std::begin(cards),
			std::end(cards),
			[rank](const Card& card){ return card.rank == rank; }) != std::end(cards);
	}

	// The function would be MUCH faster if Cards were std::set.
	// But for the test task and 5 elements...
	bool IsStraight(const Hand& cards)
	{
        bool result = true;
        for (auto i = 0; i < cards.size() - 1; ++i)
        {
            if (GetRankInt(cards[i]) != GetRankInt(cards[i + 1]) - 1)
            {
                result = false;
                break;
            }
        }

        if (result)
        {
            return true;
        }

		// If not, check the special case with Ace
		bool isSpecialCaseWorked =
			cards[0].rank == Rank::Ace &&
			cards[1].rank == Rank::C2 &&
			cards[2].rank == Rank::C3 &&
			cards[3].rank == Rank::C4 &&
			cards[4].rank == Rank::C5;

		return isSpecialCaseWorked;
	}

	bool IsSameSuit(const Hand& cards)
	{
		auto firstSuit = cards[0].suit;
		for(auto it = std::begin(cards); it != std::end(cards); ++it)
		{
			if (it->suit != firstSuit)
			{
				return false;
			}
		}

		return true;
	}

	CompareResult::Value CompareStraightFlush(const Hand& rhs, const Hand& lhs)
	{
		IsStraight(rhs);
		IsSameSuit(rhs);
	}

	CompareResult::Value Compare4OfAKind(const Hand& rhs, const Hand& lhs)
	{
		;	
	}

	CompareResult::Value CompareFullHouse(const Hand& rhs, const Hand& lhs)
	{
		;	
	}

	CompareResult::Value CompareFlush(const Hand& rhs, const Hand& lhs)
	{
		;	
	}

	CompareResult::Value CompareStraight(const Hand& rhs, const Hand& lhs)
	{
		;	
	}

	CompareResult::Value Compare3OfAKind(const Hand& rhs, const Hand& lhs)
	{
		;	
	}

	CompareResult::Value CompareTwoPair(const Hand& rhs, const Hand& lhs)
	{
		;	
	}

	CompareResult::Value CompareOnePair(const Hand& rhs, const Hand& lhs)
	{
		;	
	}

	CompareResult::Value CompareHighCard(const Hand& rhs, const Hand& lhs)
	{
		;	
	}
}

Hand GetBestSet(
	const CardSet& inHand,
	const CardSet& onBoard,
	std::function<CompareResult::Value(const Hand&, const Hand&)> isFirstBetterPredicate)
{
	const size_t numOfHandCards = 2;
	const size_t numOfCombinationsFromHand = 6;
	const size_t numOfBoardCards = 3;
	const size_t numOfCombinationsFromBoard = 10;

	size_t combinationsFromHandIndices[numOfCombinationsFromHand][numOfHandCards] =
	{
		{0, 1},
		{0, 2},
		{0, 3},
		{1, 2},
		{1, 3},
		{2, 3}
	};

	size_t combinationsFromBoardIndices[numOfCombinationsFromBoard][numOfBoardCards] =
	{
		{0, 1, 2},
		{0, 1, 3},
		{0, 1, 4},
		{0, 2, 3},
		{0, 2, 4},
		{0, 3, 4},
		{1, 2, 3},
		{1, 2, 4},
		{1, 3, 4},
		{2, 3, 4}
	};

    bool isFirstIteration = true;
	Hand bestSet;
	for (size_t i = 0; i < numOfCombinationsFromHand; ++i)
	{
		for (size_t j = 0; j < numOfCombinationsFromBoard; ++j)
		{
            // Create a hand (5 cards). It must be sorted by Rank
            Hand currentSet;
            currentSet[0] = inHand[combinationsFromHandIndices[i][0]];
            currentSet[1] = inHand[combinationsFromHandIndices[i][1]];
            currentSet[2] = onBoard[combinationsFromBoardIndices[j][0]];
            currentSet[3] = onBoard[combinationsFromBoardIndices[j][1]];
            currentSet[4] = onBoard[combinationsFromBoardIndices[j][2]];
            std::sort(
                std::begin(currentSet),
                std::end(currentSet),
                [](const Card& r, const Card& l) { return r.rank < l.rank; });

			if (isFirstIteration)
			{
				// The current set is the best we have
				bestSet.swap(currentSet);
                isFirstIteration = false;
				continue;
			}

			if (isFirstBetterPredicate(currentSet, bestSet))
			{
				bestSet.swap(currentSet);
			}
		}
	}

	return bestSet;
}

CompareResult::Value CompareHighHand(const Hand& rhs, const Hand& lhs)
{
	CompareResult::Value result = CompareResult::BothLose;

	result = CompareStraightFlush(rhs, lhs);
	if (result != CompareResult::BothLose)
	{
		return result;
	}

	result = Compare4OfAKind(rhs, lhs);
	if (result != CompareResult::BothLose)
	{
		return result;
	}

	result = CompareFullHouse(rhs, lhs);
	if (result != CompareResult::BothLose)
	{
		return result;
	}

	result = CompareFlush(rhs, lhs);
	if (result != CompareResult::BothLose)
	{
		return result;
	}

	result = CompareStraight(rhs, lhs);
	if (result != CompareResult::BothLose)
	{
		return result;
	}

	result = Compare3OfAKind(rhs, lhs);
	if (result != CompareResult::BothLose)
	{
		return result;
	}

	result = CompareTwoPair(rhs, lhs);
	if (result != CompareResult::BothLose)
	{
		return result;
	}

	result = CompareOnePair(rhs, lhs);
	if (result != CompareResult::BothLose)
	{
		return result;
	}

	result = CompareHighCard(rhs, lhs);
	return result;
}
