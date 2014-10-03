#include "Logic.FullHouse.h"

#include "Types.h"
#include "Logic.Utils.h"

namespace Logic
{
    namespace
    {
        void CheckFullHouse(const Hand& cards, bool& isApplicable3And2, bool& isApplicable2And3)
        {
            // The hand is sorted, so we just check if 4 first or 4 last cards have the same rank
            auto itBegin = std::begin(cards);
            auto it2 = GetAdvancedIt(itBegin, 2);
            auto it3 = GetAdvancedIt(itBegin, 3);
            isApplicable2And3 = AreCardsSameRank(itBegin, it2) && AreCardsSameRank(it2, std::end(cards));
            isApplicable3And2 = AreCardsSameRank(itBegin, it3) && AreCardsSameRank(it3, std::end(cards));
        }
    }

    CompareResult::Value CompareFullHouse(const Hand& first, const Hand& second)
    {
        bool isFirstApplicable3And2 = false, isFirstApplicable2And3 = false;
        CheckFullHouse(first, isFirstApplicable3And2, isFirstApplicable2And3);
        const bool isFirstApplicable = isFirstApplicable2And3 || isFirstApplicable3And2;

        bool isSecondApplicable3And2 = false, isSecondApplicable2And3 = false;
        CheckFullHouse(second, isSecondApplicable3And2, isSecondApplicable2And3);
        const bool isSecondApplicable = isSecondApplicable2And3 || isSecondApplicable3And2;

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

        const auto rank3OfAKindFirst = GetRankInt(isFirstApplicable3And2 ? first[0] : first[2]);
        const auto rank2OfAKindFirst = GetRankInt(isFirstApplicable3And2 ? first[3]: first[0]);
        const auto rank3OfAKindSecond = GetRankInt(isSecondApplicable3And2 ? second[0] : second[2]);
        const auto rank2OfAKindSecond = GetRankInt(isSecondApplicable3And2 ? second[3] : second[0]);

        if (rank3OfAKindFirst > rank3OfAKindSecond)
        {
            return CompareResult::FirstWon;
        }

        if (rank3OfAKindFirst < rank3OfAKindSecond)
        {
            return CompareResult::SecondWon;
        }

        if (rank2OfAKindFirst > rank2OfAKindSecond)
        {
            return CompareResult::FirstWon;
        }

        if (rank2OfAKindFirst < rank2OfAKindSecond)
        {
            return CompareResult::SecondWon;
        }

        return CompareResult::BothWon;
    }
}