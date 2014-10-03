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

    void CheckFullHouse(const Hand& cards, bool& isApplicable3And2, bool& isApplicable2And3)
    {
        // The hand is sorted, so we just check if 4 first or 4 last cards have the same rank
        auto itBegin = std::begin(cards);
        auto it2 = GetAdvancedIt(itBegin, 2);
        auto it3 = GetAdvancedIt(itBegin, 3);
        isApplicable2And3 = AreCardsSameRank(itBegin, it2) && AreCardsSameRank(it2, std::end(cards));
        isApplicable3And2 = AreCardsSameRank(itBegin, it3) && AreCardsSameRank(it3, std::end(cards));
    }

    void Check3OfAKind(const Hand& cards, bool& isApplicable0, bool& isApplicable1, bool& isApplicable2)
    {
        const size_t NumberOfSameRanksRequired = 3;
        auto itBegin = std::begin(cards);
        isApplicable0 = AreCardsSameRank(itBegin, GetAdvancedIt(itBegin, NumberOfSameRanksRequired));
        isApplicable1 = AreCardsSameRank(GetAdvancedIt(itBegin, 1), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 1));
        isApplicable2 = AreCardsSameRank(GetAdvancedIt(itBegin, 2), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 2));
    }

    void CheckTwoPair(const Hand& cards, bool& isApplicable0And2, bool& isApplicable0And3, bool& isApplicable1And3)
    {
        const size_t NumberOfSameRanksRequired = 2;
        auto itBegin = std::begin(cards);
        isApplicable0And2 = 
            AreCardsSameRank(itBegin, GetAdvancedIt(itBegin, NumberOfSameRanksRequired)) &&
            AreCardsSameRank(GetAdvancedIt(itBegin, 2), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 2));
        isApplicable0And3 = 
            AreCardsSameRank(itBegin, GetAdvancedIt(itBegin, NumberOfSameRanksRequired)) &&
            AreCardsSameRank(GetAdvancedIt(itBegin, 3), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 3));
        isApplicable1And3 = 
            AreCardsSameRank(GetAdvancedIt(itBegin, 1), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 1)) &&
            AreCardsSameRank(GetAdvancedIt(itBegin, 3), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 3));
    }

    void CheckOnePair(const Hand& cards, bool& isApplicable0, bool& isApplicable1, bool& isApplicable2, bool& isApplicable3)
    {
        const size_t NumberOfSameRanksRequired = 2;
        auto itBegin = std::begin(cards);
        isApplicable0 = AreCardsSameRank(itBegin, GetAdvancedIt(itBegin, NumberOfSameRanksRequired));
        isApplicable1 = AreCardsSameRank(GetAdvancedIt(itBegin, 1), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 1));
        isApplicable2 = AreCardsSameRank(GetAdvancedIt(itBegin, 2), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 2));
        isApplicable3 = AreCardsSameRank(GetAdvancedIt(itBegin, 3), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 3));
    }

    const int GetHighestRankForLow8Hand(const Hand& card)
    {
        // In Low Hand there shouldn't be duplicated ranks, so card[1] is not Ace
        if (card[0].rank == Rank::Ace)
        {
            return GetRankInt(card[1]);
        }

        return GetRankInt(card[0]);
    }

    const bool AllCardsNoMore8(const Hand& cards)
    {
        for (size_t i = 0; i < cards.size(); ++i)
        {
            if (cards[i].rank == Rank::Ace)
            {
                continue;
            }

            if (GetRankInt(cards[i]) > static_cast<int>(Rank::C8))
            {
                return false;
            }
        }

        return true;
    }

    const bool AllCardsDifferByRank(const Hand& cards)
    {
        for (size_t i = 0; i < cards.size(); ++i)
        {
            for (size_t j = i + 1; j < cards.size(); ++j)
            {
                if (cards[i].rank == cards[j].rank)
                {
                    return false;
                }
            }
        }

        return true;
    }
}

Hand GetBestHand(
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
    const int highestCardFromFirst = GetHighestStraigtRank(first);

    const bool isSecondApplicable = IsStraight(second) && AreCardsSameSuit(second);
    const int highestCardFromSecond = GetHighestStraigtRank(second);

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

    return CompareHighCard(first, second);
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
    // The number in bools means the index of the first of 3 same ranks
    bool isFirstApplicable0 = false, isFirstApplicable1 = false, isFirstApplicable2 = false;
    Check3OfAKind(first, isFirstApplicable0, isFirstApplicable1, isFirstApplicable2);
    const bool isFirstApplicable = isFirstApplicable0 || isFirstApplicable1 || isFirstApplicable2;

    bool isSecondApplicable0 = false, isSecondApplicable1 = false, isSecondApplicable2 = false;
    Check3OfAKind(second, isSecondApplicable0, isSecondApplicable1, isSecondApplicable2);
    const bool isSecondApplicable = isSecondApplicable0 || isSecondApplicable1 || isSecondApplicable2;

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

    const auto rankMainFirst = GetRankInt(isFirstApplicable0 ? first[0] : (isFirstApplicable1 ? first[1] : first[2]));
    const auto rankKicker1First = GetRankInt(isFirstApplicable0 ? first[3] : first[0]);
    const auto rankKicker2First = GetRankInt(isFirstApplicable2 ? first[1] : first[4]);
    const auto rankMainSecond = GetRankInt(isSecondApplicable0 ? second[0] : (isSecondApplicable1 ? second[1] : second[2]));
    const auto rankKicker1Second = GetRankInt(isSecondApplicable0 ? second[3] : second[0]);
    const auto rankKicker2Second = GetRankInt(isSecondApplicable2 ? second[1] : second[4]);

    if (rankMainFirst > rankMainSecond)
    {
        return CompareResult::FirstWon;
    }

    if (rankMainFirst < rankMainSecond)
    {
        return CompareResult::SecondWon;
    }

    if (rankKicker1First > rankKicker1Second)
    {
        return CompareResult::FirstWon;
    }

    if (rankKicker1First < rankKicker1Second)
    {
        return CompareResult::SecondWon;
    }

    if (rankKicker2First > rankKicker2Second)
    {
        return CompareResult::FirstWon;
    }

    if (rankKicker2First < rankKicker2Second)
    {
        return CompareResult::SecondWon;
    }

    return CompareResult::BothWon;
}

CompareResult::Value CompareTwoPairs(const Hand& first, const Hand& second)
{
    // The numbers in bools mean the indices of the pairs
    bool isFirstApplicable0And2 = false, isFirstApplicable0And3 = false, isFirstApplicable1And3 = false;
    CheckTwoPair(first, isFirstApplicable0And2, isFirstApplicable0And3, isFirstApplicable1And3);
    const bool isFirstApplicable = isFirstApplicable0And2 || isFirstApplicable0And3 || isFirstApplicable1And3;

    bool isSecondApplicable0And2 = false, isSecondApplicable0And3 = false, isSecondApplicable1And3 = false;
    CheckTwoPair(second, isSecondApplicable0And2, isSecondApplicable0And3, isSecondApplicable1And3);
    const bool isSecondApplicable = isSecondApplicable0And2 || isSecondApplicable0And3 || isSecondApplicable1And3;

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

    const auto rank1First = GetRankInt((isFirstApplicable0And2 || isFirstApplicable0And3) ? first[0] : first[1]);
    const auto rank2First = GetRankInt((isFirstApplicable0And3 || isFirstApplicable1And3) ? first[3] : first[2]);
    const auto rankKickerFirst = GetRankInt(isFirstApplicable0And2 ? first[4] : (isFirstApplicable0And3 ? first[2] : first[0]));

    const auto rank1Second = GetRankInt((isSecondApplicable0And2 || isSecondApplicable0And3) ? second[0] : second[1]);
    const auto rank2Second = GetRankInt((isSecondApplicable0And3 || isSecondApplicable1And3) ? second[3] : second[2]);
    const auto rankKickerSecond = GetRankInt(isSecondApplicable0And2 ? second[4] : (isSecondApplicable0And3 ? second[2] : second[0]));

    if (rank1First > rank1Second)
    {
        return CompareResult::FirstWon;
    }

    if (rank1First < rank1Second)
    {
        return CompareResult::SecondWon;
    }

    if (rank2First > rank2Second)
    {
        return CompareResult::FirstWon;
    }

    if (rank2First < rank2Second)
    {
        return CompareResult::SecondWon;
    }

    if (rankKickerFirst > rankKickerSecond)
    {
        return CompareResult::FirstWon;
    }

    if (rankKickerFirst < rankKickerSecond)
    {
        return CompareResult::SecondWon;
    }

    return CompareResult::BothWon;
}

CompareResult::Value CompareOnePair(const Hand& first, const Hand& second)
{
    // The number in bools mean the index of the pair
    bool isFirstApplicable0 = false, isFirstApplicable1 = false, isFirstApplicable2 = false, isFirstApplicable3 = false;
    CheckOnePair(first, isFirstApplicable0, isFirstApplicable1, isFirstApplicable2, isFirstApplicable3);
    const bool isFirstApplicable = isFirstApplicable0 || isFirstApplicable1 || isFirstApplicable2 || isFirstApplicable3;

    bool isSecondApplicable0 = false, isSecondApplicable1 = false, isSecondApplicable2 = false, isSecondApplicable3 = false;
    CheckOnePair(second, isSecondApplicable0, isSecondApplicable1, isSecondApplicable2, isSecondApplicable3);
    const bool isSecondApplicable = isSecondApplicable0 || isSecondApplicable1 || isSecondApplicable2 || isSecondApplicable3;

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

    const auto rankMainFirst = GetRankInt(isFirstApplicable0 ? first[0] : (isFirstApplicable1 ? first[1] : (isFirstApplicable2 ? first[2] : first[3])));
    const auto rankKicker1First = GetRankInt(isFirstApplicable0 ? first[2] : first[0]);
    const auto rankKicker2First = GetRankInt((isFirstApplicable0 || isFirstApplicable1) ? first[3] : first[1]);
    const auto rankKicker3First = GetRankInt((isFirstApplicable0 || isFirstApplicable1 || isFirstApplicable2) ? first[4] : first[2]);

    const auto rankMainSecond = GetRankInt(isSecondApplicable0 ? second[0] : (isSecondApplicable1 ? second[1] : (isSecondApplicable2 ? second[2] : second[3])));
    const auto rankKicker1Second = GetRankInt(isSecondApplicable0 ? second[2] : second[0]);
    const auto rankKicker2Second = GetRankInt((isSecondApplicable0 || isSecondApplicable1) ? second[3] : second[1]);
    const auto rankKicker3Second = GetRankInt((isSecondApplicable0 || isSecondApplicable1 || isSecondApplicable2) ? second[4] : second[2]);

    if (rankMainFirst > rankMainSecond)
    {
        return CompareResult::FirstWon;
    }

    if (rankMainFirst < rankMainSecond)
    {
        return CompareResult::SecondWon;
    }

    if (rankKicker1First > rankKicker1Second)
    {
        return CompareResult::FirstWon;
    }

    if (rankKicker1First < rankKicker1Second)
    {
        return CompareResult::SecondWon;
    }

    if (rankKicker2First > rankKicker2Second)
    {
        return CompareResult::FirstWon;
    }

    if (rankKicker2First < rankKicker2Second)
    {
        return CompareResult::SecondWon;
    }

    if (rankKicker3First > rankKicker3Second)
    {
        return CompareResult::FirstWon;
    }

    if (rankKicker3First < rankKicker3Second)
    {
        return CompareResult::SecondWon;
    }

    return CompareResult::BothWon;
}

CompareResult::Value CompareHighCard(const Hand& first, const Hand& second)
{
    for (size_t i = 0; i < first.size(); ++i)
    {
        if (GetRankInt(first[i]) > GetRankInt(second[i]))
        {
            return CompareResult::FirstWon;
        }

        if (GetRankInt(first[i]) < GetRankInt(second[i]))
        {
            return CompareResult::SecondWon;
        }
    }

    return CompareResult::BothWon;
}

CompareResult::Value CompareHighHand(const Hand& rhs, const Hand& lhs, HighRanking::Value& highRankingResult)
{
	CompareResult::Value result = CompareResult::BothLose;

	result = CompareStraightFlush(rhs, lhs);
	if (result != CompareResult::BothLose)
	{
        highRankingResult = HighRanking::StraighFlush;
		return result;
	}

	result = Compare4OfAKind(rhs, lhs);
	if (result != CompareResult::BothLose)
	{
        highRankingResult = HighRanking::FourOfAKind;
		return result;
	}

	result = CompareFullHouse(rhs, lhs);
	if (result != CompareResult::BothLose)
	{
        highRankingResult = HighRanking::FullHouse;
		return result;
	}

	result = CompareFlush(rhs, lhs);
	if (result != CompareResult::BothLose)
    {
        highRankingResult = HighRanking::Flush;
		return result;
	}

	result = CompareStraight(rhs, lhs);
	if (result != CompareResult::BothLose)
    {
        highRankingResult = HighRanking::Straight;
		return result;
	}

	result = Compare3OfAKind(rhs, lhs);
	if (result != CompareResult::BothLose)
    {
        highRankingResult = HighRanking::ThreeOfAKind;
		return result;
	}

	result = CompareTwoPairs(rhs, lhs);
	if (result != CompareResult::BothLose)
    {
        highRankingResult = HighRanking::TwoPair;
		return result;
	}

	result = CompareOnePair(rhs, lhs);
	if (result != CompareResult::BothLose)
    {
        highRankingResult = HighRanking::OnePair;
		return result;
	}

    result = CompareHighCard(rhs, lhs);
    highRankingResult = HighRanking::HighCard;
	return result;
}

CompareResult::Value CompareLowHand(const Hand& first, const Hand& second)
{
    const bool isFirstApplicable = AllCardsNoMore8(first) && AllCardsDifferByRank(first);
    const bool isSecondApplicable = AllCardsNoMore8(second) && AllCardsDifferByRank(second);

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

    const int highestRankFirst = GetHighestRankForLow8Hand(first);
    const int highestRankSecond = GetHighestRankForLow8Hand(second);

    if (highestRankFirst > highestRankSecond)
    {
        return CompareResult::SecondWon;
    }

    if (highestRankFirst < highestRankSecond)
    {
        return CompareResult::FirstWon;
    }

    return CompareResult::BothWon;
}
