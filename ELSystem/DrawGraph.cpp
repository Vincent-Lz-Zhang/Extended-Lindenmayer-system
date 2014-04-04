#include "DrawGraph.h"


COLOR DrawGraph::m_col_A = { 0,0,0,'A' } ;
COLOR DrawGraph::m_col_B = { 0,0,0,'B' } ;
COLOR DrawGraph::m_col_C = { 0,0,0,'C' } ; 
COLOR DrawGraph::m_col_D = { 0,0,0,'D' } ; 
COLOR DrawGraph::m_col_E = { 0,0,0,'E' } ; 
COLOR DrawGraph::m_col_F = { 0,0,0,'F' } ;




DrawGraph::DrawGraph(string str,int a)
{

	m_delta = a*PI/180;  // convert the unit from  degree to radian

	m_command = str;

	m_pst.nx = 0;
	m_pst.ny = 0;
    m_pst.size = PACELEN;
    m_pst.beta = 0;

}

DrawGraph::~DrawGraph()

{

}

void DrawGraph::Draw(HWND hdlg)
{
	HDC hdc;
	RECT rect;
	hdc = GetDC (hdlg) ;
    GetClientRect (hdlg, &rect) ;

	///////////////////
	/* it seems that setting mapping mode 
	  and changing the origin point must
     be located here, in Draw() function
    */

	SetMapMode (hdc, MM_LOENGLISH) ;

	SetViewportOrgEx (hdc, rect.right/2, rect.bottom * 2 / 3, NULL) ;

	int cx,cy;
	int new_x,new_y;

	for ( int i=0; i<m_command.length(); i++)
	{
		switch (m_command[i])
		{
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
			cx = m_pst.size*sin(m_pst.beta);
			cy = m_pst.size*cos(m_pst.beta);

			new_x = m_pst.nx+cx;
			new_y = m_pst.ny+cy;

			LineTo(hdc,new_x,new_y);

			MoveToEx(hdc,new_x,new_y,NULL);
  
			m_pst.nx = new_x;
			m_pst.ny = new_y;

			break;
		case 'G':
			cx = m_pst.size*sin(m_pst.beta);
			cy = m_pst.size*cos(m_pst.beta);

			new_x = m_pst.nx+cx;
			new_y = m_pst.ny+cy;

			MoveToEx(hdc,new_x,new_y,NULL);

			m_pst.nx = new_x;
			m_pst.ny = new_y;

			break;
		case '+':
			m_pst.beta += m_delta;
			break;
		case '-':
			m_pst.beta -= m_delta;
			break;
		case '[':
			m_sta_stat.push(m_pst);

			break;

		case ']':
			m_pst = m_sta_stat.top();
			m_sta_stat.pop();

			break;

		default:
			break;
		}
	}

	ReleaseDC (hdlg, hdc);

}

COLOR DrawGraph::FindCol(char c)

{
	COLOR col= { 0,0,0,'X' };

	switch(c)
	{
	case 'A':
		return m_col_A;
		break;
	case 'B':
		return m_col_B;
		break;
	case 'C':
		return m_col_C;
		break;
	case 'D':
		return m_col_D;
		break;
	case 'E':
		return m_col_E;
		break;
	case 'F':
		return m_col_F;
		break;
	default:
		return col;
		break;
	}
}



void DrawGraph::SetCol(char c, COLOR col)
{
	switch(c)
	{
	case 'A':
		m_col_A = col;
		break;
	case 'B':
		m_col_B = col;
		break;
	case 'C':
		m_col_C = col;
		break;
	case 'D':
		m_col_D = col;
		break;
	case 'E':
		m_col_E = col;
		break;
	case 'F':
		m_col_F = col;
		break;
	default:
		break;
	}
}


