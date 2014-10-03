#pragma once

#include "Types.h"

namespace Logic
{
    bool IsStraight(const Hand& cards);

    const Rank::Value GetHighestStraigtRank(const Hand& card);

    bool AreCardsSameSuit(const Hand& cards);

    int GetRankInt(const Card& card);
}