#include "CListBox.h"

// ---------------------------------------------------------
// CListBox::CListBox()
// constructor
// ---------------------------------------------------------
//
CListBox::CListBox()
{
//	selected = 0;
}
// ---------------------------------------------------------
// CListBox::Draw()
// Draw List box
// ---------------------------------------------------------
//
void CListBox::Draw()
{
	cHwnd = CreateWindow(TEXT("LISTBOX"), NULL, WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER | LBS_SORT |  LBS_NOTIFY, 
	                    	posX, posY, Size.width, Size.height, pHwnd, (HMENU) ID, NULL, NULL) ; 

}
// ---------------------------------------------------------
// CListBox::AddElement(TCHAR *caption)
// add element to list box
// ---------------------------------------------------------
//
void CListBox::AddElement(TCHAR *caption)
{
	SendMessage(cHwnd, LB_INSERTSTRING, (WPARAM) -1, (LPARAM) caption); 

}
// ---------------------------------------------------------
// CListBox::DeleteElement(int number)
// Delete element from list box
// ---------------------------------------------------------
//
void CListBox::DeleteElement(int number)
{
	SendMessage(cHwnd, LB_DELETESTRING, (WPARAM) number, 0); 

}
// ---------------------------------------------------------
// CListBox::GetSelected()
// get selected element in list box
// ---------------------------------------------------------
//
int CListBox::GetSelected()
{

	selected = SendMessage(cHwnd, LB_GETCURSEL, 0, 0);
	return  selected ; 
}
void CListBox::SetSelected(int index)
{
	SendMessage (cHwnd, LB_SETCURSEL, (LPARAM)index, 0); 
}
void CListBox::SetItemData(int index, int number)
{

	 SendMessage(cHwnd, LB_SETITEMDATA, index, (LPARAM)number); 
}
int CListBox::GetItemData(int index)
{

	return (INT)SendMessage(cHwnd, LB_GETITEMDATA, index,0); 
}
bool CListBox::isChange(WPARAM wParam)
{
	if(HIWORD(wParam) == LBN_SELCHANGE)
	{
		return TRUE;
	}else
		return FALSE; 
}
