#include "ImageConverter.h"

ImageConverter::ImageConverter()
{
	this->sessions.push_back(Session());
	this->isLoadExecuted = false;
}

ImageConverter::ImageConverter(Session session)
{
	this->sessions.push_back(session);
	std::size_t size = session.getImage().size();

	this->isLoadExecuted = false;

	for (size_t i = 0; i < size; i++)
	{
		this->images.push_back(session.getImage()[i]);
	}
}

void ImageConverter::loadImage()
{
	this->images.clear();
	this->previousImages.clear();

	if (this->isLoadExecuted)
	{
		Session session;
		this->sessions.push_back(session);
	}

	char paths[100];
	std::cin.getline(paths, 100);
	std::vector<std::string> imagePaths;

	int i = 0;
	std::string str;
	while (paths[i] != '\0')
	{
		if (paths[i] != ' ')
		{
			str += paths[i];
		}
		else
		{
			imagePaths.push_back(str);
			str.clear();
		}
		i++;

		if (paths[i] == '\0')
		{
			imagePaths.push_back(str);
		}

	}

	std::size_t numberOfImages = imagePaths.size();

	if (numberOfImages == 0)
	{
		throw std::invalid_argument("Empty file path/s!");
	}

	for (size_t j = 0; j < numberOfImages; j++)
	{
		Image image(imagePaths[j]);
		this->images.push_back(image);
		this->sessions[this->sessions.size() - 1].addImage(image);
	}

	this->isLoadExecuted = true;

	std::cout << "Session with ID: " << this->sessions[this->sessions.size() - 1].getID() << " started" << std::endl;
}

void ImageConverter::saveAsImage()
{
	std::size_t numberOfImages = this->images.size();

	for (size_t i = 0; i < numberOfImages; i++)
	{
		std::string filePath;
		std::cout << "Enter name for new file: ";
		std::cin >> filePath;
		this->images[i].writeToFile(filePath);
	}
}

void ImageConverter::saveImage()
{
	std::size_t numberOfImages = this->images.size();

	for (size_t i = 0; i < numberOfImages; i++)
	{
		std::string fileName;
		std::string fileFormat;

		this->helpImageName(this->images[i], fileName, fileFormat);

		// This code is not mine
		std::time_t timeNow = std::time(0);
		std::tm* currentTime = std::localtime(&timeNow);
		char timeBuffer[80];
		std::strftime(timeBuffer, sizeof(timeBuffer), "%Y%m%d%H%M%S", currentTime);
		//

		fileName += '_';
		fileName += timeBuffer;
		fileName += fileFormat;

		this->images[i].writeToFile(fileName);
	}
}

void ImageConverter::convertImageToGrayscale()
{
	std::size_t numberOfImages = this->images.size();

	for (size_t i = 0; i < numberOfImages; i++)
	{
		if (this->images[i].getFormat() != "P2" && this->images[i].getFormat() != "P5" &&
			this->images[i].getFormat() != "P1" && this->images[i].getFormat() != "P4")
		{
			if (this->images[i].isImageColorful())
			{
				this->images[i].makePixelsGray();
			}
		}
	}
}

void ImageConverter::convertImageMonochrome()
{
	std::size_t numberOfImages = this->images.size();

	for (size_t i = 0; i < numberOfImages; i++)
	{
		if (this->images[i].isImageColorful())
		{
			this->images[i].makePixelsMonochrome();
		}
	}
}

void ImageConverter::convertImageNegative()
{
	std::size_t numberOfImages = this->images.size();

	for (size_t i = 0; i < numberOfImages; i++)
	{
		this->images[i].makePixelsNegative();
	}
}

void ImageConverter::rotateImageLeft()
{
	std::size_t numberOfImages = this->images.size();

	for (size_t i = 0; i < numberOfImages; i++)
	{
		this->images[i].rotatePixelsLeft();
	}
}

void ImageConverter::rotateImageRight()
{
	std::size_t numberOfImages = this->images.size();

	for (size_t i = 0; i < numberOfImages; i++)
	{
		this->images[i].rotatePixelsRight();
	}
}

void ImageConverter::flipImageTop()
{
	std::size_t numberOfImages = this->images.size();

	for (size_t i = 0; i < numberOfImages; i++)
	{
		this->images[i].flipPixelsTop();
	}
}

void ImageConverter::flipImageLeft()
{
	std::size_t numberOfImages = this->images.size();

	for (size_t i = 0; i < numberOfImages; i++)
	{
		this->images[i].flipPixelsLeft();
	}
}

void ImageConverter::returnImagePixels()
{
	std::size_t numberOfImages = this->images.size();

	for (size_t i = 0; i < numberOfImages; i++)
	{
		this->images[i].returnPreviousPixels();
	}
}

void ImageConverter::addNewImage()
{
	std::string path;
	std::cin >> path;

	Image image(path);
	this->sessions[this->sessions.size() - 1].addImage(image);
	this->images.push_back(image);
	this->previousImages.push_back(image);
}

void ImageConverter::addPeviousImage()
{
	Image image = this->previousImages.back();
	this->sessions[this->sessions.size() - 1].addImage(image);
	this->images.push_back(image);
}

void ImageConverter::cropImage(int x1, int y1, int x2, int y2)
{
	std::size_t numberOfImages = this->images.size();

	for (size_t i = 0; i < numberOfImages; i++)
	{
		this->previousImages.push_back(this->images[i]);
		this->images[i].cropImage(x1, y1, x2, y2);
	}
}

void ImageConverter::returnFromCrop()
{
	std::size_t numberOfImages = this->images.size();

	for (size_t i = 0; i < numberOfImages; i++)
	{
		this->images[i] = this->previousImages[i];
	}
}

void ImageConverter::makeCollage(std::string type)
{
	std::string image1, image2;
	std::cin >> image1 >> image2;

	std::size_t numberOfImages = this->images.size();

	bool isFirstImageIn = false;
	bool isSecondImageIn = false;

	for (size_t i = 0; i < numberOfImages; i++)
	{
		if (this->images[i].getName() == image1)
		{
			isFirstImageIn = true;
		}

		if (this->images[i].getName() == image2)
		{
			isSecondImageIn = true;
		}
	}

	if (isFirstImageIn && isSecondImageIn)
	{
		for (size_t i = 0; i < numberOfImages; i++)
		{
			for (size_t j = i + 1; j < numberOfImages; j++)
			{
				if ((this->images[i].getName() == image1 || this->images[i].getName() == image2) &&
					(this->images[j].getName() == image1 || this->images[j].getName() == image2))
				{
					this->doCollage(this->images[i], this->images[j], type);
				}
			}
		}
	}
	else
	{
		throw std::invalid_argument("Invalid name!");
	}
}

void ImageConverter::helpImageName(const Image& image, std::string& fileName, std::string& fileFormat)
{
	std::size_t imageNameSize = image.getName().size();

	std::size_t j = 0;

	for (j; j < imageNameSize; j++)
	{
		if (image.getName()[j] == '.')
		{
			break;
		}

		fileName += image.getName()[j];
	}

	for (size_t p = j; p < imageNameSize; p++)
	{
		fileFormat += image.getName()[p];
	}
}

void ImageConverter::doCollage(const Image& first, const Image& second, std::string type)
{
	if (first.getFormat() != second.getFormat())
	{
		throw std::invalid_argument("Cannot make a collage from different types!(" + first.getFormat() +
			" and " + second.getFormat() + ")");
	}

	int collageWidth, collageHeight;
	int maxValue = 0;

	for (size_t i = 0; i < 2; i++)
	{
		int imageMaxValue = this->images[i].getMaxValue();

		if (imageMaxValue > maxValue)
		{
			maxValue = imageMaxValue;
		}
	}

	if (type == "horizontal")
	{
		collageWidth = first.getWidth() + second.getWidth();
		collageHeight = std::max(first.getHeight(), second.getHeight());
	}
	else if (type == "vertical")
	{
		collageWidth = std::max(first.getWidth(), second.getWidth());
		collageHeight = first.getHeight() + second.getHeight();
	}
	else
	{
		throw std::invalid_argument("Invalid collage type specified.");
	}

	Image collageImage(collageWidth, collageHeight, first.getFormat(), maxValue);

	Pixel black(0, 0, 0);
	for (int y = 0; y < collageHeight; y++)
	{
		for (int x = 0; x < collageWidth; x++)
		{
			collageImage.setPixels(x, y, black);
		}
	}

	int offsetX = 0;
	int offsetY = 0;

	if (type == "vertical")
	{
		if (first.getWidth() > second.getWidth())
		{
			offsetX = (collageWidth - second.getWidth()) / 2;

			for (int y = 0; y < first.getHeight(); y++)
			{
				for (int x = 0; x < first.getWidth(); x++)
				{
					Pixel pixel = first.getPixels(x, y);
					collageImage.setPixels(x, y + offsetY, pixel);
				}
			}

			offsetY += first.getHeight();

			for (int y = 0; y < second.getHeight(); y++)
			{
				for (int x = 0; x < second.getWidth(); x++)
				{
					Pixel pixel = second.getPixels(x, y);
					collageImage.setPixels(x + offsetX, y + offsetY, pixel);
				}
			}
		}
		else
		{
			offsetX = (collageWidth - first.getWidth()) / 2;

			for (int y = 0; y < first.getHeight(); y++)
			{
				for (int x = 0; x < first.getWidth(); x++)
				{
					Pixel pixel = first.getPixels(x, y);
					collageImage.setPixels(x + offsetX, y + offsetY, pixel);
				}
			}

			offsetY += first.getHeight();

			for (int y = 0; y < second.getHeight(); y++)
			{
				for (int x = 0; x < second.getWidth(); x++)
				{
					Pixel pixel = second.getPixels(x, y);
					collageImage.setPixels(x, y + offsetY, pixel);
				}
			}
		}
	}
	else if (type == "horizontal")
	{
		if (first.getHeight() > second.getHeight())
		{
			offsetY = (collageHeight - second.getHeight()) / 2;

			for (int y = 0; y < first.getHeight(); y++)
			{
				for (int x = 0; x < first.getWidth(); x++)
				{
					Pixel pixel = first.getPixels(x, y);
					collageImage.setPixels(x + offsetX, y, pixel);
				}
			}

			offsetX += first.getWidth();

			for (int y = 0; y < second.getHeight(); y++)
			{
				for (int x = 0; x < second.getWidth(); x++)
				{
					Pixel pixel = second.getPixels(x, y);
					collageImage.setPixels(x + offsetX, y + offsetY, pixel);
				}
			}
		}
		else
		{
			offsetY = (collageHeight - first.getHeight()) / 2;

			for (int y = 0; y < first.getHeight(); y++)
			{
				for (int x = 0; x < first.getWidth(); x++)
				{
					Pixel pixel = first.getPixels(x, y);
					collageImage.setPixels(x + offsetX, y + offsetY, pixel);
				}
			}

			offsetX += first.getWidth();

			for (int y = 0; y < second.getHeight(); y++)
			{
				for (int x = 0; x < second.getWidth(); x++)
				{
					Pixel pixel = second.getPixels(x, y);
					collageImage.setPixels(x + offsetX, y, pixel);
				}
			}
		}
	}

	std::string firstFileName;
	std::string firstFileFormat;
	std::string secondFileName;
	std::string secondFileFormat;

	this->helpImageName(first, firstFileName, firstFileFormat);
	this->helpImageName(second, secondFileName, secondFileFormat);

	std::string fileName = firstFileName + "_" + secondFileName + firstFileFormat;

	collageImage.setName(fileName);

	this->images.push_back(collageImage);
	this->previousImages.push_back(collageImage);
	this->sessions[this->sessions.size() - 1].addImage(collageImage);
}

void ImageConverter::doOposite(std::string lastCommand)
{
	if (lastCommand == "grayscale" || lastCommand == "negative" || lastCommand == "monochrome")
	{
		this->returnImagePixels();
	}
	else if (lastCommand == "rotate left")
	{
		this->rotateImageRight();
	}
	else if (lastCommand == "rotate right")
	{
		this->rotateImageLeft();
	}
	else if (lastCommand == "flip top")
	{
		this->flipImageTop();
	}
	else if (lastCommand == "flip left")
	{
		this->flipImageLeft();
	}
	else if (lastCommand == "crop")
	{
		this->returnFromCrop();
	}
	else if (lastCommand == "add")
	{
		this->sessions[this->sessions.size() - 1].removeLast();
		this->images.pop_back();
	}
}

void ImageConverter::printSessionInfo()
{
	this->sessions[this->sessions.size() - 1].printSession();
}
