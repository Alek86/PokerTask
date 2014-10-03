#include "Logic.FullHouse.h"

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
            auto itBegin = std::begin(cards);
            auto it2 = GetAdvancedIt(itBegin, 2);
            auto it3 = GetAdvancedIt(itBegin, 3);

            result.isApplicable = AreCardsSameRank(itBegin, it2) && AreCardsSameRank(it2, std::end(cards));
            if (result.isApplicable)
            {
                result.rankMain1.SetValue(cards[2].rank);
                result.rankMain2.SetValue(cards[0].rank);
                return result;
            }

            result.isApplicable = AreCardsSameRank(itBegin, it3) && AreCardsSameRank(it3, std::end(cards));
            if (result.isApplicable)
            {
                result.rankMain1.SetValue(cards[0].rank);
                result.rankMain2.SetValue(cards[3].rank);
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