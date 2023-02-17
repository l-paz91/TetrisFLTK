// -----------------------------------------------------------------------------
#ifndef Shape_H
#define Shape_H
// -----------------------------------------------------------------------------
// 
/*
	Shape is an interface class to allow drawing various Fl types to a window.

	A Shape can be attached to a FltkWrapper::Window. 

	You must use FltkWrapper::Window::attach(Shape) in the constructor of your
	Window to add the Shape to the window.

	Use draw() to update the image.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//


// -----------------------------------------------------------------------------

namespace FltkWrapper
{
	class Shape
	{
	public:
		virtual void draw() = 0;
		~Shape() {}
	};
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Shape_H