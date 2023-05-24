#include <math.h>
#include <cstdio>

void printFrame(HDC hdc, int x1, int y1, int x2, int y2) 
{ 
    int dx, dy;
    dx = x1 + 4 * 15 + 3*80;
    dy = 100;
    HBRUSH hbr;
    hbr = CreateSolidBrush(RGB(222,222,222));
    SelectObject(hdc, hbr) ;
    MoveToEx(hdc, 20, 180, NULL);
    Rectangle(hdc,x1,y1,dx,160);            
}
