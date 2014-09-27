#pragma once

#include "Types.h"

#include <functional>

Hand GetBestSet(
	const CardSet& inHand,
	const CardSet& onBoard,
	std::function<CompareResult::Value(const Hand&, const Hand&)> isFirstBetterPredicate);

CompareResult::Value CompareHighHand(const Hand& rhs, const Hand& lhs);

CompareResult::Value CompareStraightFlush(const Hand& first, const Hand& second);
CompareResult::Value Compare4OfAKind(const Hand& first, const Hand& second);
CompareResult::Value CompareFullHouse(const Hand& first, const Hand& second);
CompareResult::Value CompareFlush(const Hand& first, const Hand& second);
CompareResult::Value CompareStraight(const Hand& first, const Hand& second);
CompareResult::Value Compare3OfAKind(const Hand& first, const Hand& second);
CompareResult::Value CompareTwoPairs(const Hand& first, const Hand& second);
CompareResult::Value CompareOnePair(const Hand& first, const Hand& second);
CompareResult::Value CompareHighCard(const Hand& first, const Hand& second);