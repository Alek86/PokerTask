#include "Logic.Utils.h"

#include "Types.h"

namespace
{

}

namespace Logic
{
    int GetRankInt(const Card& card)
    {
        return static_cast<int>(card.rank);
    }

    bool IsStraight(const Hand& cards)
    {
        bool result = true;
        for (size_t i = 0; i < cards.size() - 1; ++i)
        {
            if (GetRankInt(cards[i]) != GetRankInt(cards[i + 1]) + 1)
            {
                result = false;
                break;
            }
        }

        if (result)
        {
            return true;
        }

        // If not, check the special case with Ace
        bool isSpecialCaseTrue =
            cards[0].rank == Rank::Ace &&
            cards[1].rank == Rank::C5 &&
            cards[2].rank == Rank::C4 &&
            cards[3].rank == Rank::C3 &&
            cards[4].rank == Rank::C2;

        return isSpecialCaseTrue;
    }

    const Rank::Value GetHighestStraigtRank(const Hand& card)
    {
        // The cards must be Straight category if they are passed to this function.
        // The ace could be a lower card, need to check this situation

        if (card[0].rank == Rank::Ace && card[1].rank == Rank::C5)
        {
            return card[1].rank;
        }

        return card[0].rank;
    }

    bool AreCardsSameSuit(const Hand& cards)
    {
        auto firstSuit = cards[0].suit;
        for(auto it = std::begin(cards); it != std::end(cards); ++it)
        {
            if (it->suit != firstSuit)
            {
                return false;
            }
        }

        return true;
    }

}