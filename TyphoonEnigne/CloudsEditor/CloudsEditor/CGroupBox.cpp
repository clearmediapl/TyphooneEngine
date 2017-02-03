#include "CGroupBox.h"

// ---------------------------------------------------------
// CGroupBox::CGroupBox()
// constructor
// ---------------------------------------------------------
//
CGroupBox::CGroupBox()
{
	

}
// ---------------------------------------------------------
// CGroupBox::Draw(TCHAR *text)
// Draw group box
// ---------------------------------------------------------
//
void CGroupBox::Draw(TCHAR *text)
{
		
	 cHwnd  = CreateWindow(TEXT("button"), text,  WS_CHILD | WS_VISIBLE | BS_GROUPBOX , 
		                   posX,posY,Size.width,Size.height, pHwnd, (HMENU)ID, NULL, NULL);

}
