#include "Logic.OnePair.h"

#include "Types.h"
#include "Logic.Utils.h"

namespace Logic
{
    namespace
    {
        void CheckOnePair(const Hand& cards, bool& isApplicable0, bool& isApplicable1, bool& isApplicable2, bool& isApplicable3)
        {
            const size_t NumberOfSameRanksRequired = 2;
            auto itBegin = std::begin(cards);
            isApplicable0 = AreCardsSameRank(itBegin, GetAdvancedIt(itBegin, NumberOfSameRanksRequired));
            isApplicable1 = AreCardsSameRank(GetAdvancedIt(itBegin, 1), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 1));
            isApplicable2 = AreCardsSameRank(GetAdvancedIt(itBegin, 2), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 2));
            isApplicable3 = AreCardsSameRank(GetAdvancedIt(itBegin, 3), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 3));
        }
    }

    CompareResult::Value CompareOnePair(const Hand& first, const Hand& second)
    {
        // The number in bools mean the index of the pair
        bool isFirstApplicable0 = false, isFirstApplicable1 = false, isFirstApplicable2 = false, isFirstApplicable3 = false;
        CheckOnePair(first, isFirstApplicable0, isFirstApplicable1, isFirstApplicable2, isFirstApplicable3);
        const bool isFirstApplicable = isFirstApplicable0 || isFirstApplicable1 || isFirstApplicable2 || isFirstApplicable3;

        bool isSecondApplicable0 = false, isSecondApplicable1 = false, isSecondApplicable2 = false, isSecondApplicable3 = false;
        CheckOnePair(second, isSecondApplicable0, isSecondApplicable1, isSecondApplicable2, isSecondApplicable3);
        const bool isSecondApplicable = isSecondApplicable0 || isSecondApplicable1 || isSecondApplicable2 || isSecondApplicable3;

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

        const auto rankMainFirst = GetRankInt(isFirstApplicable0 ? first[0] : (isFirstApplicable1 ? first[1] : (isFirstApplicable2 ? first[2] : first[3])));
        const auto rankKicker1First = GetRankInt(isFirstApplicable0 ? first[2] : first[0]);
        const auto rankKicker2First = GetRankInt((isFirstApplicable0 || isFirstApplicable1) ? first[3] : first[1]);
        const auto rankKicker3First = GetRankInt((isFirstApplicable0 || isFirstApplicable1 || isFirstApplicable2) ? first[4] : first[2]);

        const auto rankMainSecond = GetRankInt(isSecondApplicable0 ? second[0] : (isSecondApplicable1 ? second[1] : (isSecondApplicable2 ? second[2] : second[3])));
        const auto rankKicker1Second = GetRankInt(isSecondApplicable0 ? second[2] : second[0]);
        const auto rankKicker2Second = GetRankInt((isSecondApplicable0 || isSecondApplicable1) ? second[3] : second[1]);
        const auto rankKicker3Second = GetRankInt((isSecondApplicable0 || isSecondApplicable1 || isSecondApplicable2) ? second[4] : second[2]);

        if (rankMainFirst > rankMainSecond)
        {
            return CompareResult::FirstWon;
        }

        if (rankMainFirst < rankMainSecond)
        {
            return CompareResult::SecondWon;
        }

        if (rankKicker1First > rankKicker1Second)
        {
            return CompareResult::FirstWon;
        }

        if (rankKicker1First < rankKicker1Second)
        {
            return CompareResult::SecondWon;
        }

        if (rankKicker2First > rankKicker2Second)
        {
            return CompareResult::FirstWon;
        }

        if (rankKicker2First < rankKicker2Second)
        {
            return CompareResult::SecondWon;
        }

        if (rankKicker3First > rankKicker3Second)
        {
            return CompareResult::FirstWon;
        }

        if (rankKicker3First < rankKicker3Second)
        {
            return CompareResult::SecondWon;
        }

        return CompareResult::BothWon;
    }
}
