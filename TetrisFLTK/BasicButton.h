// -----------------------------------------------------------------------------
#ifndef BasicButton_H
#define BasicButton_H
// -----------------------------------------------------------------------------
// 
/*
	A basic button is a Widget (which is an FL_Widget under the hood)
	You can set a callback on it when pressed and attach it to a Window

*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Colour.h"
#include "Widget.h"

// -----------------------------------------------------------------------------

namespace FltkWrapper
{
	struct BasicButton : public Widget
	{
		BasicButton(Point pXY, int pWidth, int pHeight, const char* pLabel, Callback pCallback)
			: Widget(pXY, pWidth, pHeight, pLabel, pCallback)
		{}

		void setColour(FltkWrapper::Colour::ColourType pColour)
		{
			mFlWidget->color(pColour);
		}

		void attach(Window& pWindow)
		{
			mFlWidget = new Fl_Button(mLocation.asIntX(), mLocation.asIntY(), mWidth, mHeight, mLabel.c_str());
			mFlWidget->callback(reinterpret_cast<Fl_Callback*>(mCallback), &pWindow);
			mWindow = &pWindow;
		}
	};
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !BasicButton_H