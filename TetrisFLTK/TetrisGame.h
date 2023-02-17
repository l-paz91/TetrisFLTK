// -----------------------------------------------------------------------------
#ifndef TetrisGame_H
#define TetrisGame_H
// -----------------------------------------------------------------------------
// 
/*
	Main class that holds the Tetris Game information

	This tetris game is based off the console version from here:
	https://github.com/l-paz91/Tetris/tree/main/Console%20Window%20Modified

*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Image.h"
#include "Shape.h"

#include <vector>
#include <string>
#include <Fl/Fl_PNG_Image.H>

// -----------------------------------------------------------------------------

namespace FltkWrapper
{
	using namespace std;

	class TetrisGame : public Shape
	{
	public:
		TetrisGame();
		~TetrisGame();

		virtual void draw() override;

	private:
		void setupTetrisBoard();

		void update();
		void render();

		Fl_Image* mGreyBlock2;

		vector<char> mTetrisBoard;
		vector<wstring> mTetrominos;
		vector<int> mLines;
		vector<char> mAssets;
	};
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !TetrisGame_H