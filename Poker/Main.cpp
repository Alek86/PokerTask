#include <iostream>

#include "Logic.h"
#include "Types.h"
#include "Parse.h"
#include "Tests.h"

int main(int argc, char *argv[])
{
    try
    {
        CardSet handA;
        CardSet handB;
        CardSet board;
        
        Parse("HandA:Qc-Jd-Td-3d HandB:Tc-Jc-8h-6d Board:Ad-Kh-Qs-2d-3c", handA, handB, board);

        using namespace std::placeholders;
        auto resA = HighRanking::HighCard;
        auto resB = HighRanking::HighCard;
        auto resMain = HighRanking::HighCard;
        auto bestHandAHigh = GetBestHand(handA, board, std::bind(CompareHighHand, _1, _2, std::ref(resA)));
        auto bestHandBHigh = GetBestHand(handB, board, std::bind(CompareHighHand, _1, _2, std::ref(resB)));
        auto bestHandALow = GetBestHand(handA, board, CompareLowHand);
        auto bestHandBLow = GetBestHand(handB, board, CompareLowHand);

        auto compResultHigh = CompareHighHand(bestHandAHigh, bestHandBHigh, resMain);
        auto compResultLow = CompareLowHand(bestHandALow, bestHandBLow);

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