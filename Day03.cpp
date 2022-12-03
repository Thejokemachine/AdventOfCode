//
//  Day03.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-03.
//

#include "Day03.hpp"

#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>

using namespace AdventOfCode_2022;


int getPriority(char item)
{
    bool isLowerCase = item > 'Z';
    char offset = isLowerCase ? 'a' : 'A';

    if (not isLowerCase)
    {
        item += 26;
    }

    return item - offset + 1;
}

std::string Day03::challenge01(std::ifstream& input)
{
    std::string line;

    int totalPriority = 0;

    while (std::getline(input, line))
    {
        auto comp1 = line.substr(0, line.size() / 2);
        auto comp2 = line.substr(comp1.length(), line.size() / 2);

        for (auto c : comp1)
        {
            if (comp2.find(c) != std::string::npos)
            {
                totalPriority += getPriority(c);
                break;
            }
        }
    }

    return std::to_string(totalPriority);
}

std::string Day03::challenge02(std::ifstream& input)
{
    std::string line;
    int index = 0;

    int totalPriority = 0;

    std::string currentGroup[3];

    while (std::getline(input, line))
    {
        currentGroup[index] = line;

        ++index;

        if ((index % 3) == 0)
        {
            index = 0;

            for (auto c : currentGroup[0])
            {
                if (currentGroup[1].find(c) != std::string::npos &&
                    currentGroup[2].find(c) != std::string::npos)
                {
                    totalPriority += getPriority(c);
                    break;
                }
            }
        }
    }

    return std::to_string(totalPriority);
}
