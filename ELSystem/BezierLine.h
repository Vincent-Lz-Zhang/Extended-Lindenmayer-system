
#ifndef BEZIERLINE_H_
#define BEZIERLINE_H_

#include <math.h>
#include <windows.h>

typedef struct
{
	POINT p0, p1, p2, p3;

}
POINT_POSITION;


class BezierLine

{

private:

	RECT m_rectangle;
	//POINT points[4];
	POINT_POSITION m_pp;

	double m_ratio;


public:


	BezierLine(int nx=45, int ny=50);
	~BezierLine();
	POINT_POSITION UpRect(RECT &);    // receive a RECT variable, and return POINT POSITION
	void UpPoints(POINT_POSITION &);        // receive a reference to a POINT POSITION and asign it to m_pp

    double ReportAngle() const;
	POINT_POSITION TranslatePoint(int, int, double);  // receive a POINT of current point and current angle 
	                                                  // from L-System object, then update the element in 
	                                                  // POINT[], and return the variation of angle

};

#endif