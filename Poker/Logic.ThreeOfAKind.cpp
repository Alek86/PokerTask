#include "Logic.ThreeOfAKind.h"

#include "Types.h"
#include "Logic.Utils.h"
#include "Logic.CheckResult.h"

namespace Logic
{
    namespace
    {
        namespace
        {            
            CheckResult Check(const Hand& cards)
            {
                CheckResult result;
                const size_t NumberOfSameRanksRequired = 3;
                auto itBegin = std::begin(cards);
                
                result.isApplicable = AreCardsSameRank(itBegin, GetAdvancedIt(itBegin, NumberOfSameRanksRequired));
                if (result.isApplicable)
                {
                    result.rankMain1.SetValue(cards[0].rank);
                    result.rankKicker1.SetValue(cards[3].rank);
                    result.rankKicker2.SetValue(cards[4].rank);
                    return result;
                }

                result.isApplicable = AreCardsSameRank(GetAdvancedIt(itBegin, 1), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 1));
                if (result.isApplicable)
                {
                    result.rankMain1.SetValue(cards[1].rank);
                    result.rankKicker1.SetValue(cards[0].rank);
                    result.rankKicker2.SetValue(cards[4].rank);
                    return result;
                }

                result.isApplicable = AreCardsSameRank(GetAdvancedIt(itBegin, 2), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 2));
                if (result.isApplicable)
                {
                    result.rankMain1.SetValue(cards[2].rank);
                    result.rankKicker1.SetValue(cards[0].rank);
                    result.rankKicker2.SetValue(cards[1].rank);
                    return result;
                }

                return result;
            }
        }
    }

    CompareResult::Value CompareThreeOfAKind(const Hand& first, const Hand& second)
    {
        auto firstResult = Check(first);
        auto secondResult = Check(second);
        return Compare(firstResult, secondResult);
    }
}
