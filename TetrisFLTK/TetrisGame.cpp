// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "TetrisGame.h"

// -----------------------------------------------------------------------------

namespace
{
	namespace TetrisGamePrivate
	{
		constexpr int tetrisGridWidth = 12;
		constexpr int tetrisGridHeight = 22;
		constexpr int tetrominoFallSpeed = 20;
		constexpr int screenWidth = 120;
		constexpr int screenHeight = 30;
	}
}

// -----------------------------------------------------------------------------

FltkWrapper::TetrisGame::TetrisGame()
	//: mGreyBlock(Point(0, 0), 26, 26, "GreyBlock.png")
	: mTetrisBoard(TetrisGamePrivate::tetrisGridWidth* TetrisGamePrivate::tetrisGridHeight)
	, mTetrominos(7)
	, mLines()
{
	mGreyBlock2 = new Fl_PNG_Image("GreyBlock.png");

	mAssets.push_back(' ');
	mAssets.push_back('A');
	mAssets.push_back('B');
	mAssets.push_back('C');
	mAssets.push_back('D');
	mAssets.push_back('E');
	mAssets.push_back('F');
	mAssets.push_back('G');
	mAssets.push_back('=');
	mAssets.push_back('#');

	setupTetrisBoard();
}

// -----------------------------------------------------------------------------

FltkWrapper::TetrisGame::~TetrisGame()
{
	delete mGreyBlock2;
}

// -----------------------------------------------------------------------------

void FltkWrapper::TetrisGame::draw()
{
	update();
	render();
}

// -----------------------------------------------------------------------------

void FltkWrapper::TetrisGame::update()
{

}

// -----------------------------------------------------------------------------

void FltkWrapper::TetrisGame::render()
{
	using namespace TetrisGamePrivate;

	// ---- draw game grid
	for (int x = 0; x < tetrisGridWidth; ++x)
	{
		for (int y = 0; y < tetrisGridHeight; ++y)
		{
			if (mAssets[mTetrisBoard[y * tetrisGridWidth + x]] == '#')
			{
				mGreyBlock2->draw(x*26, y*26);
			}
		}
	}
}

// -----------------------------------------------------------------------------

void FltkWrapper::TetrisGame::setupTetrisBoard()
{
	// create assets
	mTetrominos[0].append(L"..X.");
	mTetrominos[0].append(L"..X.");
	mTetrominos[0].append(L"..X.");
	mTetrominos[0].append(L"..X.");

	mTetrominos[1].append(L"..X.");
	mTetrominos[1].append(L".XX.");
	mTetrominos[1].append(L"..X.");
	mTetrominos[1].append(L"....");

	mTetrominos[2].append(L"....");
	mTetrominos[2].append(L".XX.");
	mTetrominos[2].append(L".XX.");
	mTetrominos[2].append(L"....");

	mTetrominos[3].append(L"..X.");
	mTetrominos[3].append(L".XX.");
	mTetrominos[3].append(L".X..");
	mTetrominos[3].append(L"....");

	mTetrominos[4].append(L".X..");
	mTetrominos[4].append(L".XX.");
	mTetrominos[4].append(L"..X.");
	mTetrominos[4].append(L"....");

	mTetrominos[5].append(L".X..");
	mTetrominos[5].append(L".X..");
	mTetrominos[5].append(L".XX.");
	mTetrominos[5].append(L"....");

	mTetrominos[6].append(L"..X.");
	mTetrominos[6].append(L"..X.");
	mTetrominos[6].append(L".XX.");
	mTetrominos[6].append(L"....");

	using namespace TetrisGamePrivate;

	for (int x = 0; x < tetrisGridWidth; ++x)
	{
		for (int y = 0; y < tetrisGridHeight; ++y)
		{
			// set all grid spaces to 0 unless it's grid boundaries, then set it to 9
			mTetrisBoard[y * tetrisGridWidth + x] = (x == 0 || x == tetrisGridWidth - 1 || y == tetrisGridHeight - 1) ? 9 : 0;
		}
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


