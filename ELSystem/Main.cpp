/*
  CSIT691 Independent Project 
  Extended L-System
  ZHANG Lingzhang 5th Mar 2009
  Supervisor: Prof.Rossiter
  HKUST
*/

#include <windows.h>
#include "resource.h"
#include "ELSystem.h"
#include "DrawGraph.h"
#include "ParaValidator.h"

#define ID_STATIC_AXIOM 1
#define ID_STATIC_RULES 2
#define ID_STATIC_ORDER 3
#define ID_STATIC_ANGLE 4

#define ID_EDIT_AXIOM 5
#define ID_EDIT_RULES 6
#define ID_EDIT_ORDER 7
#define ID_EDIT_ANGLE 8

#define ID_BTN_APPLY 9
#define ID_BTN_RESET 10
#define ID_BTN_CONCEAL 11

//   Global   variables

HWND hDMlesGraph;

HBRUSH hBrushWhite;      

char g_ax[3];         // axiom
char g_ru[20];        // rules string
int g_ord;            // order
char g_ordStr[4];     //
int g_ang;            // angle
char g_angStr[10];    // 

ELSystem g_elsys; 
//DrawGraph dgr("F",0);
DrawGraph g_dg_ptr;


static COLOR col_A, col_B, col_C, col_D, col_E, col_F;
///////////////////////

LRESULT CALLBACK WndProc      (HWND, UINT, WPARAM, LPARAM) ;
BOOL    CALLBACK AboutDlgProc (HWND, UINT, WPARAM, LPARAM) ;
BOOL    CALLBACK GraphDlgProc (HWND, UINT, WPARAM, LPARAM) ;
BOOL    CALLBACK ColorDlgProc (HWND, UINT, WPARAM, LPARAM) ;
BOOL    CALLBACK ColorScrDlgProc (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)

   {

     hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));   

     static TCHAR szAppName[] = TEXT ("ELSystem") ;
     MSG          msg ;
     HWND         hwnd ;
     WNDCLASS     wndclass ;
     
     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (hInstance, szAppName) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (LTGRAY_BRUSH) ;
     wndclass.lpszMenuName  = szAppName ;
     wndclass.lpszClassName = szAppName ;
     
     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"),
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }
     
     hwnd = CreateWindow (szAppName, TEXT ("Extended L-System"),
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          310, 450,
                          NULL, NULL, hInstance, NULL) ;
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ; 
     
     hDMlesGraph = CreateDialog (hInstance, TEXT ("Graphics"), 
                                  hwnd, GraphDlgProc) ;

     while (GetMessage (&msg, NULL, 0, 0))
     {
          if (hDMlesGraph == 0 || !IsDialogMessage (hDMlesGraph, &msg))
          {
               TranslateMessage (&msg) ;
               DispatchMessage  (&msg) ;
          }
     }

	 DeleteObject(hBrushWhite); 

     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static HINSTANCE hInstance ;

	 TCHAR axiom[] = TEXT ("Axiom");
	 TCHAR rule[] = TEXT ("Replacement Rules");
	 TCHAR order[] = TEXT ("Order");
	 TCHAR angle[] = TEXT ("Angle");
	 TCHAR btnApply[] = TEXT ("Apply");
	 TCHAR btnReset[] = TEXT ("Reset");
	 TCHAR btnConcl[] = TEXT ("Conceal");

	 TCHAR empty[1];
	 empty[0] = '\0';

	 static HWND hwnd_Stic_Axm, hwnd_Stic_Rule, hwnd_Stic_Ord, hwnd_Stic_Ang;
     static HWND hwnd_Edit_Axm, hwnd_Edit_Rule, hwnd_Edit_Ord, hwnd_Edit_Ang;
	 static HWND hwnd_Btn_Apply, hwnd_Btn_Reset, hwnd_Btn_Concl;

     static int   cxChar, cyChar ;

     switch (message)
     {
     case WM_CREATE :

		  cxChar = LOWORD (GetDialogBaseUnits ()) ;
          cyChar = HIWORD (GetDialogBaseUnits ()) ;

          hInstance = ((LPCREATESTRUCT) lParam)->hInstance ;

		  //////////////////////////////////////
		  // initialize the GDIs
		  /////////////////////////////

          hwnd_Stic_Axm = CreateWindow ( TEXT( "STATIC"), axiom, WS_CHILD | WS_VISIBLE,
			  cxChar, cyChar, 5 * cxChar, cyChar, 
			  hwnd, (HMENU) ID_STATIC_AXIOM, hInstance, NULL);
						
          hwnd_Edit_Axm = CreateWindow (TEXT ("edit"), NULL,
                         WS_CHILD | WS_VISIBLE |
                                   WS_BORDER | ES_LEFT ,
                         8 * cxChar, cyChar, 4*cxChar, cyChar, hwnd, (HMENU) ID_EDIT_AXIOM,
                          hInstance, NULL) ;
       
		  hwnd_Stic_Rule = CreateWindow ( TEXT( "STATIC"), rule, WS_CHILD | WS_VISIBLE,
			  cxChar, 3 * cyChar, 16 * cxChar, cyChar, 
			  hwnd, (HMENU) ID_STATIC_RULES, hInstance, NULL);		  
         
          hwnd_Edit_Rule = CreateWindow (TEXT ("edit"), NULL,
                         WS_CHILD | WS_VISIBLE |
                                   WS_BORDER | ES_LEFT ,
                         cxChar, 5 * cyChar, 30 * cxChar, cyChar, hwnd, (HMENU) ID_EDIT_RULES,
                          hInstance, NULL) ;

		  hwnd_Stic_Ord = CreateWindow ( TEXT( "STATIC"), order, WS_CHILD | WS_VISIBLE,
			  cxChar, 7 * cyChar, 5 * cxChar, cyChar, 
			  hwnd, (HMENU) ID_STATIC_ORDER, hInstance, NULL);	
		  
          hwnd_Edit_Ord = CreateWindow (TEXT ("edit"), NULL,
                         WS_CHILD | WS_VISIBLE |
                                   WS_BORDER | ES_LEFT ,
                         7 * cxChar, 7 * cyChar, 3 * cxChar, cyChar, hwnd, (HMENU) ID_EDIT_ORDER,
                          hInstance, NULL) ;     		  

		  hwnd_Stic_Ang = CreateWindow ( TEXT( "STATIC"), angle, WS_CHILD | WS_VISIBLE,
			  12 * cxChar, 7 * cyChar, 5 * cxChar, cyChar, 
			  hwnd, (HMENU) ID_STATIC_ANGLE, hInstance, NULL);		  
             
		  hwnd_Edit_Ang = CreateWindow (TEXT ("edit"), NULL,
                         WS_CHILD | WS_VISIBLE |
                                   WS_BORDER | ES_LEFT ,
                         18 * cxChar, 7 * cyChar, 4 * cxChar, cyChar, hwnd, (HMENU) ID_EDIT_ANGLE,
                          hInstance, NULL) ;

          // buttons 

		  hwnd_Btn_Apply = CreateWindow ( TEXT("button"), 
                                   btnApply,
                                   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                   14 * cxChar, 20 * cyChar,
                                   6 * cxChar, 7 * cyChar / 4,
                                   hwnd, (HMENU) ID_BTN_APPLY,
                                   hInstance, NULL) ;

		  hwnd_Btn_Reset = CreateWindow ( TEXT("button"), 
                                   btnReset,
                                   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                   21 * cxChar, 20 * cyChar,
                                   7 * cxChar, 7 * cyChar / 4,
                                   hwnd, (HMENU) ID_BTN_RESET,
                                   hInstance, NULL) ;

		  hwnd_Btn_Concl = CreateWindow ( TEXT("button"), 
                                   btnConcl,
                                   WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                                   29 * cxChar, 20 * cyChar,
                                   8 * cxChar, 7 * cyChar / 4,
                                   hwnd, (HMENU) ID_BTN_CONCEAL,
                                   hInstance, NULL) ;

		  return 0 ;

     case WM_COMMAND :
          switch (LOWORD (wParam))
          {
          case IDM_APP_ABOUT :
               DialogBox (hInstance, TEXT ("AboutBox"), hwnd, AboutDlgProc) ;
               break ;

          case IDM_EDIT_COLOR :
               DialogBox (hInstance, TEXT ("ColorBox"), hwnd, ColorDlgProc) ;
               break ;

		  case ID_BTN_APPLY :
			  
			  // retrieve the values from controls
			  GetDlgItemText (hwnd, ID_EDIT_AXIOM , g_ax, 2) ;
			  GetDlgItemText (hwnd, ID_EDIT_RULES, g_ru, 19);
			  GetDlgItemText (hwnd, ID_EDIT_ORDER, g_ordStr, 3);
			  g_ord = atoi(g_ordStr);
			  GetDlgItemText (hwnd, ID_EDIT_ANGLE, g_angStr , 4);
			  g_ang = atoi(g_angStr);
              
			  // pass the variables to ELSystem class object and generate the m_Tree

			  g_elsys.Update(g_ax, g_ru, g_ord);
			  g_elsys.Pick();
              g_elsys.Gentree();
             
			  // course the graphics window being redrawn 
			  InvalidateRect (hDMlesGraph, NULL, TRUE) ;

			  break;

		  case ID_BTN_RESET:

			  // clear the texts in controls
              SetDlgItemText(hwnd, ID_EDIT_AXIOM , empty);
              SetDlgItemText(hwnd, ID_EDIT_RULES , empty);
              SetDlgItemText(hwnd, ID_EDIT_ORDER , empty);
              SetDlgItemText(hwnd, ID_EDIT_ANGLE , empty);

			  break;
          }
          return 0 ;
          
     case WM_DESTROY :
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

BOOL CALLBACK AboutDlgProc (HWND hDlg, UINT message, 
                            WPARAM wParam, LPARAM lParam)
{
     switch (message)
     {
     case WM_INITDIALOG :
          return FALSE ;
          
     case WM_COMMAND :
          switch (LOWORD (wParam))
          {
          case IDOK :
          case IDCANCEL :
               EndDialog (hDlg, 0) ;
               return TRUE ;
          }
          break ;
     }
     return FALSE ;
}

void PaintColor(HWND hctrl, int r, int g, int b)
{

	 HBRUSH hBrush;
     HDC hdc;
     RECT rect;
     
	 InvalidateRect (hctrl, NULL, TRUE);
     UpdateWindow (hctrl);

     hdc = GetDC (hctrl);
     GetClientRect (hctrl, &rect);
     hBrush = CreateSolidBrush ( RGB(r,g,b) );
     hBrush = (HBRUSH) SelectObject (hdc, hBrush);
     

     Rectangle (hdc, rect.left, rect.top, rect.right, rect.bottom);
     
     DeleteObject (SelectObject (hdc, hBrush));
     ReleaseDC (hctrl, hdc);

}



BOOL CALLBACK ColorDlgProc (HWND hDlg, UINT message, 
                            WPARAM wParam, LPARAM lParam)
{

	static HINSTANCE hInstance ;

	PAINTSTRUCT  ps ;

	//static COLOR col_A, col_B, col_C, col_D, col_E, col_F;
    static HWND hCtrlCol_A, hCtrlCol_B, hCtrlCol_C, 
		        hCtrlCol_D, hCtrlCol_E, hCtrlCol_F;

     switch (message)
     {
		 case WM_CREATE:
          hInstance = ((LPCREATESTRUCT) lParam)->hInstance ;
		  return FALSE;
		 case WM_INITDIALOG:

			 //hInstance = ((LPCREATESTRUCT) lParam)->hInstance ;

			 hCtrlCol_A = GetDlgItem (hDlg, IDC_COLOR_A);
			 hCtrlCol_B = GetDlgItem (hDlg, IDC_COLOR_B);
			 hCtrlCol_C = GetDlgItem (hDlg, IDC_COLOR_C);
			 hCtrlCol_D = GetDlgItem (hDlg, IDC_COLOR_D);
			 hCtrlCol_E = GetDlgItem (hDlg, IDC_COLOR_E);
			 hCtrlCol_F = GetDlgItem (hDlg, IDC_COLOR_F);
			 col_A = g_dg_ptr.FindCol('A');
			 col_B = g_dg_ptr.FindCol('B');
			 col_C = g_dg_ptr.FindCol('C');
			 col_D = g_dg_ptr.FindCol('D');
             col_E = g_dg_ptr.FindCol('E');
			 col_F = g_dg_ptr.FindCol('F');
			 return FALSE;
		 case WM_COMMAND:
			 switch (LOWORD (wParam))
			 {
				 case IDOK:
					 g_dg_ptr.SetCol('A',col_A);
					 g_dg_ptr.SetCol('B',col_B);
					 g_dg_ptr.SetCol('C',col_C);
					 g_dg_ptr.SetCol('D',col_D);
					 g_dg_ptr.SetCol('E',col_E);
					 g_dg_ptr.SetCol('F',col_F);
                     EndDialog (hDlg, TRUE);
					 return TRUE;
				 case IDCANCEL:
					 EndDialog (hDlg, FALSE);               
					 return TRUE;
                 case IDC_BTN_COR_A:

					 DialogBox (hInstance, TEXT ("ColorScrollBox"), hCtrlCol_A, ColorScrDlgProc) ;             
					 return FALSE;

				 case IDC_BTN_COR_B:

					 DialogBox (hInstance, TEXT ("ColorScrollBox"), hCtrlCol_B, ColorScrDlgProc) ;             
					 return FALSE;

				 case IDC_BTN_COR_C:

					 DialogBox (hInstance, TEXT ("ColorScrollBox"), hCtrlCol_C, ColorScrDlgProc) ;             
					 return FALSE;

				 case IDC_BTN_COR_D:

					 DialogBox (hInstance, TEXT ("ColorScrollBox"), hCtrlCol_D, ColorScrDlgProc) ;             
					 return FALSE;

				 case IDC_BTN_COR_E:

					 DialogBox (hInstance, TEXT ("ColorScrollBox"), hCtrlCol_E, ColorScrDlgProc) ;             
					 return FALSE;

				 case IDC_BTN_COR_F:

					 DialogBox (hInstance, TEXT ("ColorScrollBox"), hCtrlCol_F, ColorScrDlgProc) ;             
					 return FALSE;

			 }
		 case WM_PAINT:

		
			 BeginPaint (hDlg, &ps) ;		 		
			 EndPaint (hDlg, &ps) ;   

			 PaintColor(hCtrlCol_A, col_A.r, col_A.g, col_A.b );
			 PaintColor(hCtrlCol_B, col_B.r, col_B.g, col_B.b );
			 PaintColor(hCtrlCol_C, col_C.r, col_C.g, col_C.b );
			 PaintColor(hCtrlCol_D, col_D.r, col_D.g, col_D.b );
			 PaintColor(hCtrlCol_E, col_E.r, col_E.g, col_E.b );
			 PaintColor(hCtrlCol_F, col_F.r, col_F.g, col_F.b );

			 return TRUE;
	 }

	return FALSE;
}

BOOL CALLBACK GraphDlgProc (HWND hDlg, UINT message, 
                           WPARAM wParam, LPARAM lParam)
{
    //HDC  hdc ;
    PAINTSTRUCT  ps ;
    

    static int  cxClient, cyClient ;

	switch (message)		 	
	{
     
	case WM_SIZE :

		cxClient = LOWORD (lParam) ;        
		cyClient = HIWORD (lParam) ;
		  
		return TRUE;
	 
	case WM_PAINT :
		 
		BeginPaint (hDlg, &ps) ;		 
		EndPaint (hDlg, &ps) ;		
		// draw the graphics	
		g_dg_ptr = DrawGraph(g_elsys.Report(), g_ang);			
		g_dg_ptr.Draw(hDlg);
		  
		return TRUE;		
		
	case WM_INITDIALOG :
          			
		return TRUE ;

		
	case WM_CTLCOLORDLG :          
			
		if ( (HWND) lParam  == hDlg )		  			
		{             				
			return (BOOL) hBrushWhite;		  			
		}
		 
	
	}

  return FALSE ;
}

BOOL CALLBACK ColorScrDlgProc (HWND hDlg, UINT message, 
                           WPARAM wParam, LPARAM lParam)

{

	 HWND hwndParent, hScr_Red, hScr_Green,hScr_Blue, hctrl;

	 int ictrlID, iparentID;

	 static int icolor;

	 switch (message)
     {
		      
	 case WM_INITDIALOG :

		 hScr_Red = GetDlgItem (hDlg, IDC_SCROLLBAR_RED);              
		 SetScrollRange(hScr_Red, SB_CTL, 0, 255, FALSE);              
		 SetScrollPos(hScr_Red, SB_CTL, 0, FALSE);

		 hScr_Green = GetDlgItem (hDlg, IDC_SCROLLBAR_GREEN);              
		 SetScrollRange(hScr_Green, SB_CTL, 0, 255, FALSE);              
		 SetScrollPos(hScr_Green, SB_CTL, 0, FALSE);

		 hScr_Blue = GetDlgItem (hDlg, IDC_SCROLLBAR_BLUE);              
		 SetScrollRange(hScr_Blue, SB_CTL, 0, 255, FALSE);              
		 SetScrollPos(hScr_Blue, SB_CTL, 0, FALSE);

		 return TRUE;
	 
	 case WM_COMMAND:
			 
		 switch (LOWORD (wParam))
			 
		 {
				 
		 case IDOK:

			 EndDialog (hDlg, TRUE);
					 
			 return TRUE;
				 
		 case IDCANCEL:
					 
			 EndDialog (hDlg, FALSE);               
					 
			 return TRUE;

		 }
		      		 
	case WM_HSCROLL :
         
	hctrl  = (HWND) lParam ;
          
	ictrlID = GetWindowLong(hctrl, GWL_ID);
          
    hwndParent = GetParent(hDlg) ;

    iparentID = GetWindowLong(hwndParent, GWL_ID);

          switch (LOWORD (wParam))
          {
		
			  icolor = HIWORD (wParam);

          case SB_THUMBPOSITION :
          case SB_THUMBTRACK :
			  switch(ictrlID)
                                    //= 
			  {

			  case IDC_SCROLLBAR_RED:

				  switch(iparentID)
				  {
				  case IDC_COLOR_A:
					  col_A.r = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_A.r, col_A.g, col_A.b);
					  break;
				  case IDC_COLOR_B:
					  col_B.r = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_B.r, col_B.g, col_B.b);
					  break;
				  case IDC_COLOR_C:
					  col_C.r = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_C.r, col_C.g, col_C.b);
					  break;
				  case IDC_COLOR_D:
					  col_D.r = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_D.r, col_D.g, col_D.b);
					  break;
				  case IDC_COLOR_E:
					  col_E.r = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_E.r, col_E.g, col_E.b);
					  break;
				  case IDC_COLOR_F:
					  col_F.r = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_F.r, col_F.g, col_F.b);
					  break;
				  default:
					  return FALSE;
				  }

				  break;

			  case IDC_SCROLLBAR_GREEN:
				  switch(iparentID)
				  {
				  case IDC_COLOR_A:
					  col_A.g = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_A.r, col_A.g, col_A.b);
					  break;
				  case IDC_COLOR_B:
					  col_B.g = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_B.r, col_B.g, col_B.b);
					  break;
				  case IDC_COLOR_C:
					  col_C.g = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_C.r, col_C.g, col_C.b);
					  break;
				  case IDC_COLOR_D:
					  col_D.g = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_D.r, col_D.g, col_D.b);
					  break;
				  case IDC_COLOR_E:
					  col_E.g = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_E.r, col_E.g, col_E.b);
					  break;
				  case IDC_COLOR_F:
					  col_F.g = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_F.r, col_F.g, col_F.b);
					  break;
				  default:
					  return FALSE;
				  }

				  break;


			  case IDC_SCROLLBAR_BLUE:
				  switch(iparentID)
				  {
				  case IDC_COLOR_A:
					  col_A.b = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_A.r, col_A.g, col_A.b);
					  break;
				  case IDC_COLOR_B:
					  col_B.b = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_B.r, col_B.g, col_B.b);
					  break;
				  case IDC_COLOR_C:
					  col_C.b = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_C.r, col_C.g, col_C.b);
					  break;
				  case IDC_COLOR_D:
					  col_D.b = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_D.r, col_D.g, col_D.b);
					  break;
				  case IDC_COLOR_E:
					  col_E.b = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_E.r, col_E.g, col_E.b);
					  break;
				  case IDC_COLOR_F:
					  col_F.b = icolor;
					  SetScrollPos(hctrl, SB_CTL, icolor, TRUE);		  
					  PaintColor(hwndParent,col_F.r, col_F.g, col_F.b);
					  break;

				  default:
					  return FALSE;
				  }

				  break;

			  default:
				  return FALSE;


			  }
               
			  break ;
          default :
               return FALSE ;
          }

       /*
          DeleteObject ((HGDIOBJ) SetClassLong (hwndParent, GCL_HBRBACKGROUND,
                              (LONG) CreateSolidBrush (
                                   RGB (iColor[0], iColor[1], iColor[2])))) ;
          
          InvalidateRect (hwndParent, NULL, TRUE) ;
*/
        //  SetScrollPos  (hctrl, SB_CTL, icolor, TRUE);
		//  PaintColor(hwndParent, );
          return TRUE ;
	 }



	 return FALSE;
}
