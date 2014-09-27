#include "Logic.h"
#include "Types.h"
#include "Parse.h"
#include "Tests.h"

#include <iostream>
#include <fstream>
#include <ios>
#include <sstream>

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

std::string ProcesResults(
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
    
    return ProcesResults(line, resultHigh, highRankingResult, resultLow, bestHandALow, bestHandBLow);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cout << "Running tests... To process file pass 2 parameters" << std::endl;
        RunTests();
        std::cout << "Done" << std::endl;
        return 0;
    }

    if (argc != 3)
    {
        std::cerr << "Wrong number of parameters" << std::endl;
        return 1;
    }

    try
    {
        std::ifstream input(argv[1], std::ios_base::in);
        std::ofstream output(argv[2], std::ios_base::out);
        
        if (!input.is_open())
        {
            std::cerr << "Cannot open input file " << argv[1] << std::endl;
            return 2;
        }

        if (!output.is_open())
        {
            std::cerr << "Cannot open output file " << argv[2] << std::endl;
            return 3;
        }

        std::string line;
        while (!input.eof())
        {
            std::getline(input, line);

            if (line.empty() || line[0] == '\r' || line[0] == '\n')
            {
                break;
            }

            auto resLine = ProcessInputLine(line);
            output << resLine.c_str() << std::endl;
        }
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        return 100;
    }
}