#pragma once

#include "Types.h"

namespace Logic
{
    template <typename It>
    bool AreCardsSameRank(It begin, It end)
    {
        if (begin == end)
        {
            return true;
        }

        auto firstRank = begin->rank;
        for(auto it = begin; it != end; ++it)
        {
            if (it->rank != firstRank)
            {
                return false;
            }
        }

        return true;
    }

    template <typename It>
    It GetAdvancedIt(It it, size_t n)
    {
        std::advance(it, n);
        return it;
    }

    bool IsStraight(const Hand& cards);

    const Rank::Value GetHighestStraigtRank(const Hand& card);

    bool AreCardsSameSuit(const Hand& cards);

    int GetRankInt(const Card& card);
}