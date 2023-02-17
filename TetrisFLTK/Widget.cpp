// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Widget.h"

// -----------------------------------------------------------------------------

FltkWrapper::Widget::Widget(Point pXY, int pWidth, int pHeight, const std::string& pLabel, Callback pCallback)
	: mLabel(pLabel)
	, mLocation(pXY)
	, mCallback(pCallback)
	, mWidth(pWidth)
	, mHeight(pHeight)
{

}

// -----------------------------------------------------------------------------

void FltkWrapper::Widget::move(int pNewX, int pNewY)
{
	hide();
	mLocation.mX = pNewX;
	mLocation.mY = pNewY;

	mFlWidget->position(mLocation.asIntX(), mLocation.asIntY());
	show();
}

// -----------------------------------------------------------------------------

void FltkWrapper::Widget::hide()
{
	mFlWidget->hide();
}

// -----------------------------------------------------------------------------

void FltkWrapper::Widget::show()
{
	mFlWidget->show();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


