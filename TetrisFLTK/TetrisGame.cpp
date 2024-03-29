// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "TetrisGame.h"

#include <thread>
#include <sstream>

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

		constexpr int screenMult = 26;
	}
}

// -----------------------------------------------------------------------------

FltkWrapper::TetrisGame::TetrisGame()
	: mScoreText(Point(400, 200), "Score: ")
	, mTetrisInputOptions(VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP, VK_ESCAPE, VK_SPACE)
	, mTetrisBoard(TetrisGamePrivate::tetrisGridWidth* TetrisGamePrivate::tetrisGridHeight)
	, mTetrominos(7)
	, mLines()
	, mAssets()
	, mGameTickCounter(0)
	, mNumTetrominosOnBoard(0)
	, mScore(0)
	, mCurrentTetromino(6)
	, mCurrentRotation(0)
	, mCurrentX(TetrisGamePrivate::tetrisGridWidth / 2)
	, mCurrentY(0)
	, mPieceCount(0)
	, mTetrominoFallSpeed(TetrisGamePrivate::tetrominoFallSpeed)
	, mForceTetrominoDown(false)
	, mLockRotate(false)
{
	mGreyBlock = new Fl_PNG_Image("GreyBlock.png");
	mCyanBlock = new Fl_PNG_Image("CyanBlock.png");
	mGreenBlock = new Fl_PNG_Image("GreenBlock.png");
	mNavyBlock = new Fl_PNG_Image("NavyBlock.png");
	mOrangeBlock = new Fl_PNG_Image("OrangeBlock.png");
	mPurpleBlock = new Fl_PNG_Image("PurpleBlock.png");
	mRedBlock = new Fl_PNG_Image("RedBlock.png");
	mYellowBlock = new Fl_PNG_Image("YellowBlock.png");

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
	delete mGreyBlock;
	delete mCyanBlock;
	delete mGreenBlock;
	delete mNavyBlock;
	delete mOrangeBlock;
	delete mPurpleBlock;
	delete mRedBlock;
	delete mYellowBlock;
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
	using namespace TetrisGamePrivate;

	mForceTetrominoDown = (mGameTickCounter == mTetrominoFallSpeed);

	// ---- input
	int currentKeyPress = mTetrisInputOptions.getKeyPress();

	if (currentKeyPress == mTetrisInputOptions.mLeft)
	{
		if (doesPieceFit(mCurrentTetromino, mCurrentRotation, mCurrentX - 1, mCurrentY))
		{
			mCurrentX = mCurrentX - 1;
		}
	}

	if (currentKeyPress == mTetrisInputOptions.mRight)
	{
		if (doesPieceFit(mCurrentTetromino, mCurrentRotation, mCurrentX + 1, mCurrentY))
		{
			mCurrentX = mCurrentX + 1;
		}
	}

	if (currentKeyPress == mTetrisInputOptions.mDown)
	{
		if (doesPieceFit(mCurrentTetromino, mCurrentRotation, mCurrentX, mCurrentY + 1))
		{
			mCurrentY = mCurrentY + 1;
		}
	}

	if (currentKeyPress == mTetrisInputOptions.mRotate)
	{
		if (!mLockRotate && doesPieceFit(mCurrentTetromino, mCurrentRotation + 1, mCurrentX, mCurrentY))
		{
			mCurrentRotation = mCurrentRotation + 1;
			mLockRotate = true;
		}
	}
	else
	{
		mLockRotate = false;
	}

	if (currentKeyPress == mTetrisInputOptions.mQuit)
	{
		//return true;
	}

	if (mForceTetrominoDown)
	{
		if (doesPieceFit(mCurrentTetromino, mCurrentRotation, mCurrentX, mCurrentY + 1))
		{
			++mCurrentY; // it can, so do it
		}
		else
		{
			// lock current piece in main grid
			for (int x = 0; x < 4; ++x)
			{
				for (int y = 0; y < 4; ++y)
				{
					if (mTetrominos[mCurrentTetromino][getTetrominoBlockIndexAfterRotation(x, y, mCurrentRotation)] == L'X')
					{
						mTetrisBoard[(mCurrentY + y) * tetrisGridWidth + (mCurrentX + x)] = mCurrentTetromino + 1;
					}
				}
			}

			++mPieceCount;
			if (mPieceCount % 10 == 0)
			{
				if (mTetrominoFallSpeed >= 10)
				{
					--mTetrominoFallSpeed;
				}
			}

			// check if full horizontal lines
			for (int y = 0; y < 4; ++y)
			{
				if (mCurrentY + y < tetrisGridHeight - 1)
				{
					bool fullLine = true;
					for (int x = 1; x < tetrisGridWidth - 1; ++x)
					{
						fullLine &= (mTetrisBoard[(mCurrentY + y) * tetrisGridWidth + x]) != 0;
					}

					if (fullLine)
					{
						// remove line
						for (int x = 1; x < tetrisGridWidth - 1; ++x)
						{
							mTetrisBoard[(mCurrentY + y) * tetrisGridWidth + x] = 8;
						}

						mLines.push_back(mCurrentY + y);
					}
				}
			}

			mScore += 25;
			std::stringstream newScore;
			newScore << "Score: " << mScore;
			mScoreText.setLabel(newScore.str());

			// choose next piece
			mCurrentX = tetrisGridWidth / 2;
			mCurrentY = 0;
			mCurrentRotation = 0;
			mCurrentTetromino = rand() % 7;
			//currentPiece = 0;

			// if piece does not fit
			mGameTickCounter = 0;
			bool b = doesPieceFit(mCurrentTetromino, mCurrentRotation, mCurrentX, mCurrentY);
			if (!b)
			{
				return;
			}
		}

		mGameTickCounter = 0;
	}

	//return false;
}

// -----------------------------------------------------------------------------

void FltkWrapper::TetrisGame::render()
{
	using namespace TetrisGamePrivate;
	
	// ---- draw game grid
	for (int x = 0; x < tetrisGridWidth; ++x)
	{
		int xCoord = x * screenMult;

		for (int y = 0; y < tetrisGridHeight; ++y)
		{
			int yCoord = y * screenMult;

			char index = mAssets[mTetrisBoard[y * tetrisGridWidth + x]];

			switch (index)
			{
			case '#':
				mGreyBlock->draw(xCoord, yCoord);
				break;
			case 'A':
				mCyanBlock->draw(xCoord, yCoord);
				break;
			case 'B':
				mPurpleBlock->draw(xCoord, yCoord);
				break;
			case 'C':
				mYellowBlock->draw(xCoord, yCoord);
				break;
			case 'D':
				mGreenBlock->draw(xCoord, yCoord);
				break;
			case 'E':
				mRedBlock->draw(xCoord, yCoord);
				break;
			case 'F':
				mOrangeBlock->draw(xCoord, yCoord);
				break;
			case 'G':
				mNavyBlock->draw(xCoord, yCoord);
				break;
			default:
				break;
			}
		}
	}

	// ---- draw current piece
	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			wchar_t currentT = mTetrominos[mCurrentTetromino][getTetrominoBlockIndexAfterRotation(x, y, mCurrentRotation)];
			if (currentT == L'X')
			{
				int xCoord = (mCurrentX + x) * screenMult;
				int yCoord = (mCurrentY + y) * screenMult;

				char index = mCurrentTetromino + 65;

				switch (index)
				{
				case '#':
					mGreyBlock->draw(xCoord, yCoord);
					break;
				case 'A':
					mCyanBlock->draw(xCoord, yCoord);
					break;
				case 'B':
					mPurpleBlock->draw(xCoord, yCoord);
					break;
				case 'C':
					mYellowBlock->draw(xCoord, yCoord);
					break;
				case 'D':
					mGreenBlock->draw(xCoord, yCoord);
					break;
				case 'E':
					mRedBlock->draw(xCoord, yCoord);
					break;
				case 'F':
					mOrangeBlock->draw(xCoord, yCoord);
					break;
				case 'G':
					mNavyBlock->draw(xCoord, yCoord);
					break;
				default:
					break;
				}
			}
		}
	}

	// ---- draw score
	mScoreText.draw();

	// ---- remove line if complete
	if (!mLines.empty())
	{
		this_thread::sleep_for(400ms); // delay a bit

		for (int line : mLines)
		{
			for (int x = 1; x < tetrisGridWidth - 1; ++x)
			{
				for (int y = line; y > 0; --y)
				{
					mTetrisBoard[y * tetrisGridWidth + x] = mTetrisBoard[(y - 1) * tetrisGridWidth + x];
				}

				mTetrisBoard[x] = 0;
			}
		}

		mScore += (1 << mLines.size()) * 100;

		mLines.clear();
	}
}

// -----------------------------------------------------------------------------

void FltkWrapper::TetrisGame::setupTetrisBoard()
{
	// create assets

	// cyan
	mTetrominos[0].append(L"..X.");
	mTetrominos[0].append(L"..X.");
	mTetrominos[0].append(L"..X.");
	mTetrominos[0].append(L"..X.");

	//purple
	mTetrominos[1].append(L"..X.");
	mTetrominos[1].append(L".XX.");
	mTetrominos[1].append(L"..X.");
	mTetrominos[1].append(L"....");

	// yellow
	mTetrominos[2].append(L"....");
	mTetrominos[2].append(L".XX.");
	mTetrominos[2].append(L".XX.");
	mTetrominos[2].append(L"....");

	// green
	mTetrominos[3].append(L"..X.");
	mTetrominos[3].append(L".XX.");
	mTetrominos[3].append(L".X..");
	mTetrominos[3].append(L"....");

	// red
	mTetrominos[4].append(L".X..");
	mTetrominos[4].append(L".XX.");
	mTetrominos[4].append(L"..X.");
	mTetrominos[4].append(L"....");

	// orange
	mTetrominos[5].append(L".X..");
	mTetrominos[5].append(L".X..");
	mTetrominos[5].append(L".XX.");
	mTetrominos[5].append(L"....");

	// navy
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

int FltkWrapper::TetrisGame::getTetrominoBlockIndexAfterRotation(int pX, int pY, int pR)
{
	switch (pR % 4)
	{
	case 0:
		return (pY * 4) + pX;		// 0 degrees
	case 1:
		return 12 + pY - (pX * 4);	// 90 degrees
	case 2:
		return 15 - (pY * 4) - pX;	// 180 degrees
	case 3:
		return 3 - pY + (pX * 4);	// 270 degrees
	default:
		return 0;
	}
}

// -----------------------------------------------------------------------------

bool FltkWrapper::TetrisGame::doesPieceFit(int pTetromino, int pRotation, int pPosX, int pPosY)
{
	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			// get index into piece
			int tetrominoIndex = getTetrominoBlockIndexAfterRotation(x, y, pRotation);

			// get index into main grid
			int maingridIndex = (pPosY + y) * TetrisGamePrivate::tetrisGridWidth + (pPosX + x);

			if (pPosX + x >= 0 && pPosX + x < TetrisGamePrivate::tetrisGridWidth)
			{
				if (pPosY + y >= 0 && pPosY + y < TetrisGamePrivate::tetrisGridHeight)
				{
					if (mTetrominos[pTetromino][tetrominoIndex] == L'X' && mTetrisBoard[maingridIndex] != 0)
					{
						return false;	// fail on first hit
					}
				}
			}
		}
	}
	return true;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


