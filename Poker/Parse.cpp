#include "Parse.h"

#include <algorithm>
#include <exception>

namespace
{
    Rank::Value ParseRank(const char c)
    {
        switch (c)
        {
        case 'A':
            return Rank::Ace;
        case 'K':
            return Rank::King;
        case 'Q':
            return Rank::Queen;
        case 'J':
            return Rank::Jack;
        case 'T':
            return Rank::C10;
        case '9':
            return Rank::C9;
        case '8':
            return Rank::C8;
        case '7':
            return Rank::C7;
        case '6':
            return Rank::C6;
        case '5':
            return Rank::C5;
        case '4':
            return Rank::C4;
        case '3':
            return Rank::C3;
        case '2':
            return Rank::C2;
        default:
            throw std::exception("ParseRank failed");
        }
    }

    Suit::Value ParseSuit(const char c)
    {
        switch (c)
        {
        case 'd':
            return Suit::Diamonds;
        case 'c':
            return Suit::Clubs;
        case 'h':
            return Suit::Hearts;
        case 's':
            return Suit::Spades;
        default:
            throw std::exception("ParseSuit failed");
        }
    }
}

CardSet Parse(const std::string& str)
{
    if (str.size() == 11)
    {
        CardSet result(4);
        result[0].rank = ParseRank(str[0]);
        result[0].suit = ParseSuit(str[1]);
        result[1].rank = ParseRank(str[3]);
        result[1].suit = ParseSuit(str[4]);
        result[2].rank = ParseRank(str[6]);
        result[2].suit = ParseSuit(str[7]);
        result[3].rank = ParseRank(str[9]);
        result[3].suit = ParseSuit(str[10]);
        return result;
    }

    if (str.size() == 14)
    {
        CardSet result(5);
        result[0].rank = ParseRank(str[0]);
        result[0].suit = ParseSuit(str[1]);
        result[1].rank = ParseRank(str[3]);
        result[1].suit = ParseSuit(str[4]);
        result[2].rank = ParseRank(str[6]);
        result[2].suit = ParseSuit(str[7]);
        result[3].rank = ParseRank(str[9]);
        result[3].suit = ParseSuit(str[10]);
        result[4].rank = ParseRank(str[12]);
        result[4].suit = ParseSuit(str[13]);
        return result;
    }

    throw std::exception("Parse, not expected string length");
}

Hand ParseToHand(const std::string& str )
{
    if (str.size() != 14)
    {
        throw std::exception("ParseToHand, not expected string length");
    }

    Hand result;
    result[0].rank = ParseRank(str[0]);
    result[0].suit = ParseSuit(str[1]);
    result[1].rank = ParseRank(str[3]);
    result[1].suit = ParseSuit(str[4]);
    result[2].rank = ParseRank(str[6]);
    result[2].suit = ParseSuit(str[7]);
    result[3].rank = ParseRank(str[9]);
    result[3].suit = ParseSuit(str[10]);
    result[4].rank = ParseRank(str[12]);
    result[4].suit = ParseSuit(str[13]);

    std::sort(
        std::begin(result),
        std::end(result),
        [](const Card& r, const Card& l) { return r.rank > l.rank; });

    return result;
}
