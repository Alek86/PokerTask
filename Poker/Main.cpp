#include <iostream>

#include "HighHand.h"
#include "Types.h"

int main(int argc, char *argv[])
{
	Cards hand1;
	Cards hand2;
	Cards board;

	auto bestSet = GetBestSet(hand1, board, [](const Cards& l, const Cards r) { return true; });

	//auto winner = PickWinnerInLowHand(hand1, hand2, board);
	//std::cout << winner << std::endl;

	system("pause");
}