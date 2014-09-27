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

	bool IsStraight(const Hand& cards)
	{
        bool result = true;
        for (size_t i = 0; i < cards.size() - 1; ++i)
        {
            if (GetRankInt(cards[i]) != GetRankInt(cards[i + 1]) + 1)
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
		bool isSpecialCaseTrue =
			cards[0].rank == Rank::Ace &&
			cards[1].rank == Rank::C5 &&
			cards[2].rank == Rank::C4 &&
			cards[3].rank == Rank::C3 &&
			cards[4].rank == Rank::C2;

		return isSpecialCaseTrue;
	}

    const int GetHighestStraigtRank(const Hand& card)
    {
        // The cards must be Straight category if they are passed to this funtion.
        // The ace could be a lower card, need to check this situation

        if (card[0].rank == Rank::Ace && card[1].rank == Rank::C5)
        {
            return GetRankInt(card[1]);
        }

        return GetRankInt(card[0]);
    }

	bool AreCardsSameSuit(const Hand& cards)
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

    template <typename It>
    bool AreCardsSameRank(It begin, It end)
    {
        if (begin == end)
        {
            return true;
        }

        auto firstRank = begin->rank;
        for(auto it = begin; it != end; ++it)
        {
            if (it->rank != firstRank)
            {
                return false;
            }
        }

        return true;
    }

    Rank::Value Get4OfKindKicker(const Hand& cards)
    {
        if (cards[0].rank != cards[2].rank)
        {
            return cards[0].rank;
        }

        return cards[4].rank;
    }

    template <typename It>
    It GetAdvancedIt(It it, size_t n)
    {
        std::advance(it, n);
        return it;
    }

    bool Check4OfAKind(const Hand& cards)
    {
        auto itBegin = std::begin(cards);
        auto it4 = GetAdvancedIt(itBegin, 4);
        auto it1 = GetAdvancedIt(itBegin, 1);
        return AreCardsSameRank(itBegin, it4) || AreCardsSameRank(it1, std::end(cards));
    }

    void CheckFullHouse(const Hand& cards, bool& isApplicable3And2, bool& isApplicable2And3 )
    {
        // The hand is sorted, so we just check if 4 first or 4 last cards have the same rank
        auto itBegin = std::begin(cards);
        auto it2 = GetAdvancedIt(itBegin, 2);
        auto it3 = GetAdvancedIt(itBegin, 3);
        isApplicable2And3 = AreCardsSameRank(itBegin, it2) && AreCardsSameRank(it2, std::end(cards));
        isApplicable3And2 = AreCardsSameRank(itBegin, it3) && AreCardsSameRank(it3, std::end(cards));
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
            // Create a hand (5 cards). It must be sorted descending by Rank
            Hand currentSet;
            currentSet[0] = inHand[combinationsFromHandIndices[i][0]];
            currentSet[1] = inHand[combinationsFromHandIndices[i][1]];
            currentSet[2] = onBoard[combinationsFromBoardIndices[j][0]];
            currentSet[3] = onBoard[combinationsFromBoardIndices[j][1]];
            currentSet[4] = onBoard[combinationsFromBoardIndices[j][2]];
            std::sort(
                std::begin(currentSet),
                std::end(currentSet),
                [](const Card& r, const Card& l) { return r.rank > l.rank; });

			if (isFirstIteration)
			{
				// The current set is the best we have
				bestSet.swap(currentSet);
                isFirstIteration = false;
				continue;
			}

            auto compareResult = isFirstBetterPredicate(currentSet, bestSet);
			if (compareResult == CompareResult::FirstWon)
			{
				bestSet.swap(currentSet);
			}
		}
	}

	return bestSet;
}

CompareResult::Value CompareStraightFlush(const Hand& first, const Hand& second)
{
    const bool isFirstApplicable = IsStraight(first) && AreCardsSameSuit(first);
    const bool isSecondApplicable = IsStraight(second) && AreCardsSameSuit(second);

    if (isFirstApplicable && !isSecondApplicable)
    {
        return CompareResult::FirstWon;
    }

    if (!isFirstApplicable && isSecondApplicable)
    {
        return CompareResult::SecondWon;
    }

    if (!isFirstApplicable && !isSecondApplicable)
    {
        return CompareResult::BothLose;
    }

    const int highestCardFromFirst = GetHighestStraigtRank(first);
    const int highestCardFromSecond = GetHighestStraigtRank(second);

    if (highestCardFromFirst > highestCardFromSecond)
    {
        return CompareResult::FirstWon;
    }

    if (highestCardFromFirst < highestCardFromSecond)
    {
        return CompareResult::SecondWon;
    }

    return CompareResult::BothWon;
}

CompareResult::Value Compare4OfAKind(const Hand& first, const Hand& second)
{
    const bool isFirstApplicable = Check4OfAKind(first);
    const bool isSecondApplicable = Check4OfAKind(second);

    if (isFirstApplicable && !isSecondApplicable)
    {
        return CompareResult::FirstWon;
    }

    if (!isFirstApplicable && isSecondApplicable)
    {
        return CompareResult::SecondWon;
    }

    if (!isFirstApplicable && !isSecondApplicable)
    {
        return CompareResult::BothLose;
    }

    // In 4-of-a-kind in a sorted array the third card always has the duplicated rank
    if (GetRankInt(first[2]) > GetRankInt(second[2]))
    {
        return CompareResult::FirstWon;
    }

    if (GetRankInt(first[2]) < GetRankInt(second[2]))
    {
        return CompareResult::SecondWon;
    }

    const auto kickerFirst = Get4OfKindKicker(first);
    const auto kickerSecond = Get4OfKindKicker(second);

    if (kickerFirst > kickerSecond)
    {
        return CompareResult::FirstWon;
    }

    if (kickerFirst < kickerSecond)
    {
        return CompareResult::SecondWon;
    }

    return CompareResult::BothWon;
}

CompareResult::Value CompareFullHouse(const Hand& first, const Hand& second)
{
    bool isFirstApplicable3And2 = false, isFirstApplicable2And3 = false;
    CheckFullHouse(first, isFirstApplicable3And2, isFirstApplicable2And3);
    const bool isFirstApplicable = isFirstApplicable2And3 || isFirstApplicable3And2;

    bool isSecondApplicable3And2 = false, isSecondApplicable2And3 = false;
    CheckFullHouse(second, isSecondApplicable3And2, isSecondApplicable2And3);
    const bool isSecondApplicable = isSecondApplicable2And3 || isSecondApplicable3And2;

    if (isFirstApplicable && !isSecondApplicable)
    {
        return CompareResult::FirstWon;
    }

    if (!isFirstApplicable && isSecondApplicable)
    {
        return CompareResult::SecondWon;
    }

    if (!isFirstApplicable && !isSecondApplicable)
    {
        return CompareResult::BothLose;
    }

    const auto rank3OfAKindFirst = GetRankInt(isFirstApplicable3And2 ? first[0] : first[2]);
    const auto rank2OfAKindFirst = GetRankInt(isFirstApplicable3And2 ? first[3]: first[0]);
    const auto rank3OfAKindSecond = GetRankInt(isSecondApplicable3And2 ? second[0] : second[2]);
    const auto rank2OfAKindSecond = GetRankInt(isSecondApplicable3And2 ? second[3] : second[0]);

    if (rank3OfAKindFirst > rank3OfAKindSecond)
    {
        return CompareResult::FirstWon;
    }

    if (rank3OfAKindFirst < rank3OfAKindSecond)
    {
        return CompareResult::SecondWon;
    }

    if (rank2OfAKindFirst > rank2OfAKindSecond)
    {
        return CompareResult::FirstWon;
    }

    if (rank2OfAKindFirst < rank2OfAKindSecond)
    {
        return CompareResult::SecondWon;
    }

    return CompareResult::BothWon;
}

CompareResult::Value CompareFlush(const Hand& first, const Hand& second)
{
    bool isFirstApplicable = AreCardsSameSuit(first);
    bool isSecondApplicable = AreCardsSameSuit(second);

    if (isFirstApplicable && !isSecondApplicable)
    {
        return CompareResult::FirstWon;
    }

    if (!isFirstApplicable && isSecondApplicable)
    {
        return CompareResult::SecondWon;
    }

    if (!isFirstApplicable && !isSecondApplicable)
    {
        return CompareResult::BothLose;
    }

    const auto highestRankFirst = GetRankInt(first[0]);
    const auto highestRankSecond = GetRankInt(second[0]);
    if (highestRankFirst > highestRankSecond)
    {
        return CompareResult::FirstWon;
    }

    if (highestRankFirst < highestRankSecond)
    {
        return CompareResult::SecondWon;
    }

    return CompareResult::BothWon;
}

CompareResult::Value CompareStraight(const Hand& first, const Hand& second)
{
    const bool isFirstApplicable = IsStraight(first);
    const bool isSecondApplicable = IsStraight(second);

    if (isFirstApplicable && !isSecondApplicable)
    {
        return CompareResult::FirstWon;
    }

    if (!isFirstApplicable && isSecondApplicable)
    {
        return CompareResult::SecondWon;
    }

    if (!isFirstApplicable && !isSecondApplicable)
    {
        return CompareResult::BothLose;
    }

    const int highestCardFromFirst = GetHighestStraigtRank(first);
    const int highestCardFromSecond = GetHighestStraigtRank(second);

    if (highestCardFromFirst > highestCardFromSecond)
    {
        return CompareResult::FirstWon;
    }

    if (highestCardFromFirst < highestCardFromSecond)
    {
        return CompareResult::SecondWon;
    }

    return CompareResult::BothWon;
}

CompareResult::Value Compare3OfAKind(const Hand& first, const Hand& second)
{
    throw std::exception("Not implemented");
}

CompareResult::Value CompareTwoPair(const Hand& first, const Hand& second)
{
    throw std::exception("Not implemented");
}

CompareResult::Value CompareOnePair(const Hand& first, const Hand& second)
{
    throw std::exception("Not implemented");
}

CompareResult::Value CompareHighCard(const Hand& first, const Hand& second)
{
    throw std::exception("Not implemented");
}

CompareResult::Value CompareHighHand(const Hand& rhs, const Hand& lhs)
{
	CompareResult::Value result = CompareResult::BothLose;

	result = CompareStraightFlush(rhs, lhs);
	if (result != CompareResult::BothLose)
	{
		return result;
	}

   
    return result; // TODO Delete!



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
