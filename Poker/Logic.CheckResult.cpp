#include "Logic.CheckResult.h"

namespace Logic
{
    CompareResult::Value Compare(const CheckResult& first, const CheckResult& second)
    {
        if (first.isApplicable && !second.isApplicable)
            return CompareResult::FirstWon;
        if (!first.isApplicable && second.isApplicable)
            return CompareResult::SecondWon;
        if (!first.isApplicable && !second.isApplicable)
            return CompareResult::BothLose;

        auto firstRank = first.rankMain1.GetValue();
        auto secondRank = second.rankMain1.GetValue();
        if (firstRank && secondRank)
        {
            if (*firstRank > *secondRank)
                return CompareResult::FirstWon;
            if (*firstRank < *secondRank)
                return CompareResult::SecondWon;
        }

        firstRank = first.rankMain2.GetValue();
        secondRank = second.rankMain2.GetValue();
        if (firstRank && secondRank)
        {
            if (*firstRank > *secondRank)
                return CompareResult::FirstWon;
            if (*firstRank < *secondRank)
                return CompareResult::SecondWon;
        }

        firstRank = first.rankKicker1.GetValue();
        secondRank = second.rankKicker1.GetValue();
        if (firstRank && secondRank)
        {
            if (*firstRank > *secondRank)
                return CompareResult::FirstWon;
            if (*firstRank < *secondRank)
                return CompareResult::SecondWon;
        }

        firstRank = first.rankKicker2.GetValue();
        secondRank = second.rankKicker2.GetValue();
        if (firstRank && secondRank)
        {
            if (*firstRank > *secondRank)
                return CompareResult::FirstWon;
            if (*firstRank < *secondRank)
                return CompareResult::SecondWon;
        }

        firstRank = first.rankKicker3.GetValue();
        secondRank = second.rankKicker3.GetValue();
        if (firstRank && secondRank)
        {
            if (*firstRank > *secondRank)
                return CompareResult::FirstWon;
            if (*firstRank < *secondRank)
                return CompareResult::SecondWon;
        }

        return CompareResult::BothWon;
    }
}