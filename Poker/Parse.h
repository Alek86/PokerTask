#pragma once

#include "Types.h"

#include <string>

CardSet Parse(const std::string& str);

// Just for testing purposes
Hand ParseToHand(const std::string& str);