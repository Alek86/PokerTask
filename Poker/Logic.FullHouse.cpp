#include "Logic.FullHouse.h"

#include "Types.h"
#include "Logic.Utils.h"

namespace Logic
{
    namespace
    {
        struct CheckResult
        {
            bool isApplicable;
            Rank::Value rank3OfAKind;
            Rank::Value rank2OfAKind;
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

            if (first.rank3OfAKind > second.rank3OfAKind)
            {
                return CompareResult::FirstWon;
            }

            if (first.rank3OfAKind < second.rank3OfAKind)
            {
                return CompareResult::SecondWon;
            }

            if (first.rank2OfAKind > second.rank2OfAKind)
            {
                return CompareResult::FirstWon;
            }

            if (first.rank2OfAKind < second.rank2OfAKind)
            {
                return CompareResult::SecondWon;
            }

            return CompareResult::BothWon;
        }

        CheckResult Check(const Hand& cards)
        {
            CheckResult result;
            // The hand is sorted, so we just check if 4 first or 4 last cards have the same rank
            auto itBegin = std::begin(cards);
            auto it2 = GetAdvancedIt(itBegin, 2);
            auto it3 = GetAdvancedIt(itBegin, 3);

            result.isApplicable = AreCardsSameRank(itBegin, it2) && AreCardsSameRank(it2, std::end(cards));
            if (result.isApplicable)
            {
                result.rank2OfAKind = cards[0].rank;
                result.rank3OfAKind = cards[2].rank;
                return result;
            }

            result.isApplicable = AreCardsSameRank(itBegin, it3) && AreCardsSameRank(it3, std::end(cards));
            if (result.isApplicable)
            {
                result.rank2OfAKind = cards[3].rank;
                result.rank3OfAKind = cards[0].rank;
                return result;
            }

            return result;
        }
    }

    CompareResult::Value CompareFullHouse(const Hand& first, const Hand& second)
    {
        const auto firstResult = Check(first);
        const auto secondResult = Check(second);
        return Compare(firstResult, secondResult);
    }
}