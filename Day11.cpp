//
//  Day11.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-11.
//

#include "Day11.hpp"

#include "utilities.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <functional>
#include <iostream>

using namespace AdventOfCode_2022;

using size_type = long long;

struct Monkey
{
    void throwItem(Monkey& receiver)
    {
        receiver.items.emplace(items.front());
        items.pop();
    }
    int testWorry(size_type worry)
    {
        return (worry % divTest == 0) ? onTrue : onFalse;
    }

    std::queue<size_type> items;

    std::function<size_type(size_type)> onInspect;
    size_type divTest;
    int onTrue;
    int onFalse;

    size_type totalInspections = 0;
};

Monkey createMonkey(std::ifstream& stream)
{
    Monkey monkey;
    std::string line;

    std::getline(stream, line);
    line = line.substr(18);
    auto startingItems = utilities::splitString(line, ", ");
    for (auto item : startingItems)
    {
        monkey.items.emplace(std::stoi(item));
    }

    std::getline(stream, line);
    auto split = utilities::splitString(line, " ");
    auto v = split.back();
    char op = split[split.size() - 2].front();
    size_type value = 0;
    if (std::isdigit(v.back())) {
        value = std::stoi(split.back());
    }
    else
    {
        op = '^';
    }
    monkey.onInspect = [&monkey, value, op](size_type old) {
        size_type newValue = old;
        if (op == '+')
        {
            newValue += value;
        }
        else if (op == '*')
        {
            newValue *= value;
        }
        else if (op == '^')
        {
            newValue *= old;
        }

        return newValue;
    };

    std::getline(stream, line);
    auto back = utilities::splitString(line, " ").back();
    std::getline(stream, line);
    int onTrue = std::stoi(utilities::splitString(line, " ").back());
    std::getline(stream, line);
    int onFalse = std::stoi(utilities::splitString(line, " ").back());
    monkey.divTest = std::stoi(back);
    monkey.onTrue = onTrue;
    monkey.onFalse = onFalse;

    return monkey;
}

void performRounds(const int ROUNDS, std::vector<Monkey>& monkeys, std::function<void(size_type&)> reduceWorry)
{
    for (int i = 0; i < ROUNDS; ++i)
    {
        for (auto& monkey : monkeys)
        {
            while (not monkey.items.empty())
            {
                auto& worry = monkey.items.front();
                worry = monkey.onInspect(worry);

                reduceWorry(worry);

                monkey.totalInspections++;
                int target = monkey.testWorry(worry);
                monkey.throwItem(monkeys[target]);
            }
        }
    }
}

std::string Day11::challenge01(std::ifstream& input)
{
    std::string line;

    std::vector<Monkey> monkeys;

    while (std::getline(input, line))
    {
        if (line.find("Monkey") != std::string::npos)
        {
            monkeys.push_back(createMonkey(input));
        }
    }

    performRounds(20, monkeys, [](size_type& worry) {
        worry /= 3;
    });

    std::sort(monkeys.begin(), monkeys.end(), [](const auto& a, const auto& b) { return a.totalInspections > b.totalInspections; });

    auto monkeyBusiness = monkeys[0].totalInspections * monkeys[1].totalInspections;

    return std::to_string(monkeyBusiness);
}

std::string Day11::challenge02(std::ifstream& input)
{
    std::string line;

    std::vector<Monkey> monkeys;

    while (std::getline(input, line))
    {
        if (line.find("Monkey") != std::string::npos)
        {
            monkeys.push_back(createMonkey(input));
        }
    }

    size_type minimized = 1;
    for (const auto& m : monkeys)
    {
        minimized *= m.divTest;
    }

    performRounds(10000, monkeys, [&monkeys, minimized](size_type& worry) {
        worry %= minimized;
    });

    std::sort(monkeys.begin(), monkeys.end(), [](const auto& a, const auto& b) { return a.totalInspections > b.totalInspections; });

    auto monkeyBusiness = monkeys[0].totalInspections * monkeys[1].totalInspections;

    return std::to_string(monkeyBusiness);
}
