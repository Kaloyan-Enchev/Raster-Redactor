#pragma once
#include "ImageConverter.h"


class CommandCenter
{
private:
    ImageConverter converter;
    std::vector<std::string> commands;

    void printAllCommands() const;

    // Default constructor
    CommandCenter();

public:

    static CommandCenter& getInstance()
    {
        static CommandCenter object;

        return object;
    }

    // Deleted copy constructor
    CommandCenter(const CommandCenter& other) = delete;
    // Deleted copy assignment operator
    CommandCenter& operator=(const CommandCenter& other) = delete;

    // Function that executes command
    void executeCommand(const std::string command);
};
