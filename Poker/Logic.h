#pragma once

#include "Types.h"

#include <functional>

Hand GetBestSet(
	const CardSet& inHand,
	const CardSet& onBoard,
	std::function<CompareResult::Value(const CardSet&, const CardSet&)> isFirstBetterPredicate);

CompareResult::Value CompareHighHand(const Hand& rhs, const Hand& lhs);