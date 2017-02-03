#include "CButton.h"

// ---------------------------------------------------------
// CButton::CButton(HWND hWnd, int positionX, int positionY, int sizeX, int sizeY,int ID)
// constructor
// hWnd - hwnd of parent
// position x - position x of button
// position y - position y of button
// sizeX - width of botton
// sizeY - height of botton
// ID - ID of botton
// ---------------------------------------------------------
//

CButton::CButton() : CWindow()
{
	press = false;
	

}
// ---------------------------------------------------------
// CButton::Draw(TCHAR *text)
// Draw a button with text
// ---------------------------------------------------------
//
void CButton::Draw(TCHAR *text)
{
	
	cHwnd = CreateWindow(TEXT("button"), text, WS_CHILD | WS_VISIBLE  ,
		                 posX,posY,Size.width,Size.height, pHwnd, (HMENU)ID, NULL, NULL);

}
// ---------------------------------------------------------
// CButton::Check(int ID)
// Check when button is clicked
// ---------------------------------------------------------
//
bool CButton::Check(int cID)
{
	if(cID == ID )
	{
		return TRUE;
	}
}

