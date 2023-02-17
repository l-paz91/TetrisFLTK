// -----------------------------------------------------------------------------
#ifndef Point_H
#define Point_H
// -----------------------------------------------------------------------------
// 
/*
	A Point is a simple 2D co-ordinate

*/
// -----------------------------------------------------------------------------

//--INCLUDES--//


// -----------------------------------------------------------------------------

namespace FltkWrapper
{
	struct Point
	{
		Point() : mX(0), mY(0) {}

		Point(double pX, double pY) : mX(pX), mY(pY) {}

		const int asIntX() const { return int(mX); }
		const int asIntY() const { return int(mY); }

		double mX;
		double mY;
	};

	inline bool operator==(Point pA, Point pB) { return pA.mX == pB.mX && pA.mY == pB.mY; }
	inline bool operator!=(Point pA, Point pB) { return !(pA == pB); }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Point_H