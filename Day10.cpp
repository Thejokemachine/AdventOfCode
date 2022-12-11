//
//  Day10.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-10.
//

#include "Day10.hpp"

#include "utilities.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <map>

using namespace AdventOfCode_2022;

struct Instruction
{
    int cycles;
    int increment;
    bool finished = false;
};

using InstructionQueue = std::queue<Instruction>;

InstructionQueue buildQueue(std::ifstream& stream)
{
    InstructionQueue queue;
    std::string line;
    while (std::getline(stream, line))
    {
        auto split = utilities::splitString(line, " ");

        if (split.front() == "noop")
        {
            queue.emplace(1, 0);
        }
        else if (split.front() == "addx")
        {
            queue.emplace(2, std::stoi(split.back()));
        }
    }

    return queue;
}

void runInstructions(std::ifstream& input, std::function<void(int cycle, int x)> onCycle)
{
    auto instructions = buildQueue(input);

    int cycleIndex = 0;
    int X = 1;

    Instruction* currentInstruction = &instructions.front();

    while (currentInstruction)
    {
        ++cycleIndex;

        if (currentInstruction->finished)
        {
            if (not instructions.empty())
            {
                currentInstruction = &instructions.front();
            }
            else
            {
                currentInstruction = nullptr;
                break;
            }
        }

        if (currentInstruction->cycles > 0)
        {
            --currentInstruction->cycles;
        }

        onCycle(cycleIndex, X);

        if (currentInstruction->cycles == 0)
        {
            X += currentInstruction->increment;
            currentInstruction->finished = true;
            instructions.pop();
        }
    }
}

std::string Day10::challenge01(std::ifstream& input)
{
    std::map<int, int> cycleRegister = {
        {20, 0},
        {60, 0},
        {100, 0},
        {140, 0},
        {180, 0},
        {220, 0},
    };

    runInstructions(input, [&](int cycle, int x) {
        if (cycleRegister.contains(cycle))
        {
            cycleRegister[cycle] = x;
        }
    });

    int total = 0;
    for (auto& [cycle, value] : cycleRegister)
    {
        total += cycle * value;
    }

    return std::to_string(total);
}

std::string Day10::challenge02(std::ifstream& input)
{
    const int SCREEN_WIDTH = 40;

    runInstructions(input, [](int cycle, int x) {
        int pixel = (cycle - 1) % SCREEN_WIDTH;
        if (pixel == 0)
        {
            std::cout << std::endl;
        }

        if (std::abs(pixel - x) <= 1)
        {
            std::cout << '#';
        }
        else
        {
            std::cout << '.';
    }});

    std::cout << std::endl << std::endl;

    return std::to_string(0);
}
