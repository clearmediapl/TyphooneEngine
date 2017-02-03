#include "CCheckBox.h"
#include "CWindow.h"

// ---------------------------------------------------------
// CCheckBox::CCheckBox(HWND hWnd, int positionX, int positionY, int sizeX, int sizeY,int ID)
// constructor
// hWnd - hwnd of parent
// position x - position x of check box
// position y - position y of check box
// sizeX - width of check box
// sizeY - height of check box
// ID - ID of check box
// ---------------------------------------------------------
//
CCheckBox::CCheckBox() : CWindow()
{

	check = -10;
	radiobutton = false;
	group = NULL;

	
}
// ---------------------------------------------------------
// CCheckBox::SetRadioButton()
// Set to draw radiobutton
// ---------------------------------------------------------
//
void CCheckBox::SetRadioButton()
{
	radiobutton = true;

}
void CCheckBox::SetGroup()
{

	group = WS_GROUP;
}
// ---------------------------------------------------------
// CCheckBox::Draw(TCHAR *text)
// Draw a checkbox with my label
// ---------------------------------------------------------
//
void CCheckBox::Draw(TCHAR *text)
{
	if(!radiobutton) // draw checkbox
	{
		cHwnd = CreateWindow(TEXT("button"), text, WS_CHILD | WS_VISIBLE |BS_AUTOCHECKBOX , 
		                 posX,posY,Size.width,Size.height, pHwnd, (HMENU)ID, NULL, NULL);
	}
	else //draw radiobutton
	{
		
			cHwnd = CreateWindow(TEXT("button"), text, WS_CHILD | WS_VISIBLE| group |BS_AUTORADIOBUTTON, 
		                 posX,posY,Size.width,Size.height, pHwnd, (HMENU)ID, NULL, NULL);
		
	}

}
// ---------------------------------------------------------
// CCheckBox::Check()
// return true when checkbox is checked
// ---------------------------------------------------------
//
bool CCheckBox::Check()
{

	check = IsDlgButtonChecked(pHwnd, ID);
	if(check == 1)
	{
		return TRUE;
	}
    else  return FALSE;

}
void CCheckBox::SetCheck(bool stage)
{
	if(stage)
	{
		SendMessage(cHwnd, BM_SETCHECK, 1, 0);
	}
	else SendMessage(cHwnd, BM_SETCHECK, 0, 0);


}

