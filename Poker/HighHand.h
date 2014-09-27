#pragma once

#include "Types.h"

#include <vector>
#include <iostream>
#include <functional>

Cards GetBestSet(const Cards& hand, const Cards& board, std::function<bool(const Cards&, const Cards&)> isFirstBetterPredicate)
{
	const size_t numOfHandCards = 2;
	const size_t numOfCombinationsFromHand = 6;
	const size_t numOfBoardCards = 3;
	const size_t numOfCombinationsFromBoard = 10;

	size_t combinationsFromHandIndices[numOfCombinationsFromHand][numOfHandCards] =
	{
		{0, 1},
		{0, 2},
		{0, 3},
		{1, 2},
		{1, 3},
		{2, 3}
	};

	size_t combinationsFromBoardIndices[numOfCombinationsFromBoard][numOfBoardCards] =
	{
		{0, 1, 2},
		{0, 1, 3},
		{0, 1, 4},
		{0, 2, 3},
		{0, 2, 4},
		{0, 3, 4},
		{1, 2, 3},
		{1, 2, 4},
		{1, 3, 4},
		{2, 3, 4}
	};

	Cards bestSet;
	for (int i = 0; i < numOfCombinationsFromHand; ++i)
	{
		for (int j = 0; j < numOfCombinationsFromBoard; ++j)
		{
			Cards currentSet(5);
			currentSet.push_back(hand[combinationsFromHandIndices[i][0]]);
			currentSet.push_back(hand[combinationsFromHandIndices[i][1]]);
			currentSet.push_back(hand[combinationsFromBoardIndices[j][0]]);
			currentSet.push_back(hand[combinationsFromBoardIndices[j][1]]);
			currentSet.push_back(hand[combinationsFromBoardIndices[j][2]]);

			if (bestSet.empty())
			{
				// The first iteration, the current set is the best we have
				bestSet.swap(currentSet);
				continue;
			}

			if (isFirstBetterPredicate(currentSet, bestSet))
			{
				bestSet.swap(currentSet);
			}
		}
	}

	return bestSet;
}