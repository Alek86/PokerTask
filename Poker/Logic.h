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


    // These functions are here for testing purposes
    CompareResult::Value Compare4OfAKind(const Hand& first, const Hand& second);
    CompareResult::Value CompareFullHouse(const Hand& first, const Hand& second);
    CompareResult::Value CompareFlush(const Hand& first, const Hand& second);
    CompareResult::Value CompareStraight(const Hand& first, const Hand& second);
    CompareResult::Value Compare3OfAKind(const Hand& first, const Hand& second);
    CompareResult::Value CompareTwoPairs(const Hand& first, const Hand& second);
    CompareResult::Value CompareOnePair(const Hand& first, const Hand& second);
    CompareResult::Value CompareHighCard(const Hand& first, const Hand& second);
}