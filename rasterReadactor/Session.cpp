#include "Session.h"

unsigned int Session::nextID = 0;

Session::Session()
{
	this->id= ++nextID;
}

Session::Session(Image image)
{
	this->id = ++nextID;

	this->images.push_back(image);
}

void Session::printSession() const
{
	std::size_t numberOfImages = this->images.size();

	for (size_t i = 0; i < numberOfImages; i++)
	{
		if (this->images[i].getFormat() == "P3" || this->images[i].getFormat() == "P6")
		{
			std::cout << this->images[i].getName() << " - portable pixmap format" << std::endl;
		}
		else if (this->images[i].getFormat() == "P1" || this->images[i].getFormat() == "P4")
		{
			std::cout << this->images[i].getName() << " - portable bitmap format" << std::endl;
		}
		else if (this->images[i].getFormat() == "P2" || this->images[i].getFormat() == "P5")
		{
			std::cout << this->images[i].getName() << " - portable graymap format" << std::endl;
		}
	}
}

void Session::addImage(Image& image)
{
	this->images.push_back(image);
}

void Session::removeLast()
{
	this->images.pop_back();
}

unsigned int Session::getID() const
{
	return this->id;
}


std::vector<Image> Session::getImage() const
{
	return this->images;
}
