#include "Logic.TwoPairs.h"

#include "Types.h"
#include "Logic.Utils.h"

namespace Logic
{
    namespace
    {
        void CheckTwoPair(const Hand& cards, bool& isApplicable0And2, bool& isApplicable0And3, bool& isApplicable1And3)
        {
            const size_t NumberOfSameRanksRequired = 2;
            auto itBegin = std::begin(cards);
            isApplicable0And2 = 
                AreCardsSameRank(itBegin, GetAdvancedIt(itBegin, NumberOfSameRanksRequired)) &&
                AreCardsSameRank(GetAdvancedIt(itBegin, 2), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 2));
            isApplicable0And3 = 
                AreCardsSameRank(itBegin, GetAdvancedIt(itBegin, NumberOfSameRanksRequired)) &&
                AreCardsSameRank(GetAdvancedIt(itBegin, 3), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 3));
            isApplicable1And3 = 
                AreCardsSameRank(GetAdvancedIt(itBegin, 1), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 1)) &&
                AreCardsSameRank(GetAdvancedIt(itBegin, 3), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 3));
        }
    }

    CompareResult::Value CompareTwoPairs(const Hand& first, const Hand& second)
    {
        // The numbers in bools mean the indices of the pairs
        bool isFirstApplicable0And2 = false, isFirstApplicable0And3 = false, isFirstApplicable1And3 = false;
        CheckTwoPair(first, isFirstApplicable0And2, isFirstApplicable0And3, isFirstApplicable1And3);
        const bool isFirstApplicable = isFirstApplicable0And2 || isFirstApplicable0And3 || isFirstApplicable1And3;

        bool isSecondApplicable0And2 = false, isSecondApplicable0And3 = false, isSecondApplicable1And3 = false;
        CheckTwoPair(second, isSecondApplicable0And2, isSecondApplicable0And3, isSecondApplicable1And3);
        const bool isSecondApplicable = isSecondApplicable0And2 || isSecondApplicable0And3 || isSecondApplicable1And3;

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

        const auto rank1First = GetRankInt((isFirstApplicable0And2 || isFirstApplicable0And3) ? first[0] : first[1]);
        const auto rank2First = GetRankInt((isFirstApplicable0And3 || isFirstApplicable1And3) ? first[3] : first[2]);
        const auto rankKickerFirst = GetRankInt(isFirstApplicable0And2 ? first[4] : (isFirstApplicable0And3 ? first[2] : first[0]));

        const auto rank1Second = GetRankInt((isSecondApplicable0And2 || isSecondApplicable0And3) ? second[0] : second[1]);
        const auto rank2Second = GetRankInt((isSecondApplicable0And3 || isSecondApplicable1And3) ? second[3] : second[2]);
        const auto rankKickerSecond = GetRankInt(isSecondApplicable0And2 ? second[4] : (isSecondApplicable0And3 ? second[2] : second[0]));

        if (rank1First > rank1Second)
        {
            return CompareResult::FirstWon;
        }

        if (rank1First < rank1Second)
        {
            return CompareResult::SecondWon;
        }

        if (rank2First > rank2Second)
        {
            return CompareResult::FirstWon;
        }

        if (rank2First < rank2Second)
        {
            return CompareResult::SecondWon;
        }

        if (rankKickerFirst > rankKickerSecond)
        {
            return CompareResult::FirstWon;
        }

        if (rankKickerFirst < rankKickerSecond)
        {
            return CompareResult::SecondWon;
        }

        return CompareResult::BothWon;
    }
}
