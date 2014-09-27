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

//         CardSet handA = Parse("Ac-Kd-Jd-3d");
//         CardSet handB = Parse("5c-5d-6c-7d");
//         CardSet board = Parse("Ah-Kh-5s-2s-Qd");
        
         auto bestHandA = GetBestHand(handA, board, CompareHighHand);
         auto bestHandB = GetBestHand(handB, board, CompareHighHand);
         CompareResult::Value comparisonResult = CompareHighHand(bestHandA, bestHandB);

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