#include "Logic.FourOfAKind.h"

#include "Types.h"
#include "Logic.Utils.h"

namespace Logic
{
    namespace
    {
        struct CheckResult
        {
            bool isApplicable;
            Rank::Value rankDuplicated;
            Rank::Value rankKicker;
        };

        CompareResult::Value Compare(const CheckResult& first, const CheckResult& second)
        {
            if (first.isApplicable && !second.isApplicable)
            {
                return CompareResult::FirstWon;
            }

            if (!first.isApplicable && second.isApplicable)
            {
                return CompareResult::SecondWon;
            }

            if (!first.isApplicable && !second.isApplicable)
            {
                return CompareResult::BothLose;
            }

            if (first.rankDuplicated > second.rankDuplicated)
            {
                return CompareResult::FirstWon;
            }

            if (first.rankDuplicated < second.rankDuplicated)
            {
                return CompareResult::SecondWon;
            }
            
            if (first.rankKicker > second.rankKicker)
            {
                return CompareResult::FirstWon;
            }

            if (first.rankKicker < second.rankKicker)
            {
                return CompareResult::SecondWon;
            }

            return CompareResult::BothWon;
        }

        Rank::Value GetFourOfAKindKicker(const Hand& cards)
        {
            if (cards[0].rank != cards[2].rank)
            {
                return cards[0].rank;
            }

            return cards[4].rank;
        }

        CheckResult CheckFourOfAKind(const Hand& cards)
        {
            CheckResult result;

            auto itBegin = std::begin(cards);
            auto it4 = GetAdvancedIt(itBegin, 4);
            auto it1 = GetAdvancedIt(itBegin, 1);
            result.isApplicable = AreCardsSameRank(itBegin, it4) || AreCardsSameRank(it1, std::end(cards));

            // In 4-of-a-kind in a sorted array the third card always has the duplicated rank
            result.rankDuplicated = cards[2].rank;
            result.rankKicker = GetFourOfAKindKicker(cards);

            return result;
        }
    }

    CompareResult::Value CompareFourOfAKind(const Hand& first, const Hand& second)
    {
        const auto firstResult = CheckFourOfAKind(first);
        const auto secondResult = CheckFourOfAKind(second);
        return Compare(firstResult, secondResult);

    }
}