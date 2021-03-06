#include <windows.h>
#include <fstream>
#include <winuser.h>
#include <string.h>
#include <wingdi.h>
#include <Windowsx.h>
#include "driver.hpp"
#include "speditor.hpp"
#include <commctrl.h>
#include "funcs.hpp"
#include "Resource.h"
#include "Archive.hpp"
#include <sqlite3.h>

driver TheDriver;
speditor TheSpeditor;
archive TheArchive;
HWND c1, c2, c3, c4, c51, c52, c53, c54, c55, c56, c6, c7, c8, t0a, t0b,  t1, t2, t3, t4, t5, t6, t7, c5a; 
HWND hwnd;               /* This is the handle for our window */
int new_add_d;
int new_add_s;

using namespace std;

int LoadSpeditor(void *data, int argc, char **argv, char **azColName) // �adowanie wierszy do tabeli zbiorczej
{
    strcpy(TheSpeditor.id, argv[0]);     //id
	strcpy(TheSpeditor.name, argv[1]);   //nazwa
	strcpy(TheSpeditor.street, argv[2]); //ulica
	strcpy(TheSpeditor.number, argv[3]); //numer
    strcpy(TheSpeditor.city, argv[4]);   //miasto
    strcpy(TheSpeditor.postal, argv[5]); //kod
    strcpy(TheSpeditor.owner, argv[6]);  //w�a�ciciel
    strcpy(TheSpeditor.phone, argv[7]);  //telefon
    strcpy(TheSpeditor.email, argv[8]);  //email
    strcpy(TheSpeditor.fax, argv[9]);   //fax
    strcpy(TheSpeditor.country, argv[10]);   //kraj
	return 0;
}

int LoadDriver(void *data, int argc, char **argv, char **azColName) // �adowanie wierszy do tabeli zbiorczej
{
	strcpy(TheDriver.id, argv[0]);       //id
	strcpy(TheDriver.name, argv[1]);     //Imie i nazwisko
	strcpy(TheDriver.birth, argv[2]);    //data urodzenia
	strcpy(TheDriver.jobstart, argv[3]); //data zatrudnienia
    strcpy(TheDriver.nrdoc, argv[4]);    //numer dokument�w
    strcpy(TheDriver.company, argv[5]);  //firma id
	return 0;
}

int LoadCombo2(void *data, int argc, char **argv, char **azColName) // �adowanie wierszy do tabeli zbiorczej
{  
    int iCount = SendMessage(c2, CB_GETCOUNT, 0, 0);
    SendMessage(c2, CB_ADDSTRING, iCount, (LPARAM) argv[0]);
	return 0;
}

int LoadCombo3(void *data, int argc, char **argv, char **azColName) // �adowanie wierszy do listy firm w oknie danych kierowcy
{ 
    int iCount2 = SendMessage(c5a, CB_GETCOUNT, 0, 0);	
    SendMessage(c5a, CB_ADDSTRING, iCount2, (LPARAM) argv[0]);	
    return 0;
}

int LoadArchive(void *data, int argc, char **argv, char **azColName)  //�adowanie danych z archiwum
{
	SetWindowText(c3,argv[0]);
	SetWindowText(c4,argv[1]);
	SetWindowText(c6,argv[3]);
	int pos = atoi(argv[2]);
    switch(pos)
    {
      case 1:
           Button_SetCheck(c51, BST_CHECKED);
           Button_SetCheck(c52, BST_UNCHECKED);
           Button_SetCheck(c53, BST_UNCHECKED);
           Button_SetCheck(c54, BST_UNCHECKED);
           Button_SetCheck(c55, BST_UNCHECKED);
           Button_SetCheck(c56, BST_UNCHECKED);
           break; 
      case 2:
           Button_SetCheck(c52, BST_CHECKED);
           Button_SetCheck(c51, BST_UNCHECKED);
           Button_SetCheck(c53, BST_UNCHECKED);
           Button_SetCheck(c54, BST_UNCHECKED);
           Button_SetCheck(c55, BST_UNCHECKED);
           Button_SetCheck(c56, BST_UNCHECKED);
           break;
      case 3:
           Button_SetCheck(c53, BST_CHECKED);
           Button_SetCheck(c51, BST_UNCHECKED);
           Button_SetCheck(c52, BST_UNCHECKED);
           Button_SetCheck(c54, BST_UNCHECKED);
           Button_SetCheck(c55, BST_UNCHECKED);
           Button_SetCheck(c56, BST_UNCHECKED);
           break; 
      case 4:
           Button_SetCheck(c54, BST_CHECKED);
           Button_SetCheck(c51, BST_UNCHECKED);
           Button_SetCheck(c52, BST_UNCHECKED);
           Button_SetCheck(c53, BST_UNCHECKED);
           Button_SetCheck(c55, BST_UNCHECKED);
           Button_SetCheck(c56, BST_UNCHECKED);
           break;
       case 5:
           Button_SetCheck(c55, BST_CHECKED);
           Button_SetCheck(c51, BST_UNCHECKED);
           Button_SetCheck(c52, BST_UNCHECKED);
           Button_SetCheck(c53, BST_UNCHECKED);
           Button_SetCheck(c54, BST_UNCHECKED);
           Button_SetCheck(c56, BST_UNCHECKED);
           break; 
       case 6:
           Button_SetCheck(c56, BST_CHECKED);
           Button_SetCheck(c51, BST_UNCHECKED);
           Button_SetCheck(c52, BST_UNCHECKED);
           Button_SetCheck(c53, BST_UNCHECKED);
           Button_SetCheck(c54, BST_UNCHECKED);
           Button_SetCheck(c55, BST_UNCHECKED);
           break;
       default:
           break;            
    }
	return 0;
}

int Data_Save(int fcode)
{
 //fcode = 1 -> dane firmy
 //fcode = 2 -> dane kierowcy

 sqlite3 *db;
 char *zErrMsg = 0;
 int rc = 0;
 char sql3[500];
 rc = sqlite3_open("database.db", &db);
 int nfcode = 0;

switch(fcode)
 {
 	case 1: //Dane firmy
 		if(new_add_s == 1)
 		{
 		//itoa(TheSpeditor.id, buff, 10);	
 		strcpy(sql3, "UPDATE `speditors` SET `name` = '");	
 		strncat(sql3, TheSpeditor.name, strlen(TheSpeditor.name));
 		strncat(sql3, "', `street` = '", 15);
 		strncat(sql3, TheSpeditor.street, strlen(TheSpeditor.street));
 		strncat(sql3, "', `nr` = '", 11);
 		strncat(sql3, TheSpeditor.number, strlen(TheSpeditor.number));
 		strncat(sql3, "', `city` = '", 13);
 		strncat(sql3, TheSpeditor.city, strlen(TheSpeditor.city));
 		strncat(sql3, "', `postal` = '", 15);
 		strncat(sql3, TheSpeditor.postal, strlen(TheSpeditor.postal));
 		strncat(sql3, "', `owner` = '", 14);
 		strncat(sql3, TheSpeditor.owner, strlen(TheSpeditor.owner));
 		strncat(sql3, "', `phone` = '", 14);
 		strncat(sql3, TheSpeditor.phone, strlen(TheSpeditor.phone));
 		strncat(sql3, "', `email` = '", 14);
 		strncat(sql3, TheSpeditor.email, strlen(TheSpeditor.email));
 		strncat(sql3, "', `fax` = '", 12);
 		strncat(sql3, TheSpeditor.fax, strlen(TheSpeditor.fax));
 		strncat(sql3, "', `country` = '", 16);
 		strncat(sql3, TheSpeditor.country, strlen(TheSpeditor.country));
 		strncat(sql3, "' WHERE `id` =", 14);
 		strncat(sql3, TheSpeditor.id, strlen(TheSpeditor.country));
 		rc = sqlite3_exec(db, sql3, 0, 0, &zErrMsg);
        if( rc != SQLITE_OK )
	    	{
            sqlite3_free(zErrMsg);
	     	}
		}
 		else
 	    {	
 		strcpy(sql3, "INSERT INTO `speditors` (`name`, `street`, `nr`, `city`, `postal`, `owner`, `phone`, `email`, `fax`, `country`) VALUES ('");	
 		strncat(sql3, TheSpeditor.name, strlen(TheSpeditor.name));
 		strncat(sql3, "', '", 4);
 		strncat(sql3, TheSpeditor.street, strlen(TheSpeditor.street));
 		strncat(sql3, "', '", 4);
 		strncat(sql3, TheSpeditor.number, strlen(TheSpeditor.number));
 		strncat(sql3, "', '", 4);
 		strncat(sql3, TheSpeditor.city, strlen(TheSpeditor.city));
 		strncat(sql3, "', '", 4);
 		strncat(sql3, TheSpeditor.postal, strlen(TheSpeditor.postal));
 		strncat(sql3, "', '", 4);
 		strncat(sql3, TheSpeditor.owner, strlen(TheSpeditor.owner));
 		strncat(sql3, "', '", 4);
 		strncat(sql3, TheSpeditor.phone, strlen(TheSpeditor.phone));
 		strncat(sql3, "', '", 4);
 		strncat(sql3, TheSpeditor.email, strlen(TheSpeditor.email));
 		strncat(sql3, "', '", 4);
 		strncat(sql3, TheSpeditor.fax, strlen(TheSpeditor.fax));
 		strncat(sql3, "', '", 4);
 		strncat(sql3, TheSpeditor.country, strlen(TheSpeditor.country));
 		strncat(sql3, "');", 3);
 		rc = sqlite3_exec(db, sql3, 0, 0, &zErrMsg);
        if( rc != SQLITE_OK )
		{
            sqlite3_free(zErrMsg);
		}
		}
 		break;
 	case 2: //Dane kierowcy	
 	    if(new_add_d == 1)
 		{	
 		strcpy(sql3, "UPDATE `drivers` SET `name` = '");	
 		strncat(sql3, TheDriver.name, strlen(TheDriver.name));
 		strncat(sql3, "', `birth` = '", 14);
 		strncat(sql3, TheDriver.birth, strlen(TheDriver.birth));
 		strncat(sql3, "', `documents` = '", 18);
 		strncat(sql3, TheDriver.nrdoc, strlen(TheDriver.nrdoc));
 		strncat(sql3, "', `employed` = '", 17);
 		strncat(sql3, TheDriver.jobstart, strlen(TheDriver.jobstart));
 		strncat(sql3, "', `company` = ", 15);
 		strncat(sql3, TheDriver.company, strlen(TheDriver.company));
 		strncat(sql3, " WHERE `id` =", 13);
 		strncat(sql3, TheDriver.id, strlen(TheDriver.id));
 		rc = sqlite3_exec(db, sql3, 0, 0, &zErrMsg);
        if( rc != SQLITE_OK )
		 {
            sqlite3_free(zErrMsg);
		 }
		}
		else
		{
		strcpy(sql3, "INSERT INTO `drivers` (`name`, `birth`, `documents`, `employed`, `company`) VALUES ('");	
 		strncat(sql3, TheDriver.name, strlen(TheDriver.name));
 		strncat(sql3, "', '", 14);
 		strncat(sql3, TheDriver.birth, strlen(TheDriver.birth));
 		strncat(sql3, "', '", 18);
 		strncat(sql3, TheDriver.nrdoc, strlen(TheDriver.nrdoc));
 		strncat(sql3, "', '", 17);
 		strncat(sql3, TheDriver.jobstart, strlen(TheDriver.jobstart));
 		strncat(sql3, "', ", 15);
 		strncat(sql3, TheDriver.company, strlen(TheDriver.company));
 		strncat(sql3, " )", 2);
		rc = sqlite3_exec(db, sql3, 0, 0, &zErrMsg);
        if( rc != SQLITE_OK )
		 {
            sqlite3_free(zErrMsg);
		 }
		strcpy(sql3, "INSERT INTO `archive` (`driver`, `start`, `finish`, `action`, `place`) VALUES (");
		strncat(sql3, TheDriver.id, strlen(TheDriver.id));
		strncat(sql3, ", '01-01-1901', '01-01-1901', 3, '..........')", 46);
		rc = sqlite3_exec(db, sql3, 0, 0, &zErrMsg);
        if( rc != SQLITE_OK )
		 {
            sqlite3_free(zErrMsg);
		 }
		}
 	    break;
 	case 3: //Dane archiwum
	    strcpy(sql3, "UPDATE `archive` SET `start` = '");
	    strncat(sql3, TheArchive.astart, strlen(TheArchive.astart));
	    strncat(sql3, "', `finish` = '", 15);
	    strncat(sql3, TheArchive.akoniec, strlen(TheArchive.akoniec));
	    strncat(sql3, "', `action` = ", 14);
	    strncat(sql3, TheArchive.aaction, strlen(TheArchive.aaction));
	    strncat(sql3, ", `place` = '", 13);
	    strncat(sql3, TheArchive.aplace, strlen(TheArchive.aplace));
	    strncat(sql3, "' WHERE `driver` = ", 19);
	    strncat(sql3, TheArchive.idpr, strlen(TheArchive.idpr));
	    rc = sqlite3_exec(db, sql3, 0, 0, &zErrMsg);
        if( rc != SQLITE_OK )
		{
            sqlite3_free(zErrMsg);
		}
	    break;    
 }
 sqlite3_close(db);
 return 1;
}


int Data_Select(int fcode, LPCTSTR row_id)
{
 //fcode = 1 -> dane firmy
 //fcode = 2 -> dane kierowcy

 sqlite3 *db;
 char *zErrMsg = 0;
 int rc = 0;
 char sql2[500];
 LPCSTR sql;
 rc = sqlite3_open("database.db", &db);
 LPCTSTR nItem = "- - - - - - - - - - - - - - - - - - - - - - - - - - - -";

switch(fcode)
 {
  case 1: //Dane firmy
 		strcpy(sql2, "SELECT `id`, `name`, `street`, `nr`, `city`, `postal`, `owner`, `phone`, `email`, `fax`, `country` FROM `speditors` WHERE `id` = ");
		strncat(sql2, row_id, 5);
		rc = sqlite3_exec(db, sql2, LoadSpeditor, 0, &zErrMsg);
        if( rc != SQLITE_OK )
		{
            sqlite3_free(zErrMsg);
		}
		break;
  case 2: //Dane kierowcy
       strcpy(sql2, "SELECT `id`, `name`, `birth`, `employed`, `documents`, `company` FROM `drivers` WHERE `id` = ");
       strncat(sql2, row_id, 5);
	   rc = sqlite3_exec(db, sql2, LoadDriver, 0, &zErrMsg);
       if( rc != SQLITE_OK )
	   {
            sqlite3_free(zErrMsg);
	   }
	   break;
  case 3: //Lista kierowc�w 
       SendMessage(c2, CB_ADDSTRING, 0, (LPARAM) nItem);
       sql = "SELECT `name` FROM `drivers`";
	   rc = sqlite3_exec(db, sql, LoadCombo2, 0, &zErrMsg);
       if( rc != SQLITE_OK )
	   {
            sqlite3_free(zErrMsg);
	   }
       break;
  case 4: //Archiwum
       strcpy(sql2, "SELECT `start`, `finish`, `action`, `place` FROM `archive` WHERE `driver` = ");
       strncat(sql2, row_id, 5);
	   rc = sqlite3_exec(db, sql2, LoadArchive, 0, &zErrMsg);
       if( rc != SQLITE_OK )
	   {
            sqlite3_free(zErrMsg);
	   }
       break;
   case 5:  //lista firm
       strcpy(sql2, "SELECT `name` FROM `speditors` ORDER BY `id`");
       rc = sqlite3_exec(db, sql2, LoadCombo3, 0, &zErrMsg);
       if( rc != SQLITE_OK )
	   {
            sqlite3_free(zErrMsg);
	   }
       break;    
 }  
 sqlite3_close(db);
 return 0;
}

BOOL CALLBACK DlgABProc(HWND ahwnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  int DlgItem;
  HFONT DlgFontC;
  HWND DlgItemWnd;
  HDC DlgItemDC;
  HBRUSH DlgBrush = CreateSolidBrush( RGB(192, 192, 192 ) );  //tlo
  COLORREF Dlgcl;
  switch( Msg )
    {
    case WM_INITDIALOG:
    	{
		 DlgFontC = CreateFont(18,0,0,0,700,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,0, VARIABLE_PITCH,TEXT("Times New Roman"));
         SendDlgItemMessageA(ahwnd, 401, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
		 SendDlgItemMessageA(ahwnd, 402, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
		 SendDlgItemMessageA(ahwnd, 403, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
	   }	
	   break;
    case WM_COMMAND:
        {
            // reakcja na przyciski
            switch( LOWORD( wParam ) )
            {
            case 403: 
				EndDialog( ahwnd, 1); 
				break;
			default:
			   	EndDialog( ahwnd, 1); 
				break;
            }
        }
        break; 
    case WM_CTLCOLORSTATIC: //obsluga kolorow w kontrolkach            
           DlgItemWnd = (HWND) lParam;
           DlgItem = GetDlgCtrlID(DlgItemWnd);
           DlgItemDC = (HDC) wParam;
           DlgFontC = CreateFont(18,0,0,0,700,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,0, VARIABLE_PITCH,TEXT("Times New Roman"));
           if(DlgItem == 401)
           {
           	     Dlgcl = RGB(5,10,200);  
                 SetBkMode(DlgItemDC, TRANSPARENT);
                 SetTextColor(DlgItemDC,Dlgcl);
                 return( LRESULT ) DlgBrush;
           }
           if(DlgItem == 402)
           {
				 Dlgcl = RGB(0,0,0);   
                 SetBkMode(DlgItemDC, TRANSPARENT);
                 SetTextColor(DlgItemDC,Dlgcl);
                 return( LRESULT ) DlgBrush;
           }
           if(DlgItem == 405)
           {
                 SetBkMode(DlgItemDC, TRANSPARENT);
                 return( LRESULT ) DlgBrush;
           }
          break; //koniec obslugi kolorow w kontrolkach
        default: return FALSE;
    }
   
    return TRUE;
}

BOOL CALLBACK DlgDFProc(HWND dhwnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{	
    int DlgItem;
    HFONT DlgFontC;
    HWND DlgItemWnd;
    HDC DlgItemDC;
    HBRUSH DlgBrush = CreateSolidBrush( RGB(192, 192, 192 ) );  //tlo
    COLORREF Dlgcl;
    //char tabm[32]; 
    char t_val[101];
    int err_code = 0;
    LPCTSTR nItem = "- - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    
  switch( Msg )
    {
    case WM_INITDIALOG:
        {
        	SetDlgItemTextA(dhwnd, 2011, TheSpeditor.name);
        	SetDlgItemTextA(dhwnd, 2013, TheSpeditor.street);
        	SetDlgItemTextA(dhwnd, 2015, TheSpeditor.number);
        	SetDlgItemTextA(dhwnd, 2017, TheSpeditor.city);
        	SetDlgItemTextA(dhwnd, 2019, TheSpeditor.postal);
        	SetDlgItemTextA(dhwnd, 2021, TheSpeditor.owner);
        	SetDlgItemTextA(dhwnd, 2023, TheSpeditor.phone);
        	SetDlgItemTextA(dhwnd, 2025, TheSpeditor.email);
        	SetDlgItemTextA(dhwnd, 2027, TheSpeditor.fax);
        	SetDlgItemTextA(dhwnd, 2029, TheSpeditor.country);
        	DlgFontC = CreateFont(18,0,0,0,700,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,0, VARIABLE_PITCH,TEXT("Times New Roman"));
        	SendDlgItemMessageA(dhwnd, 2010, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2012, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2014, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2016, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2018, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2020, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2022, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2024, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2026, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2028, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2011, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2013, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2015, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2017, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2019, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2021, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2023, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2025, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2027, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2029, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2008, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2009, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(dhwnd, 2011, EM_SETLIMITTEXT, (WPARAM) 64, 0);
        	SendDlgItemMessageA(dhwnd, 2013, EM_SETLIMITTEXT, (WPARAM) 50, 0);
        	SendDlgItemMessageA(dhwnd, 2015, EM_SETLIMITTEXT, (WPARAM) 10, 0);
        	SendDlgItemMessageA(dhwnd, 2017, EM_SETLIMITTEXT, (WPARAM) 30, 0);
        	SendDlgItemMessageA(dhwnd, 2019, EM_SETLIMITTEXT, (WPARAM) 6, 0);
        	SendDlgItemMessageA(dhwnd, 2021, EM_SETLIMITTEXT, (WPARAM) 50, 0);
            SendDlgItemMessageA(dhwnd, 2023, EM_SETLIMITTEXT, (WPARAM) 20, 0);
            SendDlgItemMessageA(dhwnd, 2025, EM_SETLIMITTEXT, (WPARAM) 30, 0);
            SendDlgItemMessageA(dhwnd, 2027, EM_SETLIMITTEXT, (WPARAM) 20, 0);
            SendDlgItemMessageA(dhwnd, 2029, EM_SETLIMITTEXT, (WPARAM) 4, 0);
            if(new_add_s == 2)
            {
             SetDlgItemTextA(dhwnd, 2011, nItem);
        	 SetDlgItemTextA(dhwnd, 2013, nItem);
        	 SetDlgItemTextA(dhwnd, 2015, nItem);
        	 SetDlgItemTextA(dhwnd, 2017, nItem);
        	 SetDlgItemTextA(dhwnd, 2019, "..-...");
        	 SetDlgItemTextA(dhwnd, 2021, nItem);
        	 SetDlgItemTextA(dhwnd, 2023, nItem);
        	 SetDlgItemTextA(dhwnd, 2025, nItem);
        	 SetDlgItemTextA(dhwnd, 2027, nItem);
        	 SetDlgItemTextA(dhwnd, 2029, "...");	
			}
        }	
        break;
    case WM_COMMAND:
        {
            // reakcja na przyciski
            switch( LOWORD( wParam ) )
            {
            case 2008: 
				EndDialog( dhwnd, 1); 
				break;
			case 2009: 
			 GetDlgItemText(dhwnd, 2011, (LPSTR)&t_val, 100);  //Nazwa
             strcpy(TheSpeditor.name, t_val);
             
			 GetDlgItemText(dhwnd, 2013, (LPSTR)&t_val, 100); //Ulica
			 strcpy(TheSpeditor.street, t_val);
			 
             GetDlgItemText(dhwnd, 2017, (LPSTR)&t_val, 100); //Miasto
		     strcpy(TheSpeditor.city, t_val);

			 GetDlgItemText(dhwnd, 2019, (LPSTR)&t_val, 100); //kod
             strcpy(TheSpeditor.postal, t_val);
		
			 GetDlgItemText(dhwnd, 2021, (LPSTR)&t_val, 100);  //w�a�ciciel
             strcpy(TheSpeditor.owner, t_val);
			  
			 GetDlgItemText(dhwnd, 2023, (LPSTR)&t_val, 100);  //telefon
			 strcpy(TheSpeditor.phone, t_val);
			  
		   	 GetDlgItemText(dhwnd, 2025, (LPSTR)&t_val, 100); //email
			 strcpy(TheSpeditor.email, t_val);

			 GetDlgItemText(dhwnd, 2027, (LPSTR)&t_val, 100);  //fax
			 strcpy(TheSpeditor.fax, t_val);
						  
			 GetDlgItemText(dhwnd, 2029, (LPSTR)&t_val, 100);
			 strcpy(TheSpeditor.country, t_val);  //kraj
			  
			 GetDlgItemText(dhwnd, 2015, (LPSTR)&t_val, 100); //Numer
			 strcpy(TheSpeditor.number, t_val);
			
		    Data_Save(1);
		    EndDialog( dhwnd, 1); 
		    
			break;	
			default:
				if(LOWORD(wParam)<2009 || LOWORD(wParam)>2029)
			   	EndDialog( dhwnd, 1); 
				break;
            }
        }
    case WM_CTLCOLORSTATIC: //obsluga kolorow w kontrolkach            
           DlgItemWnd = (HWND) lParam;
           DlgItem = GetDlgCtrlID(DlgItemWnd);
           DlgItemDC = (HDC) wParam;
           DlgFontC = CreateFont(18,0,0,0,700,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,0, VARIABLE_PITCH,TEXT("Times New Roman"));
           if(DlgItem == 1000)
           {
                 SetBkMode(DlgItemDC, TRANSPARENT);
                 return( LRESULT ) DlgBrush;
           }
           if(DlgItem == 2010 || DlgItem == 2012 || DlgItem== 2014 || DlgItem == 2016 || DlgItem == 2018 || DlgItem == 2020 || DlgItem == 2022 || DlgItem == 2024 || DlgItem == 2026 || DlgItem == 2028)
           {
				 Dlgcl = RGB(5,10,200);   
                 SetBkMode(DlgItemDC, TRANSPARENT);
                 SetTextColor(DlgItemDC,Dlgcl);
                 return( LRESULT ) DlgBrush;
           }
          break; //koniec obslugi kolorow w kontrolkach
        default: return FALSE;
    }
   
    return TRUE;
}


BOOL CALLBACK DlgDPProc(HWND phwnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{	
    int DlgItem;
    HFONT DlgFontC;
    HWND DlgItemWnd;
    HDC DlgItemDC;
    HBRUSH DlgBrush = CreateSolidBrush( RGB(192, 192, 192 ) );  //tlo
    COLORREF Dlgcl;
    char t_val[101];
    LPCTSTR nItem = "- - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    int CurSel = 0;
    
  switch( Msg )
    {
    case WM_INITDIALOG:
        {
        	c5a = CreateWindowEx(WS_EX_CLIENTEDGE, "COMBOBOX", "Firmy", WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST, 140, 100, 560, 800, phwnd, (HMENU)3021, NULL, NULL);         
        	SetDlgItemTextA(phwnd, 3011, TheDriver.name);
        	SetDlgItemTextA(phwnd, 3013, TheDriver.birth);
        	SetDlgItemTextA(phwnd, 3015, TheDriver.nrdoc);
        	SetDlgItemTextA(phwnd, 3017, TheDriver.jobstart);
        	SetDlgItemTextA(phwnd, 3019, TheDriver.company);
        	DlgFontC = CreateFont(18,0,0,0,700,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,0, VARIABLE_PITCH,TEXT("Times New Roman"));
        	SendDlgItemMessageA(phwnd, 3010, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(phwnd, 3012, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(phwnd, 3014, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(phwnd, 3016, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(phwnd, 3018, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(phwnd, 3011, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(phwnd, 3013, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(phwnd, 3015, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(phwnd, 3017, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(phwnd, 3019, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(phwnd, 3011, EM_SETLIMITTEXT, (WPARAM) 50, 0);
        	SendDlgItemMessageA(phwnd, 3013, EM_SETLIMITTEXT, (WPARAM) 10, 0);
        	SendDlgItemMessageA(phwnd, 3015, EM_SETLIMITTEXT, (WPARAM) 14, 0);
        	SendDlgItemMessageA(phwnd, 3017, EM_SETLIMITTEXT, (WPARAM) 10, 0);
        	SendDlgItemMessageA(phwnd, 3019, EM_SETLIMITTEXT, (WPARAM) 4, 0);
        	SendDlgItemMessageA(phwnd, 3008, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	SendDlgItemMessageA(phwnd, 3009, WM_SETFONT, ( WPARAM ) DlgFontC, 0);
        	if(new_add_d == 2)
        	{
        		SetDlgItemTextA(phwnd, 3011, nItem);
        		SetDlgItemTextA(phwnd, 3013, nItem);
        		SetDlgItemTextA(phwnd, 3015, nItem);
        		SetDlgItemTextA(phwnd, 3017, "..-..-....");
        		SetDlgItemTextA(phwnd, 3019, "..");
			}
			SendMessage(c5a, CB_ADDSTRING, 0, (LPARAM) nItem);
			Data_Select(5, 0);
			if(new_add_d == 1)
			{
				SendMessage(c5a, CB_SETCURSEL, atoi(TheSpeditor.id), 0);
			}
			else
			{
				SendMessage(c5a, CB_SETCURSEL, 0, 0);
			}
        }	
        break;
    case WM_COMMAND:
        {
            // reakcja na przyciski
            switch( LOWORD( wParam ) )
            {
            case 3008: 
				EndDialog( phwnd, 1); 
				break;
			case 3009: 
			 GetDlgItemText(phwnd, 3011, (LPSTR)&t_val, 100);  //Imi� i Nazwisko
             strcpy(TheDriver.name, t_val);
             
			 GetDlgItemText(phwnd, 3013, (LPSTR)&t_val, 100); //Data urodzenia
			 strcpy(TheDriver.birth, t_val);
			 
             GetDlgItemText(phwnd, 3015, (LPSTR)&t_val, 100); //Numer dokumentu
		     strcpy(TheDriver.nrdoc, t_val);

			 GetDlgItemText(phwnd, 3017, (LPSTR)&t_val, 100); //Zatrudniony od
             strcpy(TheDriver.jobstart, t_val);
		
			 //GetDlgItemText(phwnd, 3019, (LPSTR)&t_val, 100);  //Firma
			 CurSel = SendMessage(c5a, CB_GETCURSEL, 0, 0);
             itoa(CurSel, t_val, 10);
			 strcpy(TheDriver.company, t_val);
			 
		     //zapis danych do pliku/bazy
		     Data_Save(2);
		     EndDialog( phwnd, 1); 
			 break;	
			default:
				if(LOWORD(wParam)<3009 || LOWORD(wParam)>3021)
			   	EndDialog( phwnd, 1); 
				break;
            }
        }
    case WM_CTLCOLORSTATIC: //obsluga kolorow w kontrolkach            
           DlgItemWnd = (HWND) lParam;
           DlgItem = GetDlgCtrlID(DlgItemWnd);
           DlgItemDC = (HDC) wParam;
           DlgFontC = CreateFont(18,0,0,0,700,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,0, VARIABLE_PITCH,TEXT("Times New Roman"));
           if(DlgItem == 2000)
           {
                 SetBkMode(DlgItemDC, TRANSPARENT);
                 return( LRESULT ) DlgBrush;
           }
           if(DlgItem == 3010 || DlgItem == 3012 || DlgItem== 3014 || DlgItem == 3016 || DlgItem == 3018)
           {
				 Dlgcl = RGB(5,10,200);   
                 SetBkMode(DlgItemDC, TRANSPARENT);
                 SetTextColor(DlgItemDC,Dlgcl);
                 return( LRESULT ) DlgBrush;
           }
          break; //koniec obslugi kolorow w kontrolkach
        default: return FALSE;
    }
   
    return TRUE;
}



void PrintDoc()
{
int r = 0;
int PrintStatus = 1;
int idng = atoi(TheArchive.aaction);
HRESULT hResult;
LPPRINTDLGEX pPDX = NULL;
LPPRINTPAGERANGE pPageRanges = NULL;
HFONT TNR9_B;
HFONT TNR12_BU;
HFONT TNR9;
HFONT TNR8;
HFONT TNR9_U;
HFONT TNR6_S;

char s_place[64];

int line_h = 68;
int s_line_size = 0;
int s_place_size = 0;

s_line_size = 7 + strlen(TheSpeditor.street) + strlen(TheSpeditor.number) + strlen(TheSpeditor.postal) + strlen(TheSpeditor.city) + strlen(TheSpeditor.country);

char s_line[s_line_size];

strcpy(s_line, TheSpeditor.street);
strcat(s_line, " ");
strcat(s_line, TheSpeditor.number);
strcat(s_line, ", ");
strcat(s_line, TheSpeditor.postal);
strcat(s_line, ", ");
strcat(s_line, TheSpeditor.city);
strcat(s_line, ", ");
strcat(s_line, TheSpeditor.country);

strcpy(s_place, TheArchive.aplace);
strcat(s_place, "   data:   ");
char * ptr = new char[10];
ptr = &TheArchive.akoniec[6];
strcat(s_place, ptr);
delete [] ptr;
s_place_size = strlen(TheArchive.aplace)+21;

pPDX =(LPPRINTDLGEX) GlobalAlloc(GPTR, sizeof(PRINTDLGEX));
if(!pPDX)
     {
       PrintStatus = 0;  
     }

pPageRanges =(LPPRINTPAGERANGE) GlobalAlloc(GPTR, 10 * sizeof(PRINTPAGERANGE));
if(!pPageRanges)
    {
       PrintStatus = 0;
    }
if(PrintStatus == 1)
    {    
       pPDX->lStructSize = sizeof( PRINTDLGEX );
       pPDX->hwndOwner = hwnd;
       pPDX->hDevMode = NULL;
       pPDX->hDevNames = NULL;
       pPDX->hDC = NULL;
       pPDX->Flags = PD_RETURNDC | PD_COLLATE;
       pPDX->Flags2 = 0;
       pPDX->ExclusionFlags = 0;
       pPDX->nPageRanges = 0;
       pPDX->nMaxPageRanges = 10;
       pPDX->lpPageRanges = pPageRanges;
       pPDX->nMinPage = 1;
       pPDX->nMaxPage = 1;
       pPDX->nCopies = 1;
       pPDX->hInstance = 0;
       pPDX->lpPrintTemplateName = NULL;
       pPDX->lpCallback = NULL;
       pPDX->nPropertyPages = 0;
       pPDX->lphPropertyPages = NULL;
       pPDX->nStartPage = 0xffffffff;
       pPDX->dwResultAction = 0;  
       
       hResult = PrintDlgEx(pPDX);
       
       if(hResult == S_OK && pPDX->dwResultAction == 1)
          {
               DOCINFO docInfo;
               ZeroMemory(& docInfo, sizeof(docInfo));
               docInfo.cbSize = sizeof(docInfo);
               docInfo.lpszDocName = "Urlop�wka";
               r = StartDoc(pPDX->hDC, & docInfo);
               SetMapMode(pPDX->hDC, MM_LOMETRIC);
               if(r != SP_ERROR)
               {
                   r = StartPage(pPDX->hDC);
                   if( r > 0 )
                   {
                   int PgHeight;
                   int PgWidth;
                   int PgHres;
                   int PgWres;
                   PgHeight = GetDeviceCaps(pPDX->hDC, VERTRES);
                   PgWidth = GetDeviceCaps(pPDX->hDC, HORZRES);
                   PgHres = GetDeviceCaps(pPDX->hDC, LOGPIXELSY);
                   PgWres = GetDeviceCaps(pPDX->hDC, LOGPIXELSX);
                   
                   SetTextAlign(pPDX->hDC, TA_CENTER);
                   
                   int PrintScale = GetDeviceCaps(pPDX->hDC, LOGPIXELSY);
                   
                   if(GetDeviceCaps(pPDX->hDC, LOGPIXELSY) < 600)
                   {
                   	PrintScale = 600;
				   }
                   
                   int FT12 = -MulDiv(11, PrintScale, 140);
                   int FT9  = -MulDiv( 8, PrintScale, 140);
                   int FT6  = -MulDiv( 6, PrintScale, 140);
                   int FT8  = -MulDiv( 7, PrintScale, 140);
                   
                   TNR12_BU = CreateFont(FT12, 0, 0, 0, FW_BOLD, 0, 1, 0, EASTEUROPE_CHARSET, 0, 0, 0, 0, "Times New Roman");
                   TNR9_B = CreateFont(FT9, 0, 0, 0, FW_BOLD, 0, 0, 0, EASTEUROPE_CHARSET, 0, 0, 0, 0, "Times New Roman");
                   TNR9 = CreateFont(FT9, 0, 0, 0, 0, 0, 0, 0, EASTEUROPE_CHARSET, 0, 0, 0, 0, "Times New Roman");
                   TNR9_U = CreateFont(FT9, 0, 0, 0, 0, 0, 1, 0, EASTEUROPE_CHARSET, 0, 0, 0, 0, "Times New Roman");
                   TNR8 = CreateFont(FT8, 0, 0, 0, 0, 0, 0, 0, EASTEUROPE_CHARSET, 0, 0, 0, 0, "Times New Roman");
                   HFONT TNR6_S = CreateFont(FT6, 0, 0, 0, 0, 0, 0, 0, EASTEUROPE_CHARSET, 0, 0, 0, 0, "Times New Roman");
                   
                   SelectObject(pPDX->hDC, TNR12_BU);
                   TextOut(pPDX->hDC, 1049, -180, "ZA��CZNIK", 9);
                   SelectObject(pPDX->hDC, TNR9);
                   TextOut(pPDX->hDC, 1049, -250, "ZA�WIADCZENIE O DZIA�ALNO�CI", 28);
                   SelectObject(pPDX->hDC, TNR6_S);
                   TextOut(pPDX->hDC, 1340, -245, "1", 1);
                   SelectObject(pPDX->hDC, TNR9);
                   TextOut(pPDX->hDC, 1047, -290, "(ROZPORZ�DZENIE (WE) 561/2006 LUB AETR",38);
                   SelectObject(pPDX->hDC, TNR6_S);
                   TextOut(pPDX->hDC, 1407, -285, "2", 1);
                   SelectObject(pPDX->hDC, TNR9);  
                   TextOut(pPDX->hDC, 1418, -290, ")", 1); 
                   TextOut(pPDX->hDC, 1049, -345, "Nale�y wype�ni� na komputerze lub maszynowo i podpisa� przed rozpocz�ciem podr�y. Nale�y przechowywa� wraz z", 109);
                   TextOut(pPDX->hDC, 1049, -380, "oryginalnymi zapisami urz�dze� kontrolnych zgodnie z odpowiednimi wymogami", 74);
                   SelectObject(pPDX->hDC, TNR9_B);
                   TextOut(pPDX->hDC, 1049, -420, "SFA�SZOWANIE ZA�WIADCZENIA STANOWI NARUSZENIE PRZEPIS�W", 55);
                   SelectObject(pPDX->hDC, TNR9); 
                   Rectangle(pPDX->hDC, 200, -500, 1900, -(23*line_h+500));
                   SetTextAlign(pPDX->hDC, TA_LEFT);
                   SelectObject(pPDX->hDC, TNR9_B);
                   TextOut(pPDX->hDC, 220, -520, "Cz�� wype�niana przez przedsi�biorstwo", 39); 
                   SelectObject(pPDX->hDC, TNR9);
                   TextOut(pPDX->hDC, 220, -520-(line_h*1), "(1)", 3);
                   TextOut(pPDX->hDC, 370, -520-(line_h*1), "Nazwa przedsi�biorstwa:", 23);
                   TextOut(pPDX->hDC, 725, -520-(line_h*1), TheSpeditor.name, strlen(TheSpeditor.name));
                   TextOut(pPDX->hDC, 220, -520-(line_h*2), "(2)", 3);
                   TextOut(pPDX->hDC, 370, -520-(line_h*2), "Ulica i numer, kod pocztowy, miejscowo�c, pa�stwo:", 50);
                   TextOut(pPDX->hDC, 1105, -520-(line_h*2), s_line, s_line_size);
                   TextOut(pPDX->hDC, 220, -520-(line_h*3), "(3)", 3);
                   TextOut(pPDX->hDC, 370, -520-(line_h*3), "Numer telefonu (w tym mi�dzynarodowy numer kierunkowy):", 55);
                   TextOut(pPDX->hDC, 1225, -520-(line_h*3), TheSpeditor.phone, strlen(TheSpeditor.phone));
                   TextOut(pPDX->hDC, 220, -520-(line_h*4), "(4)", 3);
                   TextOut(pPDX->hDC, 370, -520-(line_h*4), "Numer faksu (w tym mi�dzynarodowy numer kierunkowy):", 52);
                   TextOut(pPDX->hDC, 1190, -520-(line_h*4), TheSpeditor.fax, strlen(TheSpeditor.fax));
                   TextOut(pPDX->hDC, 220, -520-(line_h*5), "(5)", 3);
                   TextOut(pPDX->hDC, 370, -520-(line_h*5), "Adres email:", 12);
                   TextOut(pPDX->hDC, 562, -520-(line_h*5), TheSpeditor.email, strlen(TheSpeditor.email));
                   SelectObject(pPDX->hDC, TNR9_B);
                   TextOut(pPDX->hDC, 220, -520-(line_h*6), "Ja, ni�ej podpisany:", 20); 
                   SelectObject(pPDX->hDC, TNR9);
                   TextOut(pPDX->hDC, 220, -520-(line_h*7), "(6)", 3);
                   TextOut(pPDX->hDC, 370, -520-(line_h*7), "Imi� i nazwisko:", 16);
                   TextOut(pPDX->hDC, 610, -520-(line_h*7), TheSpeditor.owner, strlen(TheSpeditor.owner));
                   TextOut(pPDX->hDC, 220, -520-(line_h*8), "(7)", 3);
                   TextOut(pPDX->hDC, 370, -520-(line_h*8), "Stanowisko w przedsi�biorstwie:", 31);
                   TextOut(pPDX->hDC, 830, -520-(line_h*8), "w�a�ciciel", 10);
                   SelectObject(pPDX->hDC, TNR9_B);
                   TextOut(pPDX->hDC, 220, -520-(line_h*9), "o�wiadczam, �e kierowca:", 24);
                   SelectObject(pPDX->hDC, TNR9);
                   TextOut(pPDX->hDC, 220, -520-(line_h*10), "(8)", 3);
                   TextOut(pPDX->hDC, 370, -520-(line_h*10), "Imi� i nazwisko:", 16);
                   TextOut(pPDX->hDC, 610, -520-(line_h*10), TheDriver.name, strlen(TheDriver.name));
                   TextOut(pPDX->hDC, 220, -520-(line_h*11), "(9)", 3);
                   TextOut(pPDX->hDC, 370, -520-(line_h*11), "Data urodzenia (dzie�-miesi�c-rok):", 35);
                   TextOut(pPDX->hDC, 880, -520-(line_h*11), TheDriver.birth, 10);
                   TextOut(pPDX->hDC, 220, -520-(line_h*12), "(10)", 4);
                   TextOut(pPDX->hDC, 370, -520-(line_h*12), "Numer prawa jazdy lub dowodu osobistego lub paszportu:", 54);
                   TextOut(pPDX->hDC, 1180, -520-(line_h*12), TheDriver.nrdoc, strlen(TheDriver.nrdoc));
                   TextOut(pPDX->hDC, 220, -520-(line_h*13), "(11)", 4);
                   TextOut(pPDX->hDC, 370, -520-(line_h*13), "kt�ry rozpocz�� prac� w przedsi�biorstwie dnia (dzie�-miesi�c-rok:", 66);
                   TextOut(pPDX->hDC, 1300, -520-(line_h*13), TheDriver.jobstart, strlen(TheDriver.jobstart));
                   SelectObject(pPDX->hDC, TNR9_B);
                   TextOut(pPDX->hDC, 220, -520-(line_h*14), "w okresie:", 10);
                   SelectObject(pPDX->hDC, TNR9);
                   TextOut(pPDX->hDC, 220, -520-(line_h*15), "(12)", 4);
                   TextOut(pPDX->hDC, 370, -520-(line_h*15), "od (godzina-dzie�-miesi�c-rok):", 31);
                   TextOut(pPDX->hDC, 820, -520-(line_h*15), TheArchive.astart, strlen(TheArchive.astart));
                   TextOut(pPDX->hDC, 220, -520-(line_h*16), "(13)", 4);
                   TextOut(pPDX->hDC, 370, -520-(line_h*16), "od (godzina-dzie�-miesi�c-rok):", 31);
                   TextOut(pPDX->hDC, 820, -520-(line_h*16), TheArchive.akoniec, strlen(TheArchive.akoniec));
                   TextOut(pPDX->hDC, 220, -520-(line_h*17), "(14)", 4);
                   Rectangle(pPDX->hDC, 308, -525-(line_h*17), 338, -525-(line_h*17)-30);
                   TextOut(pPDX->hDC, 370, -520-(line_h*17), "przebywa� na zwolnieniu lekarskim", 33);
                   SelectObject(pPDX->hDC, TNR6_S);
                   TextOut(pPDX->hDC, 851, -520-(line_h*17)+5, "***", 3);
                   SelectObject(pPDX->hDC, TNR9);
                   TextOut(pPDX->hDC, 220, -520-(line_h*18), "(15)", 4);
                   Rectangle(pPDX->hDC, 308, -525-(line_h*18), 338, -525-(line_h*18)-30);
                   TextOut(pPDX->hDC, 370, -520-(line_h*18), "przebywa� na urlopie wypoczynkowym", 34);
                   SelectObject(pPDX->hDC, TNR6_S);
                   TextOut(pPDX->hDC, 900, -520-(line_h*18)+5, "***", 3);
                   SelectObject(pPDX->hDC, TNR9);
                   TextOut(pPDX->hDC, 220, -520-(line_h*19), "(16)", 4);
                   Rectangle(pPDX->hDC, 308, -525-(line_h*19), 338, -525-(line_h*19)-30);
                   TextOut(pPDX->hDC, 370, -520-(line_h*19), "mia� czas wolny lub odpoczywa�", 30);
                   SelectObject(pPDX->hDC, TNR6_S);
                   TextOut(pPDX->hDC, 812, -520-(line_h*19)+5, "***", 3);
                   SelectObject(pPDX->hDC, TNR9);
                   TextOut(pPDX->hDC, 220, -520-(line_h*20), "(17)", 4);
                   Rectangle(pPDX->hDC, 308, -525-(line_h*20), 338, -525-(line_h*20)-30);
                   TextOut(pPDX->hDC, 370, -520-(line_h*20), "prowadzi� pojazd wy��czony z zakresu stosowania rozporz�dzenia (WE) 165/2009 lub AETR", 85);
                   SelectObject(pPDX->hDC, TNR6_S);
                   TextOut(pPDX->hDC, 1634, -520-(line_h*20)+5, "***", 3);
                   SelectObject(pPDX->hDC, TNR9);
                   TextOut(pPDX->hDC, 220, -520-(line_h*21), "(18)", 4);
                   Rectangle(pPDX->hDC, 308, -525-(line_h*21), 338, -525-(line_h*21)-30);
                   TextOut(pPDX->hDC, 370, -520-(line_h*21), "wykonywa� prac� inn� ni� prowadzenie pojazdu", 44);
                   SelectObject(pPDX->hDC, TNR6_S);
                   TextOut(pPDX->hDC, 1020, -520-(line_h*21)+5, "***", 3);
                   SelectObject(pPDX->hDC, TNR9);
                   TextOut(pPDX->hDC, 220, -520-(line_h*22), "(19)", 4);
                   Rectangle(pPDX->hDC, 308, -525-(line_h*22), 338, -525-(line_h*22)-30);
                   TextOut(pPDX->hDC, 370, -520-(line_h*22), "pozostawa� w gotowo�ci", 22);
                   SelectObject(pPDX->hDC, TNR6_S);
                   TextOut(pPDX->hDC, 703, -520-(line_h*22)+5, "***", 3);
                   SelectObject(pPDX->hDC, TNR9);
                   int yl1s = -525-(line_h*(17+idng-1));
                   int yl2s = yl1s - 30;
                   POINT old_point;
                   MoveToEx(pPDX->hDC, 308, yl1s, &old_point );
                   LineTo(pPDX->hDC, 338, yl1s-30);
                   MoveToEx(pPDX->hDC, 308, yl1s-30, &old_point );
                   LineTo(pPDX->hDC, 338, yl1s);
                   TextOut(pPDX->hDC, 220, -520-(line_h*23), "(20)", 4);
                   TextOut(pPDX->hDC, 370, -520-(line_h*23), "Miejscowo��:", 12);
                   TextOut(pPDX->hDC, 580, -520-(line_h*23), s_place, s_place_size);
                   TextOut(pPDX->hDC, 220, -520-(line_h*25)+35, "Podpis: ", 8);
                   SelectObject(pPDX->hDC, TNR9_U);
                   TextOut(pPDX->hDC, 330, -520-(line_h*25)+35, "�������������������", 19);
                   SelectObject(pPDX->hDC, TNR9);
                   TextOut(pPDX->hDC, 220, -510-(line_h*26), "(21)", 4);
                   TextOut(pPDX->hDC, 370, -510-(line_h*26), "Ja, jako kierowca, potwierdzam, �e w wy�ej wymienionym okresie nie prowadzi�em pojazdu wchodz�cego w", 100);
                   TextOut(pPDX->hDC, 370, -550-(line_h*26), "zakres stosowania rozporz�dzenia (WE) nr 561/2009 lub AETR", 58);
                   TextOut(pPDX->hDC, 220, -550-(line_h*27), "(22)", 4);
                   TextOut(pPDX->hDC, 370, -550-(line_h*27), "Miejscowo��:", 12);
                   TextOut(pPDX->hDC, 580, -550-(line_h*27), s_place, s_place_size);
                   TextOut(pPDX->hDC, 220, -550-(line_h*28), "Podpis kierowcy: ", 18);
                   SelectObject(pPDX->hDC, TNR9_U);
                   TextOut(pPDX->hDC, 455, -550-(line_h*28), "�������������������", 19);  
                   MoveToEx(pPDX->hDC, 220, -550-(line_h*32)-30, &old_point );
                   LineTo(pPDX->hDC, 750, -550-(line_h*32)-30);
                   SelectObject(pPDX->hDC, TNR6_S);
                   TextOut(pPDX->hDC, 220, -550-(line_h*32)-35, "1", 1);
                   SelectObject(pPDX->hDC, TNR8);
                   TextOut(pPDX->hDC, 260, -550-(line_h*32)-40, "Niniejszy formularz jest dost�pny w formie elektronicznej i przeznaczonej do druki na stronie internetowej: http://ec.europa.eu", 127);
                   SelectObject(pPDX->hDC, TNR6_S);
                   TextOut(pPDX->hDC, 220, -550-(line_h*32)-75, "2", 1);  
                   SelectObject(pPDX->hDC, TNR8);
                   TextOut(pPDX->hDC, 260, -550-(line_h*32)-80, "Umowa europejska dotycz�ca pracy za��g pojazd�w wykonuj�cych mi�dzynarodowe przewozy drogowe",92);   
                   SelectObject(pPDX->hDC, TNR6_S);
                   TextOut(pPDX->hDC, 220, -550-(line_h*32)-115, "***", 3);  
                   SelectObject(pPDX->hDC, TNR8);
                   TextOut(pPDX->hDC, 260, -550-(line_h*32)-120, "Mo�na wybra� tylko jedn� z rubryk",33); 
                   r = EndPage(pPDX->hDC);
                      if( r > 0 )
                      {
                         r = EndDoc(pPDX->hDC);
                      }
                   }  
               }       
           }
           if( pPDX->hDC )
           {
               DeleteDC( pPDX->hDC );
           }
           if( pPDX->hDevMode )
           {
               GlobalFree( pPDX->hDevMode );
           }
           if( pPDX->hDevNames )
           { 
               GlobalFree( pPDX->hDevNames );
           }
           
           GlobalFree( pPDX );
           GlobalFree( pPageRanges );
    }
}

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "WindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HFONT hfont;
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (hThisInstance, "IKONA");
    wincl.hIconSm = LoadIcon (hThisInstance, "IKONA");
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = "MYMENU";                /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;   
    //wincl.hbrBackground = GetSysColorBrush(COLOR_3DFACE);                   /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    HBRUSH TLO = CreateSolidBrush(RGB(192,192,192));
    wincl.hbrBackground = TLO;
    

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;
    
    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Urlop�wki v2.0",       /* Title Text */
           WS_DLGFRAME | WS_POPUPWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           550,                 /* The programs width */
           490,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );    
     
     hfont = CreateFont(30,0,0,0,700,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,0, VARIABLE_PITCH,TEXT("Times New Roman"));
     
     t0a = CreateWindow("STATIC","URLOP�WKI v2.0", WS_CHILD | WS_VISIBLE, 170, 5, 350, 25, hwnd, (HMENU)110, NULL, hwnd);  
     SendMessage(t0a, WM_SETFONT,( WPARAM ) hfont, 0);
     t0b = CreateWindow("STATIC"," ", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 43, 524, 350, hwnd, (HMENU)111, NULL, hwnd); 
     t1 = CreateWindow("STATIC","Firma: ", WS_CHILD | WS_VISIBLE | SS_RIGHT, 15, 53, 80, 25, hwnd, (HMENU)11, NULL, hwnd);
     c1 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -", WS_CHILD | WS_VISIBLE | WS_BORDER,  110 , 50, 400, 25, hwnd, (HMENU)1, NULL, NULL);         
     t2 = CreateWindow("STATIC","Kierowca: ", WS_CHILD | WS_VISIBLE | SS_RIGHT, 15, 83, 80, 25, hwnd, (HMENU)12, NULL, hwnd);
     c2 = CreateWindowEx(WS_EX_CLIENTEDGE, "COMBOBOX", "Kierowcy", WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST, 110 , 80, 250, 400, hwnd, (HMENU)2, NULL, NULL);         
     Data_Select(3, 0);
     SendMessage(c2, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
     t3 = CreateWindow("STATIC","Okres od: ", WS_CHILD | WS_VISIBLE | SS_RIGHT , 15, 115, 80, 25, hwnd, (HMENU)13, NULL, hwnd);
     c3 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "00:00-00-00-0000", WS_CHILD | WS_VISIBLE | WS_BORDER | DTS_TIMEFORMAT, 110, 113, 140, 25, hwnd, (HMENU)3, NULL, hwnd); 
     SendMessage(c3, DTM_SETFORMAT, (WPARAM)0 , (LPARAM) "HH:mm-dd-MM-yyyy");
     //dp1 = CreateWindow("Button", "x", WS_CHILD | WS_VISIBLE | SS_CENTER , 248, 114, 22, 22, hwnd, (HMENU)31, NULL, hwnd); 
     t4 = CreateWindow("STATIC","Okres do: ", WS_CHILD | WS_VISIBLE | SS_RIGHT, 15, 145, 80, 25, hwnd, (HMENU)14, NULL, hwnd);
     c4 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT","00:00-00-00-0000", WS_CHILD | WS_VISIBLE | WS_BORDER | DTS_TIMEFORMAT, 110, 143, 140, 25, hwnd, (HMENU)4, NULL, hwnd);
     SendMessage(c4, DTM_SETFORMAT, (WPARAM)0 , (LPARAM) "HH:mm-dd-MM-yyyy");
     //dp2 = CreateWindow("Button", "x", WS_CHILD | WS_VISIBLE | SS_CENTER , 248, 144, 22, 22, hwnd, (HMENU)41, NULL, hwnd); 
     t5 = CreateWindow("STATIC","Czynno��: ", WS_CHILD | WS_VISIBLE | SS_RIGHT, 15, 177, 80, 25, hwnd, (HMENU)14, NULL, hwnd);
     c51 = CreateWindowEx( 0, "BUTTON", "Przebywa� na zwolnieniu chorobowym", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 110, 173, 300, 30, hwnd, (HMENU)51, NULL, NULL );
     c52 = CreateWindowEx( 0, "BUTTON", "Przebywa� na urlopie wypoczynkowym", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 110, 203, 300, 30, hwnd, (HMENU)52, NULL, NULL );
     c53 = CreateWindowEx( 0, "BUTTON", "Mia� czas wolny lub odpoczywa�", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON , 110, 233, 300, 30, hwnd, (HMENU)53, NULL, NULL );
     c54 = CreateWindowEx( 0, "BUTTON", "Prowadzi� pojazd wy��czony z zakresu stosowania rozporz�dzenia (WE) nr 561/2006 lub AETR", WS_CHILD | WS_VISIBLE | BS_MULTILINE | BS_AUTORADIOBUTTON , 110, 263,410, 40, hwnd, (HMENU)54, NULL, NULL );
     c55 = CreateWindowEx( 0, "BUTTON", "Wykonywa� prac� inn� ni� prowadzenie pojazdu", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 110, 300, 350, 30, hwnd, (HMENU)55, NULL, NULL );
     c56 = CreateWindowEx( 0, "BUTTON", "Pozostawa� w gotowo�ci", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 110, 330, 300, 30, hwnd, (HMENU)56, NULL, NULL );
     t6 = CreateWindow("STATIC","Miejsce: ", WS_CHILD | WS_VISIBLE | SS_RIGHT, 15, 363, 80, 25, hwnd, (HMENU)16, NULL, hwnd);
     c6 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT","", WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 360, 150, 25, hwnd, (HMENU)6, NULL, hwnd);
     c7 = CreateWindow("Button", "Zapisz i drukuj", WS_CHILD | WS_VISIBLE | SS_CENTER , 158, 405, 110, 25, hwnd, (HMENU)7, NULL, hwnd); 
     c8 = CreateWindow("Button", "Zamknij", WS_CHILD | WS_VISIBLE | SS_CENTER , 278, 405, 110, 25, hwnd, (HMENU)8, NULL, hwnd); 
    SendMessage(c53, BM_SETCHECK, BST_CHECKED,0);
                       
    //ustawianie czcionek
    hfont = CreateFont(18,0,0,0,700,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,0, VARIABLE_PITCH,TEXT("Times New Roman"));
    SendMessage(t1, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(t2, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(t3, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(t4, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(t5, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(t6, WM_SETFONT,( WPARAM ) hfont, 0);
    hfont = CreateFont(18,0,0,0,100,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,0, VARIABLE_PITCH,TEXT("Times New Roman"));
    SendMessage(c1, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(c2, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(c3, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(c4, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(c51, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(c52, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(c53, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(c54, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(c55, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(c56, WM_SETFONT,( WPARAM ) hfont, 0);
    SendMessage(c6, WM_SETFONT,( WPARAM ) hfont, 0);
    
    /* Make the window visible on the screen */
      ShowWindow (hwnd, nFunsterStil);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{    
    int save_stat = 0; 
    int spid = 0;
    HDC dcItem;
    COLORREF textcl;
    LPCTSTR val2 = "v2" ; //idkierowca
    char val3[32] = "v3" ; //okres od
    char val4[32] = "v4" ; //okres do
    LPTSTR val5 = (LPTSTR) "v5"  ; //czynno��
    char val6[64] = "v6" ; //miejsce
    int pIndex = 0;
    int TLN = 0;
    int TLN2 = 0;
    LPCTSTR lpcts, ctmp;
    HWND hItem;
    int retAB = 0;
    HBRUSH TheBrush = CreateSolidBrush( RGB(192, 192, 192 ) );

    char buffer[20];
    
    switch (message)                  /* handle the messages */
    {
    case WM_COMMAND: //obsluga klikni�cia w kontrolk�
          switch(LOWORD(wParam)) //numer kontrolki
          {            
                case 1: //Combo firma
                     break; 
                case 2: //Combo kierowca
                     if(HIWORD (wParam) == CBN_SELENDOK)
                     {
                     pIndex = SendMessage(c2, CB_GETCURSEL, 0, 0);
                     if(pIndex >0)
                               {
                                  itoa(pIndex,buffer,10);
                                  lpcts = buffer;
                                  Data_Select(2, lpcts);
                                  Data_Select(1, TheDriver.company);
                                  SetWindowText(c1,TheSpeditor.name);
                                  Data_Select(4, TheDriver.id);
                               }
                     else
                               {
                                 SetWindowText(c1,"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
                                 SetWindowText(c3,"00:00 00-00-0000");
                                 SetWindowText(c4,"00:00 00-00-0000");
                                 Button_SetCheck(c53, BST_CHECKED);
                                 SetWindowText(c6,"-----");
                               } 
                     SetFocus(c6);	            
                     }
                     break; 
                case 3: //Editbox okres od
                     break;
                case 4: //Editbox okres do
                     break;  
                case 6: //Editbox miejsce   
                     break;
                case 7: //Button save&print

                     TLN = GetWindowTextLength(c6);   
   
                     if(TLN == 0 || atoi(TheDriver.id) == 0)
                     {
                     FMessage("Wpisz miasto i/lub kierowc�!");     
                     }
                     else
                     {
                     strcpy(TheArchive.idpr, TheDriver.id); 
                     GetWindowText(c3, TheArchive.astart, 17);  
                     GetWindowText(c4, TheArchive.akoniec, 17); 
                     GetWindowText(c6, TheArchive.aplace, 64); 
                     
                     if(Button_GetCheck(c51) == BST_CHECKED)
                     {
                       strcpy(TheArchive.aaction, "1");                      
                     }
                     if(Button_GetCheck(c52) == BST_CHECKED)
                     {
                       strcpy(TheArchive.aaction, "2");                       
                     }
                     if(Button_GetCheck(c53) == BST_CHECKED)
                     {
                       strcpy(TheArchive.aaction, "3");                           
                     }
                     if(Button_GetCheck(c54) == BST_CHECKED)
                     {
                       strcpy(TheArchive.aaction, "4");                         
                     }
                     if(Button_GetCheck(c55) == BST_CHECKED)
                     {
                       strcpy(TheArchive.aaction, "5");                          
                     }
                     if(Button_GetCheck(c56) == BST_CHECKED)
                     {
                       strcpy(TheArchive.aaction, "6");                           
                     }
                     save_stat = Data_Save(3);
                     }
                     if(save_stat == 1)
                     {
                      //PrintDoc(TheArchive.idpr, TheArchive.astart, TheArchive.akoniec, TheArchive.aaction, TheArchive.aplace);            
                       PrintDoc();
					 }
                     break;      
                case 8: //Button exit
                     PostQuitMessage (0);
                     break; 
                case 31:  //DateTimePicker 1
                     //ShowWindow(DateTimePickerDLG,1);
                     break;
                case 32:  //DateTimePicker 2
                     break; 
			    case 101: //Zako�czenie programu
			         PostQuitMessage (0);
				     break;	
				case 102: //Edycja danych firmy
				     if(TheSpeditor.id == 0)
				     {
				     	FMessage("Wybierz pracownika aby zmieni� dane jego pracodawcy");
					 }
					 else
					 {
					 	new_add_s = 1;
				    	int retDF = DialogBox( GetModuleHandle( NULL ), MAKEINTRESOURCE( 200 ), hwnd, DlgDFProc);
				     }
				     break;	 	
				case 103: //Edycja danych kierowcy
 					 if(TheSpeditor.id == 0)
				     {
				     	FMessage("Wybierz pracownika aby zmieni� jego dane");
					 }
					 else
					 {
					 	new_add_d = 1;
				    	int retDP = DialogBox( GetModuleHandle( NULL ), MAKEINTRESOURCE( 300 ), hwnd, DlgDPProc);
				     }
				     break;
				case 104: //O programie
				     retAB = DialogBox( GetModuleHandle( NULL ), MAKEINTRESOURCE( 400 ), hwnd, DlgABProc);
				     break;	   
				case 112: //Dodawanie nowej firmy
				     new_add_s = 2;
				     retAB = DialogBox( GetModuleHandle( NULL ), MAKEINTRESOURCE( 200 ), hwnd, DlgDFProc);
				     break;	    
				case 113: //Dodawanie nowogo kierowcy
					 new_add_d = 2;
				     retAB = DialogBox( GetModuleHandle( NULL ), MAKEINTRESOURCE( 300 ), hwnd, DlgDPProc);
				     break;              
           }
      break; //koniec obs�ugi klikni�cia na kontrolk�
      
      case WM_CTLCOLORSTATIC: //obsluga kolorow w kontrolkach            
           hItem = (HWND) lParam;
           dcItem = (HDC) wParam;
           if(hItem == t0a)
           {
                 textcl = RGB(255,0,0);   
                 SetBkMode(dcItem, TRANSPARENT);
                 SetTextColor(dcItem,textcl);
                 return( LRESULT ) TheBrush;
           } 
           if(hItem == t1 || hItem == t2 || hItem == t3 || hItem == t4 || hItem == t5 || hItem == t6)  
           {
                textcl = RGB(5,10,200);   
                SetTextColor(dcItem,textcl);
                SetBkMode(dcItem, TRANSPARENT);
                TheBrush = CreateSolidBrush(RGB(240,240,240));
                return( LRESULT ) TheBrush;    
           } 
           if(hItem == c1 || hItem == c4 )  
           {
                SetBkMode(dcItem, TRANSPARENT);
                TheBrush = CreateSolidBrush(RGB(255,255,255));
                return( LRESULT ) TheBrush;    
           } 
          break; //koniec obslugi kolorow w kontrolkach
                                          
      case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
      default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
   }        
}


