#include <iostream>

#include "Logic.h"
#include "Types.h"

int main(int argc, char *argv[])
{
	Cards hand1;
	Cards hand2;
	Cards board;

	auto bestSet = GetBestSet(hand1, board, CompareHighHand);

	//auto winner = PickWinnerInLowHand(hand1, hand2, board);
	//std::cout << winner << std::endl;

	system("pause");
}