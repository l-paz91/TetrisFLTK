// -----------------------------------------------------------------------------
#ifndef Font_H
#define Font_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Colour.h"

#include <FL/fl_draw.H>

// -----------------------------------------------------------------------------

namespace FltkWrapper
{
	class Font
	{
	public:

		enum class FontType
		{
			eHELVETICA = FL_HELVETICA,
			eHELVETICA_BOLD = FL_HELVETICA_BOLD,
			eHELVETICA_ITALIC = FL_HELVETICA_ITALIC,
			eHELVETICA_BOLD_ITALIC = FL_HELVETICA_BOLD_ITALIC,
			eCOURIER = FL_COURIER,
			eCOURIER_BOLD = FL_COURIER_BOLD,
			eCOURIER_ITALIC = FL_COURIER_ITALIC,
			eCOURIER_BOLD_ITALIC = FL_COURIER_BOLD_ITALIC,
			eTIMES = FL_TIMES,
			eTIMES_BOLD = FL_TIMES_BOLD,
			eTIMES_ITALIC = FL_TIMES_ITALIC,
			eTIMES_BOLD_ITALIC = FL_TIMES_BOLD_ITALIC,
			eSYMBOL = FL_SYMBOL,
			eSCREEN = FL_SCREEN,
			eSCREEN_BOLD = FL_SCREEN_BOLD,
			eZAPF_DINGBATS = FL_ZAPF_DINGBATS
		};

		Font() : mFont(static_cast<int>(FontType::eHELVETICA)) {}
		Font(FontType pFontType) : mFont(static_cast<int>(pFontType)) { }
		Font(int pFontType) : mFont(pFontType) { }
		
		void setColour(Colour pColour) { mColour = pColour; }
		const Colour getColour() const { return mColour; }

		int as_int() const { return mFont; }
	private:
		Colour mColour;
		int mFont;
	};
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Font_H