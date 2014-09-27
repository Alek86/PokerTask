#include "Tests.h"

#include "Logic.h"
#include "Parse.h"

#include <string>
#include <iostream>

namespace
{
    void ShowError(
        const std::string& functionName,
        const std::string& first,
        const std::string& second,
        CompareResult::Value expectedResult,
        CompareResult::Value result)
    {
        std::cout << functionName.c_str() << ": ";
        std::cout << "Compare '" << first.c_str() << "' with '" << second.c_str() << "' failed. ";
        std::cout << "Expected " << expectedResult << " but got " << result;
        std::cout << std::endl;
    }

    void TestStraightFlush(const std::string& first, const std::string& second, CompareResult::Value expectedResult)
    {
        auto result = CompareStraightFlush(ParseToHand(first), ParseToHand(second));
        if (result != expectedResult)
        {
            ShowError(__FUNCTION__, first, second, expectedResult, result);
        }
    }

    void Test4OfAKind(const std::string& first, const std::string& second, CompareResult::Value expectedResult)
    {
        auto result = Compare4OfAKind(ParseToHand(first), ParseToHand(second));
        if (result != expectedResult)
        {
            ShowError(__FUNCTION__, first, second, expectedResult, result);
        }
    }

    void TestFullHouse(const std::string& first, const std::string& second, CompareResult::Value expectedResult)
    {
        auto result = CompareFullHouse(ParseToHand(first), ParseToHand(second));
        if (result != expectedResult)
        {
            ShowError(__FUNCTION__, first, second, expectedResult, result);
        }
    }

    void TestFlush(const std::string& first, const std::string& second, CompareResult::Value expectedResult)
    {
        auto result = CompareFlush(ParseToHand(first), ParseToHand(second));
        if (result != expectedResult)
        {
            ShowError(__FUNCTION__, first, second, expectedResult, result);
        }
    }
}

void RunTests()
{
    TestStraightFlush("Ah-Th-Kh-Jh-Qh", "Ts-Ks-Ac-Js-Qs", CompareResult::FirstWon);
    TestStraightFlush("Ad-Td-Kd-Ts-Qd", "Ts-Ks-Js-As-Qs", CompareResult::SecondWon);
    TestStraightFlush("Ad-Td-Kd-Js-Qd", "Ts-Ks-Ac-Js-Qs", CompareResult::BothLose);
    TestStraightFlush("Ad-Td-Kd-Jd-Qd", "Ts-Ks-As-Js-Qs", CompareResult::BothWon);
    TestStraightFlush("Ah-3h-2h-5h-4h", "Ts-Ks-Ac-Js-Qs", CompareResult::FirstWon);


    Test4OfAKind("2s-2h-2c-2d-4h", "Ts-Ks-Ac-Js-Qs", CompareResult::FirstWon);
    Test4OfAKind("Ah-3h-2h-5h-4h", "2s-2h-2c-2d-Ah", CompareResult::SecondWon);
    Test4OfAKind("3s-3h-Jc-3c-3d", "2s-2h-2d-4h-2c", CompareResult::FirstWon);
    Test4OfAKind("2s-2h-2d-4h-2c", "Jc-3s-3h-3c-3d", CompareResult::SecondWon);
    Test4OfAKind("2s-2h-2c-2d-Ah", "2s-2h-Jh-2c-2d", CompareResult::FirstWon);
    Test4OfAKind("2s-2h-9s-2c-2d", "2s-2h-Th-2c-2d", CompareResult::SecondWon);
    Test4OfAKind("2s-2h-9s-2c-2d", "2s-2h-2c-9c-2d", CompareResult::BothWon);
    Test4OfAKind("2s-3h-9s-2c-2d", "2s-Ah-2c-9c-2d", CompareResult::BothLose);

    TestFullHouse("2s-3h-3s-2c-3d", "2s-Ah-2c-9c-2d", CompareResult::FirstWon);
    TestFullHouse("2s-Ah-2c-9c-2d", "2s-4h-4s-2c-4d", CompareResult::SecondWon);
    TestFullHouse("5s-5h-Jc-Jc-Jd", "2s-4h-4s-2c-4d", CompareResult::FirstWon);
    TestFullHouse("2s-Ah-As-2c-2d", "5s-5h-Jc-Jc-Jd", CompareResult::SecondWon);
    TestFullHouse("2s-Jh-Js-2c-Jd", "5s-5h-Jc-Jc-Jd", CompareResult::SecondWon);
    TestFullHouse("5s-Jh-Js-5c-Jd", "5s-5h-Jc-Jc-Jd", CompareResult::BothWon);

    TestFlush("5s-Ts-Ks-5s-As", "5s-5h-Jc-Jc-Kd", CompareResult::FirstWon);
    TestFlush("5s-5h-Jc-Jc-Ad", "5s-4s-Ks-2s-As", CompareResult::SecondWon);
    TestFlush("5s-5h-Jc-Jc-Ad", "5s-4s-Kc-2s-As", CompareResult::BothLose);
    TestFlush("5s-2s-Js-Ks-Ts", "5d-4d-Jd-2d-Qd", CompareResult::FirstWon);
    TestFlush("5s-2s-Js-9s-Ts", "5d-4d-7d-2d-Qd", CompareResult::SecondWon);
    TestFlush("5s-2s-Js-Ks-Ts", "5d-4d-Kd-2d-Qd", CompareResult::BothWon);


}