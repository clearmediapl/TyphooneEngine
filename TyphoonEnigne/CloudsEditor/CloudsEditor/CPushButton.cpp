#include "CPushButton.h"
// ---------------------------------------------------------
// CPushButton::CPushButton()
// constructor
// ---------------------------------------------------------
//
CPushButton::CPushButton()
{
	style = BS_AUTORADIOBUTTON; // default radio button style
	group = NULL;
}
// ---------------------------------------------------------
// CPushButton::SetCheckBoxStyle();
// Set check box style to push button
// ---------------------------------------------------------
//
void CPushButton::SetNewGroup()
{
	group = WS_GROUP;
}
void CPushButton::SetCheckBoxStyle()
{
	style = BS_AUTOCHECKBOX;
}
// ---------------------------------------------------------
// CPushButton::Draw(TCHAR *caption)
// Draw push button
// ---------------------------------------------------------
//
void CPushButton::Draw(TCHAR *caption)
{
	cHwnd = CreateWindow(TEXT("button"), caption, WS_CHILD | WS_VISIBLE | group| BS_PUSHLIKE | style ,
		                 posX,posY,Size.width,Size.height, pHwnd, (HMENU)ID, NULL, NULL);

}
// ---------------------------------------------------------
// CPushButton::SetCheck(bool stage)
// Set checked or unchecked push button
// ---------------------------------------------------------
//
void CPushButton::SetCheck(bool stage)
{
	if(stage)
	{
		SendMessage(cHwnd, BM_SETCHECK, 1, 0);

	}else SendMessage(cHwnd, BM_SETCHECK, 0, 0);


}

// ---------------------------------------------------------
// CPushButton::Check();
// check when is pushed
// ---------------------------------------------------------
//
bool CPushButton::Check()
{
	int check = IsDlgButtonChecked(pHwnd, ID);
	if(check == 1)
	{
		return TRUE;
	}
    else  return FALSE;

}