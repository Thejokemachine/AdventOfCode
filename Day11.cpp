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

struct Monkey
{
    void throwint(Monkey& receiver)
    {
        receiver.ints.emplace(ints.front());
        ints.pop();
    }
    int testWorry(int worry)
    {
        return (worry % divTest == 0) ? onTrue : onFalse;
    }

    std::queue<int> ints;

    std::function<int(int)> onInspect;
    int divTest;
    int onTrue;
    int onFalse;

    int totalInspections = 0;
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
        monkey.ints.emplace(std::stoi(item));
    }

    std::getline(stream, line);
    auto split = utilities::splitString(line, " ");
    auto v = split.back();
    char op = split[split.size() - 2].front();
    int value = 0;
    if (std::isdigit(v.back())) {
        value = std::stoi(split.back());
    }
    else
    {
        op = '^';
    }
    monkey.onInspect = [&monkey, value, op](int old) {
        int newValue = old;
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

void performRounds(const int ROUNDS, std::vector<Monkey>& monkeys, std::function<void(int&)> reduceWorry)
{
    for (int i = 0; i < ROUNDS; ++i)
    {
        for (auto& monkey : monkeys)
        {
            while (not monkey.ints.empty())
            {
                auto& worry = monkey.ints.front();
                worry = monkey.onInspect(worry);

                reduceWorry(worry);

                monkey.totalInspections++;
                int target = monkey.testWorry(worry);
                monkey.throwint(monkeys[target]);
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

    performRounds(20, monkeys, [](int& worry) {
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

    int minimized = 1;
    for (const auto& m : monkeys)
    {
        minimized *= m.divTest;
    }

    performRounds(10000, monkeys, [&monkeys, minimized](int& worry) {
        worry %= minimized;
    });

    std::sort(monkeys.begin(), monkeys.end(), [](const auto& a, const auto& b) { return a.totalInspections > b.totalInspections; });

    auto monkeyBusiness = monkeys[0].totalInspections * monkeys[1].totalInspections;

    return std::to_string(monkeyBusiness);
}
