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
#include "InputOptions.h"
#include "Shape.h"
#include "Text.h"

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
		void incrementGameTickCounter() { ++mGameTickCounter; }

	private:
		void setupTetrisBoard();
		int getTetrominoBlockIndexAfterRotation(int pX, int pY, int pR);
		bool doesPieceFit(int pTetromino, int pRotation, int pPosX, int pPosY);

		void update();
		void render();

		Fl_Image* mGreyBlock;
		Fl_Image* mCyanBlock;
		Fl_Image* mGreenBlock;
		Fl_Image* mNavyBlock;
		Fl_Image* mOrangeBlock;
		Fl_Image* mPurpleBlock;
		Fl_Image* mRedBlock;
		Fl_Image* mYellowBlock;

		Text mScoreText;

		InputOptions mTetrisInputOptions;
		vector<char> mTetrisBoard;
		vector<wstring> mTetrominos;
		vector<int> mLines;
		vector<char> mAssets;

		int mGameTickCounter;
		int mNumTetrominosOnBoard;
		int mScore;

		int mCurrentTetromino;
		int mCurrentRotation;
		int mCurrentX;
		int mCurrentY;
		int mPieceCount;

		int mTetrominoFallSpeed;
		bool mForceTetrominoDown;
		bool mLockRotate;
	};
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !TetrisGame_H