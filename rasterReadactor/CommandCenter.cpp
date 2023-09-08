#include "CommandCenter.h"

void CommandCenter::printAllCommands() const
{
	std::cout << "The following commands are supported: " << std::endl;
	std::cout << "load <paths> (opens <path>)" << std::endl;
	std::cout << "grayscale (makes images grayscale)" << std::endl;
	std::cout << "monochrome (makes images monochrome)" << std::endl;
	std::cout << "negative (makes images negative)" << std::endl;
	std::cout << "rotate left (rotates images to left)" << std::endl;
	std::cout << "rotate right (rotates images to right)" << std::endl;
	std::cout << "flip top (flips images top)" << std::endl;
	std::cout << "flip left (flips images left)" << std::endl;
	std::cout << "undo (remove last command)" << std::endl;
	std::cout << "redo (neutralizes undo)" << std::endl;
	std::cout << "add (add new image to the session)" << std::endl;
	std::cout << "list session (prints all info for the images in the current session)" << std::endl;
	std::cout << "save (saves the images with current time added in the name)" << std::endl;
	std::cout << "saveas <path> (saves the images in <path>)" << std::endl;
	std::cout << "help (prints this information)" << std::endl;
	std::cout << "crop <x1> <y1> <x2> <y2> (crops a the image with coordinates <x1> <y1> (upper left corner) <x2> <y2> (lower right corner))" << std::endl;
	std::cout << "make collage <horizontal,vertical> <path> (makes collage from two images with same format)" << std::endl;
	std::cout << "exit (exits the program)" << std::endl;
}

CommandCenter::CommandCenter() : converter(ImageConverter())
{
}

void CommandCenter::executeCommand(const std::string command)
{
	if (this->commands.size() == 0 && command != "load")
	{
		throw std::invalid_argument("First command should be \"load!\"");
	}

	int x1, y1, x2, y2;

	if (command == "load")
	{
		converter.loadImage();
	}
	else if (command == "grayscale")
	{
		converter.convertImageToGrayscale();
	}
	else if (command == "negative")
	{
		converter.convertImageNegative();
	}
	else if (command == "monochrome")
	{
		converter.convertImageMonochrome();
	}
	else if (command == "rotate left")
	{
		converter.rotateImageLeft();
	}
	else if (command == "rotate right")
	{
		converter.rotateImageRight();
	}
	else if (command == "flip top")
	{
		converter.flipImageTop();
	}
	else if (command == "flip left")
	{
		converter.flipImageLeft();
	}
	else if (command == "crop")
	{
		std::cin >> x1 >> y1 >> x2 >> y2;

		converter.cropImage(x1, y1, x2, y2);
	}
	else if (command == "add")
	{
		converter.addNewImage();
	}
	else if (command == "undo")
	{
		if (this->commands.size() == 0)
		{
			throw std::runtime_error("You cannot use undo as first command!");
		}

		if (this->commands[this->commands.size() - 1] != "load" && 
			this->commands[this->commands.size() - 1] != "help" &&
			this->commands[this->commands.size() - 1] != "save" &&
			this->commands[this->commands.size() - 1] != "saveas")
		{
			converter.doOposite(this->commands[this->commands.size() - 1]);
		}
		else
		{
			throw std::runtime_error("You cannot use undo after \"load\", \"help\", \"save\", \"saveas\"!");
		}
	}
	else if (command == "redo")
	{
		if (this->commands[this->commands.size() - 1] == "undo")
		{
			if (this->commands[this->commands.size() - 2] == "grayscale")
			{
				converter.convertImageToGrayscale();
			}
			else if (this->commands[this->commands.size() - 2] == "negative")
			{
				converter.convertImageNegative();
			}
			else if (this->commands[this->commands.size() - 2] == "monochrome")
			{
				converter.convertImageMonochrome();
			}
			else if (this->commands[this->commands.size() - 2] == "rotate left")
			{
				converter.rotateImageLeft();
			}
			else if (this->commands[this->commands.size() - 2] == "rotate right")
			{
				converter.rotateImageRight();
			}
			else if (this->commands[this->commands.size() - 2] == "flip top")
			{
				converter.flipImageTop();
			}
			else if (this->commands[this->commands.size() - 2] == "flip left")
			{
				converter.flipImageLeft();
			}
			else if (this->commands[this->commands.size() - 2] == "crop")
			{
				converter.cropImage(x1, y1, x2, y2);
			}
			else if (this->commands[this->commands.size() - 2] == "add")
			{
				converter.addPeviousImage();
			}
		}
		else
		{
			throw std::runtime_error("There is no previous command \"undo\" to do redo!");
		}
	}
	else if (command == "save")
	{
		converter.saveImage();
	}
	else if (command == "saveas")
	{
		converter.saveAsImage();
	}
	else if (command == "list session")
	{
		converter.printSessionInfo();
	}
	else if (command == "make collage horizontal")
	{
		converter.makeCollage("horizontal");
	}
	else if (command == "make collage vertical")
	{
		converter.makeCollage("vertical");
	}
	else if (command == "help")
	{
		this->printAllCommands();
	}
	else if (command == "exit")
	{
		return;
	}
	else
	{
		throw std::runtime_error("Invalid command! (type help to see all commands)");
	}

	this->commands.push_back(command);
}
