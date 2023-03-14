// -----------------------------------------------------------------------------
#ifndef Colour_H
#define Colour_H
// -----------------------------------------------------------------------------
// 
/*
	Colour is a simple wrapper around FL_Color. Simply grab a preset or
	make your own.

*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <FL/fl_draw.H>

// -----------------------------------------------------------------------------
namespace FltkWrapper
{
	struct Colour
	{
		enum ColourType
		{
			eRED = FL_RED, 
			eBLUE = FL_BLUE, 
			eGREEN = FL_GREEN,
			eYELLOW = FL_YELLOW, 
			eWHITE = FL_WHITE, 
			eBLACK = FL_BLACK,
			eMAGENTA = FL_MAGENTA, 
			eCYAN = FL_CYAN, 
			eDARK_RED = FL_DARK_RED,
			eDARK_GREEN = FL_DARK_GREEN, 
			eDARK_YELLOW = FL_DARK_YELLOW, 
			eDARK_BLUE = FL_DARK_BLUE,
			eDARK_MAGENTA = FL_DARK_MAGENTA,
			eDARK_CYAN = FL_DARK_CYAN, 
			ePINK = 252, 
			eCREAM = 215,
			eLIME = 71, 
			eCORAL = 130, 
			eBACKGROUND2_DEFAULT = FL_BACKGROUND2_COLOR, 
			eBACKGROUND_DEFAULT = FL_BACKGROUND_COLOR
		};

		enum Transparency 
		{ 
			eINVISIBLE = 0, 
			eVISIBLE = 255 
		};

		Colour()
			: mColour(eBLACK)
			, mTransparency(eVISIBLE)
		{}

		Colour(ColourType pColourType) 
			: mColour(Fl_Color(pColourType))
			, mTransparency(eVISIBLE)
		{ }

		Colour(ColourType pColourType, Transparency pTransparency) 
			: mColour(Fl_Color(pColourType))
			, mTransparency(pTransparency) 
		{ }

		Colour(int pColourType) 
			: mColour(Fl_Color(pColourType))
			, mTransparency(eVISIBLE)
		{ }

		Colour(Transparency pTransparency) 
			: mColour(Fl_Color())
			, mTransparency(pTransparency) 
		{ }

		Colour(uchar pR, uchar pG, uchar pB) 
		{ 
			fl_color(pR, pG, pB);
			mColour = fl_color(); 
			mTransparency = eVISIBLE;
		}

		int as_int() const { return mColour; }
		char visibility() const { return mTransparency; }
		void setVisibility(bool visible) { mTransparency = visible; }

	private:
		unsigned char mTransparency;	// 0 or 1 for now
		Fl_Color mColour;
	};
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Colour_H