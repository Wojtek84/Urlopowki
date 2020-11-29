#include <windows.h>
#include <fstream>
#include <winuser.h>
#include <string.h>
#include <wingdi.h>
#include <Windowsx.h>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "funcs.hpp"

HWND DFDlgWnd;
HFONT hFontC, hFontV;
HWND w1c, w1v, w2c, w2v, w3c, w3v, w4c, w4v, w5c, w5v, w6c, w6v, w7c, w7v, w8c, w8v, w9c, w9v, w10c, w10v;


//void CreateDlg(speditor TheSped, HWND hParent)
//{
   // DFDlgWnd = CreateWindowEx (
   //       0,                   /* Extended possibilites for variation */
   //        0,         /* Classname */
   //        "Dane firmy",       /* Title Text */
   //        WS_DLGFRAME | WS_POPUPWINDOW, /* default window */
   //        CW_USEDEFAULT,       /* Windows decides the position */
   //       CW_USEDEFAULT,       /* where the window ends up on the screen */
   //        550,                 /* The programs width */
   //        490,                 /* and height in pixels */
   //        hParent,        /* The window is a child-window to desktop */
   //        NULL,                /* No menu */
   //        NULL,       /* Program Instance handler */
   //       NULL                 /* No Window Creation data */
   //      );    
   
   //  hFontC = CreateFont(20,0,0,0,700,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,0, VARIABLE_PITCH,TEXT("Times New Roman"));
   //  hFontV = CreateFont(20,0,0,0,350,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,0, VARIABLE_PITCH,TEXT("Times New Roman"));
     
   //  w1c = CreateWindow("STATIC","Nazwa:", WS_CHILD | WS_VISIBLE, 100, 10, 250, 25, DFDlgWnd, (HMENU)110, NULL, DFDlgWnd);  
   //  SendMessage(w1c, WM_SETFONT,( WPARAM ) hFontC, 0);	
     
  //   ShowWindow(DFDlgWnd, nFunsterStil);
//}

BOOL CALLBACK DlgABProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  switch( Msg )
    {
    case WM_COMMAND:
        {
            // reakcja na przyciski
            switch( LOWORD( wParam ) )
            {
            case 403: 
          	    FMessage("IDB_EXIT");
				EndDialog( hwnd, 1); 
				break;
			default:
				FMessage("KURWA TWOJA PIERDOLONA MAÆ!");
				break;
            }
        }
        break;
       
        default: return FALSE;
    }
   
    return TRUE;
}
