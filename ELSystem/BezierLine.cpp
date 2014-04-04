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

#include "BezierLine.h"

BezierLine::BezierLine(int nx, int ny)
{
	m_ratio = 0.6666;

	m_rectangle.top    = 0;
	m_rectangle.left   = 0;
	m_rectangle.bottom = ny;      // theorically, these two parameter can be any value, because whatever they
	m_rectangle.right  = nx;      // are, the initial Bezier line is a straight line
    
	m_points[0].x =     (m_rectangle.right - m_rectangle.left) / 2;
	m_points[0].y = 3 * (m_rectangle.bottom - m_rectangle.top)  / 4;

	m_points[1].x =     (m_rectangle.right - m_rectangle.left) / 2;
	m_points[1].y = 5 * (m_rectangle.bottom - m_rectangle.top) / 8;

	m_points[2].x =     (m_rectangle.right - m_rectangle.left) / 2;
    m_points[2].y = 3 * (m_rectangle.bottom - m_rectangle.top) / 8;

	m_points[3].x =     (m_rectangle.right - m_rectangle.left) / 2;
    m_points[3].y =     (m_rectangle.bottom - m_rectangle.top) / 4;


}

BezierLine::~BezierLine()
{


}

void BezierLine::UpRect(RECT & r, POINT* pts)  
{

	m_rectangle = r;

	for (int i=0; i<4; i++)
	{
		pts[i].x = m_points[i].x;
		pts[i].y = m_points[i].y;
	}

}

void BezierLine::UpPoints(const POINT* pts) 
{
		
	for (int i=0; i<4; i++)
	{
		m_points[i].x = pts[i].x;
		m_points[i].y = pts[i].y;
	}


}


double BezierLine::TranslatePoint(int x, int y, bool if_flip, double ang, POINT* pts) const
{
	double tempX0, tempY0, tempX1, tempY1, tempX2, tempY2, tempX3, tempY3;

	//firstly, scale the component of points

	tempX0 = double(m_points[0].x) * m_ratio;
	tempY0 = double(m_points[0].y) * m_ratio;

	tempX1 = double(m_points[1].x) * m_ratio;
	tempY1 = double(m_points[1].y) * m_ratio;

	tempX2 = double(m_points[2].x) * m_ratio;
	tempY2 = double(m_points[2].y) * m_ratio;

	tempX3 = double(m_points[3].x) * m_ratio;
	tempY3 = double(m_points[3].y) * m_ratio;

	double turn_delt = acos( ( (tempX1-tempX0)*(tempX3-tempX2) + (tempY1-tempY0)*(tempY3-tempY2) )/
		                     ( sqrt( (tempX1-tempX0)*(tempX1-tempX0) + (tempY1-tempY0)*(tempY1-tempY0) ) * 
							   sqrt( (tempX3-tempX2)*(tempX3-tempX2) + (tempY3-tempY2)*(tempY3-tempY2) ) ) ); 

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

	// check if should flip the x axis, if so, flip x asix in polar coordinate should be...
	// if we want to mirror the B relative to A, should do C=2*A-B, and C and B are symmetrical  

	if(!if_flip)	
	{

	
		radius1 = sqrt  ( tempX1*tempX1 + tempY1*tempY1 );	
		delta1  = atan2 ( tempX1, tempY1);

	
		radius2 = sqrt  ( tempX2*tempX2 + tempY2*tempY2 );	
		delta2  = atan2 ( tempX2, tempY2);

	
		radius3 = sqrt  ( tempX3*tempX3 + tempY3*tempY3 );	
		delta3  = atan2 ( tempX3, tempY3);
	}
	
	else if(if_flip)
	{	  
		radius1 = sqrt  ( tempX1*tempX1 + tempY1*tempY1 );	  
		delta1  = atan2 ( tempX1, tempY1);
		  
		radius2 = sqrt  ( tempX2*tempX2 + tempY2*tempY2 );		  
		delta2  = atan2 ( tempX2, tempY2);
		  
		radius3 = sqrt  ( tempX3*tempX3 + tempY3*tempY3 );		  
		delta3  = atan2 ( tempX3, tempY3);
      
		delta2 -= 2 * delta1;
      
		delta3 -= 2 * delta1;		
	}


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

	pts[0].x = int (tempX0);
	pts[0].y = int (tempY0);

	pts[1].x = int (tempX1);
	pts[1].y = int (tempY1);

	pts[2].x = int (tempX2);
	pts[2].y = int (tempY2);

	pts[3].x = int (tempX3);
	pts[3].y = int (tempY3);

	return turn_delt;

}

/// for animation
double BezierLine::TranslatePointAni(int x, int y, bool if_flip, double ang, POINT* pts, double ratio) const
{
	double tempX0, tempY0, tempX1, tempY1, tempX2, tempY2, tempX3, tempY3;

	//firstly, scale the component of points

	tempX0 = double(m_points[0].x) * ratio;
	tempY0 = double(m_points[0].y) * ratio;

	tempX1 = double(m_points[1].x) * ratio;
	tempY1 = double(m_points[1].y) * ratio;

	tempX2 = double(m_points[2].x) * ratio;
	tempY2 = double(m_points[2].y) * ratio;

	tempX3 = double(m_points[3].x) * ratio;
	tempY3 = double(m_points[3].y) * ratio;

	double turn_delt = acos( ( (tempX1-tempX0)*(tempX3-tempX2) + (tempY1-tempY0)*(tempY3-tempY2) )/
		                     ( sqrt( (tempX1-tempX0)*(tempX1-tempX0) + (tempY1-tempY0)*(tempY1-tempY0) ) * 
							   sqrt( (tempX3-tempX2)*(tempX3-tempX2) + (tempY3-tempY2)*(tempY3-tempY2) ) ) ); 

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

	// check if should flip the x axis, if so, flip x asix in polar coordinate should be...
	// if we want to mirror the B relative to A, should do C=2*A-B, and C and B are symmetrical  

	if(!if_flip)	
	{

	
		radius1 = sqrt  ( tempX1*tempX1 + tempY1*tempY1 );	
		delta1  = atan2 ( tempX1, tempY1);

	
		radius2 = sqrt  ( tempX2*tempX2 + tempY2*tempY2 );	
		delta2  = atan2 ( tempX2, tempY2);

	
		radius3 = sqrt  ( tempX3*tempX3 + tempY3*tempY3 );	
		delta3  = atan2 ( tempX3, tempY3);
	}
	
	else if(if_flip)
	{	  
		radius1 = sqrt  ( tempX1*tempX1 + tempY1*tempY1 );	  
		delta1  = atan2 ( tempX1, tempY1);
		  
		radius2 = sqrt  ( tempX2*tempX2 + tempY2*tempY2 );		  
		delta2  = atan2 ( tempX2, tempY2);
		  
		radius3 = sqrt  ( tempX3*tempX3 + tempY3*tempY3 );		  
		delta3  = atan2 ( tempX3, tempY3);
      
		delta2 -= 2 * delta1;
      
		delta3 -= 2 * delta1;		
	}


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

	pts[0].x = int (tempX0);
	pts[0].y = int (tempY0);

	pts[1].x = int (tempX1);
	pts[1].y = int (tempY1);

	pts[2].x = int (tempX2);
	pts[2].y = int (tempY2);

	pts[3].x = int (tempX3);
	pts[3].y = int (tempY3);

	return turn_delt;

}

/// this member function is only for debugging purpose////////

void BezierLine::PrintPoints(POINT* pts, LPCTSTR lpTitle) const
{

        TCHAR szFormatpts[] = TEXT ("%-04i %-04i %-04i %-04i %-04i %-04i %-04i %-04i"),
        szBufferpts[50];

        wsprintf (szBufferpts, szFormatpts, pts[0].x, pts[0].y,
                                            pts[1].x, pts[1].y,
									        pts[2].x, pts[2].y,
								        	pts[3].x, pts[3].y);
		MessageBox (NULL, szBufferpts,
                      lpTitle, MB_ICONINFORMATION);

}