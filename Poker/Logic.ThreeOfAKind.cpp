#include "Logic.ThreeOfAKind.h"

#include "Types.h"
#include "Logic.Utils.h"

namespace Logic
{
    namespace
    {
        void Check3OfAKind(const Hand& cards, bool& isApplicable0, bool& isApplicable1, bool& isApplicable2)
        {
            const size_t NumberOfSameRanksRequired = 3;
            auto itBegin = std::begin(cards);
            isApplicable0 = AreCardsSameRank(itBegin, GetAdvancedIt(itBegin, NumberOfSameRanksRequired));
            isApplicable1 = AreCardsSameRank(GetAdvancedIt(itBegin, 1), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 1));
            isApplicable2 = AreCardsSameRank(GetAdvancedIt(itBegin, 2), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 2));
        }
    }

    CompareResult::Value Compare3OfAKind(const Hand& first, const Hand& second)
    {
        // The number in bools means the index of the first of 3 same ranks
        bool isFirstApplicable0 = false, isFirstApplicable1 = false, isFirstApplicable2 = false;
        Check3OfAKind(first, isFirstApplicable0, isFirstApplicable1, isFirstApplicable2);
        const bool isFirstApplicable = isFirstApplicable0 || isFirstApplicable1 || isFirstApplicable2;

        bool isSecondApplicable0 = false, isSecondApplicable1 = false, isSecondApplicable2 = false;
        Check3OfAKind(second, isSecondApplicable0, isSecondApplicable1, isSecondApplicable2);
        const bool isSecondApplicable = isSecondApplicable0 || isSecondApplicable1 || isSecondApplicable2;

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

        const auto rankMainFirst = GetRankInt(isFirstApplicable0 ? first[0] : (isFirstApplicable1 ? first[1] : first[2]));
        const auto rankKicker1First = GetRankInt(isFirstApplicable0 ? first[3] : first[0]);
        const auto rankKicker2First = GetRankInt(isFirstApplicable2 ? first[1] : first[4]);
        const auto rankMainSecond = GetRankInt(isSecondApplicable0 ? second[0] : (isSecondApplicable1 ? second[1] : second[2]));
        const auto rankKicker1Second = GetRankInt(isSecondApplicable0 ? second[3] : second[0]);
        const auto rankKicker2Second = GetRankInt(isSecondApplicable2 ? second[1] : second[4]);

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

        return CompareResult::BothWon;
    }
}
