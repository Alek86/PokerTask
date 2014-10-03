#include "Logic.Straight.h"

#include "Types.h"
#include "Logic.Utils.h"
#include "Logic.CheckResult.h"

namespace Logic
{
    namespace
    {
        CheckResult Check(const Hand& first)
        {
            CheckResult result;
            result.isApplicable = IsStraight(first);

            if (result.isApplicable)
            {
                result.rankMain1.SetValue(GetHighestStraigtRank(first));
            }

            return result;
        }
    }

    CompareResult::Value CompareStraight(const Hand& first, const Hand& second)
    {
        auto firstResult = Check(first);
        auto secondResult = Check(second);
        return Compare(firstResult, secondResult);
    }
}
