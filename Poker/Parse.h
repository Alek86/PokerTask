#pragma once

#include "Types.h"

#include <string>

void Parse(const std::string& str, CardSet& handA, CardSet& handB, CardSet& board);
CardSet Parse(const std::string& str);

// Just for testing purposes
Hand ParseToHand(const std::string& str);