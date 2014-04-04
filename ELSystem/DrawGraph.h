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
#ifndef DRAWGRAPH_H_
#define DRAWGRAPH_H_

#include <windows.h>
#include <math.h>
#include "BezierLine.h"

#include <stack>
#include <string>
using namespace std;

#define PI        3.14159
#define PACELEN   15
#define NUM_STACK 40
#define NUM_COLS 6

typedef struct
{

	int nx;       // x component of position
	int ny;       // y component of position
    int size;     // the length of one pace
    double beta;  // the current angle
    bool flip;    // if the x axis will be flipped
}
STATE;

typedef struct
{

	COLORREF rgb;
	char index;

}
COLOR;

class Animation;
class ParaIO;
class DrawGraph
{
private:


	STATE m_pst;         // current state


	static COLOR m_col_A, m_col_B, m_col_C,
		         m_col_D, m_col_E, m_col_F;

	string m_command;    // string of command

	double m_delta;      // angle that the direction will be changed

	stack<STATE> m_sta_stat;  // stack of current states

	double * m_ranAng;        // array of random numbers for angle  
	double * m_ranLen;        // array of random numbers for length 

public:
	
	friend class Animation;
	friend class ParaIO;

	BezierLine m_bl_A, m_bl_B, m_bl_C,          // BezierLine objects
		       m_bl_D, m_bl_E, m_bl_F;

	DrawGraph();                                // command string and angle

	void Update(string &, int);                 // the same parameters as constructor

	~DrawGraph();                               // default destructor

	RECT CheckBoundary(HWND, BOOL, BOOL);       // calculate the size of the generated graphics, used for calculating scroll
	                                            // bars' range

	void Draw(HWND, int, int, BOOL, BOOL);      // paint on the graphic dialog

	COLOR FindCol(char c) const;                // get the COLOR structur by character as index

	void SetCol(char c, COLOR col);             // set the COLOR structur by character as index

	void ClearState();                          // clear the current state information

	void GenRandomA(int, int);                  // generate the random number array for angle, length of array and maximum
	void GenRandomL(int, int);                  // generate the random number array for length ratio, length of array and maximum
 
	void ClearDyAryA();                         // free the dynamic array's memory
	void ClearDyAryL();                         // free the dynamic array's memory
};

#endif

