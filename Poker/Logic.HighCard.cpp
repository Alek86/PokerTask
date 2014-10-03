#include "Logic.HighCard.h"

#include "Types.h"
#include "Logic.Utils.h"

namespace Logic
{
    CompareResult::Value CompareHighCard(const Hand& first, const Hand& second)
    {
        for (size_t i = 0; i < first.size(); ++i)
        {
            if (GetRankInt(first[i]) > GetRankInt(second[i]))
            {
                return CompareResult::FirstWon;
            }

            if (GetRankInt(first[i]) < GetRankInt(second[i]))
            {
                return CompareResult::SecondWon;
            }
        }

        return CompareResult::BothWon;
    }
}

