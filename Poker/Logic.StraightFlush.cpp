#include "Logic.StraightFlush.h"
#include "Logic.Utils.h"

namespace Logic
{
    namespace
    {
        struct CheckResult
        {
            bool isApplicable;
            Rank::Value rankMain;
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

            if (first.rankMain > second.rankMain)
            {
                return CompareResult::FirstWon;
            }

            if (first.rankMain < second.rankMain)
            {
                return CompareResult::SecondWon;
            }

            return CompareResult::BothWon;
        }

        CheckResult Check(const Hand& first)
        {
            CheckResult result;
            result.isApplicable = IsStraight(first) && AreCardsSameSuit(first);

            if (result.isApplicable)
            {
                result.rankMain = GetHighestStraigtRank(first);
            }

            return result;
        }
    }

    CompareResult::Value CompareStraightFlush(const Hand& first, const Hand& second)
    {
        auto firstResult = Check(first);
        auto secondResult = Check(second);
        return Compare(firstResult, secondResult);
    }
}