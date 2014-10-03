#include "Logic.Straight.h"

#include "Types.h"
#include "Logic.Utils.h"

namespace Logic
{
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
}
