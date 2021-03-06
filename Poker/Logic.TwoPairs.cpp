#include "Logic.TwoPairs.h"

#include "Types.h"
#include "Logic.Utils.h"
#include "Logic.CheckResult.h"

namespace Logic
{
    namespace
    {
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
                result.rankMain1.SetValue(cards[0].rank);
                result.rankMain2.SetValue(cards[2].rank);
                result.rankKicker1.SetValue(cards[4].rank);
                return result;
            }

            result.isApplicable = 
                AreCardsSameRank(itBegin, GetAdvancedIt(itBegin, NumberOfSameRanksRequired)) &&
                AreCardsSameRank(GetAdvancedIt(itBegin, 3), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 3));
            if (result.isApplicable)
            {
                result.rankMain1.SetValue(cards[0].rank);
                result.rankMain2.SetValue(cards[3].rank);
                result.rankKicker1.SetValue(cards[2].rank);
                return result;
            }

            result.isApplicable = 
                AreCardsSameRank(GetAdvancedIt(itBegin, 1), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 1)) &&
                AreCardsSameRank(GetAdvancedIt(itBegin, 3), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 3));
            if (result.isApplicable)
            {
                result.rankMain1.SetValue(cards[1].rank);
                result.rankMain2.SetValue(cards[3].rank);
                result.rankKicker1.SetValue(cards[0].rank);
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
