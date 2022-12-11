//
//  Day07.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-07.
//

#include "Day07.hpp"

#include "utilities.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace AdventOfCode_2022;

struct Folder;

struct Directory
{
    virtual bool isFolder() = 0;

    std::string name;
    std::shared_ptr<Folder> parent;
};

struct Folder : public Directory
{
    virtual bool isFolder() override { return true; };

    std::unordered_map<std::string, std::shared_ptr<Directory>> directories;
};

struct File : public Directory
{
    virtual bool isFolder() override { return false; };

    size_t size;
};

int getSize(const Folder& folder)
{
    int size = 0;

    for (const auto& [name, dir] : folder.directories)
    {
        if (not dir->isFolder())
        {
            size += std::dynamic_pointer_cast<File>(dir)->size;
        }
        else if (dir->isFolder())
        {
            size += getSize(*std::dynamic_pointer_cast<Folder>(dir));
        }
    }

    return size;
}

void forEachFolder(const Folder& folder, std::function<void(const Folder&)> func)
{
    for (const auto& [name, dir] : folder.directories)
    {
        if (dir->isFolder())
        {
            func(*std::static_pointer_cast<Folder>(dir));
            forEachFolder(*std::static_pointer_cast<Folder>(dir), func);
        }
    }
}

std::shared_ptr<Folder> buildDirectory(std::ifstream& input)
{
    std::string line;

    std::shared_ptr<Folder> currentDirectory;
    bool lsMode = false;

    while (std::getline(input, line))
    {
        auto split = utilities::splitString(line, " ");

        bool isCommand = split.front().front() == '$';
        lsMode &= not isCommand;

        if (lsMode)
        {
            const auto& directoryName = split[1];

            if (split.front().find("dir") != std::string::npos)
            {
                auto newFolder = std::make_shared<Folder>();

                newFolder->name = directoryName;
                newFolder->parent = currentDirectory;

                currentDirectory->directories[directoryName] = newFolder;
            }
            else
            {
                auto newFile = std::make_shared<File>();

                newFile->name = directoryName;
                newFile->parent = currentDirectory;
                newFile->size = std::stoi(split.front());

                currentDirectory->directories[directoryName] = newFile;
            }
        }
        else if (isCommand)
        {
            const auto& cmd = split[1];

            if (cmd.find("cd") != std::string::npos)
            {
                const auto& directoryName = split[2];
                if (!currentDirectory)
                {
                    currentDirectory = std::make_shared<Folder>();
                    currentDirectory->name = directoryName;
                }
                else
                {
                    if (directoryName.find("..") != std::string::npos)
                    {
                        currentDirectory = currentDirectory->parent;
                    }
                    else
                    {
                        currentDirectory = std::static_pointer_cast<Folder>(currentDirectory->directories.at(directoryName));
                    }
                }
            }
            else if (cmd.find("ls") != std::string::npos)
            {
                lsMode = true;
            }
        }
    }

    while (currentDirectory->parent)
    {
        currentDirectory = currentDirectory->parent;
    }

    return currentDirectory;
}

std::string Day07::challenge01(std::ifstream& input)
{
    auto root = buildDirectory(input);

    int totalSize = 0;

    forEachFolder(*root, [&totalSize](const Folder& folder) {
        int size = getSize(folder);
        if (size <= 100000)
        {
            totalSize += size;
        }
    });

    return std::to_string(totalSize);
}

std::string Day07::challenge02(std::ifstream& input)
{
    auto root = buildDirectory(input);

    int TOTAL_SPACE = 70000000;
    int REQUIRED_SPACE = 30000000;

    int usedSpace = getSize(*root);
    int spaceLeft = TOTAL_SPACE - usedSpace;
    int spaceToDelete = REQUIRED_SPACE - spaceLeft;

    std::vector<int> candidates;
    int minimum = usedSpace;

    forEachFolder(*root, [&minimum, spaceToDelete](const Folder& folder) {
        int size = getSize(folder);
        if (size >= spaceToDelete && size < minimum)
        {
            minimum = size;
        }
    });

    return std::to_string(minimum);
}
