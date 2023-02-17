// -----------------------------------------------------------------------------
#ifndef TetrisWindow_H
#define TetrisWindow_H
// -----------------------------------------------------------------------------
// 
/*
	Tetris Window is the entry point to the game.

*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "BasicButton.h"
#include "Widget.h"
#include "Window.h"
#include "TetrisGame.h"

// -----------------------------------------------------------------------------

namespace FltkWrapper
{
	class TetrisWindow : public Window
	{
	public:
		TetrisWindow(Point pXY, int pWidth, int pHeight, const char* pLabel);

	private:
		//actions
		void tick();
		void restartPressed();
		void quitPressed();

		// callbacks
		static void cb_tick(Address pAddr);
		static void cb_restartB(Address, Address pAddr);
		static void cb_quitB(Address, Address pAddr);

		// objects
		TetrisGame mTetrisGame;

		BasicButton mRestartBtn;
		BasicButton mQuitBtn;
	};
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !TetrisWindow_H