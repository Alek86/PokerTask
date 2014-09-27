#include <iostream>

#include "Logic.h"
#include "Types.h"
#include "Parse.h"
#include "Tests.h"

int main(int argc, char *argv[])
{
    try
    {
        CardSet handA = Parse("Qc-Jd-Td-3d");
        CardSet handB = Parse("3s-3h-8h-6d");
        CardSet board = Parse("Ad-Kh-Qs-Qd-3c");

        using namespace std::placeholders;
        auto resA = HighRanking::HighCard;
        auto resB = HighRanking::HighCard;
        auto resMain = HighRanking::HighCard;
        auto bestHandA = GetBestHand(handA, board, std::bind(CompareHighHand, _1, _2, std::ref(resA)));
        auto bestHandB = GetBestHand(handB, board, std::bind(CompareHighHand, _1, _2, std::ref(resB)));
        auto comparisonResult = CompareHighHand(bestHandA, bestHandB, resMain);

        RunTests();

        std::cout << std::endl;
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        system("pause");
        return 1;
    }




	//auto winner = PickWinnerInLowHand(hand1, hand2, board);
	//std::cout << winner << std::endl;

    std::cout << std::endl;
	system("pause");
}