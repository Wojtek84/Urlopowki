#include <windows.h>
#include <fstream>
#include <winuser.h>
#include <string.h>
#include <wingdi.h>
#include <Windowsx.h>

void FMessage(LPCTSTR mymessage)
{
int msgbox = MessageBox(NULL, mymessage, "Wiadomosc", MB_ICONINFORMATION | MB_DEFBUTTON2);    
}

