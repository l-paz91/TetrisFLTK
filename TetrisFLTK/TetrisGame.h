// -----------------------------------------------------------------------------
#ifndef TetrisGame_H
#define TetrisGame_H
// -----------------------------------------------------------------------------
// 
/*
	Main class that holds the Tetris Game information

*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Image.h"

#include <vector>
#include <string>
#include <Fl/Fl_PNG_Image.H>

// -----------------------------------------------------------------------------

namespace FltkWrapper
{
	using namespace std;

	class TetrisGame
	{
	public:
		TetrisGame();

		void update();
		void render();


		Image mGreyBlock;

	};
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !TetrisGame_H