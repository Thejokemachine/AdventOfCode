//
//  Day05.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-05.
//

#include "Day05.hpp"

#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <sstream>
#include <iostream>

#include "utilities.hpp"

using namespace AdventOfCode_2022;

struct Command
{
  int amount;
  int from;
  int to;
  
  Command(const std::string& input)
  {
    auto split = utilities::splitString(input, ' ');
    amount = std::stoi(1[split.data()]);
    from = std::stoi(3[split.data()]);
    to = std::stoi(5[split.data()]);
  }
};

class CrateStacks
{
private:

  std::unordered_map<int, std::deque<char>> stacks;
  
public:
  
  void moveCratesSeperately(int from, int to, int amount)
  {
    for (int i = 0; i < amount; ++i)
    {
      stacks[to].emplace_back(stacks[from].back());
      stacks[from].pop_back();
    }
  }
  
  void moveCrates(int from, int to, int amount)
  {
    char crates[amount];
    
    auto& stackFrom = stacks[from];
    auto& stackTo = stacks[to];
    
    for (int i = 0; i < amount; ++i)
    {
      crates[i] = stackFrom.back();
      stackFrom.pop_back();
    }
    
    for (int i = amount-1; i >= 0; --i)
    {
      stackTo.push_back(crates[i]);
    }
  }
  
  void addCrate(int stackID, char crate)
  {
    stacks[stackID].push_front(crate);
  }
  
  std::string getTopCrates() const
  {
    std::stringstream ss;
    
    for (int i = 1; i <= stacks.size(); ++i)
    {
      ss << stacks.at(i).back();
    }
    
    return ss.str();
  }
};

bool initializeStacks(CrateStacks& stacks, const std::string& line)
{
  for (int i = 0; i < (line.length()+1) / 4; ++i)
  {
    int index = 1 + i * 4;
    char c = index[line.data()];
    
    if (std::isdigit(c))
    {
      return true;
      break;
    }
    
    if (std::isgraph(c))
    {
      stacks.addCrate(i+1, c);
    }
  }
  
  return false;
}

void createCrateStacksAndCommands(std::ifstream& input, std::queue<Command>& commands, CrateStacks& stacks)
{
  bool stacksInitialized = false;
  
  std::string line;
  
  while (std::getline(input, line))
  {
    if (not stacksInitialized)
    {
      stacksInitialized = initializeStacks(stacks, line);
    }
    else
    {
      if (not line.empty())
      {
        commands.emplace(line);
      }
    }
  }
}

void forEachCommand(std::queue<Command>& commands, std::function<void(const Command&)> func)
{
  while (not commands.empty())
  {
    const auto& cmd = commands.front();
    
    func(cmd);
    
    commands.pop();
  }
}

std::string Day05::challenge01(std::ifstream& input)
{
  std::queue<Command> commands;
  
  CrateStacks stacks;
  
  createCrateStacksAndCommands(input, commands, stacks);
  
  forEachCommand(commands, [&](const Command& cmd){
    stacks.moveCratesSeperately(cmd.from, cmd.to, cmd.amount);
  });
  
  return stacks.getTopCrates();
}

std::string Day05::challenge02(std::ifstream& input)
{
  std::queue<Command> commands;
  
  CrateStacks stacks;
  
  createCrateStacksAndCommands(input, commands, stacks);
  
  forEachCommand(commands, [&](const Command& cmd){
    stacks.moveCratesSeperately(cmd.from, cmd.to, cmd.amount);
  });
  
  return stacks.getTopCrates();
}
