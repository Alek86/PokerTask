#include "Logic.FourOfAKind.h"

#include "Types.h"
#include "Logic.Utils.h"
#include "Logic.HighCard.h"

namespace Logic
{
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
}