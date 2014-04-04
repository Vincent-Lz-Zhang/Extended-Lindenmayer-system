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

#include <windows.h>
#include "resource.h"
#include "ELSystem.h"
#include "DrawGraph.h"
#include "ParaValidator.h"

#include <commdlg.h>
#include <math.h>

#define SCALE_FACTOR 3

//----------------------------//
// resouse identities///////////

//------- static texts -------//

#define ID_STATIC_AXIOM 1
#define ID_STATIC_RULES 2
#define ID_STATIC_ORDER 3
#define ID_STATIC_ANGLE 4

//------- edit controls -------//

#define ID_EDIT_AXIOM 5
#define ID_EDIT_RULES 6
#define ID_EDIT_ORDER 7
#define ID_EDIT_ANGLE 8

//------- buttons -------//

#define ID_BTN_APPLY 9
#define ID_BTN_RESET 10
#define ID_BTN_CONCEAL 11

////////////////////////////////

//-------------------------------------------------------------------------------------------------------//
#define WM_CON_SIZE 0x0500  // new message for graphic dialog, indicates that the apply button is hit, and 
                            // the new graphics size should be calculated to get the scroll bars' range,
                            // and then, redraw the client area in the window
//-------------------------------------------------------------------------------------------------------//
//   Global   variables ////////////////


//// handle of windows or dialogs /////
HWND   hDMlesGraph;
//-----------------------------------////
//// handle color obj
HBRUSH hBrushWhite;      
//-----------------------------------////

//// variables for L-system -------///
char g_ax[3];          // axiom
char g_ru[30];         // rules string
int  g_ord;            // order
char g_ordStr[4];      //
int  g_ang;            // angle
char g_angStr[10];     // 
///--------------------/////////////

/// the objects of classes that implement the functions //
ELSystem      g_elsys;     // object of ELSystem
DrawGraph     g_dg;        // object of DrawGraph
ParaValidator g_pv;        // object of ParaValidator
//----------------------------------------------------///

/////--------------------- for the information of Bezier lines --------------////////

POINT     g_bez_pt[4];    //

POINT     g_bez_pt_A[4];  // global point array and is scaled for BezierLine object A
POINT     g_bez_pt_B[4];  // global point array and is scaled for BezierLine object B
POINT     g_bez_pt_C[4];  // global point array and is scaled for BezierLine object C
POINT     g_bez_pt_D[4];  // global point array and is scaled for BezierLine object D
POINT     g_bez_pt_E[4];  // global point array and is scaled for BezierLine object E
POINT     g_bez_pt_F[4];  // global point array and is scaled for BezierLine object F
     
//--------------------------------------------------------------------------------///

/// color information //////////////////////////////////
static COLOR col_A, col_B, col_C, col_D, col_E, col_F;
//---------------------------------------------------///

////------------- scroll bars' information ------------//////
//int g_VertNumPos=0, g_HorzNumPos=0;  
//---------------------------------------------------///

// the size of page //

const int xUnit = 50;
const int yUnit = 50;
//////////////////////


//---------------------------------------------------------------------------------------//
//------------------------------ debugging functions -----------------------------------///

//-------------------- these functions are only for debugging purpose ------------------/////

void g_PrintPoints(POINT[], LPCTSTR);                     /////////////////////////////////  

void g_PrintRect(RECT &, LPCTSTR);                        /////////////////////////////////

void g_PrintWH(int, int, LPCTSTR);
//---------------------------------------------------------------------------------------//


//---------------------------------------------------------------------------------------//
//------------------------------- windows procedures ------------------------------------//

LRESULT CALLBACK WndProc           (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK AboutDlgProc      (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK GraphDlgProc      (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK ColorDlgProc      (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK LineDlgProc       (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK BezierDlgProc     (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK BezierLineWndProc (HWND, UINT, WPARAM, LPARAM);

//---------------------------------------------------------------------------------------//

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
   
	 //////////////////////////////////////////////////////////////
     // declare a new window class, which is the custom control  

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = BezierLineWndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = NULL ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) hBrushWhite ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = TEXT ("BezierLine") ;

     RegisterClass (&wndclass) ;

     ///----------------------------------------///--------------------

     hwnd = CreateWindow (szAppName, TEXT ("Extended L-System"),
                          WS_OVERLAPPEDWINDOW ,
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

	 TCHAR axiom[]    = TEXT ("Axiom");
	 TCHAR rule[]     = TEXT ("Replacement Rules");
	 TCHAR order[]    = TEXT ("Order");
	 TCHAR angle[]    = TEXT ("Angle");
	 TCHAR btnApply[] = TEXT ("Apply");
	 TCHAR btnReset[] = TEXT ("Reset");
	 TCHAR btnConcl[] = TEXT ("Conceal");

	 TCHAR empty[1];
	 empty[0] = '\0';

	 static HWND hwnd_Stic_Axm,  hwnd_Stic_Rule, hwnd_Stic_Ord, hwnd_Stic_Ang;
     static HWND hwnd_Edit_Axm,  hwnd_Edit_Rule, hwnd_Edit_Ord, hwnd_Edit_Ang;
	 static HWND hwnd_Btn_Apply, hwnd_Btn_Reset, hwnd_Btn_Concl;

     static int cxChar, cyChar;

     switch (message)
     {
     case WM_CREATE :

		  cxChar = LOWORD (GetDialogBaseUnits ());
          cyChar = HIWORD (GetDialogBaseUnits ());

          hInstance = ((LPCREATESTRUCT) lParam)->hInstance;

		  ///----------------------------------------////
		  // initialize the GDIs
		  //----------------------------------------//

          hwnd_Stic_Axm = CreateWindow ( TEXT( "STATIC"), 
			                      axiom, 
								  WS_CHILD | WS_VISIBLE,
			                      cxChar, cyChar, 5 * cxChar, cyChar, 
			                      hwnd, (HMENU) ID_STATIC_AXIOM,
								  hInstance, NULL);
						
          hwnd_Edit_Axm = CreateWindow ( TEXT ("edit"), 
			                      NULL, 
								  WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,           
                                  8 * cxChar, cyChar, 4*cxChar, cyChar,
								  hwnd, (HMENU) ID_EDIT_AXIOM,
                                  hInstance, NULL);
       
		  hwnd_Stic_Rule = CreateWindow ( TEXT( "STATIC"), 
			                       rule, 
								   WS_CHILD | WS_VISIBLE,
			                       cxChar, 3 * cyChar, 16 * cxChar, cyChar, 
			                       hwnd, (HMENU) ID_STATIC_RULES,
								   hInstance, NULL);		  
         
          hwnd_Edit_Rule = CreateWindow ( TEXT ("edit"),
			                       NULL, 
								   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
                                   cxChar, 5 * cyChar, 30 * cxChar, cyChar, 
								   hwnd, (HMENU) ID_EDIT_RULES,
                                   hInstance, NULL);
                                                 
		  hwnd_Stic_Ord = CreateWindow ( TEXT( "STATIC"), 
			                      order, 
								  WS_CHILD | WS_VISIBLE,
			                      cxChar, 7 * cyChar, 5 * cxChar, cyChar, 
			                      hwnd, (HMENU) ID_STATIC_ORDER, 
								  hInstance, NULL);	
		  
          hwnd_Edit_Ord = CreateWindow ( TEXT ("edit"), 
			                      NULL, 
								  WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
                                  7 * cxChar, 7 * cyChar, 3 * cxChar, cyChar,
								  hwnd, (HMENU) ID_EDIT_ORDER,
                                  hInstance, NULL); 
                              		  
		  hwnd_Stic_Ang = CreateWindow ( TEXT( "STATIC"), 
			                      angle, 
								  WS_CHILD | WS_VISIBLE,
			                      12 * cxChar, 7 * cyChar, 5 * cxChar, cyChar, 
			                      hwnd, (HMENU) ID_STATIC_ANGLE, 
								  hInstance, NULL);		  
             
		  hwnd_Edit_Ang = CreateWindow ( TEXT ("edit"), 
			                      NULL, 
								  WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,                    
                                  18 * cxChar, 7 * cyChar, 4 * cxChar, cyChar, 
								  hwnd, (HMENU) ID_EDIT_ANGLE,
                                  hInstance, NULL);

          //-------------------- buttons --------------------

		  hwnd_Btn_Apply = CreateWindow ( TEXT("button"), 
                                   btnApply,
                                   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                   14 * cxChar, 20 * cyChar,
                                   6 * cxChar, 7 * cyChar / 4,
                                   hwnd, (HMENU) ID_BTN_APPLY,
                                   hInstance, NULL);

		  hwnd_Btn_Reset = CreateWindow ( TEXT("button"), 
                                   btnReset,
                                   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                   21 * cxChar, 20 * cyChar,
                                   7 * cxChar, 7 * cyChar / 4,
                                   hwnd, (HMENU) ID_BTN_RESET,
                                   hInstance, NULL);

		  hwnd_Btn_Concl = CreateWindow ( TEXT("button"), 
                                   btnConcl,
                                   WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                                   29 * cxChar, 20 * cyChar,
                                   8 * cxChar, 7 * cyChar / 4,
                                   hwnd, (HMENU) ID_BTN_CONCEAL,
                                   hInstance, NULL);

		  return 0 ;

     case WM_COMMAND :
          switch (LOWORD (wParam))
          {
          case IDM_APP_ABOUT :
               DialogBox (hInstance, TEXT ("AboutBox"), hwnd, AboutDlgProc);
               break ;

          case IDM_EDIT_COLOR :
               DialogBox (hInstance, TEXT ("ColorBox"), hwnd, ColorDlgProc);
               break ;

          case IDM_EDIT_LINE :
               DialogBox (hInstance, TEXT ("LineBox"), hwnd, LineDlgProc);
               break ;

		  case ID_BTN_APPLY :
			  

			  if( 0==GetDlgItemText (hwnd, ID_EDIT_AXIOM, g_ax, 2)     || 
				  0==GetDlgItemText (hwnd, ID_EDIT_RULES, g_ru, 29)    || 
				  0==GetDlgItemText (hwnd, ID_EDIT_ORDER, g_ordStr, 3) ||
				  0==GetDlgItemText (hwnd, ID_EDIT_ANGLE, g_angStr, 4))
			  {
				            
				  MessageBox (NULL, TEXT ("Please type in a letter or a number!"),
                    
					  TEXT("Invalid Input"), MB_ICONINFORMATION);
			  }
			  else
			  {
			  
				  // retrieve the values from controls

			      g_ord = atoi(g_ordStr);
			      g_ang = atoi(g_angStr);
              
			      // pass the variables to ParaValidator class object and process the strings if necessary

			      g_pv.Update(g_ax, g_ru, g_ord);
			      g_pv.RulStrFilter();
			      g_pv.AxmStrFilter();

				  // clear the rules defined last time, 

				  g_elsys.FreshRules();

				  // pass the variables to ELSystem object, generate the tree string

			      g_elsys.Update(g_pv.ReturnAxm(), g_pv.ReturnRul(), g_pv.ReturnOrd());
			      g_elsys.Pick();
                  g_elsys.Gentree();

                  // send message to Graph dialog Procedue, tell it should redraw the client
				  
				  SendMessage(hDMlesGraph, WM_CON_SIZE, 0, 0);

			      // course the graphics window being redrawn 
			      //InvalidateRect (hDMlesGraph, NULL, TRUE) ;
			  }

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

void PaintColor(HWND hctrl, COLORREF col_ref)
{

	 HBRUSH hBrush;
     HDC hdc;
     RECT rect;
     
	 InvalidateRect (hctrl, NULL, TRUE);
     UpdateWindow (hctrl);

     hdc = GetDC (hctrl);
     GetClientRect (hctrl, &rect);
     hBrush = CreateSolidBrush ( col_ref );
     hBrush = (HBRUSH) SelectObject (hdc, hBrush);
     
     Rectangle (hdc, rect.left, rect.top, rect.right, rect.bottom);
     
     DeleteObject (SelectObject (hdc, hBrush));
     ReleaseDC (hctrl, hdc);

}

// dialog box procedure for color panel

BOOL CALLBACK ColorDlgProc (HWND hDlg, UINT message, 
                            WPARAM wParam, LPARAM lParam)
{

	static HINSTANCE hInstance;
    static COLORREF crCustColors[16] ;
	static CHOOSECOLOR cc;

	cc.lStructSize    = sizeof (CHOOSECOLOR) ;
	cc.hwndOwner      = NULL ;
	cc.hInstance      = NULL ;
	cc.rgbResult      = RGB (0x8D, 0x8C, 0x40) ;
    cc.lpCustColors   = crCustColors ;
    cc.Flags          = CC_RGBINIT | CC_FULLOPEN ;
    cc.lCustData      = 0 ;
    cc.lpfnHook       = NULL ;
    cc.lpTemplateName = NULL ;

	PAINTSTRUCT  ps;

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

			 col_A = g_dg.FindCol('A');
			 col_B = g_dg.FindCol('B');
			 col_C = g_dg.FindCol('C');
			 col_D = g_dg.FindCol('D');
             col_E = g_dg.FindCol('E');
			 col_F = g_dg.FindCol('F');

			 return FALSE;

		 case WM_COMMAND:
			 switch (LOWORD (wParam))
			 {
				 case IDOK:

					 g_dg.SetCol('A',col_A);
					 g_dg.SetCol('B',col_B);
					 g_dg.SetCol('C',col_C);
					 g_dg.SetCol('D',col_D);
					 g_dg.SetCol('E',col_E);
					 g_dg.SetCol('F',col_F);
                     EndDialog (hDlg, TRUE);

					 return TRUE;

				 case IDCANCEL:

					 EndDialog (hDlg, FALSE); 
					 
					 return TRUE;

                 case IDC_BTN_COR_A:
					      
                     cc.rgbResult = col_A.rgb; 
					 ChooseColor (&cc); 
					 col_A.rgb = cc.rgbResult;
					 PaintColor(hCtrlCol_A, col_A.rgb);
					 return FALSE;

				 case IDC_BTN_COR_B:

                     cc.rgbResult = col_B.rgb; 
					 ChooseColor (&cc); 
					 col_B.rgb = cc.rgbResult;
					 PaintColor(hCtrlCol_B, col_B.rgb);             
					 return FALSE;

				 case IDC_BTN_COR_C:

                     cc.rgbResult = col_C.rgb; 
					 ChooseColor (&cc); 
					 col_C.rgb = cc.rgbResult;
					 PaintColor(hCtrlCol_C, col_C.rgb);             
					 return FALSE;

				 case IDC_BTN_COR_D:

                     cc.rgbResult = col_D.rgb; 
					 ChooseColor (&cc); 
					 col_D.rgb = cc.rgbResult;
					 PaintColor(hCtrlCol_D, col_D.rgb);             
					 return FALSE;

				 case IDC_BTN_COR_E:

                     cc.rgbResult = col_E.rgb; 
					 ChooseColor (&cc); 
					 col_E.rgb = cc.rgbResult;
					 PaintColor(hCtrlCol_E, col_E.rgb);             
					 return FALSE;

				 case IDC_BTN_COR_F:

                     cc.rgbResult = col_F.rgb; 
					 ChooseColor (&cc); 
					 col_F.rgb = cc.rgbResult;
					 PaintColor(hCtrlCol_F, col_F.rgb);             
					 return FALSE;

			 }
		 case WM_PAINT:
	
			 BeginPaint (hDlg, &ps) ;		 		
			 EndPaint (hDlg, &ps) ;   

			 PaintColor(hCtrlCol_A, col_A.rgb);
			 PaintColor(hCtrlCol_B, col_B.rgb);
			 PaintColor(hCtrlCol_C, col_C.rgb);
			 PaintColor(hCtrlCol_D, col_D.rgb);
			 PaintColor(hCtrlCol_E, col_E.rgb);
			 PaintColor(hCtrlCol_F, col_F.rgb);

			 return TRUE;
	 }

	return FALSE;
}

BOOL CALLBACK GraphDlgProc (HWND hDlg, UINT message, 
                           WPARAM wParam, LPARAM lParam)
{
    HDC  hdc ;

	RECT rect;

	RECT rMax;  // this is a RECT structure that describes the edges of the graphics should be drawn

	//rMax.top = rMax.bottom = rMax.left = rMax.right = 0;

    PAINTSTRUCT  ps ;

	static int g_VertNumPos, g_HorzNumPos;  

    static int cxClient, cyClient;  

	static int iVertPos, iHorzPos;


	switch (message)		 	
	{
     
	case WM_CREATE:
   

		iVertPos = 0;			  		  
		iHorzPos = 0;		
		  
		SetScrollRange (hDlg, SB_VERT, 0, 1, FALSE) ;          				  
		SetScrollPos   (hDlg, SB_VERT, iVertPos, TRUE) ;
				  
		SetScrollRange (hDlg, SB_HORZ, 0, 1, FALSE) ;         				  
		SetScrollPos   (hDlg, SB_HORZ, iHorzPos, TRUE) ;
		
		return TRUE;

	case WM_INITDIALOG:

		hdc = GetDC(hDlg);

		GetClientRect(hDlg, &rect);

		cxClient = rect.right;
		cyClient = rect.bottom;

		ReleaseDC (hDlg, hdc);

		return TRUE;

	case WM_SIZE :


		cxClient = LOWORD (lParam);        
		cyClient = HIWORD (lParam);

		int temp_VertNumPos1, temp_HorzNumPos1;

		rMax = g_dg.CheckBoundary(hDlg);

		///////judge the horizontal size//////////////////

		if ( (rMax.left < 0) && (rMax.right > cxClient) ) // the horizontal width of graph is over the width of window
			                                              // this is detected by both sides of the window are exceeded
														  // then find the side with larger margin and use it to cal-
														  // culate the number of scroll bar's positions 
		{
			temp_HorzNumPos1 = ceil( float(max( abs(rMax.left), abs(rMax.right-cxClient) ) ) / 
				                     float(xUnit) );

			g_HorzNumPos = 2*temp_HorzNumPos1;

		    SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
		    SetScrollPos (hDlg, SB_HORZ, temp_HorzNumPos1, TRUE);
		}
		else if(rMax.left < 0)   // the width of graph is not over the width of window, but exceed left edge
		{
			temp_HorzNumPos1 = ceil( fabs( float(rMax.left) / float(xUnit) ) );

			g_HorzNumPos = 2*temp_HorzNumPos1;

		    SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
		    SetScrollPos (hDlg, SB_HORZ, temp_HorzNumPos1, TRUE);
		}
		else if(rMax.right > cxClient)  // the width of graph is not over the width of window, but exceed right edge
		{
			temp_HorzNumPos1 = ceil( float(rMax.right - cxClient/2) / float(xUnit) );

			g_HorzNumPos = 2*temp_HorzNumPos1;

		    SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
		    SetScrollPos (hDlg, SB_HORZ, temp_HorzNumPos1, TRUE);
		}

		
		//------------------------------------------------------------------//	

        //-------------------- judge the vertical size--------------------///

		if ( (rMax.top < 0) && (rMax.bottom > cyClient) ) // the horizontal height of graph is over the heighth of window
			                                              // this is detected by both sides of the window are exceeded
														  // then find the side with larger margin and use it to cal-
														  // culate the number of scroll bar's positions 
		{
			temp_VertNumPos1 = ceil( float(max( abs(rMax.top), abs(rMax.bottom-cyClient) ) ) / 
				                     float(yUnit) );

			g_VertNumPos = 2*temp_VertNumPos1;
			
		    SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
		    SetScrollPos (hDlg, SB_VERT , temp_VertNumPos1, TRUE);

		}
		else if(rMax.top < 0)   // the height of graph is not over the height of window, but exceed top edge
		{
			temp_VertNumPos1 = ceil( fabs( float(rMax.top) / float(yUnit) ) );

			g_VertNumPos = 2*temp_VertNumPos1;
			
		    SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
		    SetScrollPos (hDlg, SB_VERT , temp_VertNumPos1, TRUE);

		}
		else if(rMax.bottom > cyClient)   // the height of graph is not over the height of window, but exceed bottom edge
		{
			temp_VertNumPos1 = ceil( float(rMax.bottom - cyClient/2 ) / float(yUnit) );

			g_VertNumPos = 2*temp_VertNumPos1;
			
		    SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
		    SetScrollPos (hDlg, SB_VERT , temp_VertNumPos1, TRUE);

		}


		return TRUE;

	case WM_CON_SIZE:

		int temp_VertNumPos, temp_HorzNumPos;

		g_dg.Update(g_elsys.Report(), g_ang);

		rMax = g_dg.CheckBoundary(hDlg);

		//-------------------- judge the horizontal size --------------------///

		if ( (rMax.left < 0) && (rMax.right > cxClient) ) // the horizontal width of graph is over the width of window
			                                              // this is detected by both sides of the window are exceeded
														  // then find the side with larger margin and use it to cal-
														  // culate the number of scroll bar's positions 
		{
			temp_HorzNumPos = ceil( float(max( abs(rMax.left), abs(rMax.right-cxClient) ) ) / 
				                    float(xUnit) );

			g_HorzNumPos = 2*temp_HorzNumPos;

		    SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
		    SetScrollPos (hDlg, SB_HORZ, temp_HorzNumPos, TRUE);
		}
		else if(rMax.left < 0)   // the width of graph is not over the width of window, but exceed left edge
		{
			temp_HorzNumPos = ceil( fabs( float(rMax.left) / float(xUnit) ) );

			g_HorzNumPos = 2*temp_HorzNumPos;

		    SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
		    SetScrollPos (hDlg, SB_HORZ, temp_HorzNumPos, TRUE);
		}
		else if(rMax.right > cxClient)  // the width of graph is not over the width of window, but exceed right edge
		{
			temp_HorzNumPos = ceil( float(rMax.right - cxClient/2) / float(xUnit) );

			g_HorzNumPos = 2*temp_HorzNumPos;

		    SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
		    SetScrollPos (hDlg, SB_HORZ, temp_HorzNumPos, TRUE);
		}
			
		//--------------------------------------------------------------------------------------//	

        //-------------------- judge the vertical size ----------------------------------------//

		if ( (rMax.top < 0) && (rMax.bottom > cyClient) ) // the horizontal height of graph is over the heighth of window
			                                              // this is detected by both sides of the window are exceeded
														  // then find the side with larger margin and use it to cal-
														  // culate the number of scroll bar's positions 
		{
			temp_VertNumPos = ceil( float(max( abs(rMax.top), abs(rMax.bottom-cyClient) ) ) / 
				                    float(yUnit) );

			g_VertNumPos = 2*temp_VertNumPos;
			
		    SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
		    SetScrollPos (hDlg, SB_VERT , temp_VertNumPos, TRUE);

		}
		else if(rMax.top < 0)  // the height of graph is not over the height of window, but exceed top edge
		{
			temp_VertNumPos = ceil( fabs( float(rMax.top) / float(yUnit) ) );

			g_VertNumPos = 2*temp_VertNumPos;
			
		    SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
		    SetScrollPos (hDlg, SB_VERT , temp_VertNumPos, TRUE);

		}
		else if(rMax.bottom > cyClient)    // the height of graph is not over the height of window, but exceed bottom edge
		{
			temp_VertNumPos = ceil( float(rMax.bottom - cyClient/2 ) / float(yUnit) );

			g_VertNumPos = 2*temp_VertNumPos;
			
		    SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
		    SetScrollPos (hDlg, SB_VERT , temp_VertNumPos, TRUE);

		}
	
		InvalidateRect (hDlg, NULL, TRUE);

		return TRUE;

     case WM_VSCROLL:		

		 iVertPos = GetScrollPos (hDlg, SB_VERT);
          
		 switch (LOWORD (wParam))
          {
          case SB_TOP:
               iVertPos = 0;
               break ;
               
          case SB_BOTTOM:
               iVertPos = g_VertNumPos;
               break ;
               
          case SB_LINEUP:
               iVertPos -= 1 ;
               break ;
               
          case SB_LINEDOWN:
               iVertPos += 1 ;
               break ;
               
          case SB_PAGEUP:
               iVertPos -= 1;
               break ;

          case SB_PAGEDOWN:
               iVertPos += 1;
               break ;
               
          case SB_THUMBPOSITION:
               iVertPos = HIWORD (wParam);
               break ;
               
          default:
               break ;         
          }
 

          iVertPos = max (0, min (iVertPos, g_VertNumPos)) ;


          if (GetScrollPos (hDlg, SB_VERT) != iVertPos)
          {                    
               SetScrollPos (hDlg, SB_VERT, iVertPos, TRUE) ;
               InvalidateRect (hDlg, NULL, TRUE) ;
          }
          return TRUE ;
          
     case WM_HSCROLL:


		 iHorzPos = GetScrollPos (hDlg, SB_HORZ);


          switch (LOWORD (wParam))
          {
          case SB_LINELEFT:
               iHorzPos -= 1 ;
               break ;
               
          case SB_LINERIGHT:
               iHorzPos += 1 ;
               break ;
               
          case SB_PAGELEFT:
               iHorzPos -= 1;
               break ;
               
          case SB_PAGERIGHT:
               iHorzPos += 1;
               break ;
               
          case SB_THUMBPOSITION:
               iHorzPos = HIWORD (wParam);
               break ;
               
          default :
               break ;
          }

          iHorzPos = max (0, min (iHorzPos, g_HorzNumPos)) ;

          if (GetScrollPos (hDlg, SB_HORZ) != iHorzPos)
          {                    
               SetScrollPos (hDlg, SB_HORZ, iHorzPos, TRUE) ;
               InvalidateRect (hDlg, NULL, TRUE) ;
          }

          return TRUE ;

     case WM_KEYDOWN:

          switch (wParam)
          {
          case VK_HOME:
               SendMessage (hDlg, WM_VSCROLL, SB_TOP, 0) ;
               break ;
               
          case VK_END:
               SendMessage (hDlg, WM_VSCROLL, SB_BOTTOM, 0) ;
               break ;
               
          case VK_PRIOR:
               SendMessage (hDlg, WM_VSCROLL, SB_PAGEUP, 0) ;
               break ;
               
          case VK_NEXT:
               SendMessage (hDlg, WM_VSCROLL, SB_PAGEDOWN, 0) ;
               break ;
               
          case VK_UP:
               SendMessage (hDlg, WM_VSCROLL, SB_LINEUP, 0) ;
               break ;

          case VK_DOWN:
               SendMessage (hDlg, WM_VSCROLL, SB_LINEDOWN, 0) ;
               break ;
               
          case VK_LEFT:
               SendMessage (hDlg, WM_HSCROLL, SB_PAGEUP, 0) ;
               break ;
               
          case VK_RIGHT:
               SendMessage (hDlg, WM_HSCROLL, SB_PAGEDOWN, 0) ;
               break ;
          }          

		  return TRUE;

	case WM_PAINT :
		 
		BeginPaint (hDlg, &ps);		 
		EndPaint (hDlg, &ps);		
		
		g_dg.Draw(hDlg, ( GetScrollPos(hDlg, SB_HORZ) - g_HorzNumPos/2 ) * xUnit, 
			            ( g_VertNumPos/2 - GetScrollPos(hDlg, SB_VERT) ) * yUnit);

		return TRUE;		

		
	case WM_CTLCOLORDLG:          
			
		if ( (HWND) lParam  == hDlg )		  			
		{             				
			return (BOOL) hBrushWhite;		  			
		}		 
	
	}

  return FALSE ;
}


/// the function for drawing Bezier line

void DrawBezier (HDC hdc, POINT apt[])
{
     PolyBezier (hdc, apt, 4) ;
     
     MoveToEx (hdc, apt[0].x, apt[0].y, NULL) ;
     LineTo   (hdc, apt[1].x, apt[1].y) ;
     
     MoveToEx (hdc, apt[2].x, apt[2].y, NULL) ;
     LineTo   (hdc, apt[3].x, apt[3].y) ;
}

//----------------------------------------//

// draw Bezier line to a window

void DrawBezierToBlock(HWND hctrl, POINT apt[])
{
	HDC hdc;
     
	RECT rect;

	InvalidateRect (hctrl, NULL, TRUE);
     
	UpdateWindow (hctrl);

	hdc = GetDC(hctrl);
     
	GetClientRect (hctrl, &rect);

	SelectObject (hdc, hBrushWhite);

	Rectangle (hdc, rect.left, rect.top, rect.right, rect.bottom);
	
	PolyBezier (hdc, apt, 4);

	ReleaseDC (hctrl, hdc);
}


// dialog box procedure for basic line panel

BOOL CALLBACK LineDlgProc (HWND hDlg, UINT message, 
                           WPARAM wParam, LPARAM lParam)
{

	static HINSTANCE hInstance;
	
	RECT rect;

	HDC hdc;

	// since similar strucrur with color dialog box,
	// similar variables
    static HWND hCtrlLine_A, hCtrlLine_B, hCtrlLine_C, 
		        hCtrlLine_D, hCtrlLine_E, hCtrlLine_F;

	switch (message)    
	{
		 
	case WM_INITDIALOG:
			 
		// initialize the array for Bezier line A's points

		hCtrlLine_A = GetDlgItem (hDlg, IDC_LINE_A);
		hdc = GetDC(hCtrlLine_A);    	
		GetClientRect (hCtrlLine_A, &rect);

		g_dg.m_bl_A.UpRect(rect, g_bez_pt_A);

		// initialize the array for Bezier line B's points

		hCtrlLine_B = GetDlgItem (hDlg, IDC_LINE_B);
		hdc = GetDC(hCtrlLine_B);    	
		GetClientRect (hCtrlLine_B, &rect);

		g_dg.m_bl_B.UpRect(rect, g_bez_pt_B);

		// initialize the array for Bezier line C's points

		hCtrlLine_C = GetDlgItem (hDlg, IDC_LINE_C);
		hdc = GetDC(hCtrlLine_C);    	
		GetClientRect (hCtrlLine_C, &rect);

		g_dg.m_bl_C.UpRect(rect, g_bez_pt_C);

		// initialize the array for Bezier line D's points

		hCtrlLine_D = GetDlgItem (hDlg, IDC_LINE_D);
		hdc = GetDC(hCtrlLine_D);    	
		GetClientRect (hCtrlLine_D, &rect);

		g_dg.m_bl_D.UpRect(rect, g_bez_pt_D);

		// initialize the array for Bezier line E's points

		hCtrlLine_E = GetDlgItem (hDlg, IDC_LINE_E);
		hdc = GetDC(hCtrlLine_E);    	
		GetClientRect (hCtrlLine_E, &rect);

		g_dg.m_bl_E.UpRect(rect, g_bez_pt_E);

		// initialize the array for Bezier line F's points

		hCtrlLine_F = GetDlgItem (hDlg, IDC_LINE_F);
		hdc = GetDC(hCtrlLine_F);    	
		GetClientRect (hCtrlLine_F, &rect);

		g_dg.m_bl_F.UpRect(rect, g_bez_pt_F);
		
		return FALSE;
		 
	case WM_CREATE:
          
		hInstance = ((LPCREATESTRUCT) lParam)->hInstance;
		  
		return FALSE;

	case WM_PAINT:

		DrawBezierToBlock(hCtrlLine_A,g_bez_pt_A);
		DrawBezierToBlock(hCtrlLine_B,g_bez_pt_B);
		DrawBezierToBlock(hCtrlLine_C,g_bez_pt_C);
		DrawBezierToBlock(hCtrlLine_D,g_bez_pt_D);
		DrawBezierToBlock(hCtrlLine_E,g_bez_pt_E);
		DrawBezierToBlock(hCtrlLine_F,g_bez_pt_F);

		return FALSE;
		  
	case WM_COMMAND:
			 
		int i;

		switch (LOWORD (wParam))			 
		{
				 
		case IDOK:

			g_dg.m_bl_A.UpPoints(g_bez_pt_A);
			g_dg.m_bl_B.UpPoints(g_bez_pt_B);
			g_dg.m_bl_C.UpPoints(g_bez_pt_C);
			g_dg.m_bl_D.UpPoints(g_bez_pt_D);
			g_dg.m_bl_E.UpPoints(g_bez_pt_E);
			g_dg.m_bl_F.UpPoints(g_bez_pt_F);

			EndDialog (hDlg, TRUE);	
			
			return TRUE;
				 
		case IDCANCEL:
					 
			EndDialog (hDlg, FALSE);               
					 
			return TRUE;

		case IDC_BTN_LINE_A:

			if (DialogBox (hInstance, TEXT ("BezierBox"), hCtrlLine_A, BezierDlgProc) )
			{
				for (i=0; i<4; i++)			  
				  {				  
					  g_bez_pt_A[i].x = g_bez_pt[i].x;				  
					  g_bez_pt_A[i].y = g_bez_pt[i].y;			  
				  }
				DrawBezierToBlock(hCtrlLine_A,g_bez_pt_A);
			}
			return FALSE;

		case IDC_BTN_LINE_B:

			if (DialogBox (hInstance, TEXT ("BezierBox"), hCtrlLine_B, BezierDlgProc) )
			{					  
				for (i=0; i<4; i++)			  
				  {				  
					  g_bez_pt_B[i].x = g_bez_pt[i].x;				  
					  g_bez_pt_B[i].y = g_bez_pt[i].y;			  
				  }

				DrawBezierToBlock(hCtrlLine_B,g_bez_pt_B);
			}
			return FALSE;

		case IDC_BTN_LINE_C:

			if (DialogBox (hInstance, TEXT ("BezierBox"), hCtrlLine_C, BezierDlgProc) )
			{						  
				for (i=0; i<4; i++)			  
				  {				  
					  g_bez_pt_C[i].x = g_bez_pt[i].x;				  
					  g_bez_pt_C[i].y = g_bez_pt[i].y;			  
				  }

				DrawBezierToBlock(hCtrlLine_C,g_bez_pt_C);
			}
			return FALSE;
			
		case IDC_BTN_LINE_D:

			if (DialogBox (hInstance, TEXT ("BezierBox"), hCtrlLine_D, BezierDlgProc) )
			{				
				  for (i=0; i<4; i++)			  
				  {				  
					  g_bez_pt_D[i].x = g_bez_pt[i].x;				  
					  g_bez_pt_D[i].y = g_bez_pt[i].y;			  
				  }

				DrawBezierToBlock(hCtrlLine_D,g_bez_pt_D);
			}
			return FALSE;

		case IDC_BTN_LINE_E:

			if (DialogBox (hInstance, TEXT ("BezierBox"), hCtrlLine_E, BezierDlgProc) )
			{								  
				for (i=0; i<4; i++)			  
				  {				  
					  g_bez_pt_E[i].x = g_bez_pt[i].x;				  
					  g_bez_pt_E[i].y = g_bez_pt[i].y;			  
				  }

				DrawBezierToBlock(hCtrlLine_E,g_bez_pt_E);
			}
			return FALSE;		 
     
		case IDC_BTN_LINE_F:

			if (DialogBox (hInstance, TEXT ("BezierBox"), hCtrlLine_F, BezierDlgProc) )
			{								  
				for (i=0; i<4; i++)			  
				  {				  
					  g_bez_pt_F[i].x = g_bez_pt[i].x;				  
					  g_bez_pt_F[i].y = g_bez_pt[i].y;			  
				  }

				DrawBezierToBlock(hCtrlLine_F,g_bez_pt_F);
			}
			return FALSE;
		}
	
	}	
		
	return FALSE;

}


// dialog box procedure for Bezier Line editer dialog

BOOL CALLBACK BezierDlgProc (HWND hDlg, UINT message, 
                           WPARAM wParam, LPARAM lParam)
{

	switch (message)     
	{

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
	}
	return FALSE;

}


// window procedure for Bezier Line editing control,it's a custom control

LRESULT CALLBACK BezierLineWndProc (HWND hwnd, UINT message, 
                                   WPARAM wParam, LPARAM lParam)
{
	static POINT apt[4];

    HDC hdc;

    static int cxClient, cyClient;

	static RECT rect;

	PAINTSTRUCT ps;
     
	switch (message)    
	{

	case WM_CREATE:	

		hdc = GetDC(hwnd);
		GetClientRect (hwnd, &rect);

		cxClient = rect.right;
		cyClient = rect.bottom;

		ReleaseDC (hwnd, hdc);
		
		apt[0].x = cxClient / 2;
		apt[0].y = 3 * cyClient / 4;

		apt[1].x = cxClient / 2;
		apt[1].y = 5 * cyClient / 8;

		apt[2].x = cxClient / 2;
        apt[2].y = 3 * cyClient / 8;

		apt[3].x = cxClient / 2;
        apt[3].y = cyClient / 4;

		return FALSE;
     
	case WM_PAINT :
		 
		hdc = BeginPaint (hwnd, &ps) ;
		DrawBezier (hdc, apt) ;
		EndPaint (hwnd, &ps) ;

		return 0 ;

	case WM_LBUTTONDOWN:     
	case WM_RBUTTONDOWN:     
	case WM_MOUSEMOVE:
          		
		  if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)        
		
		  {               			                            
			
			  if (wParam & MK_LBUTTON)              			
			  {                   				
				  apt[1].x = LOWORD(lParam);                    				
				  apt[1].y = HIWORD(lParam);               			
			  }                              			
			  if (wParam & MK_RBUTTON)               			
			  {                   				
				  apt[2].x = LOWORD(lParam);                   				
				  apt[2].y = HIWORD(lParam);             			
			  }

			  InvalidateRect(hwnd, NULL, TRUE);
				  
			  for (int i=0; i<4; i++)			  				  
			  {				  
					  g_bez_pt[i].x = apt[i].x / SCALE_FACTOR;				  
					  g_bez_pt[i].y = apt[i].y / SCALE_FACTOR;			  				  
			  }		
			}

		return FALSE;            
	}    
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}


//////////////////////////////////////////////////////////////////////////////////////////////
/// thesw functions are only for debugging purpose////////////////////////////////////////

void g_PrintPoints(POINT* pts, LPCTSTR lpTitle)
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

void g_PrintRect(RECT & f_rect, LPCTSTR lpTitle)
{

        TCHAR szFormatrec[] = TEXT ("%-04i %-04i %-04i %-04i"),
              szBufferrec[30];

        wsprintf (szBufferrec, szFormatrec, f_rect.top,    f_rect.left,
			                                f_rect.bottom, f_rect.right);

		MessageBox (NULL, szBufferrec,
                      lpTitle, MB_ICONINFORMATION);

}

void g_PrintWH(int Width, int Height, LPCTSTR lpTitle)
{

        TCHAR szFormatWH[] = TEXT ("%-04i %-04i"),
              szBufferWH[30];

        wsprintf (szBufferWH, szFormatWH, Width, Height);

		MessageBox (NULL, szBufferWH,
                      lpTitle, MB_ICONINFORMATION);

}

//////////////////////////////////////////////////////////////////////////////////////////////
