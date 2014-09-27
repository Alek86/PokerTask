#include <iostream>

#include "Logic.h"
#include "Types.h"
#include "Parse.h"
#include "Tests.h"

int main(int argc, char *argv[])
{
    try
    {
//         CardSet hand1 = Parse("As-Kd-Js-9d");
//         CardSet board = Parse("Jd-Td-5c-2c-Qd");
//         auto bestSet = GetBestSet(hand1, board, CompareHighHand);

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