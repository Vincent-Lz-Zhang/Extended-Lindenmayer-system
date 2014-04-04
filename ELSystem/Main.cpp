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
  Fixed by Zhang Lingzhang at 12th Apr
  Revised by ZHANG Lingzhang at 16th Apr
  Revised by ZHANG Lingzhang at 22th Apr
**********************************************/

#include <windows.h>
#include "resource.h"
#include "ELSystem.h"
#include "DrawGraph.h"
#include "ParaValidator.h"
#include "Frame.h"
#include "Animation.h"
#include "ParaIO.h"
#include <commdlg.h>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <cstdlib>

//----------------------------//
#define SCALE_FACTOR 3
//----------------------------//
#define ID_TIMER    1
//----------------------------//

//-----resouse identities-----//

//------- static texts -------//

#define ID_STATIC_AXIOM 1
#define ID_STATIC_RULES 2
#define ID_STATIC_ORDER 3
#define ID_STATIC_ANGLEL 4
#define ID_STATIC_ANGLER 24
//------- edit controls -------//

#define ID_EDIT_AXIOM 5
#define ID_EDIT_RULES 6
#define ID_EDIT_ORDER 7
#define ID_EDIT_ANGLEL 8
#define ID_EDIT_ANGLER 28
//------- buttons -------//

#define ID_BTN_APPLY 9
#define ID_BTN_RESET 10
#define ID_BTN_ANIMATE 11

//------------------------------//
#define ID_DYNAMIC_START 50     // used for the identifier of danamic menu's items
//------------------------------//

#define ID_GB_FRMRATE 12
//radio buttons
#define ID_RBTN_EIGHT   13
#define ID_RBTN_TEN     14
#define ID_RBTN_TWELVE  15
#define ID_RBTN_FORTEEN 16
#define ID_RBTN_SIXTEEN 17

//autocheck button
#define ID_CBTN_ANGRAN  18
#define ID_CBTN_LENRAN  19

//edit control for offset
#define ID_EDIT_ANGRAN_OFS 20
#define ID_EDIT_LENRAN_OFS 21
//static text %
#define ID_STATIC_PERANG  22
#define ID_STATIC_PERLEN  23

//-----------------------------------------My Defining Messages------------------------------------------//
//-------------------------------------------------------------------------------------------------------//
#define WM_CON_SIZE 0x0500  // new message for graphic dialog, indicates that the apply button is hit, and 
                            // the new graphics size should be calculated to get the scroll bars' range,
                            // and then, redraw the client area in the window

#define WM_ADD_FRAME 0x0501   // new message for informing the child control-frame editer, that user has 
                              // added new frames

#define WM_ENABLE_CONTROLS 0x0502  // should enable scroll bars
#define WM_DISABLE_CONTROLS 0x0503 // should disable scroll bars
//-------------------------------------------------------------------------------------------------------//


//   Global   variables ////////////////


//// handle of windows or dialogs /////
HWND   hDMlesGraph;
//-----------------------------------////
//// handle color obj
HBRUSH hBrushWhite;      
//-----------------------------------////

//// variables for L-system -------///
char g_ax[15];          // axiom
char g_ru[61];         // rules string
int  g_ord;            // order
char g_ordStr[4];      //
int  g_angL;            // angle
char g_angStrL[10];     // 
int  g_angR;            // angle
char g_angStrR[10];     //
///--------------------/////////////
char g_ranA[4];         // range of random offset ratio for angle
int  g_ranAng = 0;
char g_ranL[4];         // range of random offset ratio for length ratio
int  g_ranLen = 0;

char g_name[20];
/// the objects of classes that implement the functions //
ELSystem      g_elsys;     // object of ELSystem
DrawGraph     g_dg;        // object of DrawGraph
ParaValidator g_pv;        // object of ParaValidator

Frame         g_frame;      // object of Frame
ParaIO        g_pIO;        // objet of ParaIO
//----------------------------------------------------///

//-----------------For File IO--------------------------//
const char * file = "lib.dat";  // the external file's name
static int lib_cnt;  // count the number of items in the library
//----------------------------------------------------//

/////--------------------- for the information of Bezier lines --------------////////

POINT     g_bez_pt[4];    //

POINT     g_bez_pt_A[4];  // global point array and is scaled for BezierLine object A
POINT     g_bez_pt_B[4];  // global point array and is scaled for BezierLine object B
POINT     g_bez_pt_C[4];  // global point array and is scaled for BezierLine object C
POINT     g_bez_pt_D[4];  // global point array and is scaled for BezierLine object D
POINT     g_bez_pt_E[4];  // global point array and is scaled for BezierLine object E
POINT     g_bez_pt_F[4];  // global point array and is scaled for BezierLine object F
     
//--------------------------------------------------------------------------------///

//---------------- color information ----------------//
static COLOR col_A, col_B, col_C, col_D, col_E, col_F;
//---------------------------------------------------///



//----the size of page----//
const int xUnit = 50;
const int yUnit = 50;
//------------------------//
int interval = 83;    // used for animation
//------------------------//
static BOOL fAng, fLen;  // used for random offset of length and angle
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

BOOL    CALLBACK ExportDlgProc     (HWND, UINT, WPARAM, LPARAM);
//---------------------------------------------------------------------------------------//

//-----------------------------------Animation Part--------------------------------------//

LRESULT CALLBACK FrameEdtWndProc   (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK AnimDlgProc       (HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK PlayWndProc       (HWND, UINT, WPARAM, LPARAM);
//---------------------------------------------------------------------------------------//

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)

{
		
	ifstream fin;
			 
	static HMENU hMenu, hMenuPopup;

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

     //---------------------------------------------------------//

     //--------------------for animation------------------------//

     // declare a new window class, which is the custom control  

     wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
     wndclass.lpfnWndProc   = FrameEdtWndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = NULL ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) hBrushWhite ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = TEXT ("FrameEditer") ;

     RegisterClass (&wndclass) ;

     //--------------------------------------------------------------//

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = PlayWndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = NULL ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) hBrushWhite ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = TEXT ("PlayWnd") ;

     RegisterClass (&wndclass) ;

	 //----------------------------------------------------------------//
     hwnd = CreateWindow (szAppName, TEXT ("Extended L-System"),
                          WS_OVERLAPPEDWINDOW ,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          310, 450,
                          NULL, NULL, hInstance, NULL) ;
     
	 hMenu = LoadMenu (hInstance, szAppName) ;
	 hMenuPopup = CreateMenu () ;
    		  
	 fin.open(file, ios::in |ios::binary);
		  		   		  
	 if (fin.is_open())  		  
	 {		 			  
		 while (fin.read((char *) & g_pIO, sizeof g_pIO))       		  
		 {				  
			 lib_cnt++;		   
			 InsertMenu(hMenu, IDM_MARK, MF_STRING, ID_DYNAMIC_START+lib_cnt, g_pIO.GetNameFromFile() );
		 }				   
	 }
 
	 SetMenu(hwnd,hMenu);		  
	 fin.close();

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

void RecoverPara(HWND hwnd, int i)
{
	 TCHAR szFormat[] = TEXT ("%-03i");
     ifstream fin;
			  
	 fin.clear();    // not required for some implementations, but won't hurt    
			  
	 fin.open(file, ios::in | ios::binary);
		  
	 if (fin.is_open())			  
	 {					  
		 streampos place = i * sizeof g_pIO;  // convert to streampos type    		
				  
		 fin.seekg(place);    // random access    
						  
		 if (fin.fail())    						  
		 {   					  
			 MessageBox (NULL, TEXT ("Can not seek the file!"),                   								  
				 TEXT("Error"), MB_ICONERROR); 		   						  
		 }
 					  
		 fin.read((char *) &g_pIO, sizeof g_pIO);
       							  
		 SetDlgItemText (hwnd, ID_EDIT_RULES, g_pIO.ReturnRules() );
		 
		 wsprintf (g_ordStr, szFormat, g_pIO.ReturnOrder() );				  
		 SetDlgItemText (hwnd, ID_EDIT_ORDER, g_ordStr);
			  
		 wsprintf (g_angStrL, szFormat, g_pIO.ReturnAngleL() );			  
		 SetDlgItemText (hwnd, ID_EDIT_ANGLEL, g_angStrL);
			  
		 wsprintf (g_angStrR, szFormat, g_pIO.ReturnAngleR() );			  
		 SetDlgItemText (hwnd, ID_EDIT_ANGLER, g_angStrR);


		 wsprintf (g_ax, g_pIO.ReturnAxiom() );			  
		 SetDlgItemText (hwnd, ID_EDIT_AXIOM, g_ax);
		 
				  
		 g_pIO.CopyToClass(g_elsys, g_dg, g_frame);
				  
		 if (fin.eof())       									  
			 fin.clear();     // clear eof flag				  
	 }    			  
	 fin.close();
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static HINSTANCE hInstance ;

	 TCHAR axiom[]    = TEXT ("Axiom:");
	 TCHAR rule[]     = TEXT ("Replacement Rules:");
	 TCHAR order[]    = TEXT ("Order:");
	 TCHAR angleL[]   = TEXT ("AngleL:");
	 TCHAR angleR[]   = TEXT ("AngleR:");
	 TCHAR btnApply[] = TEXT ("Apply");
	 TCHAR btnReset[] = TEXT ("Reset");
	 TCHAR btnAnima[] = TEXT ("Animate");

	 TCHAR group[]    = TEXT ("Frame Rate:");            // Group button
     TCHAR cbtn_ang[] = TEXT ("Randomize angle");   // check button
     TCHAR cbtn_len[] = TEXT ("Randomize length");  // check button
	 TCHAR percent[]  = TEXT ("%");

	 TCHAR rbtn_eig[] = TEXT ("8 fps");    // radio button
	 TCHAR rbtn_ten[] = TEXT ("10 fps");    // radio button
	 TCHAR rbtn_twl[] = TEXT ("12 fps");    // radio button
	 TCHAR rbtn_fur[] = TEXT ("14 fps");    // radio button
	 TCHAR rbtn_six[] = TEXT ("16 fps");    // radio button

	 TCHAR empty[1];
	 empty[0] = '\0';

	 static HWND hwnd_Stic_Axm,  hwnd_Stic_Rule, hwnd_Stic_Ord, hwnd_Stic_AngL, hwnd_Stic_AngR;
     static HWND hwnd_Edit_Axm,  hwnd_Edit_Rule, hwnd_Edit_Ord, hwnd_Edit_AngL, hwnd_Edit_AngR;
	 static HWND hwnd_Btn_Apply, hwnd_Btn_Reset, hwnd_Btn_Anima;
     static HWND hwnd_anim;

     static HWND hwnd_Grp,      hwnd_Stic_perA, hwnd_Stic_perL, hwnd_Cbtn_Ang, 
		         hwnd_Cbtn_Len, hwnd_Edit_RanA, hwnd_Edit_RanL;
	 static HWND hwnd_Rbtn_Eig, hwnd_Rbtn_Ten, hwnd_Rbtn_Twl, hwnd_Rbtn_Fur,
		         hwnd_Rbtn_Six;

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
			                      cxChar, cyChar, 6 * cxChar, cyChar, 
			                      hwnd, (HMENU) ID_STATIC_AXIOM,
								  hInstance, NULL);
						
          hwnd_Edit_Axm = CreateWindow ( TEXT ("edit"), 
			                      NULL, 
								  WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | WS_TABSTOP | WS_GROUP,           
                                  8 * cxChar, cyChar, 15*cxChar, 5 * cyChar / 4,
								  hwnd, (HMENU) ID_EDIT_AXIOM,
                                  hInstance, NULL);
       
		  hwnd_Stic_Rule = CreateWindow ( TEXT( "STATIC"), 
			                       rule, 
								   WS_CHILD | WS_VISIBLE,
			                       cxChar, 3 * cyChar, 17 * cxChar, cyChar, 
			                       hwnd, (HMENU) ID_STATIC_RULES,
								   hInstance, NULL);		  
         
          hwnd_Edit_Rule = CreateWindow ( TEXT ("edit"),
			                       NULL, 
								   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | WS_TABSTOP | WS_GROUP,
                                   cxChar, 5 * cyChar, 35 * cxChar, 5 * cyChar / 4, 
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
								  WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | WS_TABSTOP | WS_GROUP,
                                  7 * cxChar, 7 * cyChar, 4 * cxChar, 5 * cyChar / 4,
								  hwnd, (HMENU) ID_EDIT_ORDER,
                                  hInstance, NULL); 
                              		  
		  hwnd_Stic_AngL = CreateWindow ( TEXT( "STATIC"), 
			                      angleL, 
								  WS_CHILD | WS_VISIBLE,
			                      12 * cxChar, 7 * cyChar, 13 * cxChar / 2, cyChar, 
			                      hwnd, (HMENU) ID_STATIC_ANGLEL, 
								  hInstance, NULL);		  
             
		  hwnd_Edit_AngL = CreateWindow ( TEXT ("edit"), 
			                      NULL, 
								  WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | WS_TABSTOP | WS_GROUP,                    
                                  39 * cxChar / 2, 7 * cyChar, 4 * cxChar, 5 * cyChar / 4, 
								  hwnd, (HMENU) ID_EDIT_ANGLEL,
                                  hInstance, NULL);

		  hwnd_Stic_AngR = CreateWindow ( TEXT( "STATIC"), 
			                      angleR, 
								  WS_CHILD | WS_VISIBLE,
			                      25 * cxChar, 7 * cyChar, 13 * cxChar / 2, cyChar, 
			                      hwnd, (HMENU) ID_STATIC_ANGLER, 
								  hInstance, NULL);		  
             
		  hwnd_Edit_AngR = CreateWindow ( TEXT ("edit"), 
			                      NULL, 
								  WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | WS_TABSTOP | WS_GROUP,                    
                                  32 * cxChar, 7 * cyChar, 4 * cxChar, 5 * cyChar / 4, 
								  hwnd, (HMENU) ID_EDIT_ANGLER,
                                  hInstance, NULL);
          //-------------------- buttons --------------------

		  hwnd_Btn_Apply = CreateWindow ( TEXT("button"), 
                                   btnApply,
                                   WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP,
                                   14 * cxChar, 22 * cyChar,
                                   6 * cxChar, 7 * cyChar / 4,
                                   hwnd, (HMENU) ID_BTN_APPLY,
                                   hInstance, NULL);

		  hwnd_Btn_Reset = CreateWindow ( TEXT("button"), 
                                   btnReset,
                                   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP | WS_GROUP,
                                   21 * cxChar, 22 * cyChar,
                                   7 * cxChar, 7 * cyChar / 4,
                                   hwnd, (HMENU) ID_BTN_RESET,
                                   hInstance, NULL);

		  hwnd_Btn_Anima = CreateWindow ( TEXT("button"), 
                                   btnAnima,
                                   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP | WS_GROUP,
                                   29 * cxChar, 22 * cyChar,
                                   8 * cxChar, 7 * cyChar / 4,
                                   hwnd, (HMENU) ID_BTN_ANIMATE,
                                   hInstance, NULL);
		  //---------------------------------------------------------------------------//

		  hwnd_Cbtn_Ang = CreateWindow ( TEXT("button"), 
                                   cbtn_ang,
                                   WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP,
                                   cxChar, 9 * cyChar,
                                   18 * cxChar, 5 * cyChar / 4,
                                   hwnd, (HMENU) ID_CBTN_ANGRAN,
                                   hInstance, NULL);


		  hwnd_Edit_RanA = CreateWindow ( TEXT("edit"), 
                                   NULL,
                                   WS_CHILD | WS_VISIBLE |  WS_BORDER | ES_LEFT,
                                   24 * cxChar, 9 * cyChar,
                                   4 * cxChar, 5 * cyChar / 4,
                                   hwnd, (HMENU) ID_EDIT_ANGRAN_OFS,
                                   hInstance, NULL);


         hwnd_Stic_perA = CreateWindow ( TEXT("static"), 
                                   percent,
                                   WS_CHILD | WS_VISIBLE ,
                                   29 * cxChar, 9 * cyChar,
                                   2 * cxChar, 5 * cyChar / 4,
                                   hwnd, (HMENU) ID_STATIC_PERANG,
                                   hInstance, NULL);
 
		  //-----------------------------------------------------------------------//

		  hwnd_Cbtn_Len = CreateWindow ( TEXT("button"), 
                                   cbtn_len,
                                   WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP,
                                   cxChar, 11 * cyChar,
                                   18 * cxChar, 5 * cyChar / 4,
                                   hwnd, (HMENU) ID_CBTN_LENRAN,
                                   hInstance, NULL);

		  hwnd_Edit_RanL = CreateWindow ( TEXT("edit"), 
                                   NULL,
                                   WS_CHILD | WS_VISIBLE |  WS_BORDER | ES_LEFT,
                                   24 * cxChar, 11 * cyChar,
                                   4 * cxChar, 5 * cyChar / 4,
                                   hwnd, (HMENU) ID_EDIT_LENRAN_OFS,
                                   hInstance, NULL);


         hwnd_Stic_perL = CreateWindow ( TEXT("static"), 
                                   percent,
                                   WS_CHILD | WS_VISIBLE ,
                                   29 * cxChar, 11 * cyChar,
                                   2 * cxChar, 5 * cyChar / 4,
                                   hwnd, (HMENU) ID_STATIC_PERLEN,
                                   hInstance, NULL);

		 //---------------------------------------------------------------------------//
		 hwnd_Grp = CreateWindow ( TEXT("button"), 
                                   group,
                                   WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                   cxChar, 13 * cyChar,
                                   21 * cxChar, 8 * cyChar,
                                   hwnd, (HMENU) ID_GB_FRMRATE,
                                   hInstance, NULL);

		 hwnd_Rbtn_Eig = CreateWindow ( TEXT("button"), 
                                   rbtn_eig,
                                   WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_TABSTOP | WS_GROUP,
                                   2 * cxChar , 15 * cyChar ,
                                   8 * cxChar, 5 * cyChar / 4,
                                   hwnd, (HMENU) ID_RBTN_EIGHT,
                                   hInstance, NULL); 
			 
		hwnd_Rbtn_Ten = CreateWindow ( TEXT("button"), 
                                   rbtn_ten,
                                   WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                                   2 * cxChar , 17 * cyChar ,
                                   8 * cxChar, 5 * cyChar / 4,
                                   hwnd, (HMENU) ID_RBTN_TEN,
                                   hInstance, NULL); 	 
		
		hwnd_Rbtn_Twl = CreateWindow ( TEXT("button"), 
                                   rbtn_twl,
                                   WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                                   2 * cxChar , 19 * cyChar ,
                                   8 * cxChar, 5 * cyChar / 4,
                                   hwnd, (HMENU) ID_RBTN_TWELVE,
                                   hInstance, NULL); 	 
		
		hwnd_Rbtn_Fur = CreateWindow ( TEXT("button"), 
                                   rbtn_fur,
                                   WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                                   12 * cxChar , 15 * cyChar ,
                                   8 * cxChar, 5 * cyChar / 4,
                                   hwnd, (HMENU) ID_RBTN_FORTEEN,
                                   hInstance, NULL); 	 
		
		hwnd_Rbtn_Six = CreateWindow ( TEXT("button"), 
                                   rbtn_six,
                                   WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                                   12 * cxChar , 17 * cyChar ,
                                   8 * cxChar, 5 * cyChar / 4,
                                   hwnd, (HMENU) ID_RBTN_SIXTEEN,
                                   hInstance, NULL);
	
		EnableWindow(hwnd_Edit_RanA, FALSE);
		EnableWindow(hwnd_Edit_RanL, FALSE);		  
	
		CheckRadioButton (hwnd, ID_RBTN_EIGHT, ID_RBTN_SIXTEEN, ID_RBTN_TWELVE);
	
		return 0 ;

     case WM_COMMAND :

          switch (LOWORD (wParam))
          {

		  case ID_DYNAMIC_START+1:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,0);   
			  }
			  break;

		  case ID_DYNAMIC_START+2:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,1);   
			  }   
			  break;

		  case ID_DYNAMIC_START+3:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,2);   
			  }   
			  break;

		  case ID_DYNAMIC_START+4:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,3);   
			  }   
			  break;

		  case ID_DYNAMIC_START+5:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,4);   
			  }  
			  break;

		  case ID_DYNAMIC_START+6:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,5);   
			  }   
			  break;

		  case ID_DYNAMIC_START+7:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,6);   
			  }   
			  break;

		  case ID_DYNAMIC_START+8:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,7);   
			  }   
			  break;

		  case ID_DYNAMIC_START+9:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,8);   
			  }   
			  break;

		  case ID_DYNAMIC_START+10:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,9);   
			  }   
			  break;

		  case ID_DYNAMIC_START+11:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,10);   
			  }   
			  break;

		  case ID_DYNAMIC_START+12:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,11);   
			  }   
			  break;

		  case ID_DYNAMIC_START+13:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,12);   
			  }   
			  break;

		  case ID_DYNAMIC_START+14:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,13);   
			  }   
			  break;

		  case ID_DYNAMIC_START+15:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,14);   
			  }   
			  break;

		  case ID_DYNAMIC_START+16:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,15);   
			  }   
			  break;

		  case ID_DYNAMIC_START+17:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,16);   
			  }   
			  break;

		  case ID_DYNAMIC_START+18:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,17);   
			  }   
			  break;

		  case ID_DYNAMIC_START+19:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,18);   
			  }   
			  break;

		  case ID_DYNAMIC_START+20:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,19);   
			  }   
			  break;

		  case ID_DYNAMIC_START+21:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,20);   
			  }   
			  break;

		  case ID_DYNAMIC_START+22:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,21);   
			  }   
			  break;

		  case ID_DYNAMIC_START+23:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,22);   
			  }   
			  break;

		  case ID_DYNAMIC_START+24:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+25:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+26:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+27:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+28:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+29:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+30:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+31:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+32:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+33:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+34:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+35:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+36:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+37:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+38:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+39:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;

		  case ID_DYNAMIC_START+40:
			  if(LOWORD (wParam) <= ID_DYNAMIC_START+lib_cnt)
			  {
				  RecoverPara(hwnd,LOWORD(wParam)-1-ID_DYNAMIC_START);   
			  }   
			  break;


		  case IDM_FILE_EXIT:

			  PostQuitMessage (0) ;
         
			  return 0 ;

		  case IDM_FILE_EXPORT:

			  if(DialogBox( hInstance, TEXT ("NameBox"), hwnd, ExportDlgProc))
			  {				 
				  g_pIO.GetNameFromInput(g_name);
				  g_pIO.CopyFromClass(g_elsys, g_dg, g_frame, g_angL, g_angR);

				  ofstream fout(file, ios::out | ios::app | ios::binary);
    
				  if (!fout.is_open())    
				  {        
					  MessageBox (NULL, TEXT ("Can not open the file!"),
                    
					             TEXT("Error"), MB_ICONINFORMATION);    
				  }

				  fout.write((char *) &g_pIO, sizeof g_pIO);
                  fout.close();

			  }
			  break;

          case IDM_APP_ABOUT :
               
			  DialogBox (hInstance, TEXT ("AboutBox"), hwnd, AboutDlgProc);
               
			  break ;

          case IDM_EDIT_COLOR :
               
			  DialogBox (hInstance, TEXT ("ColorBox"), hwnd, ColorDlgProc);
               
			  break ;

          case IDM_EDIT_LINE :
               
			  DialogBox (hInstance, TEXT ("LineBox"), hwnd, LineDlgProc);
               
			  break ;

		  case IDM_EDIT_ANIM:
			  
			  DialogBox (hInstance, TEXT ("AnimaBox"), hwnd, AnimDlgProc);

			  break;

		  case IDM_EDIT_COPY:

			  g_dg.Copy (hDMlesGraph, fAng, fLen);

			  break;

		  case ID_BTN_APPLY :

			 if(fAng)
			 {
				 if( 0==GetDlgItemText (hwnd, ID_EDIT_ANGRAN_OFS, g_ranA, 3) )
				 {
					 MessageBox (NULL, TEXT ("No input for angle random offset range!"), 
					  
						 TEXT("Invalid Input"), MB_ICONINFORMATION);
				 }
				 else
				 {

					 g_dg.ClearDyAryA();      // remove all previous random numbers, free the memory 			
					 g_ranAng = atoi(g_ranA); // get the user input
					 
				 }
			 }

			 if(fLen)
			 {
				 if( 0==GetDlgItemText (hwnd, ID_EDIT_LENRAN_OFS, g_ranL, 3) )
				 {
					 MessageBox (NULL, TEXT ("No input for length random offset range!"), 
					  
						 TEXT("Invalid Input"), MB_ICONINFORMATION);
				 }
				 else
				 {
					 
					 g_dg.ClearDyAryL();      // remove all previous random numbers, free the memory 
					 g_ranLen = atoi(g_ranL); // get the user input
					 
				 }
			 }
			  

			  if( 0==GetDlgItemText (hwnd, ID_EDIT_AXIOM, g_ax, 14)      || 
				  0==GetDlgItemText (hwnd, ID_EDIT_RULES, g_ru, 60)      || 
				  0==GetDlgItemText (hwnd, ID_EDIT_ORDER, g_ordStr, 3)   ||
				  0==GetDlgItemText (hwnd, ID_EDIT_ANGLEL, g_angStrL, 4) || 
				  0==GetDlgItemText (hwnd, ID_EDIT_ANGLER, g_angStrR, 4) )
			  {
				            
				  MessageBox (NULL, TEXT ("Please type in a letter or a number!"),
                    
					  TEXT("Invalid Input"), MB_ICONINFORMATION);
			  }
			  else
			  {
			  
				  // retrieve the values from controls

				  if(fAng)
				  {				  
					  g_dg.GenRandomA(g_elsys.CountSymbol(), g_ranAng); // generate new random numbers for angle
				  }
				  if(fLen)
				  {
					  g_dg.GenRandomL(g_elsys.CountLetter(), g_ranLen); // generate new random numbers for length
				  }

			      g_ord = atoi(g_ordStr);
			      g_angL = atoi(g_angStrL);
				  g_angR = atoi(g_angStrR);
              
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
              SetDlgItemText(hwnd, ID_EDIT_ANGLEL, empty);
			  SetDlgItemText(hwnd, ID_EDIT_ANGLER, empty);

			  break;

		  case ID_BTN_ANIMATE:

			  if( g_frame.IsMapEmpty() )
			  {
				  MessageBox (NULL, TEXT ("Please edit the animation."),
                    
					  TEXT("No frame yet"), MB_ICONINFORMATION);
			  }
			  else
			  {
				  

              
				  hwnd_anim = CreateWindow ( TEXT("PlayWnd"),
				                         NULL,
										 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                         CW_USEDEFAULT, CW_USEDEFAULT,
                                         700, 700,
                                         NULL, NULL, hInstance, NULL);
			  }
			  break;
          
		  case ID_RBTN_EIGHT:
			  interval = 125;
			  break;

		  case ID_RBTN_TEN:
			  interval = 100;
			  break;

		  case ID_RBTN_TWELVE:
			  interval = 83;
			  break;

		  case ID_RBTN_FORTEEN:
			  interval = 71;
			  break;

		  case ID_RBTN_SIXTEEN:
			  interval = 63;
			  break;

		  case ID_CBTN_ANGRAN:

			  fAng ^= 1;			  		
			  EnableWindow(hwnd_Edit_RanA, fAng);
		
			  break;

		 case ID_CBTN_LENRAN:

			  fLen ^= 1;
			  EnableWindow(hwnd_Edit_RanL, fLen);

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

			 return TRUE;

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
					 return TRUE;

				 case IDC_BTN_COR_B:

                     cc.rgbResult = col_B.rgb; 
					 ChooseColor (&cc); 
					 col_B.rgb = cc.rgbResult;
					 PaintColor(hCtrlCol_B, col_B.rgb);             
					 return TRUE;

				 case IDC_BTN_COR_C:

                     cc.rgbResult = col_C.rgb; 
					 ChooseColor (&cc); 
					 col_C.rgb = cc.rgbResult;
					 PaintColor(hCtrlCol_C, col_C.rgb);             
					 return TRUE;

				 case IDC_BTN_COR_D:

                     cc.rgbResult = col_D.rgb; 
					 ChooseColor (&cc); 
					 col_D.rgb = cc.rgbResult;
					 PaintColor(hCtrlCol_D, col_D.rgb);             
					 return TRUE;

				 case IDC_BTN_COR_E:

                     cc.rgbResult = col_E.rgb; 
					 ChooseColor (&cc); 
					 col_E.rgb = cc.rgbResult;
					 PaintColor(hCtrlCol_E, col_E.rgb);             
					 return TRUE;

				 case IDC_BTN_COR_F:

                     cc.rgbResult = col_F.rgb; 
					 ChooseColor (&cc); 
					 col_F.rgb = cc.rgbResult;
					 PaintColor(hCtrlCol_F, col_F.rgb);             
					 return TRUE;

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

		rMax = g_dg.CheckBoundary(hDlg, fAng, fLen);

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

			if(  abs(rMax.left)<=abs(rMax.right-cxClient)  )
			{				
				SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
				SetScrollPos (hDlg, SB_HORZ, 0, TRUE);
			}
			else 
			{
				SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
				SetScrollPos (hDlg, SB_HORZ, ceil((float(abs(rMax.left)-abs(rMax.right-cxClient))/2) / float(xUnit) ), TRUE);
			}
		}
		else if(rMax.right > cxClient)  // the width of graph is not over the width of window, but exceed right edge
		{
			temp_HorzNumPos1 = ceil( float(rMax.right - cxClient/2) / float(xUnit) );

			g_HorzNumPos = 2*temp_HorzNumPos1;

			if(  abs(rMax.right-cxClient)<=abs(rMax.left)  )
			{				
				SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
				SetScrollPos (hDlg, SB_HORZ, g_HorzNumPos, TRUE);
			}
			else 
			{
				SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
				SetScrollPos (hDlg, SB_HORZ, g_HorzNumPos-ceil((float(abs(rMax.right-cxClient)-abs(rMax.left))/2) / float(xUnit) ), TRUE);
			}

		}
		else
		{
			SetScrollPos (hDlg, SB_HORZ, g_HorzNumPos/2, TRUE);
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

			if(  abs(rMax.top)<=abs(rMax.bottom-cyClient)  )
			{				
				SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
				SetScrollPos (hDlg, SB_VERT, 0, TRUE);
			}

			else 
			{

				SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
                SetScrollPos (hDlg, SB_VERT , ceil((float(abs(rMax.top)-abs(rMax.bottom-cyClient))/2) / float(yUnit) ), TRUE);
			}
		    		    

		}
		else if(rMax.bottom > cyClient)   // the height of graph is not over the height of window, but exceed bottom edge
		{
			temp_VertNumPos1 = ceil( float(rMax.bottom - cyClient/2 ) / float(yUnit) );

			g_VertNumPos = 2*temp_VertNumPos1;

			if(  abs(rMax.top)<=abs(rMax.bottom-cyClient)  )
			{				
				SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
				SetScrollPos (hDlg, SB_VERT, g_VertNumPos, TRUE);
			}

			else 
			{

				SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
                SetScrollPos (hDlg, SB_VERT , g_VertNumPos-ceil((float(abs(rMax.bottom-cyClient)-abs(rMax.top))/2) / float(yUnit) ), TRUE);
			}

		}
		else
		{
			SetScrollPos (hDlg, SB_VERT, g_VertNumPos/2, TRUE);
		}

		InvalidateRect (hDlg, NULL, TRUE);

		return TRUE;

	case WM_CON_SIZE:

		int temp_VertNumPos, temp_HorzNumPos;

		g_dg.Update(g_elsys.Report(), g_angL, g_angR);

		rMax = g_dg.CheckBoundary(hDlg, fAng, fLen);

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

			if(  abs(rMax.left)<=abs(rMax.right-cxClient)  )
			{				
				SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
				SetScrollPos (hDlg, SB_HORZ, 0, TRUE);
			}
			else 
			{
				SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
				SetScrollPos (hDlg, SB_HORZ, ceil((float(abs(rMax.left)-abs(rMax.right-cxClient))/2) / float(xUnit) ), TRUE);
			}
		}
		else if(rMax.right > cxClient)  // the width of graph is not over the width of window, but exceed right edge
		{
			temp_HorzNumPos = ceil( float(rMax.right - cxClient/2) / float(xUnit) );

			g_HorzNumPos = 2*temp_HorzNumPos;

			if(  abs(rMax.right-cxClient)<=abs(rMax.left)  )
			{				
				SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
				SetScrollPos (hDlg, SB_HORZ, g_HorzNumPos, TRUE);
			}
			else 
			{
				SetScrollRange (hDlg, SB_HORZ, 0, g_HorzNumPos, TRUE);
				SetScrollPos (hDlg, SB_HORZ, g_HorzNumPos-ceil((float(abs(rMax.right-cxClient)-abs(rMax.left))/2) / float(xUnit) ), TRUE);
			}
		}
		else
		{
			SetScrollPos (hDlg, SB_HORZ, g_HorzNumPos/2, TRUE);
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
			
			if(  abs(rMax.top)<=abs(rMax.bottom-cyClient)  )
			{				
				SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
				SetScrollPos (hDlg, SB_VERT, 0, TRUE);
			}

			else 
			{

				SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
                SetScrollPos (hDlg, SB_VERT , ceil((float(abs(rMax.top)-abs(rMax.bottom-cyClient))/2) / float(yUnit) ), TRUE);
			}

		}
		else if(rMax.bottom > cyClient)    // the height of graph is not over the height of window, but exceed bottom edge
		{
			temp_VertNumPos = ceil( float(rMax.bottom - cyClient/2 ) / float(yUnit) );

			g_VertNumPos = 2*temp_VertNumPos;

			if(  abs(rMax.top)<=abs(rMax.bottom-cyClient)  )
			{				
				SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
				SetScrollPos (hDlg, SB_VERT, g_VertNumPos, TRUE);
			}

			else 
			{

				SetScrollRange (hDlg, SB_VERT , 0, g_VertNumPos, TRUE);
                SetScrollPos (hDlg, SB_VERT , g_VertNumPos-ceil((float(abs(rMax.bottom-cyClient)-abs(rMax.top))/2) / float(yUnit) ), TRUE);
			}

		}
		else
		{
			SetScrollPos (hDlg, SB_VERT, g_VertNumPos/2, TRUE);
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
			  MessageBeep (0) ;
               SendMessage (hDlg, WM_VSCROLL, SB_LINEUP, 0) ;
               break ;

          case VK_DOWN:
			  MessageBeep (0) ;
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
			            ( g_VertNumPos/2 - GetScrollPos(hDlg, SB_VERT) ) * yUnit,
						  fAng, fLen);

		return TRUE;		

		
	case WM_CTLCOLORDLG:          
			
		if ( (HWND) lParam  == hDlg )		  			
		{             				
			return (BOOL) hBrushWhite;		  			
		}
		
		return TRUE;
	
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
		
		return TRUE;
		 
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
			return TRUE;

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
			return TRUE;

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
			return TRUE;
			
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
			return TRUE;

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
			return TRUE;		 
     
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
			return TRUE;
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

//------------------------------------ Animation Part --------------------------------------//

LRESULT CALLBACK FrameEdtWndProc (HWND hwnd, UINT message, 
                                  WPARAM wParam, LPARAM lParam)
{
     
	const static int FRMWIDTH = 10;
	const static int FRMNUM = 35;

	const static int PAGE = 7;

	static HMENU hMenu;

	static HINSTANCE hInst;

	static BOOL state[FRMNUM];
	static int frmarry_offset = 1;

	static int pos_x,pos_y;  // cuser position

	static int index;  // indicate the selected frame

	static HWND hParent, ctl_LenR, ctl_AngL, ctl_AngR;
	HDC hdc ;  
    RECT  rect_frm ;
	HRGN hrgn;
	PAINTSTRUCT ps;
	HBRUSH hBrush;
    POINT point;
	TCHAR szBuffer[4]; // frames' number

	FRAMEINFO fi_tmp;

	int x;

	//---variables for scroll bar---//

	SCROLLINFO si;

	int iHorzPos;

	static int cyClient, cyUnit, iMax; 

	int begin;

	switch (message)    
	{

	case WM_CREATE:

		hInst = ((LPCREATESTRUCT) lParam)->hInstance;

        hMenu = LoadMenu (hInst, TEXT("FRAMEMENU")) ;
        hMenu = GetSubMenu (hMenu, 0) ;

		hParent  = GetParent(hwnd);

	    //-------------------------------//

        cyUnit   = 5 * FRMWIDTH;
		cyClient = FRMNUM * FRMWIDTH;
        iMax     = max(FRMNUM, g_frame.ReturnMaxIndex() + 5 -(g_frame.ReturnMaxIndex()%5) );

	    //-------------------------------//

		si.cbSize = sizeof (si) ;
        si.fMask  = SIF_RANGE | SIF_PAGE ;
        si.nMin   = 0 ;
        si.nMax   = iMax/5 ;
        si.nPage  = PAGE ;
        SetScrollInfo (hwnd, SB_HORZ, &si, TRUE) ;

		return 0;
     
     
	case WM_RBUTTONUP:
          
		pos_x = point.x = LOWORD (lParam) ;          
		pos_y = point.y = HIWORD (lParam) ;
          
		ClientToScreen (hwnd, &point) ;

		if( pos_y>15 && pos_y<43 )
		{  
			index = pos_x/FRMWIDTH ;
			InvalidateRect (hwnd, NULL, TRUE) ;

			if(state[index]) // this frame does exist, enable scroll bars 
			{                
			    SendMessage (hParent, WM_ENABLE_CONTROLS, frmarry_offset+pos_x/FRMWIDTH, 0) ;	
			}
			else // does not exist, just disable the scroll bars
			{
				SendMessage (hParent, WM_DISABLE_CONTROLS, 0, 0) ;
			}

            // 
			if(state[pos_x/FRMWIDTH]) // this frame does exist, enable the remove menu, disable the insert
			{
                EnableMenuItem (hMenu, IDM_FRAME_INSERT, MF_GRAYED);
                EnableMenuItem (hMenu, IDM_FRAME_DELETE, MF_ENABLED);
			}
			else // this frame does not exist, enable the insert menu, disable the remove
			{			
                EnableMenuItem (hMenu, IDM_FRAME_DELETE, MF_GRAYED);
                EnableMenuItem (hMenu, IDM_FRAME_INSERT, MF_ENABLED);
			}
		}          
          
		TrackPopupMenu (hMenu, TPM_RIGHTBUTTON, point.x, point.y, 
                          0, hwnd, NULL) ;
          
		return 0 ;
     
	case WM_COMMAND:

		switch (LOWORD (wParam))          
		{	
		case IDM_FRAME_INSERT:
				
			fi_tmp.angleL     = GetDlgItemInt(hParent, IDC_STATIC_ANGL, NULL, FALSE);
			fi_tmp.angleR     = GetDlgItemInt(hParent, IDC_STATIC_ANGR, NULL, FALSE);
			fi_tmp.len_Ratio  = GetDlgItemInt(hParent, IDC_STATIC_LEN, NULL, FALSE);
			    
			g_frame.AddFrame(frmarry_offset + pos_x/FRMWIDTH, fi_tmp);
   							    
			InvalidateRect (hwnd, NULL, TRUE) ;					
				
			SendMessage (hParent, WM_ENABLE_CONTROLS, frmarry_offset+pos_x/FRMWIDTH, 0) ;                

			return 0;

		case IDM_FRAME_DELETE:

			g_frame.RemoveFrame(frmarry_offset + pos_x/FRMWIDTH);
			
			InvalidateRect (hwnd, NULL, TRUE) ;	
			
			SendMessage (hParent, WM_DISABLE_CONTROLS, 0, 0) ;
	
			return 0;
		}
		break;

	case WM_LBUTTONDOWN :

		pos_x = LOWORD (lParam);
		pos_y = HIWORD (lParam);

		if( pos_y>15 && pos_y<43 )
		{  
			index = pos_x/FRMWIDTH ;
			InvalidateRect (hwnd, NULL, TRUE) ;

			if(state[index]) // this frame does exist, enable scroll bars 
			{                
			    SendMessage (hParent, WM_ENABLE_CONTROLS, frmarry_offset+pos_x/FRMWIDTH, 0) ;	
			}
			else // does not exist, just disable the scroll bars
			{
				SendMessage (hParent, WM_DISABLE_CONTROLS, 0, 0) ;
			}
		}

		return 0;

	case WM_LBUTTONDBLCLK:

		pos_x = LOWORD (lParam);
		pos_y = HIWORD (lParam);
				
		if( pos_y>15 && pos_y<43 )
		{  
            // 
			if(state[pos_x/FRMWIDTH]) // this frame does exist, delete it 
			{
                g_frame.RemoveFrame(frmarry_offset + pos_x/FRMWIDTH);
			    InvalidateRect (hwnd, NULL, TRUE) ;	
				SendMessage (hParent, WM_DISABLE_CONTROLS, 0, 0) ;
			}
			else // this frame does not exist, add it 
			{			
				fi_tmp.angleL     = GetDlgItemInt(hParent, IDC_STATIC_ANGL, NULL, FALSE);
				fi_tmp.angleR     = GetDlgItemInt(hParent, IDC_STATIC_ANGR, NULL, FALSE);
			    fi_tmp.len_Ratio  = GetDlgItemInt(hParent, IDC_STATIC_LEN, NULL, FALSE);

			    g_frame.AddFrame(frmarry_offset + pos_x/FRMWIDTH, fi_tmp);
   				
			    InvalidateRect (hwnd, NULL, TRUE) ;	
				
				SendMessage (hParent, WM_ENABLE_CONTROLS, frmarry_offset+pos_x/FRMWIDTH, 0) ;
			}

			state[pos_x/FRMWIDTH] ^= 1; // toggle the state
		}
		return 0;

	case WM_PAINT :

		hdc = BeginPaint (hwnd, &ps);
  
		//------------------------ some preprocessing -------------------------//
		si.cbSize = sizeof (si) ;
        si.fMask  = SIF_POS ;
        GetScrollInfo (hwnd, SB_HORZ, &si) ;
        iHorzPos = si.nPos ;
		begin = max(0,iHorzPos)+1;
	    //------------------------------------------------------------------////

		frmarry_offset = (begin-1)*5+1;  // set the offset, it is important, it is used to send frame obj
		                                 // then we can informed by frame which current frames should be labeled

		g_frame.FillStateArr(frmarry_offset, state);

		if(!state[index]) // if scroll bar's event causes paint, then need to check if the selected frame had a frame inserted 
		{
			SendMessage (hParent, WM_DISABLE_CONTROLS, 0, 0) ;
		}
		
		//------------------------------draw frames----------------------------//

		for(x=0;x<FRMNUM;x++)
		{
			Rectangle (hdc, x * FRMWIDTH, 20,
                      (x + 1) * FRMWIDTH, 52) ;
			if (index==x) // draw the frame that is selected by now               
			{
				hBrush = CreateHatchBrush (HS_DIAGCROSS, RGB(0,110,0)) ;		
                SetRect(&rect_frm,x * FRMWIDTH, 20,
                          (x + 1) * FRMWIDTH, 52);
				FillRect (hdc, &rect_frm, hBrush) ;

				DeleteObject (hBrush) ;
			}
			if (state[x]) // draw the frame that has been inserted a frame
			{
                hBrush = CreateSolidBrush( RGB(132,56,0) );
				hrgn = CreateEllipticRgn (x * FRMWIDTH + 2, 34, x * FRMWIDTH + 8, 41) ;
				FillRgn (hdc, hrgn, hBrush) ; 
                DeleteObject (hBrush) ;
			}
		}

		//------------------------------draw text------------------------------//
		        

		SetTextAlign (hdc, TA_RIGHT | TA_TOP) ;

		for (x=1; x<8; x++)
		{
            
			TextOut (hdc, x * 5 * FRMWIDTH, 0, szBuffer,
                        wsprintf (szBuffer, TEXT ("%3d"),
                                  begin * 5));
			begin++;
		}

		SetTextAlign (hdc, TA_LEFT | TA_TOP) ;

		EndPaint (hwnd, &ps);
		return 0 ;     

	case WM_ADD_FRAME:
         
		// the amount of added frames should be a number times 5
		if( (wParam%5) != 0 )
		{
			iMax += wParam + 5 -(wParam%5);
		}
		else
		{
			iMax += wParam;
		}

		si.cbSize = sizeof (si) ;
        si.fMask  = SIF_RANGE | SIF_PAGE ;
        si.nMin   = 0 ;
        si.nMax   = iMax/5 ;
        si.nPage  = PAGE ;
        SetScrollInfo (hwnd, SB_HORZ, &si, TRUE) ;
	
		return 0;
     
	case WM_HSCROLL:
               
		// Get all the vertical scroll bar information
          
		si.cbSize = sizeof (si) ;
        si.fMask  = SIF_ALL ;

        // Save the position for comparison later on
          
		GetScrollInfo (hwnd, SB_HORZ, &si) ;
        iHorzPos = si.nPos ;
          
		switch (LOWORD (wParam))
        {
          
		case SB_LINELEFT:
               
			si.nPos -= 1 ;
            break ;
                         
		case SB_LINERIGHT:
               
			si.nPos += 1 ;
            break ;
               
        case SB_PAGELEFT:
            si.nPos -= si.nPage ;
            break ;
               
        case SB_PAGERIGHT:
            si.nPos += si.nPage ;
            break ;
               
        case SB_THUMBPOSITION:
            si.nPos = si.nTrackPos ;
            break ;
               
        default :
            break ;
        }
               
		// Set the position and then retrieve it.  Due to adjustments
        // by Windows it may not be the same as the value set.

        si.fMask = SIF_POS ;
        SetScrollInfo (hwnd, SB_HORZ, &si, TRUE) ;
        GetScrollInfo (hwnd, SB_HORZ, &si) ;
          
        // If the position has changed, scroll the window 

        if (si.nPos != iHorzPos)
        {               
			InvalidateRect (hwnd, NULL, TRUE) ;
        }
          
		return 0 ;          

	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}

// draw sample graphics to a window, parameters are length ratio and angle

void DrawSampleToBlock(HWND hctrl, double ra, double agL, double agR)
{
	HDC hdc;
     
	RECT rect;
	HPEN hPen;
	InvalidateRect (hctrl, NULL, TRUE);
     
	UpdateWindow (hctrl);

	hdc = GetDC(hctrl);
     
	GetClientRect (hctrl, &rect);

	SelectObject (hdc, hBrushWhite);

	Rectangle (hdc, rect.left, rect.top, rect.right, rect.bottom);

	double length = rect.bottom / 6;
	
	SetViewportOrgEx (hdc, rect.right/2, rect.bottom/2, NULL) ;

	hPen = CreatePen (PS_SOLID, 1, RGB(123,0,0)) ;
       
	SelectObject (hdc, hPen);



	LineTo(hdc, 0,  - (length * ra));
	
	MoveToEx(hdc, 0, 0, NULL);
	
	LineTo(hdc, length*ra*sin(agL),  -(length*ra*cos(agL)) );
	
	MoveToEx(hdc, 0, 0, NULL);

	LineTo(hdc, -length*ra*sin(agR),  -(length*ra*cos(agR)) );

	ReleaseDC (hctrl, hdc);
				
	DeleteObject (hPen);
}


BOOL CALLBACK AnimDlgProc (HWND hDlg, UINT message, 
                           WPARAM wParam, LPARAM lParam)
{

	static HWND hCtrl_Len, hCtrl_AngL, hCtrl_AngR, hStic ;
		
	HWND hCtrl;

	FRAMEINFO fi_tmp;

	char frmStr[4];

	int nfrm;

	int iCtrlID;

	static int crt_frame = 1;

	static int len_ratio = 20, degreeL = 0, degreeR = 0;

	switch (message)     
	{		
	case WM_INITDIALOG :

		// disable the scroll bars initially

	    hCtrl_Len =GetDlgItem (hDlg, 1125);
		SetScrollRange (hCtrl_Len, SB_CTL, 20, 300, FALSE);
        SetScrollPos   (hCtrl_Len, SB_CTL, 20, FALSE);
        SetDlgItemInt (hDlg, IDC_STATIC_LEN, len_ratio, FALSE) ;

		EnableWindow (hCtrl_Len, FALSE);


		// disable the scroll bars initially

		hCtrl_AngL = GetDlgItem (hDlg, 1126);
		SetScrollRange (hCtrl_AngL, SB_CTL, 0, 359, FALSE);
        SetScrollPos   (hCtrl_AngL, SB_CTL, 0, FALSE);
		SetDlgItemInt (hDlg,  IDC_STATIC_ANGL, degreeL, FALSE) ;

		EnableWindow (hCtrl_AngL, FALSE);
	
		// disable the scroll bars initially

		hCtrl_AngR = GetDlgItem (hDlg, 1127);
		SetScrollRange (hCtrl_AngR, SB_CTL, 0, 359, FALSE);
        SetScrollPos   (hCtrl_AngR, SB_CTL, 0, FALSE);
		SetDlgItemInt (hDlg,  IDC_STATIC_ANGR, degreeR, FALSE) ;

		EnableWindow (hCtrl_AngR, FALSE);
		
		////
		hStic = GetDlgItem(hDlg, 1130);

		DrawSampleToBlock(hStic, double(len_ratio)/100, double(degreeL) * PI /180, double(degreeR) * PI /180);

		return TRUE;

     case WM_HSCROLL :

          hCtrl  = (HWND) lParam ;
          iCtrlID = GetWindowLong (hCtrl, GWL_ID) ;
         
		  if( hCtrl == hCtrl_Len)
		  {
			  switch (LOWORD (wParam))         
			  {                  
			  case SB_LINERIGHT :
               
				  len_ratio = min (300, len_ratio + 1) ;               
				  break ;
          
			  case SB_LINELEFT :
               
				  len_ratio = max (0, len_ratio - 1) ;
                  break ;
                
			  case SB_PAGELEFT:
         
				  len_ratio = max (0, len_ratio - 15) ;
				  break ;
                       
			  case SB_PAGERIGHT:
          
				  len_ratio = min (300, len_ratio + 15) ;
				  break ;

			  case SB_THUMBPOSITION :         
			  case SB_THUMBTRACK :
               
				  len_ratio = HIWORD (wParam) ;
                  break ;
          
			  default :               
				  return FALSE ;          
			  }
	          		  
			  SetScrollPos  (hCtrl_Len, SB_CTL, len_ratio, TRUE) ;          
			  SetDlgItemInt (hDlg, IDC_STATIC_LEN, len_ratio, FALSE) ;
		  }
		  else if( hCtrl == hCtrl_AngL)
		  {
			  switch (LOWORD (wParam))          
			  {                   
			  case SB_LINERIGHT :
               
				  degreeL = min (300, degreeL + 1) ;               
				  break ;
          
			  case SB_LINELEFT :
               
				  degreeL = max (0, degreeL - 1) ;
                  break ;
    
			  case SB_PAGELEFT:
         
				  degreeL = max (0, degreeL - 15) ;
				  break ;
                       
			  case SB_PAGERIGHT:
          
				  degreeL = min (300, degreeL + 15) ;
				  break ;
				  
			  case SB_THUMBPOSITION :          
			  case SB_THUMBTRACK :
               
				  degreeL = HIWORD (wParam) ;
                  break ;
       
			  default :
               
				  return FALSE ;         
			  }
	          		  
			  SetScrollPos  (hCtrl_AngL, SB_CTL, degreeL, TRUE) ;         
			  SetDlgItemInt (hDlg, IDC_STATIC_ANGL, degreeL, FALSE) ;
			
		  }
		  else if( hCtrl == hCtrl_AngR)
		  {
			  switch (LOWORD (wParam))          
			  {                   
			  case SB_LINERIGHT :
               
				  degreeR = min (300, degreeR + 1) ;               
				  break ;
          
			  case SB_LINELEFT :
               
				  degreeR = max (0, degreeR - 1) ;
                  break ;
    
			  case SB_PAGELEFT:
         
				  degreeR = max (0, degreeR - 15) ;
				  break ;
                       
			  case SB_PAGERIGHT:
          
				  degreeR = min (300, degreeR + 15) ;
				  break ;
				  
			  case SB_THUMBPOSITION :          
			  case SB_THUMBTRACK :
               
				  degreeR = HIWORD (wParam) ;
                  break ;
       
			  default :
               
				  return FALSE ;         
			  }
	          		  
			  SetScrollPos  (hCtrl_AngR, SB_CTL, degreeR, TRUE) ;         
			  SetDlgItemInt (hDlg, IDC_STATIC_ANGR, degreeR, FALSE) ;
			
		  }

          fi_tmp.angleL = degreeL;
		  fi_tmp.angleR = degreeR;
          fi_tmp.len_Ratio = len_ratio;
		  g_frame.UpdateFrmInfo(crt_frame, fi_tmp);

		  DrawSampleToBlock(hStic, double(len_ratio)/100, double(degreeL) * PI /180, double(degreeR) * PI /180);
		  return TRUE ;

		  
	 case WM_ENABLE_CONTROLS:

		 // get the informations of the selected frame from Frame object

		 crt_frame = wParam;

		 fi_tmp = *(g_frame.GetFrame(crt_frame));

		 // enable length scroll bar and set its value

		 EnableWindow(hCtrl_Len, TRUE);
		 len_ratio = max(20,fi_tmp.len_Ratio);    // get data of the frame
		 SetScrollPos  (hCtrl_Len, SB_CTL, len_ratio, TRUE) ;         		
		 SetDlgItemInt (hDlg, IDC_STATIC_LEN, len_ratio, FALSE) ; // set static text
		 
		 // enable angle scroll bar and set its value

		 EnableWindow(hCtrl_AngL, TRUE);
         degreeL = fi_tmp.angleL;    // get data of the frame
		 SetScrollPos  (hCtrl_AngL, SB_CTL, degreeL, TRUE) ;         		
		 SetDlgItemInt (hDlg, IDC_STATIC_ANGL, degreeL, FALSE) ; // set static text

		 // enable angle scroll bar and set its value

		 EnableWindow(hCtrl_AngR, TRUE);
         degreeR = fi_tmp.angleR;    // get data of the frame
		 SetScrollPos  (hCtrl_AngR, SB_CTL, degreeR, TRUE) ;         		
		 SetDlgItemInt (hDlg, IDC_STATIC_ANGR, degreeR, FALSE) ; // set static text

		 DrawSampleToBlock(hStic, double(len_ratio)/100, double(degreeL) * PI /180, double(degreeR) * PI /180);

		 return TRUE;
	
	 case WM_DISABLE_CONTROLS:

		 EnableWindow(hCtrl_Len, FALSE);
		 EnableWindow(hCtrl_AngL, FALSE);
		 EnableWindow(hCtrl_AngR, FALSE);
		 return TRUE;

	 case WM_COMMAND:
			 
		switch (LOWORD (wParam))			 
		{
				 
		case IDOK:					 

			EndDialog (hDlg, TRUE);
					 
			return TRUE;
				 
		case IDCANCEL:
					 
			EndDialog (hDlg, FALSE);
			
			g_frame.RemoveALL();  // if user clicks cancel button, then clear
					 
			return TRUE; 
	
		case IDC_BTN_ADD_FRM:

			if( 0==GetDlgItemText (hDlg, IDC_EDIT_FRM, frmStr, 4) )
			{								  
				MessageBox (NULL, TEXT ("Please type in a number for frames!"),
					  TEXT("Invalid Input"), MB_ICONINFORMATION);
			}
			else
			{
				nfrm = atoi(frmStr);

				// send message to anim control that more frames had been added
				SendMessage (GetDlgItem (hDlg, IDC_ANIM_FRAME),
                         WM_ADD_FRAME, nfrm, 0);					
			}
			return TRUE; 	  
		}				

	}

	return FALSE;
}

LRESULT CALLBACK PlayWndProc (HWND hwnd, UINT message, 
                             WPARAM wParam, LPARAM lParam)
{ 
	
	PAINTSTRUCT ps;

	static Animation g_anim;

	static double * lenarry;
	static double * angLarry;
	static double * angRarry;
	static int * frmarray;

	static int crt_idx; // indicate the current location of arrays
    static int frmcount;
	static double al, ar, r;

	switch (message)		 	
	{
     	
	case WM_CREATE:

		if(g_frame.MapSize()>1)
		{
			frmarray = new int[g_frame.MapSize()-1];
			lenarry = new double[g_frame.MapSize()-1];
			angLarry = new double[g_frame.MapSize()-1];
			angRarry = new double[g_frame.MapSize()-1];

			g_frame.FillAniArry(frmarray, lenarry, angLarry, angRarry);

			SetTimer (hwnd, ID_TIMER, interval, NULL);

			crt_idx = 0;
			frmcount = g_frame.FrsFrmIndex();
			al = g_frame.FrsFrmAngL();
			ar = g_frame.FrsFrmAngR();
			r = g_frame.FrsFrmLen();
		}

		return 0;
     
	case WM_TIMER:

		frmcount++;

		al += angLarry[crt_idx];
		ar += angRarry[crt_idx];
		r += lenarry[crt_idx];

		if(frmcount>frmarray[crt_idx])
		{
			crt_idx++;
		}

        if( crt_idx == g_frame.MapSize())
		{
			crt_idx = 0;
			KillTimer (hwnd, ID_TIMER); 
		}
		else
		{		
			InvalidateRect (hwnd, NULL, TRUE);
		}

		return 0;         
     
	case WM_PAINT:

		BeginPaint (hwnd, &ps);	
		EndPaint (hwnd, &ps);

		if(g_frame.MapSize()>0)
		{		
			g_anim.DrawAni(hwnd, r/100, al, ar, g_dg, fAng, fLen);
		}
		return 0;
	
	case WM_DESTROY:
          
		KillTimer (hwnd, ID_TIMER) ;

		delete [] frmarray;
		delete [] lenarry;         
		delete [] angLarry;
		delete [] angRarry;
		
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;

}


BOOL CALLBACK ExportDlgProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
     switch (message)
     {
     case WM_INITDIALOG :
          return FALSE ;
          
     case WM_COMMAND :

          switch (LOWORD (wParam))
          {
          case IDOK :
              if(0==GetDlgItemText(hDlg, IDC_EXPORT_NAME, g_name, 19))
			  {
				  MessageBox(NULL, TEXT ("Please type in a letter!"),
                    
					  TEXT("Invalid Input"), MB_ICONINFORMATION);
			  }
			  else
			  {

				  EndDialog (hDlg, TRUE) ;
			  }
			  return TRUE;
			  
          case IDCANCEL :
               
			  EndDialog (hDlg, FALSE) ;
              
			  return TRUE ;
          }
          break ;
     }
     return FALSE ;
}
