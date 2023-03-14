// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Simple Tetris Game using C++ & FLTK

	Based off "Code-It-Yourself! Tetris"

	Following along with the video by javidx9 here:
	https://www.youtube.com/watch?v=8OK8_tHeCIA&t=4s&ab_channel=javidx9

	His original code is here:
	https://github.com/OneLoneCoder/Javidx9/blob/master/SimplyCode/OneLoneCoder_Tetris.cpp

	I've modified it quite a bit

	Read my dev diary here:
	https://lptcp.blogspot.com/2023/03/dev-diary-adventures-with-tetris-c.html

*/
// https://github.com/l-paz91/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "TetrisWindow.h"

// -----------------------------------------------------------------------------

int main()
{
	using namespace FltkWrapper;

	TetrisWindow tetrisWindow(Point(0, 0), 500, 600, "Tetris Window");

	return Fl::run();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------