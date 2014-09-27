#include "Logic.h"

#include <algorithm>

namespace
{
	// TODO rewrite with std::array

	const size_t g_lengthOfCardSet = 5;

	bool IsFound(const Cards& cards, Rank::Value rank)
	{
		return std::find_if(
			std::begin(cards),
			std::end(cards),
			[rank](const Card& card){ return card.rank == rank; }) != std::end(cards);
	}

	// The function would be MUCH faster if Cards were std::set.
	// But for the test task and 5 elements...
	bool IsStraight(const Cards& cards)
	{
		if (cards.size() != g_lengthOfCardSet)
		{
			throw std::exception("IsStraight, cards size is not right");
		}

		auto minmax = std::minmax_element(
			std::begin(cards),
			std::end(cards),
			[](const Card& r, const Card& l) { return r.rank < l.rank; });
		if (minmax.second->rank - minmax.first->rank == g_lengthOfCardSet - 1)
		{
			return true;
		}

		// If not, check the special case with Ace
		auto isSpecialCaseWorked =
			IsFound(cards, Rank::Ace) &&
			IsFound(cards, Rank::C2) &&
			IsFound(cards, Rank::C3) &&
			IsFound(cards, Rank::C4) &&
			IsFound(cards, Rank::C5);

		return isSpecialCaseWorked;
	}

	bool IsSameSuit(const Cards& cards)
	{
		if (cards.size() != g_lengthOfCardSet)
		{
			throw std::exception("IsStraight, cards size is not right");
		}

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

	CompareResult::Value CompareStraightFlush(const Cards& rhs, const Cards& lhs)
	{
		IsStraight(rhs);
		IsSameSuit(rhs);
	}

	CompareResult::Value Compare4OfAKind(const Cards& rhs, const Cards& lhs)
	{
		;	
	}

	CompareResult::Value CompareFullHouse(const Cards& rhs, const Cards& lhs)
	{
		;	
	}

	CompareResult::Value CompareFlush(const Cards& rhs, const Cards& lhs)
	{
		;	
	}

	CompareResult::Value CompareStraight(const Cards& rhs, const Cards& lhs)
	{
		;	
	}

	CompareResult::Value Compare3OfAKind(const Cards& rhs, const Cards& lhs)
	{
		;	
	}

	CompareResult::Value CompareTwoPair(const Cards& rhs, const Cards& lhs)
	{
		;	
	}

	CompareResult::Value CompareOnePair(const Cards& rhs, const Cards& lhs)
	{
		;	
	}

	CompareResult::Value CompareHighCard(const Cards& rhs, const Cards& lhs)
	{
		;	
	}
}

Cards GetBestSet(
	const Cards& hand,
	const Cards& board,
	std::function<CompareResult::Value(const Cards&, const Cards&)> isFirstBetterPredicate)
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

	Cards bestSet;
	for (size_t i = 0; i < numOfCombinationsFromHand; ++i)
	{
		for (size_t j = 0; j < numOfCombinationsFromBoard; ++j)
		{
			Cards currentSet(5);
			currentSet.push_back(hand[combinationsFromHandIndices[i][0]]);
			currentSet.push_back(hand[combinationsFromHandIndices[i][1]]);
			currentSet.push_back(hand[combinationsFromBoardIndices[j][0]]);
			currentSet.push_back(hand[combinationsFromBoardIndices[j][1]]);
			currentSet.push_back(hand[combinationsFromBoardIndices[j][2]]);

			if (bestSet.empty())
			{
				// The first iteration, the current set is the best we have
				bestSet.swap(currentSet);
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

CompareResult::Value CompareHighHand(const Cards& rhs, const Cards& lhs)
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
