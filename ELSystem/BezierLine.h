/**********************************************
  CSIT691 Independent Project 
  Extended L-System
  ZHANG Lingzhang 5th Mar 2009 
  Supervisor: Prof. Rossiter
  HKUST
  Revised at 19th Mar by ZHANG Lingzhang
  Revised at 21th Mar by ZHANG Lingzhang
  Revised at 23th Mar by ZHANG Lingzhang
  Revised at 30th Mar by ZHANG Lingzhang
  Fixed by Zhang Lingzhang at 12 Apr
**********************************************/
#ifndef BEZIERLINE_H_
#define BEZIERLINE_H_

#include <math.h>
#include <windows.h>

class ParaIO;
class BezierLine

{

private:

	RECT m_rectangle;    // indicate the rectangle of a window
	POINT m_points[4];   // four points that represent a Bezier line

	double m_ratio;      // used when the window size is different from default value 


public:

    friend class ParaIO;

	BezierLine(int nx=90, int ny=100);       // constructor, indeed 90 and 100 are the 
	                                         // size of static control in Basic Line Panel

	~BezierLine();                           // default destructor

	void UpRect(RECT &, POINT[]);            // receive a RECT variable, and update the element in POINT[]

	void UpPoints(const POINT[]);            // udpate the member points by the values in POINT[]


	double TranslatePoint(int, int, bool, 
		                  double, POINT[]) const;  // receive a POINT of current point and current angle 
	                                               // from L-System object, then update the element in 
	                                               // POINT[], and return the variation of angle

	double TranslatePointAni(int, int, bool,       // used for animation
		                  double, POINT[],double) const; 

	double TranslatePointRan(int, int, bool,       // used for random offset
		                     double, POINT[], double) const;

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