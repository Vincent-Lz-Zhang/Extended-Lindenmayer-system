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

#include "DrawGraph.h"
#include   <cstdlib>    
#include   <ctime>

COLOR DrawGraph::m_col_A = { RGB(0,0,0),'A' } ;
COLOR DrawGraph::m_col_B = { RGB(0,0,0),'B' } ;
COLOR DrawGraph::m_col_C = { RGB(0,0,0),'C' } ; 
COLOR DrawGraph::m_col_D = { RGB(0,0,0),'D' } ; 
COLOR DrawGraph::m_col_E = { RGB(0,0,0),'E' } ; 
COLOR DrawGraph::m_col_F = { RGB(0,0,0),'F' } ;

DrawGraph::DrawGraph()
{

	m_deltaL    = 0;  // convert the unit from  degree to radian
    m_deltaR    = 0;
	//m_command  = str;

	m_pst.nx   = 0;
	m_pst.ny   = 0;
    m_pst.size = PACELEN;
    m_pst.beta = 0;
	m_pst.flip = false;

}

DrawGraph::~DrawGraph()
{
	ClearDyAryA();
	ClearDyAryL();
}


void DrawGraph::Update(string &str, int l, int r)
{
	m_deltaL    = l*PI/180;  // convert the unit from  degree to radian
	m_deltaR    = r*PI/180;  // convert the unit from  degree to radian

	m_command  = str;
}

RECT DrawGraph::CheckBoundary(HWND hdlg, BOOL fRanA, BOOL fRanL)
{

	HDC    hdc;
	RECT   rect;

	POINT TLBR[2];

	TLBR[0].x = TLBR[0].y = TLBR[1].x = TLBR[1].y = 0;

	hdc = GetDC (hdlg) ;

    GetClientRect (hdlg, &rect) ;

	POINT tempt[4];

	double r;

	SetMapMode (hdc, MM_LOENGLISH) ;

	SetViewportOrgEx (hdc, rect.right/2, rect.bottom / 2, NULL) ;

	int cx,cy;
	int new_x,new_y;

	int index_Ang = 0;
    int index_Len = 0;

	if(fRanA)
	{
		if(fRanL)
		{
			for ( int i=0; i<m_command.length(); i++)	
			{		
				switch (m_command[i])	
				{	
				case 'A':
		
					r = m_bl_A.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;
  		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);         
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'B':
		
					r = m_bl_B.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;
  		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);          
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'C':
		
					r = m_bl_C.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);       
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'D':
		
					r = m_bl_D.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);           
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'E':
		
					r = m_bl_E.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);         
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'F':
		
					r = m_bl_F.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
					
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);           
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'G':
		
					cx  = m_pst.size*sin(m_pst.beta);		
					cy  = m_pst.size*cos(m_pst.beta);
		
					new_x = m_pst.nx+cx;		
					new_y = m_pst.ny+cy;
		
					m_pst.nx = new_x;		
					m_pst.ny = new_y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);        
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case '~':
		
					m_pst.flip = (m_pst.flip?false:true);
		
					break;
	
				case '+':
		
					m_pst.beta += (m_deltaR * (1 + m_ranAng[index_Ang]) );
					index_Ang++;
		
					break;
	
				case '-':
		
					m_pst.beta -= (m_deltaL * (1 + m_ranAng[index_Ang]) );		
					index_Ang++;
		
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
		
				} // end of switch	
			} // end of for
		}
		else
		{	
			for ( int i=0; i<m_command.length(); i++)	
			{		
				switch (m_command[i])	
				{	
				case 'A':
		
					r = m_bl_A.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);
  		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);         
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'B':
		
					r = m_bl_B.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);
  		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);          
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'C':
		
					r = m_bl_C.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);       
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'D':
		
					r = m_bl_D.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);           
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'E':
		
					r = m_bl_E.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);         
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'F':
		
					r = m_bl_F.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
					
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);           
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'G':
		
					cx  = m_pst.size*sin(m_pst.beta);		
					cy  = m_pst.size*cos(m_pst.beta);
		
					new_x = m_pst.nx+cx;		
					new_y = m_pst.ny+cy;
		
					m_pst.nx = new_x;		
					m_pst.ny = new_y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);        
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case '~':
		
					m_pst.flip = (m_pst.flip?false:true);
		
					break;
	
				case '+':
		
					m_pst.beta += (m_deltaR * (1 + m_ranAng[index_Ang]) );
					index_Ang++;
		
					break;
	
				case '-':
		
					m_pst.beta -= (m_deltaL * (1 + m_ranAng[index_Ang]) );		
					index_Ang++;
		
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
		
				} // end of switch	
			} // end of for
		} // end of else
	} // end of if angle is random 
	else
	{
		if(fRanL)
		{
			for ( int i=0; i<m_command.length(); i++)	
			{		
				switch (m_command[i])	
				{	
				case 'A':
		
					r = m_bl_A.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;
  		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);         
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'B':
		
					r = m_bl_B.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;
  		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);          
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'C':
		
					r = m_bl_C.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);       
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'D':
		
					r = m_bl_D.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);           
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'E':
		
					r = m_bl_E.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);         
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'F':
		
					r = m_bl_F.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
					
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);           
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'G':
		
					cx  = m_pst.size*sin(m_pst.beta);		
					cy  = m_pst.size*cos(m_pst.beta);
		
					new_x = m_pst.nx+cx;		
					new_y = m_pst.ny+cy;
		
					m_pst.nx = new_x;		
					m_pst.ny = new_y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);        
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case '~':
		
					m_pst.flip = (m_pst.flip?false:true);
		
					break;
	
				case '+':
		
					m_pst.beta += m_deltaR;
		
					break;
	
				case '-':
		
					m_pst.beta -= m_deltaL;		
		
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
		
				} // end of switch	
			} // end of for
		}
		else
		{
			for ( int i=0; i<m_command.length(); i++)	
			{		
				switch (m_command[i])	
				{	
				case 'A':
		
					r = m_bl_A.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);
  		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);         
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'B':
		
					r = m_bl_B.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);
  		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);          
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'C':
		
					r = m_bl_C.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);       
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'D':
		
					r = m_bl_D.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);           
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'E':
		
					r = m_bl_E.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);         
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'F':
		
					r = m_bl_F.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);
		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
					
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);           
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case 'G':
		
					cx  = m_pst.size*sin(m_pst.beta);		
					cy  = m_pst.size*cos(m_pst.beta);
		
					new_x = m_pst.nx+cx;		
					new_y = m_pst.ny+cy;
		
					m_pst.nx = new_x;		
					m_pst.ny = new_y;
		
					TLBR[0].x = min(TLBR[0].x,m_pst.nx);        
					TLBR[0].y = max(TLBR[0].y,m_pst.ny);
		
					TLBR[1].x = max(TLBR[1].x,m_pst.nx);		
					TLBR[1].y = min(TLBR[1].y,m_pst.ny);
		
					break;
	
				case '~':
		
					m_pst.flip = (m_pst.flip?false:true);
		
					break;
	
				case '+':
		
					m_pst.beta += m_deltaR;
		
					break;
	
				case '-':
		
					m_pst.beta -= m_deltaL;		
		
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
		
				} // end of switch	
			} // end of for
		} // end of else, not random for length 
	} // end of else, not random for angle

	LPtoDP(hdc,TLBR,2);

	ReleaseDC (hdlg, hdc);

    ClearState();

    RECT MaxRect;

	MaxRect.left = TLBR[0].x;
	MaxRect.right = TLBR[1].x;
	MaxRect.top = TLBR[0].y;
	MaxRect.bottom = TLBR[1].y;

	return MaxRect;

}

void DrawGraph::Draw(HWND hdlg, int offset_x, int offset_y, BOOL fRanA, BOOL fRanL)
{
	HPEN   hPen; 
	HDC    hdc;
	RECT   rect;

	hdc = GetDC (hdlg) ;
    GetClientRect (hdlg, &rect) ;

	POINT tempt[4];

	double r;

	///-------------------------------////
	/* *********************************
	it seems that setting mapping mode 
	  and changing the origin point must
     be located here, in Draw() function
    ************************************/

	SetMapMode (hdc, MM_LOENGLISH) ;

	SetViewportOrgEx (hdc, rect.right/2, rect.bottom / 2, NULL) ;

		
	SetWindowOrgEx(hdc, offset_x, offset_y, NULL);

    int index_Ang = 0;
	int index_Len = 0;

	int cx,cy;
	int new_x,new_y;

	if(fRanA)
	{
		if(fRanL)
		{		 
			for ( int i=0; i<m_command.length(); i++)	
			{
				switch (m_command[i])			
				{					

				case 'A':
							
					hPen = CreatePen (PS_SOLID, 1, m_col_A.rgb) ;                
					SelectObject (hdc, hPen);
			    
					r = m_bl_A.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);			    
					index_Len++;
			    
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

					r = m_bl_B.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);               
					index_Len++;					
					
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

			    
					r = m_bl_C.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);                
					index_Len++;
			    
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
			
					r = m_bl_D.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;

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
			
					r = m_bl_E.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);            
					index_Len++;
			
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
			
					r = m_bl_F.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);           
					index_Len++;
			
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
				
					m_pst.beta += (m_deltaR * (1 + m_ranAng[index_Ang]) );			    
					index_Ang++;
			    
					break;
					
				case '-':
							
					m_pst.beta -= (m_deltaL * (1 + m_ranAng[index_Ang]) );						
					index_Ang++;
			
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
 
				} // end of switch
	      
			} // end of for
		
		} // end of second if

		else // not random for length, random for angle 	
		{			
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
		
					m_pst.beta += (m_deltaR * (1 + m_ranAng[index_Ang]) );		
					index_Ang++;
		
					break;
			
				case '-':
						
					m_pst.beta -= (m_deltaL * (1 + m_ranAng[index_Ang]) );						
					index_Ang++;			
		
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
        
				} // end of switch
	
			} // end of for
		} // end of else


	} // end of first if


	else // not random for angle
	{	
		if(fRanL) // random for length, not random for angle	
		{			
			for ( int i=0; i<m_command.length(); i++)				
			{				
				switch (m_command[i])
			
				{					
				case 'A':			
				
					hPen = CreatePen (PS_SOLID, 1, m_col_A.rgb) ;               
					SelectObject (hdc, hPen);
			    
					r = m_bl_A.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);			    
					index_Len++;
			    
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
			    
					r = m_bl_B.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);                
					index_Len++;
			    
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
			    
					r = m_bl_C.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);               
					index_Len++;
			   
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
		
					r = m_bl_D.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);        
					index_Len++;
	
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
		
					r = m_bl_E.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
          
					index_Len++;
		
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
		
					r = m_bl_F.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);         
					index_Len++;
		
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
					
					m_pst.beta += m_deltaR;		
			
					break;
				
				case '-':
					
					m_pst.beta -= m_deltaL;						
					
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
		

        
				} // end of switch
	
			} // end of for
		} // end of if 
	
		else // not random for length, not random for angle	
		{	
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
					
					m_pst.beta += m_deltaR ;			 
			
					break;		
		
				case '-':			
		
					m_pst.beta -= m_deltaL ;						
		
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
        
				} // end of switch
	
			} // end of for

		} // end of else

	} // end of else
	ReleaseDC (hdlg, hdc);
    ClearState();
}

COLOR DrawGraph::FindCol(char c) const

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

	
void DrawGraph::GenRandomA(int a, int range)
{
	m_ranAng = new double[a];
	range = min(100, range);
	srand(unsigned(time(NULL)));
	if(0==range)
	{
		for(int i=0; i<a; i++)	
		{		
			m_ranAng[i] = 0;	
		}
	}
	else
	{	
		for(int i=0; i<a; i++)	
		{		
			m_ranAng[i] = ( double(rand()%(2*range)) - range)/100;	
		}
	}
}
			
void DrawGraph::GenRandomL(int l, int range)
{
	m_ranLen = new double[l];
	range = min(100,range);
	srand(unsigned(time(NULL)));
	if(0==range)
	{
		for(int i=0; i<l; i++)	
		{		
			m_ranLen[i] = 0;	
		}
	}
	else
	{	
		for(int i=0; i<l; i++)	
		{		
			m_ranLen[i] = ( double(rand()%(2*range)) - range)/100;	
		}
	}
}

void DrawGraph::ClearDyAryA()
{
	if(m_ranAng!=NULL)
	{
		delete [] m_ranAng;
	    m_ranAng = NULL;
	}
}

void DrawGraph::ClearDyAryL()
{
	if(m_ranLen!=NULL)
	{	
		delete [] m_ranLen;
	    m_ranLen = NULL;
	}
}


void DrawGraph::Copy(HWND hdlg, BOOL fRanA, BOOL fRanL)
{

    HDC hdcMem, hdc ; 
	    
	HBRUSH hBrush;

	HPEN hPen;

	int cxBitmap, cyBitmap;

	double r;

	POINT tempt[4];

	
	HBITMAP hBmp;

	RECT rect;

    int index_Ang = 0;
	int index_Len = 0;

	int cx,cy;
	int new_x,new_y;
	
	rect=CheckBoundary(hdlg, fRanA, fRanL);

	cxBitmap = abs(rect.right - rect.left);
	cyBitmap = abs(rect.top - rect.bottom);

	rect.top = rect.left = 0;
	rect.right = 2*cxBitmap+50;
	rect.bottom = 2*cyBitmap;

	hdc = GetDC(hdlg);

	SaveDC (hdc);

	hdcMem = CreateCompatibleDC (hdc);

	hBmp = CreateCompatibleBitmap(hdc, 2*cxBitmap+50, 2*cyBitmap);

	SelectObject (hdcMem, hBmp);

	hBrush = CreateSolidBrush(RGB(255,255,255));
		 
	FillRect(hdcMem, &rect, hBrush);


    /////////////////////

	SetMapMode (hdcMem, MM_LOENGLISH);

	SetViewportOrgEx (hdcMem, abs(rect.left)+cxBitmap, abs(rect.top)+cyBitmap, NULL);


	if(fRanA)
	{
		if(fRanL)
		{		 
			for ( int i=0; i<m_command.length(); i++)	
			{
				switch (m_command[i])			
				{					

				case 'A':
							
					hPen = CreatePen (PS_SOLID, 1, m_col_A.rgb) ;                
					SelectObject (hdcMem, hPen);
			    
					r = m_bl_A.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);			    
					index_Len++;
			    
					PolyBezier (hdcMem, tempt, 4) ;
			    
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
			    
					m_pst.beta += r;
			    
					m_pst.nx = tempt[3].x;
					m_pst.ny = tempt[3].y;
			    
					DeleteObject (hPen);
			    
					break;
		    
				case 'B':
							
					hPen = CreatePen (PS_SOLID, 1, m_col_B.rgb) ;
					SelectObject (hdcMem, hPen);

					r = m_bl_B.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);               
					index_Len++;					
					
					PolyBezier (hdcMem, tempt, 4) ;
		    
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);

					m_pst.beta += r;
			  
					m_pst.nx = tempt[3].x;
					m_pst.ny = tempt[3].y;

					DeleteObject (hPen);
	   
					break;
					
				case 'C':
							
					hPen = CreatePen (PS_SOLID, 1, m_col_C.rgb) ;                
					SelectObject (hdcMem, hPen);

			    
					r = m_bl_C.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);                
					index_Len++;
			    
					PolyBezier (hdcMem, tempt, 4) ;
			    
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
			    
					m_pst.beta += r;
			   
					m_pst.nx = tempt[3].x;			    
					m_pst.ny = tempt[3].y;
			    
					DeleteObject (hPen);
			    
					break;
					
				case 'D':
			
					hPen = CreatePen (PS_SOLID, 1, m_col_D.rgb) ;            
					SelectObject (hdcMem, hPen);
			
					r = m_bl_D.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
					index_Len++;

					PolyBezier (hdcMem, tempt, 4) ;
			
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
			
					m_pst.beta += r;
			
					m_pst.nx = tempt[3].x;			
					m_pst.ny = tempt[3].y;
			
					DeleteObject (hPen);
					
					break;
		
				case 'E':
			
					hPen = CreatePen (PS_SOLID, 1, m_col_E.rgb) ;            
					SelectObject (hdcMem, hPen);
			
					r = m_bl_E.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);            
					index_Len++;
			
					PolyBezier (hdcMem, tempt, 4) ;
			
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
			
					m_pst.beta += r;
			
					m_pst.nx = tempt[3].x;			
					m_pst.ny = tempt[3].y;
			
					DeleteObject (hPen);
			
					break;
					
				case 'F':
			
					hPen = CreatePen (PS_SOLID, 1, m_col_F.rgb) ;            
					SelectObject (hdcMem, hPen);
			
					r = m_bl_F.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);           
					index_Len++;
			
					PolyBezier (hdcMem, tempt, 4) ;
			
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL); 
			
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
			
					MoveToEx (hdcMem,new_x,new_y,NULL);
					
					m_pst.nx = new_x;			
					m_pst.ny = new_y;			
			
					break;

		
			
				case '~':
			
					m_pst.flip = (m_pst.flip?false:true);
			
					break;
					
				case '+':			
				
					m_pst.beta += (m_deltaR * (1 + m_ranAng[index_Ang]) );			    
					index_Ang++;
			    
					break;
					
				case '-':
							
					m_pst.beta -= (m_deltaL * (1 + m_ranAng[index_Ang]) );						
					index_Ang++;
			
				break;
		
			
				case '[':
							
					m_sta_stat.push(m_pst);			
				
					break;
			
				case ']':
							
					m_pst = m_sta_stat.top();			
					m_sta_stat.pop();          
				
					MoveToEx(hdcMem,m_pst.nx,m_pst.ny,NULL);
							
					break;
						
				default:
															
					break;        
 
				} // end of switch
	      
			} // end of for
		
		} // end of second if

		else // not random for length, random for angle 	
		{			
			for ( int i=0; i<m_command.length(); i++)	
			{				
				switch (m_command[i])			
				{									
				case 'A':			
				
					hPen = CreatePen (PS_SOLID, 1, m_col_A.rgb) ;
					SelectObject (hdcMem, hPen);
			    
					r = m_bl_A.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);			    
			    
					PolyBezier (hdcMem, tempt, 4) ;
			    
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  			    
					m_pst.beta += r;
			    
					m_pst.nx = tempt[3].x;
					m_pst.ny = tempt[3].y;
			    
					DeleteObject (hPen);
			    
					break;
		    
				case 'B':			
				
					hPen = CreatePen (PS_SOLID, 1, m_col_B.rgb) ;
					SelectObject (hdcMem, hPen);
			    
					r = m_bl_B.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);
			    
					PolyBezier (hdcMem, tempt, 4) ;
			    
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  		    
					m_pst.beta += r;
			    
					m_pst.nx = tempt[3].x;			    
					m_pst.ny = tempt[3].y;
			    
					DeleteObject (hPen);
			    
					break;		
			
				case 'C':			
				
					hPen = CreatePen (PS_SOLID, 1, m_col_C.rgb) ;          
					SelectObject (hdcMem, hPen);
			 
					r = m_bl_C.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);             
			  
					PolyBezier (hdcMem, tempt, 4) ;
			   
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  			  
					m_pst.beta += r;
		   
					m_pst.nx = tempt[3].x;			   
					m_pst.ny = tempt[3].y;
			 
					DeleteObject (hPen);
			   
					break;		
		
				case 'D':
		
					hPen = CreatePen (PS_SOLID, 1, m_col_D.rgb) ;         
					SelectObject (hdcMem, hPen);
		
					r = m_bl_D.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);       
		
					PolyBezier (hdcMem, tempt, 4) ;
		
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  		
					m_pst.beta += r;
	
					m_pst.nx = tempt[3].x;	
					m_pst.ny = tempt[3].y;
	
					DeleteObject (hPen);
	
					break;	
		
				case 'E':
		
					hPen = CreatePen (PS_SOLID, 1, m_col_E.rgb) ;     
					SelectObject (hdcMem, hPen);
		
					r = m_bl_E.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);       
		
					PolyBezier (hdcMem, tempt, 4) ;
		
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;				
					m_pst.ny = tempt[3].y;
		
					DeleteObject (hPen);
		
					break;		
		
				case 'F':
		
					hPen = CreatePen (PS_SOLID, 1, m_col_F.rgb) ;        
					SelectObject (hdcMem, hPen);
		
					r = m_bl_F.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);         
		
					PolyBezier (hdcMem, tempt, 4) ;
		
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  		
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
		
					MoveToEx (hdcMem,new_x,new_y,NULL);
		
					m_pst.nx = new_x;	
					m_pst.ny = new_y;			
		
					break;		
		
				case '~':
		
					m_pst.flip = (m_pst.flip?false:true);
		
					break;		
		
				case '+':		
		
					m_pst.beta += (m_deltaR * (1 + m_ranAng[index_Ang]) );		
					index_Ang++;
		
					break;
			
				case '-':
						
					m_pst.beta -= (m_deltaL * (1 + m_ranAng[index_Ang]) );						
					index_Ang++;			
		
					break;		
		
				case '[':			
			
					m_sta_stat.push(m_pst);			
						
					break;		
		
				case ']':			
			
					m_pst = m_sta_stat.top();			
			
					m_sta_stat.pop();         
			
					MoveToEx(hdcMem,m_pst.nx,m_pst.ny,NULL);			
			
					break;		
		
				default:
						
					break;
        
				} // end of switch
	
			} // end of for
		} // end of else


	} // end of first if


	else // not random for angle
	{	
		if(fRanL) // random for length, not random for angle	
		{			
			for ( int i=0; i<m_command.length(); i++)				
			{				
				switch (m_command[i])
			
				{					
				case 'A':			
				
					hPen = CreatePen (PS_SOLID, 1, m_col_A.rgb) ;               
					SelectObject (hdcMem, hPen);
			    
					r = m_bl_A.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);			    
					index_Len++;
			    
					PolyBezier (hdcMem, tempt, 4) ;
			    
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL); 
			   
					m_pst.beta += r;
			    
					m_pst.nx = tempt[3].x;			    
					m_pst.ny = tempt[3].y;
			    
					DeleteObject (hPen);
			    
					break;

		    
				case 'B':
							
					hPen = CreatePen (PS_SOLID, 1, m_col_B.rgb) ;               
					SelectObject (hdcMem, hPen);
			    
					r = m_bl_B.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);                
					index_Len++;
			    
					PolyBezier (hdcMem, tempt, 4) ;
			    
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
			    
					m_pst.beta += r;
			    
					m_pst.nx = tempt[3].x;			    
					m_pst.ny = tempt[3].y;
			    
					DeleteObject (hPen);
			    
					break;
					
				case 'C':			
				
					hPen = CreatePen (PS_SOLID, 1, m_col_C.rgb) ;              
					SelectObject (hdcMem, hPen);
			    
					r = m_bl_C.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);               
					index_Len++;
			   
					PolyBezier (hdcMem, tempt, 4) ;
			 
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  			 
					m_pst.beta += r;
			
					m_pst.nx = tempt[3].x;			 
					m_pst.ny = tempt[3].y;
			 
					DeleteObject (hPen);
			  
					break;		
		
				case 'D':
		
					hPen = CreatePen (PS_SOLID, 1, m_col_D.rgb) ;         
					SelectObject (hdcMem, hPen);
		
					r = m_bl_D.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);        
					index_Len++;
	
					PolyBezier (hdcMem, tempt, 4) ;
		
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					DeleteObject (hPen);			
		
					break;
				
				case 'E':
		
					hPen = CreatePen (PS_SOLID, 1, m_col_E.rgb) ;         
					SelectObject (hdcMem, hPen);
		
					r = m_bl_E.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);
          
					index_Len++;
		
					PolyBezier (hdcMem, tempt, 4) ;
	
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					DeleteObject (hPen);
		
					break;		
		
				case 'F':
		
					hPen = CreatePen (PS_SOLID, 1, m_col_F.rgb) ;         
					SelectObject (hdcMem, hPen);
		
					r = m_bl_F.TranslatePointRan(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt, m_ranLen[index_Len]);         
					index_Len++;
		
					PolyBezier (hdcMem, tempt, 4) ;
		
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  		
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
		
					MoveToEx (hdcMem,new_x,new_y,NULL);
		
					m_pst.nx = new_x;		
					m_pst.ny = new_y;
					
					break;
				
				case '~':
			
					m_pst.flip = (m_pst.flip?false:true);		
					break;		
		
				case '+':
					
					m_pst.beta += m_deltaR;		
			
					break;
				
				case '-':
					
					m_pst.beta -= m_deltaL;						
					
					break;
				
				case '[':			
			
					m_sta_stat.push(m_pst);			
					
					break;		
		
				case ']':
					
					m_pst = m_sta_stat.top();							
					m_sta_stat.pop();
            			
					MoveToEx(hdcMem,m_pst.nx,m_pst.ny,NULL);			
			
					break;
						
				default:
							
					break;
		

        
				} // end of switch
	
			} // end of for
		} // end of if 
	
		else // not random for length, not random for angle	
		{	
			for ( int i=0; i<m_command.length(); i++)	
			{				
				switch (m_command[i])
			
				{					
				case 'A':
			
				
					hPen = CreatePen (PS_SOLID, 1, m_col_A.rgb) ;
                
					SelectObject (hdcMem, hPen);
			 
					r = m_bl_A.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);			 
		
					PolyBezier (hdcMem, tempt, 4) ;
			  
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL); 
			  
					m_pst.beta += r;
			  
					m_pst.nx = tempt[3].x;			   
					m_pst.ny = tempt[3].y;
			 
					DeleteObject (hPen);
			  
					break;
		  
				case 'B':			
				
					hPen = CreatePen (PS_SOLID, 1, m_col_B.rgb) ;              
					SelectObject (hdcMem, hPen);
			  
					r = m_bl_B.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);            
			  
					PolyBezier (hdcMem, tempt, 4) ;
			  
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
			 
					m_pst.beta += r;
			  
					m_pst.nx = tempt[3].x;			  
					m_pst.ny = tempt[3].y;
			   
					DeleteObject (hPen);
			  
					break;		
		
				case 'C':
						
					hPen = CreatePen (PS_SOLID, 1, m_col_C.rgb) ;              
					SelectObject (hdcMem, hPen);
			  
					r = m_bl_C.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);            
					
					PolyBezier (hdcMem, tempt, 4) ;
			
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  		
					m_pst.beta += r;
			   
					m_pst.nx = tempt[3].x;			 
					m_pst.ny = tempt[3].y;
			
					DeleteObject (hPen);
			  
					break;
				
				case 'D':
		
					hPen = CreatePen (PS_SOLID, 1, m_col_D.rgb) ;        
					SelectObject (hdcMem, hPen);
		
					r = m_bl_D.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);        
		
					PolyBezier (hdcMem, tempt, 4) ;
		
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					DeleteObject (hPen);			
		
					break;
				
				case 'E':
		
					hPen = CreatePen (PS_SOLID, 1, m_col_E.rgb) ;         
					SelectObject (hdcMem, hPen);
		
					r = m_bl_E.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);        
		
					PolyBezier (hdcMem, tempt, 4) ;
		
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  		
					m_pst.beta += r;
		
					m_pst.nx = tempt[3].x;		
					m_pst.ny = tempt[3].y;
		
					DeleteObject (hPen);
		
					break;		
		
				case 'F':
		
					hPen = CreatePen (PS_SOLID, 1, m_col_F.rgb) ;        
					SelectObject (hdcMem, hPen);
		
					r = m_bl_F.TranslatePoint(m_pst.nx, m_pst.ny,m_pst.flip, m_pst.beta, tempt);        
		
					PolyBezier (hdcMem, tempt, 4) ;
		
					MoveToEx (hdcMem, tempt[3].x, tempt[3].y, NULL);
  		
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
		
					MoveToEx (hdcMem,new_x,new_y,NULL);
		
					m_pst.nx = new_x;		
					m_pst.ny = new_y;			
		
					break;		
		
				case '~':
		
					m_pst.flip = (m_pst.flip?false:true);
		
					break;
			
				case '+':
					
					m_pst.beta += m_deltaR ;			 
			
					break;		
		
				case '-':			
		
					m_pst.beta -= m_deltaL ;						
		
					break;		
		
				case '[':
					
					m_sta_stat.push(m_pst);
								
					break;		
		
				case ']':
					
					m_pst = m_sta_stat.top();					
					m_sta_stat.pop();
            		
					MoveToEx(hdcMem,m_pst.nx,m_pst.ny,NULL);			
		
					break;
		
				default:
						
					break;		
        
				} // end of switch
	
			} // end of for

		} // end of else

	} // end of else

    ClearState();

	////////////////////


/*
		 hBrush = CreateSolidBrush(RGB(255,255,255));
		 FillRect(hdcMem, &rect, hBrush);

		 hPen = CreatePen (PS_SOLID, 3, RGB(0,0,255)) ;
		 SelectObject (hdcMem, hPen);
		 Ellipse(hdcMem, 0,0,110,110);

		 LineTo(hdcMem,50,50);
//////*/

	OpenClipboard (hdlg);

		 
	EmptyClipboard () ;
               
	SetClipboardData (CF_BITMAP, hBmp) ;
               
	CloseClipboard () ;
		 
	DeleteObject (hBmp);
		 
	DeleteDC (hdcMem) ;     
		 
	RestoreDC (hdc, -1) ;
		 
	ReleaseDC (hdlg, hdc);
}