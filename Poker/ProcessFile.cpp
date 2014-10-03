#include "ProcessFile.h"
#include "Types.h"
#include "Parse.h"
#include "Logic.h"

#include <sstream>
#include <string>
#include <functional>

namespace
{
    char ToChar(Rank::Value rank)
    {
        switch(rank)
        {
        case Rank::C2:
            return '2';
        case Rank::C3:
            return '3';
        case Rank::C4:
            return '4';
        case Rank::C5:
            return '5';
        case Rank::C6:
            return '6';
        case Rank::C7:
            return '7';
        case Rank::C8:
            return '8';
        case Rank::Ace:
            return 'A';
        default:
            return '%'; // Error
        }
    }

    std::string ToString(const Hand& cards)
    {
        std::string result;
        for (size_t i = 0; i < cards.size(); ++i)
        {
            result += ToChar(cards[i].rank);
        }

        return result;
    }

    const char* ToString(HighRanking::Value highRankingResult)
    {
        switch(highRankingResult)
        {
        case HighRanking::StraighFlush:
            return "Straight Flush";
        case HighRanking::FourOfAKind:
            return "4-of-a-Kind";
        case HighRanking::FullHouse:
            return "Full House";
        case HighRanking::Flush:
            return "Flush";
        case HighRanking::Straight:
            return "Straight";
        case HighRanking::ThreeOfAKind:
            return "3-of-a-Kind";
        case HighRanking::TwoPair:
            return "Two Pair";
        case HighRanking::OnePair:
            return "One Pair";
        case HighRanking::HighCard:
            return "High card";
        default:
            return "Unknown Result";
        }
    }

    std::string ProcessResults(
        const std::string& line,
        CompareResult::Value resultHigh,
        HighRanking::Value highRankingResult,
        CompareResult::Value resultLow,
        const Hand& bestHandALow,
        const Hand& bestHandBLow )
    {
        std::ostringstream oss;
        oss << line;
        oss << std::endl;
        oss << "=> ";

        switch (resultHigh)
        {
        case CompareResult::FirstWon:
            oss << "HandA wins Hi (";
            oss << ToString(highRankingResult);
            oss << ");";
            break;
        case CompareResult::SecondWon:
            oss << "HandB wins Hi (";
            oss << ToString(highRankingResult);
            oss << ");";
            break;
        case CompareResult::BothWon:
            oss << "Split Pot Hi (";
            oss << ToString(highRankingResult);
            oss << ");";
            break;
        case CompareResult::BothLose:
            oss << "Not expected result, both lose;";
            break;
        }

        switch (resultLow)
        {
        case CompareResult::FirstWon:
            oss << "HandA wins Lo (";
            oss << ToString(bestHandALow);
            oss << ")";
            break;
        case CompareResult::SecondWon:
            oss << "HandB wins Lo (";
            oss << ToString(bestHandBLow);
            oss << ")";
            break;
        case CompareResult::BothWon:
            oss << "Split Pot Lo (";
            oss << ToString(bestHandALow);
            oss << ")";
            break;
        case CompareResult::BothLose:
            oss << "No hand qualified for Low";
            break;
        }

        oss << std::endl;
        return oss.str();
    }
}

std::string ProcessInputLine(const std::string& line)
{
    CardSet handA;
    CardSet handB;
    CardSet board;

    Parse(line, handA, handB, board);

    using namespace std::placeholders;
    auto stubResultA = HighRanking::HighCard;
    auto stubResultB = HighRanking::HighCard;
    auto bestHandAHigh = GetBestHand(handA, board, std::bind(CompareHighHand, _1, _2, std::ref(stubResultA)));
    auto bestHandBHigh = GetBestHand(handB, board, std::bind(CompareHighHand, _1, _2, std::ref(stubResultB)));
    auto bestHandALow = GetBestHand(handA, board, CompareLowHand);
    auto bestHandBLow = GetBestHand(handB, board, CompareLowHand);

    auto highRankingResult = HighRanking::HighCard;
    auto resultHigh = CompareHighHand(bestHandAHigh, bestHandBHigh, highRankingResult);
    auto resultLow = CompareLowHand(bestHandALow, bestHandBLow);

    return ProcessResults(line, resultHigh, highRankingResult, resultLow, bestHandALow, bestHandBLow);
}