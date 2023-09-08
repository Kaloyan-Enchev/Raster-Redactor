#include <iostream>
#include "CommandCenter.h"

int main()
{
	std::string command;
	do
	{
		std::cout << "Enter a command: ";
		std::getline(std::cin, command);

		try
		{
			CommandCenter::getInstance().executeCommand(command);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}

		std::cin.ignore();
	}
	while (command != "exit");

	return 0;
	
}

