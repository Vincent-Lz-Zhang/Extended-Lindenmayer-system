
#ifndef BEZIERLINE_H_
#define BEZIERLINE_H_

#include <math.h>
#include <windows.h>


class BezierLine

{

private:

	RECT m_rectangle;    // indicate the rectangle of a window
	POINT m_points[4];   // four points that represent a Bezier line

	double m_ratio;      // used when the window size is different from default value 


public:


	BezierLine(int nx=90, int ny=100);       // constructor, indeed 90 and 100 are the 
	                                         // size of static control in Basic Line Panel

	~BezierLine();                           // default destructor

	void UpRect(RECT &, POINT[]);            // receive a RECT variable, and update the element in POINT[]

	void UpPoints(const POINT[]);            // udpate the member points by the values in POINT[]


	double TranslatePoint(int, int, bool, 
		                  double, POINT[]);  // receive a POINT of current point and current angle 
	                                         // from L-System object, then update the element in 
	                                         // POINT[], and return the variation of angle


	//////////////////////////////////////////////////////
	// for debugging only/////////////////////////////////
	/* this method output the four points of a particular 
	   Bezier line in a MessageBox, the 2nd parameter is
	   the Title of the box
	*/////////////////////////////////////////////////////

	void PrintPoints(POINT[], LPCTSTR) const; ////////////

	//////////////////////////////////////////////////////
};

#endif