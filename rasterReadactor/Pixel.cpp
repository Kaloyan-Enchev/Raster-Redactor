#include "Pixel.h"

Pixel::Pixel()
{
	this->red = 0;
	this->green = 0;
	this->blue = 0;
}

Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}
