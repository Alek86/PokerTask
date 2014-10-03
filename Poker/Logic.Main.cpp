#include "Logic.Main.h"
#include "Logic.StraightFlush.h"
#include "Logic.FourOfAKind.h"
#include "Logic.FullHouse.h"
#include "Logic.Flush.h"
#include "Logic.Straight.h"
#include "Logic.ThreeOfAKind.h"
#include "Logic.TwoPairs.h"
#include "Logic.OnePair.h"
#include "Logic.HighCard.h"
#include "Logic.Utils.h"

#include <algorithm>

namespace Logic
{
    namespace
    {
        const int GetHighestRankForLow8Hand(const Hand& card)
        {
            // In Low Hand there shouldn't be duplicated ranks, so card[1] is not Ace
            if (card[0].rank == Rank::Ace)
            {
                return GetRankInt(card[1]);
            }

            return GetRankInt(card[0]);
        }

        const bool AllCardsNoMore8(const Hand& cards)
        {
            for (size_t i = 0; i < cards.size(); ++i)
            {
                if (cards[i].rank == Rank::Ace)
                {
                    continue;
                }

                if (GetRankInt(cards[i]) > static_cast<int>(Rank::C8))
                {
                    return false;
                }
            }

            return true;
        }

        const bool AllCardsDifferByRank(const Hand& cards)
        {
            for (size_t i = 0; i < cards.size(); ++i)
            {
                for (size_t j = i + 1; j < cards.size(); ++j)
                {
                    if (cards[i].rank == cards[j].rank)
                    {
                        return false;
                    }
                }
            }

            return true;
        }
    }

    Hand GetBestHand(
        const CardSet& inHand,
        const CardSet& onBoard,
        std::function<CompareResult::Value(const Hand&, const Hand&)> isFirstBetterPredicate)
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

        bool isFirstIteration = true;
        Hand bestSet;
        for (size_t i = 0; i < numOfCombinationsFromHand; ++i)
        {
            for (size_t j = 0; j < numOfCombinationsFromBoard; ++j)
            {
                // Create a hand (5 cards). It must be sorted descending by Rank
                Hand currentSet;
                currentSet[0] = inHand[combinationsFromHandIndices[i][0]];
                currentSet[1] = inHand[combinationsFromHandIndices[i][1]];
                currentSet[2] = onBoard[combinationsFromBoardIndices[j][0]];
                currentSet[3] = onBoard[combinationsFromBoardIndices[j][1]];
                currentSet[4] = onBoard[combinationsFromBoardIndices[j][2]];
                std::sort(
                    std::begin(currentSet),
                    std::end(currentSet),
                    [](const Card& r, const Card& l) { return r.rank > l.rank; });

                if (isFirstIteration)
                {
                    // The current set is the best we have
                    bestSet.swap(currentSet);
                    isFirstIteration = false;
                    continue;
                }

                auto compareResult = isFirstBetterPredicate(currentSet, bestSet);
                if (compareResult == CompareResult::FirstWon)
                {
                    bestSet.swap(currentSet);
                }
            }
        }

        return bestSet;
    }

    CompareResult::Value CompareHighHand(const Hand& rhs, const Hand& lhs, HighRanking::Value& highRankingResult)
    {
        CompareResult::Value result = CompareResult::BothLose;

        result = Logic::CompareStraightFlush(rhs, lhs);
        if (result != CompareResult::BothLose)
        {
            highRankingResult = HighRanking::StraighFlush;
            return result;
        }

        result = CompareFourOfAKind(rhs, lhs);
        if (result != CompareResult::BothLose)
        {
            highRankingResult = HighRanking::FourOfAKind;
            return result;
        }

        result = CompareFullHouse(rhs, lhs);
        if (result != CompareResult::BothLose)
        {
            highRankingResult = HighRanking::FullHouse;
            return result;
        }

        result = CompareFlush(rhs, lhs);
        if (result != CompareResult::BothLose)
        {
            highRankingResult = HighRanking::Flush;
            return result;
        }

        result = CompareStraight(rhs, lhs);
        if (result != CompareResult::BothLose)
        {
            highRankingResult = HighRanking::Straight;
            return result;
        }

        result = Compare3OfAKind(rhs, lhs);
        if (result != CompareResult::BothLose)
        {
            highRankingResult = HighRanking::ThreeOfAKind;
            return result;
        }

        result = CompareTwoPairs(rhs, lhs);
        if (result != CompareResult::BothLose)
        {
            highRankingResult = HighRanking::TwoPair;
            return result;
        }

        result = CompareOnePair(rhs, lhs);
        if (result != CompareResult::BothLose)
        {
            highRankingResult = HighRanking::OnePair;
            return result;
        }

        result = CompareHighCard(rhs, lhs);
        highRankingResult = HighRanking::HighCard;
        return result;
    }
    CompareResult::Value CompareLowHand(const Hand& first, const Hand& second)
    {
        const bool isFirstApplicable = AllCardsNoMore8(first) && AllCardsDifferByRank(first);
        const bool isSecondApplicable = AllCardsNoMore8(second) && AllCardsDifferByRank(second);

        if (isFirstApplicable && !isSecondApplicable)
        {
            return CompareResult::FirstWon;
        }

        if (!isFirstApplicable && isSecondApplicable)
        {
            return CompareResult::SecondWon;
        }

        if (!isFirstApplicable && !isSecondApplicable)
        {
            return CompareResult::BothLose;
        }

        const int highestRankFirst = GetHighestRankForLow8Hand(first);
        const int highestRankSecond = GetHighestRankForLow8Hand(second);

        if (highestRankFirst > highestRankSecond)
        {
            return CompareResult::SecondWon;
        }

        if (highestRankFirst < highestRankSecond)
        {
            return CompareResult::FirstWon;
        }

        return CompareResult::BothWon;
    }
}