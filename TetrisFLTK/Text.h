// -----------------------------------------------------------------------------
#ifndef Text_H
#define Text_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Font.h"
#include "Point.h"
#include "Shape.h"

#include <FL/fl_draw.H>
#include <string>

// -----------------------------------------------------------------------------

namespace FltkWrapper
{
	class Text : public Shape 
	{
	public:
		Text()
			: mLabel()
			, mFont()
			, mFontSize{ (14 < fl_size()) ? fl_size() : 14 }
		{}

		// the point is the bottom left of the first letter
		Text(Point pPoint, const std::string& s) 
			: mLabel{ s }
			, mFont()
			, mFontSize(14)
		{
			//initialise the font face
			setFont(Font::FontType::eHELVETICA);
			setFontSize(14);						//14 is default FLTK size
			fl_font(mFont.as_int(), mFontSize);
			addPoint(pPoint);
		}

		virtual void draw() override
		{
			int currenFont = fl_font();
			int currentSize = fl_size();

			//set font colour
			fl_color(mFont.getColour().as_int());	// reset color
			fl_font(mFont.as_int(), mFontSize);
			fl_draw(mLabel.c_str(), atPoint(0).asIntX(), atPoint(0).asIntY());
			fl_font(currenFont, currentSize);
		}

		void setLabel(const std::string& pText) { mLabel = pText; }
		const std::string getLabel() const { return mLabel; }

		void setFont(Font pFont) { mFont = pFont; }
		const Font getFont() const { return mFont; }

		void setFontSize(int pSize) { mFontSize = pSize; }
		const int getFontSize() const { return mFontSize; }

		//length of text label
		double length() { return fl_width(mLabel.c_str()); }

	private:
		std::string mLabel;
		Font mFont;
		int mFontSize;
	};
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Text_H