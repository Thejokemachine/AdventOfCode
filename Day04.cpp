//
//  Day04.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-03.
//

#include "Day04.hpp"

#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>

#include "utilities.hpp"

using namespace AdventOfCode_2022;

std::pair<int, int> getRange(const std::string& string)
{
    auto values = utilities::splitString(string, "-");
    return { std::stoi(values[0]), std::stoi(values[1]) };
}

bool rangeContainsValue(const std::pair<int, int>& range, int value)
{
    return value >= range.first && value <= range.second;
}

bool rangeContainsRange(const std::pair<int, int>& first, const std::pair<int, int>& second)
{
    return rangeContainsValue(first, second.first) && rangeContainsValue(first, second.second);
}

bool rangeOverlapsRange(const std::pair<int, int>& first, const std::pair<int, int>& second)
{
    return rangeContainsValue(first, second.first) || rangeContainsValue(first, second.second);
}

std::string Day04::challenge01(std::ifstream& input)
{
    std::string line;

    int repeatingRanges = 0;

    while (std::getline(input, line))
    {
        auto pair = utilities::splitString(line, ",");
        auto first = pair[0];
        auto second = pair[1];

        auto firstRange = getRange(first);
        auto secondRange = getRange(second);

        if (rangeContainsRange(firstRange, secondRange) || rangeContainsRange(secondRange, firstRange))
        {
            ++repeatingRanges;
        }
    }

    return std::to_string(repeatingRanges);
}

std::string Day04::challenge02(std::ifstream& input)
{
    std::string line;

    int overlappingRanges = 0;

    while (std::getline(input, line))
    {
        auto pair = utilities::splitString(line, ",");
        auto first = pair[0];
        auto second = pair[1];

        auto firstRange = getRange(first);
        auto secondRange = getRange(second);

        if (rangeOverlapsRange(firstRange, secondRange) || rangeOverlapsRange(secondRange, firstRange))
        {
            ++overlappingRanges;
        }
    }

    return std::to_string(overlappingRanges);
}
