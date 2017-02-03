#include "CTab.h"

// ---------------------------------------------------------
// CTab::CTab()
// constructor
// ---------------------------------------------------------
//
CTab::CTab()
{
	InitCommonControls();
	index = 0;
}
// ---------------------------------------------------------
// CTab::Draw()
// Draw tab pages
// ---------------------------------------------------------
//
void CTab::Draw()
{
	cHwnd = CreateWindowEx(WS_EX_RIGHT, WC_TABCONTROL, 0, WS_CHILD | WS_VISIBLE | TCS_BOTTOM | TCS_FIXEDWIDTH,
	                        CW_USEDEFAULT, CW_USEDEFAULT, 500, 700, pHwnd, (HMENU)ID, NULL, NULL); 


}
// ---------------------------------------------------------
// CTab::AddTab(TCHAR *name)
// Add new tab to tab pages
// ---------------------------------------------------------
//
void CTab::AddTab(TCHAR *name)
{
	TCITEM tie; 
	tie.mask = TCIF_TEXT ; 
	tie.pszText = name; 
	TabCtrl_InsertItem(cHwnd, index, &tie); 
	index++;

}
// ---------------------------------------------------------
// CTab::getSelected(NMHDR *nmhr)
// Return number of selected page
// ---------------------------------------------------------
//
int CTab::GetSelected(NMHDR *nmhr)
{
	
	if (nmhr->code == TCN_SELCHANGE && nmhr->hwndFrom == cHwnd && nmhr->idFrom == ID ) 
	{
		tab = TabCtrl_GetCurSel(cHwnd); 
		
			return tab;
	}
	//return -1;

}