// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Simple Tetris Game using C++ & FLTK

*/
// https://github.com/l-paz91/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "TetrisWindow.h"

// -----------------------------------------------------------------------------

int main()
{
	using namespace FltkWrapper;

	TetrisWindow tetrisWindow(Point(0, 0), 500, 500, "Tetris Window");

	return Fl::run();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------