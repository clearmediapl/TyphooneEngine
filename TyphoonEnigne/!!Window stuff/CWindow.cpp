
#include "CWindow.h"

// ---------------------------------------------------------
// CWindow::CWindow()
// CWindow constructor
// ---------------------------------------------------------
//
CWindow::CWindow()
{

}
// ---------------------------------------------------------
// CWindow::SetID(int cID)
// Set ID for window
// ---------------------------------------------------------
//
void CWindow::SetID(int cID)
{
	ID = cID;
}
// ---------------------------------------------------------
// CWindow::SetParentHwnd(HWND hWnd)
// Set parent's hwnd for window
// ---------------------------------------------------------
//
void CWindow::SetParentHwnd(HWND hWnd)
{
	pHwnd = hWnd;
}
// ---------------------------------------------------------
// CWindow::SetPosition(int positionX, int positionY)
// Set position for window
// ---------------------------------------------------------
//
void CWindow::SetPosition(int positionX, int positionY)
{
	posX = positionX;
	posY = positionY;
}
// ---------------------------------------------------------
// CWindow::SetSize(int sizeX, int sizeY)
// Set size for window
// ---------------------------------------------------------
//
void CWindow::SetSize(int sizeX, int sizeY)
{
	Size.width = sizeX;
	Size.height = sizeY;
}
// ---------------------------------------------------------
// CWindow::GetOldSize(int x, int y)
// Get old window size
// ---------------------------------------------------------
//
void CWindow::GetParentWindowSize(int x, int y)
{
	orginalSize.width  = x;
	orginalSize.height = y;
}

// ---------------------------------------------------------
// CWindow::RefreshSize(int x, int y)
// Refresh window size
// ---------------------------------------------------------
//
void CWindow::RefreshSize(int x, int y)
{

	
	//x is new width | y is new height
	newSize.height = (y - 768  ) + Size.height;
	newSize.width  = (x - 1024) + Size.width;

    SetWindowPos(cHwnd, HWND_TOP, posX, posY, newSize.width, newSize.height, SWP_SHOWWINDOW);


}
void CWindow::SetVisible(bool state)
{
	if(state)
	{
		ShowWindow(cHwnd,SW_SHOW);
	}
	else 	ShowWindow(cHwnd,SW_HIDE);
}
