#pragma once

#include "Types.h"
#include "Logic.OptionalRank.h"

namespace Logic
{
    struct CheckResult
    {
        bool isApplicable;
        OptionalRank rankMain1;
        OptionalRank rankMain2;
        OptionalRank rankKicker1;
        OptionalRank rankKicker2;
        OptionalRank rankKicker3;
    };

    CompareResult::Value Compare(const CheckResult& first, const CheckResult& second);
}