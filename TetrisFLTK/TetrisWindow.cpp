// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "TetrisWindow.h"

// -----------------------------------------------------------------------------

FltkWrapper::TetrisWindow::TetrisWindow(Point pXY, int pWidth, int pHeight, const char* pLabel)
	: Window(pXY, pWidth, pHeight, pLabel)
	, mRestartBtn(Point(double(getWidth()) - 80, 0), 70, 20, "Restart", cb_restartB)
	, mQuitBtn(Point(double(getWidth()) - 80, 40), 70, 20, "Quit", cb_quitB)
{
	attach(mRestartBtn);
	attach(mQuitBtn);

	attach(mTetrisGame);

	// register tick function
	Fl::add_timeout(0.05, cb_tick, (void*)this);
}

// -----------------------------------------------------------------------------

void FltkWrapper::TetrisWindow::tick()
{
	mTetrisGame.incrementGameTickCounter();
	redraw();
}

// -----------------------------------------------------------------------------

void FltkWrapper::TetrisWindow::restartPressed()
{

}

// -----------------------------------------------------------------------------

void FltkWrapper::TetrisWindow::quitPressed()
{
	hide();
}

// -----------------------------------------------------------------------------

void FltkWrapper::TetrisWindow::cb_tick(Address pAddr)
{
	static_cast<TetrisWindow*>(pAddr)->tick();
	Fl::repeat_timeout(0.05, cb_tick, (void*)pAddr);
}

// -----------------------------------------------------------------------------

void FltkWrapper::TetrisWindow::cb_restartB(Address, Address pAddr)
{

}

// -----------------------------------------------------------------------------

void FltkWrapper::TetrisWindow::cb_quitB(Address, Address pAddr)
{
	static_cast<TetrisWindow*>(pAddr)->quitPressed();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


