// -----------------------------------------------------------------------------
#ifndef Image_H
#define Image_H
// -----------------------------------------------------------------------------
// 
/*
	Image is a simple wrapper around various Fl_Image types that you can attach
	to a Window.

	Images are a Shape. Shape is a custom type that can be attached to a Window.
	
	Image can support jpg, bmp, png and gif (but only the first frame)
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Point.h"
#include "Shape.h"

#include <FL/Fl_Box.H>
#include <Fl/Fl_Image.H>
#include <string>

// -----------------------------------------------------------------------------

namespace FltkWrapper
{
	struct Suffix
	{
		enum Encoding 
		{ 
			eNONE, 
			eJPG, 
			eGIF, 
			eBMP, 
			ePNG 
		};
	};

	class Image : public Shape
	{
	public:
		Image(Point pXY, int pWidth, int pHeight, std::string pFilename, Suffix::Encoding pEncoding = Suffix::eNONE);
		~Image() { delete mImage; }

		virtual void draw() override;

		void render();
		void setMask(Point pXY, int pWidth, int pHeight);
		void drawPoint(double x, double y);

		const double getWidth() const { return mImage->w(); }
		const double getHeight() const { return mImage->h(); }

	private:
		Point mPoint;
		int mWidth;
		int mHeight;
		int mCropWidth;		// define "masking box" within image relative to position (ch,cw)
		int mCropHeight;

		Fl_Box mBox;
		Fl_Image* mImage;
	};
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Image_H