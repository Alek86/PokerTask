#pragma once

#include "Types.h"

#include <functional>

Cards GetBestSet(
	const Cards& hand,
	const Cards& board,
	std::function<CompareResult::Value(const Cards&, const Cards&)> isFirstBetterPredicate);

CompareResult::Value CompareHighHand(const Cards& rhs, const Cards& lhs);