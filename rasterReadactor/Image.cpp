#include "Image.h"

Image::Image(std::string filePath)
{
	this->readFromFile(filePath);
}

Image::Image(unsigned int width, unsigned int height, std::string format, unsigned int maxValue)
{
	if (maxValue > MAX_VALUE_OF_PIXEL)
	{
		throw std::invalid_argument("Max value of pixel is 255!");
	}
	this->maxValue = maxValue;

	this->width = width;
	this->height = height;
	this->format = format;
}

std::string Image::getFormat() const
{
	return this->format;
}

unsigned int Image::getWidth() const
{
	return this->width;
}

unsigned int Image::getHeight() const
{
	return this->height;
}

unsigned int Image::getMaxValue() const
{
	return this->maxValue;
}

const std::string Image::getName() const
{
	return this->name;
}

void Image::writeToFile(std::string filePath)
{
	std::ofstream file(filePath, std::ios::binary);

	file << this->format << std::endl;
	file << this->width << " " << this->height << std::endl;

	if (this->format != "P1" && this->format != "P4")
	{
		file << this->maxValue << std::endl;
	}

	std::size_t size = width * height;


	if (this->format == "P2" || this->format == "P5")
	{
		for (std::size_t i = 0; i < size; ++i)
		{
			file.write(reinterpret_cast<const char*>(&this->pixels[i].red), sizeof(char));
		}
	}
	else
	{
		for (std::size_t i = 0; i < size; ++i)
		{
			file.write(reinterpret_cast<const char*>(&this->pixels[i]), sizeof(Pixel));
		}
	}


	file.close();
}

void Image::readFromFile(std::string filePath)
{
	std::ifstream file(filePath, std::ios::binary);

	if (!file)
	{
		throw std::runtime_error("Problem while opening the file or this file does not exist!");
	}
	this->name = filePath;

	file >> this->format;

	if (this->format != "P1" && this->format != "P2" && this->format != "P3" && this->format != "P4" &&
		this->format != "P5" && this->format != "P6")
	{
		this->name = "";
		this->format = "";
		throw std::runtime_error("This file is not supported!");
	}

	file >> this->width >> this->height;


	if (this->format != "P1" && this->format != "P4")
	{
		file >> this->maxValue;
	}
	file.ignore();

	std::size_t size = this->width * this->height;
	this->pixels.resize(size);

	if (this->format == "P2" || this->format == "P5")
	{
		char grayValue;

		for (std::size_t i = 0; i < size; ++i)
		{
			file.read(reinterpret_cast<char*>(&grayValue), sizeof(char));
			this->pixels[i].red = grayValue;
			this->pixels[i].green = grayValue;
			this->pixels[i].blue = grayValue;
		}
	}
	else
	{
		for (std::size_t i = 0; i < size; ++i)
		{
			file.read(reinterpret_cast<char*>(&this->pixels[i]), sizeof(Pixel));
		}
	}

	this->previousPixels = this->pixels;
	file.close();
}

void Image::makePixelsGray()
{
	this->previousPixels = this->pixels;
	std::size_t sizePixels = this->pixels.size();

	for (size_t i = 0; i < sizePixels; i++)
	{
		unsigned char gray;
		gray = (this->pixels[i].red + this->pixels[i].green + this->pixels[i].blue) / 3;

		this->pixels[i].red = gray;
		this->pixels[i].green = gray;
		this->pixels[i].blue = gray;
	}
}

void Image::makePixelsMonochrome()
{
	this->previousPixels = this->pixels;
	std::size_t sizePixels = this->pixels.size();

	for (size_t i = 0; i < sizePixels; i++)
	{
		unsigned char gray;
		gray = (this->pixels[i].red + this->pixels[i].green + this->pixels[i].blue) / 3;

		if (gray < 128)
		{
			this->pixels[i].red = 0;
			this->pixels[i].green = 0;
			this->pixels[i].blue = 0;
		}
		else
		{
			this->pixels[i].red = 255;
			this->pixels[i].green = 255;
			this->pixels[i].blue = 255;
		}
	}

	this->previousPixels = this->pixels;
}

void Image::makePixelsNegative()
{
	this->previousPixels = this->pixels;

	std::size_t sizePixels = this->pixels.size();

	for (size_t i = 0; i < sizePixels; i++)
	{
		this->pixels[i].red = 255 - this->pixels[i].red;
		this->pixels[i].green = 255 - this->pixels[i].green;
		this->pixels[i].blue = 255 - this->pixels[i].blue;
	}
}

void Image::rotatePixelsLeft()
{
	std::vector<Pixel> rotatedPixels(this->height * this->width);

	for (unsigned int y = 0; y < this->height; ++y)
	{
		for (unsigned int x = 0; x < this->width; ++x)
		{
			unsigned int newX = y;
			unsigned int newY = this->width - x - 1;
			rotatedPixels[newY * this->height + newX] = this->pixels[y * this->width + x];
		}
	}

	std::swap(this->width, this->height);
	this->pixels = rotatedPixels;
}

void Image::rotatePixelsRight()
{
	std::vector<Pixel> rotatedPixels(this->height * this->width);

	for (unsigned int y = 0; y < this->height; ++y)
	{
		for (unsigned int x = 0; x < this->width; ++x)
		{
			unsigned int newX = this->height - y - 1;
			unsigned int newY = x;
			rotatedPixels[newY * this->height + newX] = this->pixels[y * this->width + x];
		}
	}

	std::swap(this->width, this->height);
	this->pixels = rotatedPixels;
}

void Image::flipPixelsTop()
{
	for (unsigned int y = 0; y < this->height / 2; ++y)
	{
		for (unsigned int x = 0; x < this->width; ++x)
		{
			unsigned int topIndex = y * this->width + x;
			unsigned int bottomIndex = (this->height - y - 1) * this->width + x;

			std::swap(this->pixels[topIndex], this->pixels[bottomIndex]);
		}
	}
}

void Image::flipPixelsLeft()
{

	for (unsigned int y = 0; y < this->height; ++y)
	{
		for (unsigned int x = 0; x < this->width / 2; ++x)
		{
			unsigned int topLeftIndex = y * this->width + x;
			unsigned int topRightIndex = y * this->width + (this->width - x - 1);

			std::swap(this->pixels[topLeftIndex], this->pixels[topRightIndex]);
		}
	}
}

void Image::returnPreviousPixels()
{
	this->pixels = this->previousPixels;
}


void Image::cropImage(int x1, int y1, int x2, int y2)
{
	int imageWidth = this->width;
	int imageHeight = this->height;

	int startX = std::max(0, std::min(x1, imageWidth - 1));
	int startY = std::max(0, std::min(y1, imageHeight - 1));
	int endX = std::max(0, std::min(x2, imageWidth - 1));
	int endY = std::max(0, std::min(y2, imageHeight - 1));

	int newWidth = endX - startX + 1;
	int newHeight = endY - startY + 1;

	std::vector<Pixel> croppedPixels;

	for (int y = startY; y <= endY; y++)
	{
		for (int x = startX; x <= endX; x++)
		{
			croppedPixels.push_back(this->pixels[y * imageWidth + x]);
		}
	}

	this->width = newWidth;
	this->height = newHeight;
	this->pixels = croppedPixels;
}

bool Image::isImageColorful() const
{
	std::size_t sizePixels = this->pixels.size();
	for (size_t i = 0; i < sizePixels; i++)
	{
		if ((this->pixels[i].red != 0 && this->pixels[i].red != 255) ||
			(this->pixels[i].green != 0 && this->pixels[i].green != 255) ||
			(this->pixels[i].blue != 0 && this->pixels[i].blue != 255))
		{
			return true;
		}
	}

	return false;
}

void Image::setPixels(int x, int y, const Pixel& color)
{
	if (x >= 0 && x < this->width && y >= 0 && y < this->height)
	{
		int index = y * width + x;

		if (index >= pixels.size())
		{
			pixels.resize(index + 1);
		}

		pixels[index] = color;
	}
}

Pixel Image::getPixels(int x, int y) const
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		int index = y * width + x;

		return pixels[index];
	}
}

void Image::setName(const std::string name)
{
	this->name = name;
}
