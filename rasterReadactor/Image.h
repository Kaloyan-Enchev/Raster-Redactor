#pragma once
#include "Pixel.h"

class Image
{
private:
	static const unsigned int MAX_VALUE_OF_PIXEL = 255;

	std::string name;
	std::string format;
	unsigned int width;
	unsigned int height;
	unsigned int maxValue;

	std::vector<Pixel> pixels;
	std::vector<Pixel> previousPixels;

public:
	// Constructor with parameters (given filepath)
	Image(std::string filePath);

	// Constructor with parameters (create image with widht, height, file format, max value)
	Image(unsigned int width, unsigned int height, std::string format, unsigned int maxValue);

	// Gets the format type (PPM, PBM, PGM)
	std::string getFormat() const;

	// Gets the width of the image
	unsigned int getWidth() const;

	// Gets the height of the image
	unsigned int getHeight() const;

	// Gets the max value of the image
	unsigned int getMaxValue() const;

	// Gets the name of the image
	const std::string getName() const;

	// Function for writing the image in file
	void writeToFile(std::string filePath);

	// Function for loading the image from file
	void readFromFile(std::string filePath);

	// Function that makes pixels gray
	void makePixelsGray();

	// Function that makes pixels monochrome
	void makePixelsMonochrome();

	// Function that makes pixels negative
	void makePixelsNegative();

	// Function that rotates pixels to left
	void rotatePixelsLeft();

	// Function that rotates pixels to right
	void rotatePixelsRight();

	// Function that flips pixels top
	void flipPixelsTop();

	// Function that flips pixels left
	void flipPixelsLeft();

	// Function that returns previous pixels to current ones
	void returnPreviousPixels();

	// Function that crops the image
	void cropImage(int x1, int y1, int x2, int y2);

	// Function that checks if the image has pixel different from black and white
	bool isImageColorful() const;

	// Function that sets pixels
	void setPixels(int x, int y, const Pixel& color);

	// Gets the pixels of the image
	Pixel getPixels(int x, int y) const;

	// Function that sets the name of the image
	void setName(const std::string name);
};

