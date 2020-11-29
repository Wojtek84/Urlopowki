#include <windows.h>
#include <winuser.h>
#include <string.h>
#include <wingdi.h>
#include <Windowsx.h>

using namespace std;

class driver
{
 public:      
 char id[5];     
 char name[65];
 char nrdoc[16];
 char jobstart[11];  
 char company[5];   
 char birth[11]; 
 int n_id;
};
