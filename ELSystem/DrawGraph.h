
#ifndef DRAWGRAPH_H_
#define DRAWGRAPH_H_

#include <windows.h>
#include <math.h>


#include <stack>
#include <string>
using namespace std;

#define PI        3.14159
#define PACELEN   15
#define NUM_STACK 40
#define NUM_COLS 6

typedef struct
{

	int nx;   // x component of position
	int ny;   // y component of position
    int size;  // the length of one pace
    double beta;  // the current angle

}
STATE;

typedef struct
{

	//int r;
	//int g;
	//int b;
	COLORREF rgb;
	char index;


}
COLOR;

class DrawGraph
{
private:

/*
	struct State

	{

		int nx;   // x component of position
	    int ny;   // y component of position
    	int size;  // the length of one pace
    	int beta;  // the current angle

	} crt_state;  // the current state
*/

	STATE m_pst;

	//COLOR cols[NUM_COLS];
	static COLOR m_col_A, m_col_B, m_col_C, m_col_D, m_col_E, m_col_F;

	string m_command;

	double m_delta;

	stack<STATE> m_sta_stat; 

public:

	DrawGraph( string str="F", int a=0);
	~DrawGraph();
	void Draw(HWND hdlg);
	COLOR FindCol(char c); // get the COLOR structur by character as index
	void SetCol(char c, COLOR col);   // set the COLOR structur by character as index

};

#endif

