#include "BezierLine.h"

BezierLine::BezierLine(int nx, int ny)
{
	m_ratio = 0.6666;

	m_rectangle.top    = 0;
	m_rectangle.left   = 0;
	m_rectangle.bottom = ny;      // theorically, these two parameter can be any value, because whatever they
	m_rectangle.right  = nx;      // are, the initial Bezier line is a straight line
    
	m_pp.p0.x =     (m_rectangle.right - m_rectangle.left) / 2;
	m_pp.p0.y = 3 * (m_rectangle.bottom - m_rectangle.top) / 4;

	m_pp.p1.x =     (m_rectangle.right - m_rectangle.left) / 2;
	m_pp.p1.y = 5 * (m_rectangle.bottom - m_rectangle.top) / 8;

	m_pp.p2.x =     (m_rectangle.right - m_rectangle.left) / 2;
    m_pp.p2.y = 3 * (m_rectangle.bottom - m_rectangle.top) / 8;

	m_pp.p3.x =     (m_rectangle.right - m_rectangle.left) / 2;
    m_pp.p3.y =     (m_rectangle.bottom - m_rectangle.top) / 4;


}

BezierLine::~BezierLine()
{


}

POINT_POSITION BezierLine::UpRect(RECT & f_rect)  //
{

	m_rectangle = f_rect;
    
	m_pp.p0.x =     (m_rectangle.right - m_rectangle.left) / 2;
	m_pp.p0.y = 3 * (m_rectangle.bottom - m_rectangle.top) / 4;

	m_pp.p1.x =     (m_rectangle.right - m_rectangle.left) / 2;
	m_pp.p1.y = 5 * (m_rectangle.bottom - m_rectangle.top) / 8;

	m_pp.p2.x =     (m_rectangle.right - m_rectangle.left) / 2;
    m_pp.p2.y = 3 * (m_rectangle.bottom - m_rectangle.top) / 8;

	m_pp.p3.x =     (m_rectangle.right - m_rectangle.left) / 2;
    m_pp.p3.y =     (m_rectangle.bottom - m_rectangle.top) / 4;

	return m_pp;

}

void BezierLine::UpPoints(POINT_POSITION & f_pp)  // 'f' stands for formal
{
	/*	
	for (int i=0; i<4; i++)
	{
		points[i].x = pts[i].x;
		points[i].y = pts[i].y;
	}
*/
	m_pp = f_pp;

}

double BezierLine::ReportAngle() const
{

	double turn_delt;

	turn_delt = acos( ( (m_pp.p1.x-m_pp.p0.x)*(m_pp.p3.x-m_pp.p2.x) + (m_pp.p1.y-m_pp.p0.y)*(m_pp.p3.y-m_pp.p2.y) )/
		                     ( sqrt( (m_pp.p1.x-m_pp.p0.x)*(m_pp.p1.x-m_pp.p0.x) + (m_pp.p1.y-m_pp.p0.y)*(m_pp.p1.y-m_pp.p0.y) ) * 
							   sqrt( (m_pp.p3.x-m_pp.p2.x)*(m_pp.p3.x-m_pp.p2.x) + (m_pp.p3.y-m_pp.p2.y)*(m_pp.p3.y-m_pp.p2.y) ) ) ); 
	return turn_delt;
}


POINT_POSITION BezierLine::TranslatePoint(int x, int y, double ang)
{
	double tempX0, tempY0, tempX1, tempY1, tempX2, tempY2, tempX3, tempY3;


	POINT_POSITION temp_pp;
	//firstly, scale the component of points

	tempX0 = double(m_pp.p0.x) * m_ratio;
	tempY0 = double(m_pp.p0.y) * m_ratio;

	tempX1 = double(m_pp.p1.x) * m_ratio;
	tempY1 = double(m_pp.p1.y) * m_ratio;

	tempX2 = double(m_pp.p2.x) * m_ratio;
	tempY2 = double(m_pp.p2.y) * m_ratio;

	tempX3 = double(m_pp.p3.x) * m_ratio;
	tempY3 = double(m_pp.p3.y) * m_ratio;
/*
	double turn_delt = acos( ( (tempX1-tempX0)*(tempX3-tempX2) + (tempY1-tempY0)*(tempY3-tempY2) )/
		                     ( sqrt( (tempX1-tempX0)*(tempX1-tempX0) + (tempY1-tempY0)*(tempY1-tempY0) ) * 
							   sqrt( (tempX3-tempX2)*(tempX3-tempX2) + (tempY3-tempY2)*(tempY3-tempY2) ) ) ); 
*/
	// scendly, transform the coordinate to center

	double off_x = tempX0;
	double off_y = tempY0;

	tempX0 =   tempX0 - off_x ;
	tempY0 = -(tempY0 - off_y);

	tempX1 =   tempX1 - off_x ;
	tempY1 = -(tempY1 - off_y);

	tempX2 =   tempX2 - off_x ;
	tempY2 = -(tempY2 - off_y);

	tempX3 =   tempX3 - off_x ;
	tempY3 = -(tempY3 - off_y);


	// now, the origin is the start point, y axis is upword positive
	
	// then, transform the Cartesian coordinate to polar coordinate
	
	double radius1, delta1, radius2, delta2, radius3, delta3;

	radius1 = sqrt  ( tempX1*tempX1 + tempY1*tempY1 );
	delta1  = atan2 ( tempX1, tempY1);

	radius2 = sqrt  ( tempX2*tempX2 + tempY2*tempY2 );
	delta2  = atan2 ( tempX2, tempY2);

	radius3 = sqrt  ( tempX3*tempX3 + tempY3*tempY3 );
	delta3  = atan2 ( tempX3, tempY3);

	// now, all the points are in form of polar coordinate, 1st point's components are zero
	
	// then, put this polar coordinate in the Cartesian coordinate in L-System context, the origin 
	// should be at pt, and 0 degree's direction should be ang's direction, transform them
	
	double offset_d = ang - delta1;

	delta1  = ang;

	delta2 += offset_d;

	delta3 += offset_d;


	// now, transform this polar coordinate back to Cartesian coordinate

	tempX1 = sin(delta1) * radius1;
	tempY1 = cos(delta1) * radius1;

	tempX2 = sin(delta2) * radius2;
	tempY2 = cos(delta2) * radius2;

	tempX3 = sin(delta3) * radius3;
	tempY3 = cos(delta3) * radius3;

	// now, all the points are represented by xy components in Cartesian coordinate, and
	// the origin is pt, then, move the coordinate to (0,0)
	
	tempX0 = x;
	tempY0 = y;

	tempX1 += x;
	tempY1 += y;

	tempX2 += x;
	tempY2 += y;

	tempX3 += x;
	tempY3 += y;

	// put them into pts[]

	temp_pp.p0.x = int (tempX0);
	temp_pp.p0.y = int (tempY0);

	temp_pp.p1.x = int (tempX1);
	temp_pp.p1.y = int (tempY1);

	temp_pp.p2.x = int (tempX2);
	temp_pp.p2.y = int (tempY2);

	temp_pp.p3.x = int (tempX3);
	temp_pp.p3.y = int (tempY3);

	return temp_pp;

}