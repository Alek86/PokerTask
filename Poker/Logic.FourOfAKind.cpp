#include "Logic.FourOfAKind.h"

#include "Types.h"
#include "Logic.Utils.h"
#include "Logic.CheckResult.h"

namespace Logic
{
    namespace
    {
        Rank::Value GetFourOfAKindKicker(const Hand& cards)
        {
            if (cards[0].rank != cards[2].rank)
            {
                return cards[0].rank;
            }

            return cards[4].rank;
        }

        CheckResult Check(const Hand& cards)
        {
            CheckResult result;

            auto itBegin = std::begin(cards);
            auto it4 = GetAdvancedIt(itBegin, 4);
            auto it1 = GetAdvancedIt(itBegin, 1);
            result.isApplicable = AreCardsSameRank(itBegin, it4) || AreCardsSameRank(it1, std::end(cards));

            // In 4-of-a-kind in a sorted array the third card always has the duplicated rank
            result.rankMain1.SetValue(cards[2].rank);
            result.rankKicker1.SetValue(GetFourOfAKindKicker(cards));

            return result;
        }
    }

    CompareResult::Value CompareFourOfAKind(const Hand& first, const Hand& second)
    {
        const auto firstResult = Check(first);
        const auto secondResult = Check(second);
        return Compare(firstResult, secondResult);
    }
}