#include "DrawGraph.h"


COLOR DrawGraph::m_col_A = { RGB(0,0,0),'A' } ;
COLOR DrawGraph::m_col_B = { RGB(0,0,0),'B' } ;
COLOR DrawGraph::m_col_C = { RGB(0,0,0),'C' } ; 
COLOR DrawGraph::m_col_D = { RGB(0,0,0),'D' } ; 
COLOR DrawGraph::m_col_E = { RGB(0,0,0),'E' } ; 
COLOR DrawGraph::m_col_F = { RGB(0,0,0),'F' } ;




DrawGraph::DrawGraph(string str,int a)
{

	m_delta    = a*PI/180;  // convert the unit from  degree to radian

	m_command  = str;

	m_pst.nx   = 0;
	m_pst.ny   = 0;
    m_pst.size = PACELEN;
    m_pst.beta = 0;
	m_pst.flip = false;

}

DrawGraph::~DrawGraph()

{

}


void DrawGraph::Update(string str, int a)
{
	m_delta    = a*PI/180;  // convert the unit from  degree to radian

	m_command  = str;
}


void DrawGraph::Draw(HWND hdlg, int offset_x, int offset_y, bool bHorz, bool bVert)
{
	HPEN   hPen; 
	HDC    hdc;
	RECT   rect;

	hdc = GetDC (hdlg) ;
    GetClientRect (hdlg, &rect) ;

	POINT tempt[4];

	double r;

	///////////////////
	/* it seems that setting mapping mode 
	  and changing the origin point must
     be located here, in Draw() function
    */

	SetMapMode (hdc, MM_LOENGLISH) ;

	SetViewportOrgEx (hdc, rect.right/2, rect.bottom / 2, NULL) ;

	if(bHorz)
	{
		if(bVert)
		{
		
			SetWindowOrgEx(hdc, offset_x, offset_y, NULL);
		}
		else
		{
			SetWindowOrgEx(hdc, offset_x, 0, NULL);
		}
	}
	else if(bVert)
	{
	
		SetWindowOrgEx(hdc, 0, offset_y, NULL);
	}


	int cx,cy;
	int new_x,new_y;

	for ( int i=0; i<m_command.length(); i++)
	{
		switch (m_command[i])
		{
		case 'A':

			hPen = CreatePen (PS_SOLID, 1, m_col_A.rgb) ;
            SelectObject (hdc, hPen);

			r = m_bl_A.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);

			PolyBezier (hdc, tempt, 4) ;

			MoveToEx (hdc, tempt[3].x, tempt[3].y, NULL);
  
			m_pst.beta += r;

			m_pst.nx = tempt[3].x;
			m_pst.ny = tempt[3].y;

			DeleteObject (hPen);

			break;

		case 'B':

			hPen = CreatePen (PS_SOLID, 1, m_col_B.rgb) ;
            SelectObject (hdc, hPen);

			r = m_bl_B.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);

			PolyBezier (hdc, tempt, 4) ;

			MoveToEx (hdc, tempt[3].x, tempt[3].y, NULL);
  
			m_pst.beta += r;

			m_pst.nx = tempt[3].x;
			m_pst.ny = tempt[3].y;

			DeleteObject (hPen);

			break;
		case 'C':

			hPen = CreatePen (PS_SOLID, 1, m_col_C.rgb) ;
            SelectObject (hdc, hPen);

			r = m_bl_C.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);

			PolyBezier (hdc, tempt, 4) ;

			MoveToEx (hdc, tempt[3].x, tempt[3].y, NULL);
  
			m_pst.beta += r;

			m_pst.nx = tempt[3].x;
			m_pst.ny = tempt[3].y;


			DeleteObject (hPen);

			break;
		case 'D':

			hPen = CreatePen (PS_SOLID, 1, m_col_D.rgb) ;
            SelectObject (hdc, hPen);

			r = m_bl_D.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);

			PolyBezier (hdc, tempt, 4) ;

			MoveToEx (hdc, tempt[3].x, tempt[3].y, NULL);
  
			m_pst.beta += r;

			m_pst.nx = tempt[3].x;
			m_pst.ny = tempt[3].y;

			DeleteObject (hPen);

			break;
		case 'E':

			hPen = CreatePen (PS_SOLID, 1, m_col_E.rgb) ;
            SelectObject (hdc, hPen);

			r = m_bl_E.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);

			PolyBezier (hdc, tempt, 4) ;

			MoveToEx (hdc, tempt[3].x, tempt[3].y, NULL);
  
			m_pst.beta += r;

			m_pst.nx = tempt[3].x;
			m_pst.ny = tempt[3].y;

			DeleteObject (hPen);

			break;
		case 'F':

			hPen = CreatePen (PS_SOLID, 1, m_col_F.rgb) ;
            SelectObject (hdc, hPen);

			r = m_bl_F.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);

			PolyBezier (hdc, tempt, 4) ;

			MoveToEx (hdc, tempt[3].x, tempt[3].y, NULL);
  
			m_pst.beta += r;

			m_pst.nx = tempt[3].x;
			m_pst.ny = tempt[3].y;


			DeleteObject (hPen);

			break;
		case 'G':

			cx  = m_pst.size*sin(m_pst.beta);
			cy  = m_pst.size*cos(m_pst.beta);

			new_x = m_pst.nx+cx;
			new_y = m_pst.ny+cy;

			MoveToEx (hdc,new_x,new_y,NULL);

			m_pst.nx = new_x;
			m_pst.ny = new_y;

			break;

		case '~':
			m_pst.flip = (m_pst.flip?false:true);
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
            MoveToEx(hdc,m_pst.nx,m_pst.ny,NULL);
			break;

		default:
			break;
		}
	}

	ReleaseDC (hdlg, hdc);

}

COLOR DrawGraph::FindCol(char c)

{
	COLOR _col= { RGB(0,0,0),'X' };

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
		return _col;
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

void DrawGraph::ClearState()
{
	m_pst.nx = m_pst.ny = m_pst.beta = 0;
}
