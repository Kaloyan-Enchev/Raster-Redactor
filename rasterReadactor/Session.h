#pragma once
#include "Image.h"

class Session
{
protected:
	std::vector<Image> images;
	static unsigned int nextID;
	unsigned int id;

public:
	// Default constructor
	Session();

	// Constructor with parameters (given image)
	Session(Image image);

	// Function that prints the info in the session
	void printSession() const;

	// Function that add image to the session
	void addImage(Image& image);

	// Function that removes the last image in the session
	void removeLast();

	// Gets the id of the session
	unsigned int getID() const;

	// Gets the vector of images
	std::vector<Image> getImage() const;
};


