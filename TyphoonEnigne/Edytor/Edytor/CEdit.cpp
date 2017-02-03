#include "CEdit.h"


CEdit::CEdit()
{


}
void CEdit::Draw(TCHAR *text)
{
	cHwnd = CreateWindow(TEXT("edit"), text, WS_CHILD | WS_VISIBLE | ES_LEFT |ES_READONLY |ES_NOHIDESEL,
		                 posX,posY,Size.width,Size.height, pHwnd, (HMENU)ID, NULL, NULL);

}