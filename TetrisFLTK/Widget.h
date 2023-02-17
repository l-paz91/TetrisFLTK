// -----------------------------------------------------------------------------
#ifndef Widget_H
#define Widget_H
// -----------------------------------------------------------------------------
// 
/*
	Widget is a handle to an Fl_Widget - it is *NOT* an Fl_Widget
	We try to keep our interface classes at arms length from FLTK

*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Window.h"

#include <string>

// -----------------------------------------------------------------------------

namespace FltkWrapper
{
	// -----------------------------------------------------------------------------
	
	// Address is a synonym for void*
	typedef void* Address;		

	// FLTKs required function type for all callbacks	
	typedef void(*Callback)(Address, Address);

	// -----------------------------------------------------------------------------

	template<typename T>
	T& referenceTo(Address pObject)
	{
		// treat an Address as a reference to a T object
		return *static_cast<T*>(pObject);
	}

	// -----------------------------------------------------------------------------

	class Widget
	{
	public:
		Widget(Point pXY, int pWidth, int pHeight, const std::string& pLabel, Callback pCallback);

		virtual void move(int pNewX, int pNewY);
		virtual void hide();
		virtual void show();
		virtual void attach(Window& pWindow) = 0;

	protected:
		Window* mWindow;		// every Widget belongs to a Window
		Fl_Widget* mFlWidget;	// connection to a FLTK Widget

		std::string mLabel;
		Point mLocation;
		Callback mCallback;
		int mWidth;
		int mHeight;

	private:
		Widget& operator=(const Widget&);	// disable copying of Widget
		Widget(const Widget&);
	};
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Widget_H