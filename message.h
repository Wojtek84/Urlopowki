#include <windows.h>

void showMessage(LPCTSTR mymessage)
{
int msgbox = MessageBox(NULL, mymessage, "Message", MB_ICONINFORMATION | MB_DEFBUTTON2);    
}
