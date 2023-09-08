#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Session.h"
#include <ctime>
#include <cmath>

class ImageConverter
{
private:
	std::vector<Session> sessions;

	std::vector<Image> images;
	std::vector<Image> previousImages;

	bool isLoadExecuted;

	// Helper function for breaking apart the name of the image into name and format
	void helpImageName(const Image& image, std::string& fileName, std::string& fileFormat);

	// Helper function for making a collage
	void doCollage(const Image& first, const Image& second, std::string type);

public:
	// Default constructor
	ImageConverter();

	// Constructor with parameters (given session)
	ImageConverter(Session session);

	// Function that loads the image from file
	void loadImage();

	// Function that save as images
	void saveAsImage();

	// Function that saves the images with current time
	void saveImage();

	// Function that converts images to grayscale
	void convertImageToGrayscale();

	// Function that converts images to monochrome
	void convertImageMonochrome();

	// Function that converts images to negative
	void convertImageNegative();

	// Function that rotates the images to left
	void rotateImageLeft();

	// Function that rotates the images to right
	void rotateImageRight();

	// Function that flips the images top
	void flipImageTop();

	// Function that flips the images left
	void flipImageLeft();

	// Function that returns the previous pixels to the images
	void returnImagePixels();

	// Function that add new image to the session
	void addNewImage();

	// Function that add again previous image to the session (if redo is called after undo)
	void addPeviousImage();

	// Function that crops the images
	void cropImage(int x1, int y1, int x2, int y2);

	// Function that returns the image before crop
	void returnFromCrop();

	// Function that makes collage with specific type (horizontal, vertical)
	void makeCollage(std::string type);

	// Function that performs undo actions
	void doOposite(std::string lastCommand);

	// Function print all info for images in the session
	void printSessionInfo();
};

