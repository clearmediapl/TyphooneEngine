#include "CComboBox.h"

// ---------------------------------------------------------
// CComboBox::CComboBox()
// constructor
// ---------------------------------------------------------
//
CComboBox::CComboBox()
{
	index = 0;


}
// ---------------------------------------------------------
// CComboBox::AddItem(TCHAR *text)
// 
// ---------------------------------------------------------
//
void CComboBox::AddItem(TCHAR *text)
{
	COMBOBOXEXITEM item;

	item.mask = CBEIF_TEXT;
	item.iItem = index;
	item.iImage = 0;
	item.iSelectedImage = 1;
	item.cchTextMax = sizeof(text);
	item.pszText = text;
	index = SendMessage(cHwnd, CBEM_INSERTITEM, 0, (LPARAM)&item);
	
	index++;


}
// ---------------------------------------------------------
// CComboBox::Draw()
// 
// ---------------------------------------------------------
//
void CComboBox::Draw()
{
	cHwnd = CreateWindowEx(0, WC_COMBOBOXEX, 0, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL
		, posX, posY, Size.width, Size.height, pHwnd, (HMENU)ID, NULL, 0);



}
// ---------------------------------------------------------
// CComboBox::getSelected()
// 
// ---------------------------------------------------------
//
int CComboBox::getSelected()
{
	return SendMessage(cHwnd, CB_GETCURSEL, 0, 0);
}
// ---------------------------------------------------------
// CComboBox::SetSelected(int ID)
// 
// ---------------------------------------------------------
//
void CComboBox::SetSelected(int ID)
{
	SendMessage(cHwnd, CB_SETCURSEL, (WPARAM)ID, 0);
}
// ---------------------------------------------------------
// CComboBox::CComboBox()
// 
// ---------------------------------------------------------
//
bool CComboBox::isChange(WPARAM wParam)
{
	if(HIWORD(wParam) == CBN_SELCHANGE )
	{
		return TRUE;
	}else
		return FALSE;
	
}