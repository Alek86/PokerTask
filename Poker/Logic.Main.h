#pragma once

#include "Types.h"

#include <functional>

namespace Logic
{
    Hand GetBestHand(
	    const CardSet& inHand,
	    const CardSet& onBoard,
	    std::function<CompareResult::Value(const Hand&, const Hand&)> isFirstBetterPredicate);

    CompareResult::Value CompareHighHand(const Hand& rhs, const Hand& lhs, HighRanking::Value& highRankingResult);
    CompareResult::Value CompareLowHand(const Hand& rhs, const Hand& lhs);    
}