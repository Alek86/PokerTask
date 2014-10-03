#include "Logic.TwoPairs.h"

#include "Types.h"
#include "Logic.Utils.h"

namespace Logic
{
    namespace
    {
        struct CheckResult
        {
            bool isApplicable;
            Rank::Value rankMain1;
            Rank::Value rankMain2;
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

            if (first.rankMain1 > second.rankMain1)
            {
                return CompareResult::FirstWon;
            }

            if (first.rankMain1 < second.rankMain1)
            {
                return CompareResult::SecondWon;
            }

            if (first.rankMain2 > second.rankMain2)
            {
                return CompareResult::FirstWon;
            }

            if (first.rankMain2 < second.rankMain2)
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

        CheckResult Check(const Hand& cards)
        {
            CheckResult result;
            const size_t NumberOfSameRanksRequired = 2;
            auto itBegin = std::begin(cards);

            result.isApplicable = 
                AreCardsSameRank(itBegin, GetAdvancedIt(itBegin, NumberOfSameRanksRequired)) &&
                AreCardsSameRank(GetAdvancedIt(itBegin, 2), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 2));
            if (result.isApplicable)
            {
                result.rankMain1 = cards[0].rank;
                result.rankMain2 = cards[2].rank;
                result.rankKicker = cards[4].rank;
                return result;
            }

            result.isApplicable = 
                AreCardsSameRank(itBegin, GetAdvancedIt(itBegin, NumberOfSameRanksRequired)) &&
                AreCardsSameRank(GetAdvancedIt(itBegin, 3), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 3));
            if (result.isApplicable)
            {
                result.rankMain1 = cards[0].rank;
                result.rankMain2 = cards[3].rank;
                result.rankKicker = cards[2].rank;
                return result;
            }

            result.isApplicable = 
                AreCardsSameRank(GetAdvancedIt(itBegin, 1), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 1)) &&
                AreCardsSameRank(GetAdvancedIt(itBegin, 3), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 3));
            if (result.isApplicable)
            {
                result.rankMain1 = cards[1].rank;
                result.rankMain2 = cards[3].rank;
                result.rankKicker = cards[0].rank;
                return result;
            }

            return result;
        }
    }

    CompareResult::Value CompareTwoPairs(const Hand& first, const Hand& second)
    {
        const auto firstResult = Check(first);
        const auto secondResult = Check(second);
        return Compare(firstResult, secondResult);
    }
}
