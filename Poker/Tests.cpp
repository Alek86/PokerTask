#include "Tests.h"

#include "Logic.h"
#include "Logic.StraightFlush.h"
#include "Parse.h"

#include <string>
#include <iostream>


using namespace Logic;

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

    void TestStraight(const std::string& first, const std::string& second, CompareResult::Value expectedResult)
    {
        auto result = CompareStraight(ParseToHand(first), ParseToHand(second));
        if (result != expectedResult)
        {
            ShowError(__FUNCTION__, first, second, expectedResult, result);
        }
    }

    void Test3OfAKind(const std::string& first, const std::string& second, CompareResult::Value expectedResult)
    {
        auto result = Compare3OfAKind(ParseToHand(first), ParseToHand(second));
        if (result != expectedResult)
        {
            ShowError(__FUNCTION__, first, second, expectedResult, result);
        }
    }

    void TestTwoPairs(const std::string& first, const std::string& second, CompareResult::Value expectedResult)
    {
        auto result = CompareTwoPairs(ParseToHand(first), ParseToHand(second));
        if (result != expectedResult)
        {
            ShowError(__FUNCTION__, first, second, expectedResult, result);
        }
    }

    void TestOnePair(const std::string& first, const std::string& second, CompareResult::Value expectedResult)
    {
        auto result = CompareOnePair(ParseToHand(first), ParseToHand(second));
        if (result != expectedResult)
        {
            ShowError(__FUNCTION__, first, second, expectedResult, result);
        }
    }

    void TestHighCard(const std::string& first, const std::string& second, CompareResult::Value expectedResult)
    {
        auto result = CompareHighCard(ParseToHand(first), ParseToHand(second));
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
    TestStraightFlush("Ah-3h-2h-5h-4h", "Ts-Ks-9s-Js-Qs", CompareResult::SecondWon);
    
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
    TestFlush("As-Ks-Qs-Js-2s", "Ad-Kd-Qd-Jd-2d", CompareResult::BothWon);
    TestFlush("As-Ks-Qs-Js-2s", "Ad-Qd-6d-6d-2d", CompareResult::FirstWon);

    TestStraight("Ac-Th-Kh-Jd-Qh", "Td-Ks-Ac-Js-Qs", CompareResult::BothWon);
    TestStraight("Ac-Td-Kd-Ts-Qd", "Ts-Ks-Jd-As-Qs", CompareResult::SecondWon);
    TestStraight("Ad-Th-Kd-Js-Qd", "Ts-Ks-Ad-Js-Qs", CompareResult::BothWon);
    TestStraight("Ah-3c-2d-5h-4h", "Ts-Ks-Ac-Jc-Qs", CompareResult::SecondWon);

    Test3OfAKind("Ac-Ah-Ad-Kd-Qh", "Td-Ks-Ac-Js-Qs", CompareResult::FirstWon);
    Test3OfAKind("Td-As-Ac-Js-Qs", "Ac-Ah-Ad-Td-2h", CompareResult::SecondWon);
    Test3OfAKind("Ac-Ah-Ad-2d-3h", "Kc-Kh-Kd-Ad-Qh", CompareResult::FirstWon);
    Test3OfAKind("Kc-Kh-Kd-Ad-Qh", "Ac-Ah-Ad-2d-3h", CompareResult::SecondWon);
    Test3OfAKind("Ac-Ah-Ad-Kd-Qh", "Ac-Ah-Ad-Td-Qh", CompareResult::FirstWon);
    Test3OfAKind("Ac-Ah-Ad-Td-Qh", "Ac-Ah-Ad-Kd-Qh", CompareResult::SecondWon);
    Test3OfAKind("Ac-Ah-Ad-Kd-Qh", "Ac-Ah-Ad-Kd-5h", CompareResult::FirstWon);
    Test3OfAKind("Ac-Ah-Ad-Kd-5h", "Ac-Ah-Ad-Kd-Qh", CompareResult::SecondWon);
    Test3OfAKind("Ac-Ah-Ad-Kc-Qc", "Ac-Ah-Ad-Kd-Qh", CompareResult::BothWon);
    Test3OfAKind("Ac-3h-Ad-Kc-Qc", "Ac-7h-Ad-Kd-Qh", CompareResult::BothLose);


    TestTwoPairs("Ac-Ah-Kd-Kc-Qc", "Ac-7h-Ad-Kd-Qh", CompareResult::FirstWon);
    TestTwoPairs("Ac-7h-Ad-Kd-Qh", "Ac-Ah-Kd-Kc-Qc", CompareResult::SecondWon);
    TestTwoPairs("Ac-Ah-Kd-Kc-Qc", "Ac-Qh-Ad-Kd-Qh", CompareResult::FirstWon);
    TestTwoPairs("Ac-Qc-Ad-Kd-Qh", "Ac-Ah-Kd-Kc-Qc", CompareResult::SecondWon);
    TestTwoPairs("Ac-Ah-2d-2c-Qc", "Kc-Kh-Qd-Kc-Qc", CompareResult::FirstWon);
    TestTwoPairs("Kc-Kh-Qd-Kc-Qc", "Ac-Ah-2d-2c-Qc", CompareResult::SecondWon);
    TestTwoPairs("Ac-Ah-2d-2c-Qc", "Ac-Ah-2d-2c-Tc", CompareResult::FirstWon);
    TestTwoPairs("Ac-Ah-2d-2c-Tc", "Ac-Ah-2d-2c-Qc", CompareResult::SecondWon);
    TestTwoPairs("Ac-Ah-2d-2c-Qc", "As-Ad-2s-2h-Qd", CompareResult::BothWon);
    TestTwoPairs("Ac-Ah-5d-2c-Tc", "Ac-Ah-3d-2c-Qc", CompareResult::BothLose);

    TestOnePair("Ac-Ah-2d-Kc-Qc", "Ac-7h-Jd-Kd-Qh", CompareResult::FirstWon);
    TestOnePair("Ac-7h-Jd-Kd-Qh", "Ac-Ah-3d-Kc-Qc", CompareResult::SecondWon);
    TestOnePair("Ac-Ah-2d-Kc-Qc", "5c-5h-2d-Kc-Qc", CompareResult::FirstWon);
    TestOnePair("5c-5h-2d-Kc-Qc", "Ac-Ah-3d-Kc-Qc", CompareResult::SecondWon);
    TestOnePair("Ac-Ah-2d-Kc-Qc", "Ac-Ah-2d-Tc-Qc", CompareResult::FirstWon);
    TestOnePair("Ac-Ah-2d-Tc-Qc", "Ac-Ah-2d-Kc-Qc", CompareResult::SecondWon);
    TestOnePair("Ac-Ah-2d-Kc-Qc", "Ac-Ah-2d-Tc-Kc", CompareResult::FirstWon);
    TestOnePair("Ac-Ah-2d-Tc-Kc", "Ac-Ah-2d-Kc-Qc", CompareResult::SecondWon);
    TestOnePair("Ac-Ah-7d-Kc-Qc", "Ac-Ah-4d-Qc-Kc", CompareResult::FirstWon);
    TestOnePair("Ac-Ah-4d-Qc-Kc", "Ac-Ah-7d-Kc-Qc", CompareResult::SecondWon);
    TestOnePair("Ac-Ah-4d-Kc-Qc", "Ac-Ah-4d-Qc-Kc", CompareResult::BothWon);
    TestOnePair("Jc-Ah-4d-Qc-Kc", "Ac-Th-7d-Kc-Qc", CompareResult::BothLose);

    TestHighCard("Ac-Kh-Qd-Jc-9c", "Ac-Th-7d-Kc-Qc", CompareResult::FirstWon);
    TestHighCard("Ac-Th-7d-Kc-Qc", "Ac-Kh-Qd-Jc-9c", CompareResult::SecondWon);
    TestHighCard("Ac-Kh-9d-8c-7c", "Ac-Kh-9d-7c-5c", CompareResult::FirstWon);
    TestHighCard("Ac-Kh-9d-7c-5c", "Ac-Kh-9d-8c-7c", CompareResult::SecondWon);
    TestHighCard("Ac-Kc-Qd-Jc-9c", "Ah-Kh-Qd-Jh-9c", CompareResult::BothWon);
}