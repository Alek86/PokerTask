#include "Logic.ThreeOfAKind.h"

#include "Types.h"
#include "Logic.Utils.h"

namespace Logic
{
    namespace
    {
        namespace
        {
            struct CheckResult
            {
                bool isApplicable;
                Rank::Value rankMain;
                Rank::Value rankKicker1;
                Rank::Value rankKicker2;
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

                if (first.rankKicker1 > second.rankKicker1)
                {
                    return CompareResult::FirstWon;
                }

                if (first.rankKicker1 < second.rankKicker1)
                {
                    return CompareResult::SecondWon;
                }

                if (first.rankKicker2 > second.rankKicker2)
                {
                    return CompareResult::FirstWon;
                }

                if (first.rankKicker2 < second.rankKicker2)
                {
                    return CompareResult::SecondWon;
                }

                return CompareResult::BothWon;
            }
            
            CheckResult Check(const Hand& cards)
            {
                CheckResult result;
                const size_t NumberOfSameRanksRequired = 3;
                auto itBegin = std::begin(cards);
                
                result.isApplicable = AreCardsSameRank(itBegin, GetAdvancedIt(itBegin, NumberOfSameRanksRequired));
                if (result.isApplicable)
                {
                    result.rankMain = cards[0].rank;
                    result.rankKicker1 = cards[3].rank;
                    result.rankKicker2 = cards[4].rank;
                    return result;
                }

                result.isApplicable = AreCardsSameRank(GetAdvancedIt(itBegin, 1), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 1));
                if (result.isApplicable)
                {
                    result.rankMain = cards[1].rank;
                    result.rankKicker1 = cards[0].rank;
                    result.rankKicker2 = cards[4].rank;
                    return result;
                }

                result.isApplicable = AreCardsSameRank(GetAdvancedIt(itBegin, 2), GetAdvancedIt(itBegin, NumberOfSameRanksRequired + 2));
                if (result.isApplicable)
                {
                    result.rankMain = cards[2].rank;
                    result.rankKicker1 = cards[0].rank;
                    result.rankKicker2 = cards[1].rank;
                    return result;
                }

                return result;
            }
        }
    }

    CompareResult::Value CompareThreeOfAKind(const Hand& first, const Hand& second)
    {
        auto firstResult = Check(first);
        auto secondResult = Check(second);
        return Compare(firstResult, secondResult);
    }
}
