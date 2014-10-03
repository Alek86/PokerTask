#include "Logic.FourOfAKind.h"

#include "Types.h"
#include "Logic.Utils.h"

namespace Logic
{
    namespace
    {
        Rank::Value GetFourOfAKindKicker(const Hand& cards)
        {
            if (cards[0].rank != cards[2].rank)
            {
                return cards[0].rank;
            }

            return cards[4].rank;
        }

        bool CheckFourOfAKind(const Hand& cards)
        {
            auto itBegin = std::begin(cards);
            auto it4 = GetAdvancedIt(itBegin, 4);
            auto it1 = GetAdvancedIt(itBegin, 1);
            return AreCardsSameRank(itBegin, it4) || AreCardsSameRank(it1, std::end(cards));
        }
    }

    CompareResult::Value CompareFourOfAKind(const Hand& first, const Hand& second)
    {
        const bool isFirstApplicable = CheckFourOfAKind(first);
        const bool isSecondApplicable = CheckFourOfAKind(second);

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

        const auto kickerFirst = GetFourOfAKindKicker(first);
        const auto kickerSecond = GetFourOfAKindKicker(second);

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
}