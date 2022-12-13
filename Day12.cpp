//
//  Day12.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-12.
//

#include "Day12.hpp"

#include "utilities.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <iostream>

using namespace AdventOfCode_2022;

using Vec2 = std::pair<int, int>;
using Path = std::queue<Vec2>;

class HeightMap
{
public:

    HeightMap(std::ifstream& input)
    {
        utilities::forEachLine(input, [this](const auto& line) {
            auto& row = grid.emplace_back();
            for (auto c : line)
            {
                if (c == 'S')
                {
                    c = 'a';
                    start = {row.size(), grid.size() - 1};
                }
                else if (c == 'E')
                {
                    c = 'z';
                    goal = { row.size(), grid.size() - 1 };
                }

                row.push_back(c);
            }
        });
    }

    size_t getWidth() const
    {
        return grid.front().size();
    }

    size_t getHeight() const
    {
        return grid.size();
    }

    char getValue(const Vec2& p) const
    {
        return grid[p.second][p.first];
    }

    bool canTraverseBetween(const Vec2& p0, const Vec2& p1) const
    {
        if (p1.first < 0 || p1.first >= grid.front().size())
            return false;
        else if (p1.second < 0 || p1.second >= grid.size())
            return false;

        return (getValue(p0) + 1) >= getValue(p1);
    }

    void forEachTile(std::function<void(char c, const Vec2& p)> func)
    {
        for (auto y = 0; y < grid.size(); ++y)
        {
            for (auto x = 0; x < grid[y].size(); ++x)
            {
                auto p = Vec2(x, y);
                func(getValue(p), p);
            }
        }
    }

    Vec2 start;
    Vec2 goal;

private:
    std::vector<std::vector<char>> grid;
};

bool contains(const Path& path, const Vec2& position)
{
    for (const auto& p : path._Get_container())
    {
        if (p == position)
            return true;
    }
    return false;
}

void printPath(const HeightMap& map, const Path& path)
{
    std::cout << std::endl;

    for (auto y = 0; y < map.getHeight(); ++y)
    {
        std::cout << std::endl;

        for (auto x = 0; x < map.getWidth(); ++x)
        {
            char c = '.';

            if (contains(path, { x,y }))
            {
                c = 'x';
            }

            std::cout << c;
        }
    }
}

Path pathfind(const HeightMap& map, const Vec2& start, const Vec2& goal)
{
    Path path;

    struct Node
    {
        Node* parent = nullptr;
        Vec2 position;
        bool visited = false;
    };

    std::vector<Node> nodes(map.getWidth() * map.getHeight());
    auto& origin = nodes[start.first + start.second * map.getWidth()];
    origin.position = start;
    origin.visited = true;

    std::queue<Node*> queue;
    queue.emplace(&origin);

    Node* result = nullptr;

    while (not queue.empty())
    {
        auto current = queue.front();
        queue.pop();

        if (current->position == goal)
        {
            result = current;
            break;
        }

        auto checkNext = [&map, &nodes, &current, &queue](const Vec2& dir) {
            auto nextPosition = Vec2{ current->position.first + dir.first, current->position.second + dir.second };
            if (map.canTraverseBetween(current->position, nextPosition))
            {
                auto node = &nodes[nextPosition.first + nextPosition.second * map.getWidth()];
                if (not node->visited)
                {
                    node->visited = true;
                    node->parent = current;
                    node->position = nextPosition;
                    queue.emplace(node);
                }
            }
        };

        checkNext({ -1,  0 });
        checkNext({  1,  0 });
        checkNext({  0, -1 });
        checkNext({  0,  1 });
    }

    if (result)
    {
        while (result->parent)
        {
            path.emplace(result->position);
            result = result->parent;
        }
    }

    return path;
}

std::string Day12::challenge01(std::ifstream& input)
{
    HeightMap map(input);

    auto path = pathfind(map, map.start, map.goal);

    printPath(map, path);

    return std::to_string(path.size());
}

std::string Day12::challenge02(std::ifstream& input)
{
    HeightMap map(input);

    std::vector<Path> paths;

    map.forEachTile([&](char c, const Vec2& p) {
        if (c == 'a')
        {
            paths.emplace_back(pathfind(map, p, map.goal));
        }
    });

    std::erase_if(paths, [](const auto& v) { return v.empty(); });
    std::sort(paths.begin(), paths.end(), [](const auto& a, const auto& b) { return a.size() < b.size(); });
    auto& path = paths.front();

    printPath(map, path);

    return std::to_string(path.size());
}