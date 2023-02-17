// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <fstream>
#include <iostream>
#include <map>

#include <Fl/Fl_BMP_Image.H>
#include <Fl/Fl_GIF_Image.H>
#include <Fl/Fl_JPEG_Image.H>
#include <Fl/Fl_PNG_Image.H>

#include "Image.h"
// -----------------------------------------------------------------------------

namespace ImagePrivate
{
	std::map<std::string, FltkWrapper::Suffix::Encoding> suffixMap;

	// -----------------------------------------------------------------------------

	int initSuffixMap()
	{
		using namespace FltkWrapper;
		suffixMap["jpg"] = Suffix::eJPG;
		suffixMap["JPG"] = Suffix::eJPG;
		suffixMap["jpeg"] = Suffix::eJPG;
		suffixMap["JPEG"] = Suffix::eJPG;
		suffixMap["gif"] = Suffix::eGIF;
		suffixMap["GIF"] = Suffix::eGIF;
		suffixMap["bmp"] = Suffix::eBMP;
		suffixMap["BMP"] = Suffix::eBMP;
		suffixMap["png"] = Suffix::ePNG;
		suffixMap["PNG"] = Suffix::ePNG;
		return 0;
	}

	// -----------------------------------------------------------------------------

	std::ifstream canOpen(const std::string& s)
	{
		// check if a file exists and can be opened for reading
		std::ifstream ff(s.c_str());
		return ff;
	}

	// -----------------------------------------------------------------------------

	FltkWrapper::Suffix::Encoding getEncoding(const std::string& pFilename)
	{
		// try to deduce type from file name using a lookup table
		static int x = ImagePrivate::initSuffixMap();

		std::string::const_iterator p = std::find(pFilename.begin(), pFilename.end(), '.');

		if (p == pFilename.end())
		{
			return FltkWrapper::Suffix::eNONE;	// no suffix
		}

		std::string suf(p + 1, pFilename.end());
		return ImagePrivate::suffixMap[suf];
	}
}

// -----------------------------------------------------------------------------

FltkWrapper::Image::Image(Point pXY, int pWidth, int pHeight, std::string pFilename, Suffix::Encoding pEncoding /*= Suffix::eNONE*/)
	: mPoint(pXY)
	, mWidth(pWidth)
	, mHeight(pHeight)
	, mCropWidth(0)
	, mCropHeight(0)
	, mBox(mPoint.asIntX(), mPoint.asIntY(), mWidth, mHeight )
{
	// somewhat over elaborate constructor
	// because errors related to image files can be such a pain to debug

	using namespace FltkWrapper;

	if (!ImagePrivate::canOpen(pFilename))
	{
		std::cout << "Image(): Error opening file.\n";
		return;
	}

	if (pEncoding == Suffix::eNONE)
	{
		pEncoding = ImagePrivate::getEncoding(pFilename);
	}

	switch (pEncoding)
	{
	case Suffix::eJPG:
		mImage = new Fl_JPEG_Image(pFilename.c_str());
		break;
	case Suffix::eGIF:
		mImage = new Fl_GIF_Image(pFilename.c_str());
		break;
	case Suffix::ePNG:
		mImage = new Fl_PNG_Image(pFilename.c_str());
		break;
	case Suffix::eBMP:
		mImage = new Fl_BMP_Image(pFilename.c_str());
		break;
	default:	// Unsupported image encoding
		std::cout << "Image(): Unsupported file type.\n";
	}

	mBox.image(mImage);
}

// -----------------------------------------------------------------------------

void FltkWrapper::Image::draw()
{
	render();
}

// -----------------------------------------------------------------------------

void FltkWrapper::Image::render()
{
	if (mCropWidth && mCropHeight)
		mImage->draw(mPoint.asIntX(), mPoint.asIntY(), mWidth, mHeight, mCropWidth, mCropHeight);
	else
		mImage->draw(mPoint.asIntX(), mPoint.asIntY());
}

// -----------------------------------------------------------------------------

void FltkWrapper::Image::setMask(Point pXY, int pWidth, int pHeight)
{
	mWidth = pWidth;
	mHeight = pHeight;
	mCropWidth = pXY.asIntX();
	mCropHeight = pXY.asIntY();
}

// -----------------------------------------------------------------------------

void FltkWrapper::Image::changePoint(double x, double y)
{
	mPoint.mX = x;
	mPoint.mY = y;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------