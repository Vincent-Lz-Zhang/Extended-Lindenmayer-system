/*
  Extended L-system
  ZHANG Lingzhang 5th Mar 2009
  HKUST
*/

#include <windows.h>
#include "resource.h"

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

HWND hDMlesGraph ;



LRESULT CALLBACK WndProc      (HWND, UINT, WPARAM, LPARAM) ;
BOOL    CALLBACK AboutDlgProc (HWND, UINT, WPARAM, LPARAM) ;
BOOL    CALLBACK GraphDlgProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)

   {
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
                         7 * cxChar, 7 * cyChar, 3 * cxChar, cyChar, hwnd, (HMENU) ID_EDIT_RULES,
                          hInstance, NULL) ;     		  

		  hwnd_Stic_Ang = CreateWindow ( TEXT( "STATIC"), angle, WS_CHILD | WS_VISIBLE,
			  12 * cxChar, 7 * cyChar, 5 * cxChar, cyChar, 
			  hwnd, (HMENU) ID_STATIC_ANGLE, hInstance, NULL);		  
             
		  hwnd_Edit_Ang = CreateWindow (TEXT ("edit"), NULL,
                         WS_CHILD | WS_VISIBLE |
                                   WS_BORDER | ES_LEFT ,
                         18 * cxChar, 7 * cyChar, 3 * cxChar, cyChar, hwnd, (HMENU) ID_EDIT_RULES,
                          hInstance, NULL) ;

    
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
         
	 case WM_SIZE:
          //MoveWindow (hwndStic, 0, 0, LOWORD (lParam) * 0.5, HIWORD (lParam) * 0.5, TRUE) ;
		  //SetDlgItemText(hwnd,ID_STATIC_AXIOM,axiom);
		  //SetDlgItemText(hwnd,ID_STATIC_RULES,rule);
		  //SetDlgItemText(hwnd,ID_STATIC_ORDER,order);
		  //SetDlgItemText(hwnd,ID_STATIC_ANGLE,angle);

		  return 0;
     case WM_COMMAND :
          switch (LOWORD (wParam))
          {
          case IDM_APP_ABOUT :
               DialogBox (hInstance, TEXT ("AboutBox"), hwnd, AboutDlgProc) ;
               break ;

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
          return TRUE ;
          
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

BOOL CALLBACK GraphDlgProc (HWND hDlg, UINT message, 
                           WPARAM wParam, LPARAM lParam)
{
	 /*    
	switch (message)
     
		 
	{
			 
		 case WM_VSCROLL :

			 
		 case WM_HSCROLL :

		 default : return TRUE;

		 
		 
	}
*/
  return FALSE ;
}