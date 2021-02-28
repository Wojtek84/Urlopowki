#include <windows.h>
#include <winuser.h>
#include <string.h>
#include <wingdi.h>
#include <Windowsx.h>
#include "funcs.hpp"

using namespace std;

class speditor
{
 public:      
 char id[3];     
 char name[65];
 char street[51];
 char number[11];
 char city[31]; 
 char postal[7]; 
 char owner[51];   
 char phone[21]; 
 char email[31];
 char fax[21];
 char country[5];    
};
