//
//  Day06.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-06.
//

#include "Day06.hpp"

#include "utilities.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>

using namespace AdventOfCode_2022;

void shiftLeft(std::string& s, char back)
{
    s.push_back(back);
    s = s.substr(1);
}

int signalProcessing(std::ifstream& input, const int KEY_LENGTH)
{
    int markerPosition = 0;

    std::string content = utilities::dumpContents(input);

    std::string buffer(KEY_LENGTH, '0');
    int bufferIndex = 0;


    for (const auto& c : content)
    {
        if (bufferIndex >= KEY_LENGTH)
        {
            std::unordered_set<char> set;
            for (const auto& cb : buffer)
            {
                set.insert(cb);
            }
            if (set.size() == KEY_LENGTH)
            {
                markerPosition = bufferIndex;
                break;
            }
        }

        shiftLeft(buffer, c);
        ++bufferIndex;
    }

    return bufferIndex;
}

std::string Day06::challenge01(std::ifstream& input)
{
    return std::to_string(signalProcessing(input, 4));
}

std::string Day06::challenge02(std::ifstream& input)
{
    return std::to_string(signalProcessing(input, 14));
}

