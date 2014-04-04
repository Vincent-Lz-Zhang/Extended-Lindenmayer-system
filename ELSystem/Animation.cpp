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
**********************************************/

#include "Animation.h"

Animation::Animation()
{
	m_pst.nx   = 0;
	m_pst.ny   = 0;
    m_pst.size = ANI_STEP;
    m_pst.beta = 0;
	m_pst.flip = false;
}


Animation::~Animation()
{
}


/*----------------------------------
so far, it can not handl scroll bar
----------------------------------*/

void Animation::DrawAni(HWND hdlg, double ratio, double angle, DrawGraph & dg_temp)  // draw animation, will be evoked 
                                                                                 // by Animation class
{
	HPEN   hPen; 
	HDC    hdc;
	RECT   rect;

	hdc = GetDC (hdlg) ;
    GetClientRect (hdlg, &rect) ;

	POINT tempt[4];

	double r;

	angle = angle * PI / 180;

	/* *********************************
	it seems that setting mapping mode 
	  and changing the origin point must
     be located here, in Draw() function
    ************************************/

	SetMapMode (hdc, MM_LOENGLISH) ;

	SetViewportOrgEx (hdc, rect.right/2, rect.bottom / 2, NULL) ;

		
	//SetWindowOrgEx(hdc, offset_x, offset_y, NULL);



	int cx,cy;
	int new_x,new_y;

	for ( int i=0; i<dg_temp.m_command.length(); i++)
	{
		switch (dg_temp.m_command[i])
		{
		case 'A':

			hPen = CreatePen (PS_SOLID, 1, dg_temp.m_col_A.rgb) ;
            SelectObject (hdc, hPen);

			r = dg_temp.m_bl_A.TranslatePointAni(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, ratio);

			PolyBezier (hdc, tempt, 4) ;

			MoveToEx (hdc, tempt[3].x, tempt[3].y, NULL);
  
			m_pst.beta += r;

			m_pst.nx = tempt[3].x;
			m_pst.ny = tempt[3].y;

			DeleteObject (hPen);

			break;

		case 'B':

			hPen = CreatePen (PS_SOLID, 1, dg_temp.m_col_B.rgb) ;
            SelectObject (hdc, hPen);

			r = dg_temp.m_bl_B.TranslatePointAni(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, ratio);

			PolyBezier (hdc, tempt, 4) ;

			MoveToEx (hdc, tempt[3].x, tempt[3].y, NULL);
  
			m_pst.beta += r;

			m_pst.nx = tempt[3].x;
			m_pst.ny = tempt[3].y;

			DeleteObject (hPen);

			break;
		case 'C':

			hPen = CreatePen (PS_SOLID, 1, dg_temp.m_col_C.rgb) ;
            SelectObject (hdc, hPen);

			r = dg_temp.m_bl_C.TranslatePointAni(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, ratio);

			PolyBezier (hdc, tempt, 4) ;

			MoveToEx (hdc, tempt[3].x, tempt[3].y, NULL);
  
			m_pst.beta += r;

			m_pst.nx = tempt[3].x;
			m_pst.ny = tempt[3].y;


			DeleteObject (hPen);

			break;
		case 'D':

			hPen = CreatePen (PS_SOLID, 1, dg_temp.m_col_D.rgb) ;
            SelectObject (hdc, hPen);

			r = dg_temp.m_bl_D.TranslatePointAni(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, ratio);

			PolyBezier (hdc, tempt, 4) ;

			MoveToEx (hdc, tempt[3].x, tempt[3].y, NULL);
  
			m_pst.beta += r;

			m_pst.nx = tempt[3].x;
			m_pst.ny = tempt[3].y;

			DeleteObject (hPen);

			break;
		case 'E':

			hPen = CreatePen (PS_SOLID, 1, dg_temp.m_col_E.rgb) ;
            SelectObject (hdc, hPen);

			r = dg_temp.m_bl_E.TranslatePointAni(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, ratio);

			PolyBezier (hdc, tempt, 4) ;

			MoveToEx (hdc, tempt[3].x, tempt[3].y, NULL);
  
			m_pst.beta += r;

			m_pst.nx = tempt[3].x;
			m_pst.ny = tempt[3].y;

			DeleteObject (hPen);

			break;
		case 'F':

			hPen = CreatePen (PS_SOLID, 1, dg_temp.m_col_F.rgb) ;
            SelectObject (hdc, hPen);

			r = dg_temp.m_bl_F.TranslatePointAni(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, ratio);

			PolyBezier (hdc, tempt, 4) ;

			MoveToEx (hdc, tempt[3].x, tempt[3].y, NULL);
  
			m_pst.beta += r;

			m_pst.nx = tempt[3].x;
			m_pst.ny = tempt[3].y;


			DeleteObject (hPen);

			break;
		case 'G':

			cx  = ratio * m_pst.size * sin(m_pst.beta);
			cy  = ratio * m_pst.size * cos(m_pst.beta);

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
			m_pst.beta += angle;
			break;
		case '-':
			m_pst.beta -= angle;
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
    ClearState();

}

void Animation::ClearState()
{
	m_pst.nx = m_pst.ny = m_pst.beta = 0;
}