#include "CTrackBar.h"
#include <commctrl.h>

CTrackBar::CTrackBar()
{
	INITCOMMONCONTROLSEX InitCtrlEx;

	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC  = ICC_BAR_CLASSES;
	InitCommonControlsEx(&InitCtrlEx);


}

void CTrackBar::SetMaxValue(int value)
{
	max = value;
}
void CTrackBar::SetMinValue(int value)
{
	min = value;
}
void CTrackBar::Draw()
{
	
	cHwnd = CreateWindowEx( 0, TRACKBAR_CLASS, NULL,
		                   WS_CHILD | WS_VISIBLE | TBS_ENABLESELRANGE   ,
			               posX,posY,Size.width,Size.height,
			               pHwnd, (HMENU)ID,NULL , NULL);
SendMessage(cHwnd, TBM_SETRANGE, (WPARAM) true, (LPARAM) MAKELONG(min, max));

}
void CTrackBar::SetTrackPos(int value)
{
	SendMessage(cHwnd, TBM_SETPOS, (WPARAM) true, (LPARAM) value);
}
int CTrackBar::getValue()
{
	return SendMessage(cHwnd, TBM_GETPOS, 0, 0);

}
