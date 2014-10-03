#include "Logic.StraightFlush.h"
#include "Logic.Utils.h"

namespace Logic
{
    namespace
    {
        struct StraightFlushCheckResult
        {
            bool isApplicable;
            Rank::Value highestRank;
        };

        CompareResult::Value Compare(const StraightFlushCheckResult& first, const StraightFlushCheckResult& second)
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

            if (first.highestRank > second.highestRank)
            {
                return CompareResult::FirstWon;
            }

            if (first.highestRank < second.highestRank)
            {
                return CompareResult::SecondWon;
            }

            return CompareResult::BothWon;
        }

        StraightFlushCheckResult CheckStraightFlush( const Hand& first )
        {
            StraightFlushCheckResult result;
            result.isApplicable = IsStraight(first) && AreCardsSameSuit(first);

            if (result.isApplicable)
            {
                result.highestRank = GetHighestStraigtRank(first);
            }

            return result;
        }
    }

    CompareResult::Value CompareStraightFlush(const Hand& first, const Hand& second)
    {
        auto firstResult = CheckStraightFlush(first);
        auto secondResult = CheckStraightFlush(second);
        return Compare(firstResult, secondResult);
    }
}