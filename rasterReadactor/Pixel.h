#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>

struct Pixel
{
public:
	// Unsigned char range 0-255
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	// Default constructor with default values (0,0,0)
	Pixel();

	// Constructor with fixed values for the different colors
	Pixel(unsigned char red, unsigned char green, unsigned char blue);
};

