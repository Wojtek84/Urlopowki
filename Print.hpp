void PrintDoc(LPCTSTR cid, LPCTSTR did, LPCTSTR ood, LPCTSTR odo, LPCTSTR plc)
{
int r = 0;
HRESULT hResult;
LPPRINTDLGEX pPDX = NULL;
LPPRINTPAGERANGE pPageRanges = NULL;

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
pPDX->nMaxPage = 1000;
pPDX->nCopies = 1;
pPDX->hInstance = 0;
pPDX->lpPrintTemplateName = NULL;
pPDX->lpCallback = NULL;
pPDX->nPropertyPages = 0;
pPDX->lphPropertyPages = NULL;
pPDX->nStartPage = START_PAGE_GENERAL;
pPDX->dwResultAction = 0; 
 
}
