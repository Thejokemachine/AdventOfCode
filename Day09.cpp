//
//  Day09.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-09.
//

#include "Day09.hpp"

#include "utilities.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <vector>
#include <functional>
#include <unordered_set>
#include <array>
#include <iostream>

using namespace AdventOfCode_2022;

using Vec2 = std::pair<int, int>;

Vec2 getDirection(char c)
{
    Vec2 direction;

    switch (c)
    {
    case 'R': direction.first = 1;
        break;
    case 'L': direction.first = -1;
        break;
    case 'U': direction.second = 1;
        break;
    case 'D': direction.second = -1;
        break;
    default:
        break;
    }

    return direction;
}

size_t getHash(const Vec2& v)
{
    return std::hash<std::string>{}(std::to_string(v.first) + ":" + std::to_string(v.second));
}

int getDistance(const Vec2& start, const Vec2& end)
{
    return std::max(std::abs(end.first - start.first), std::abs(end.second - start.second));
}

int sign(int v)
{
    return v == 0 ? 0 : (v > 0 ? 1 : -1);
}

void moveRope(std::vector<Vec2>& rope, const Vec2& direction)
{
    auto& head = rope.front();
    head.first += direction.first;
    head.second += direction.second;

    for (int j = 1; j < rope.size(); ++j)
    {
        auto& current = rope[j];
        auto& next = rope[j - 1];

        if (getDistance(next, current) > 1)
        {
            current.first += sign(next.first - current.first);
            current.second += sign(next.second - current.second);
        }
    }
}

std::string Day09::challenge01(std::ifstream& input)
{
    std::vector<Vec2> rope(2);

    std::unordered_set<size_t> visited;

    visited.insert(getHash(rope.back()));

    std::string line;
    while (std::getline(input, line))
    {
        auto direction = getDirection(line.front());
        auto distance = std::stoi(line.substr(2));

        for (int i = 0; i < distance; ++i)
        {
            moveRope(rope, direction);
            visited.insert(getHash(rope.back()));
        }
    }

    return std::to_string(visited.size());
}

std::string Day09::challenge02(std::ifstream& input)
{
    std::vector<Vec2> rope(10);

    std::unordered_set<size_t> visited;

    visited.insert(getHash(rope.back()));

    std::string line;
    while (std::getline(input, line))
    {
        auto direction = getDirection(line.front());
        auto distance = std::stoi(line.substr(2));

        for (int i = 0; i < distance; ++i)
        {
            moveRope(rope, direction);
            visited.insert(getHash(rope.back()));
        }
    }

    return std::to_string(visited.size());
}
