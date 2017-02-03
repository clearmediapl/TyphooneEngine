#include "CSaveDialog.h"

// ---------------------------------------------------------
// CSaveDialog::CSaveDialog()
// constructor
// ---------------------------------------------------------
//
CSaveDialog::CSaveDialog()
{
	memset(path,0,sizeof(path));
	memset(filter,0,sizeof(filter));
	memset(caption,0,sizeof(caption));


}
// ---------------------------------------------------------
// CSaveDialog::SetCaption(TCHAR *text)
// Set caption of save dialog
// ---------------------------------------------------------
//
void CSaveDialog::SetCaption(TCHAR *text)
{
	wcscpy_s(caption, text);
}
// ---------------------------------------------------------
// CSaveDialog::SetFilter(TCHAR *text)
// Set filters
// ---------------------------------------------------------
//
void CSaveDialog::SetFilter(TCHAR *text)
{
	wcscpy_s(filter,text);
}
// ---------------------------------------------------------
// CSaveDialog::getPath()
// Get path of file from save dialog
// ---------------------------------------------------------
//
bool CSaveDialog::getPath()
{
	
		OPENFILENAME fileInfo;
		ZeroMemory(&fileInfo,sizeof(fileInfo));

		fileInfo.lStructSize = sizeof(fileInfo);
		fileInfo.hwndOwner = pHwnd;
		fileInfo.lpstrFile = path;
		fileInfo.lpstrFilter = filter;
		fileInfo.nFilterIndex = 0;
		fileInfo.nMaxFile = 255;
		fileInfo.nMaxFileTitle = 64;
		fileInfo.lpstrTitle = caption;
		fileInfo.nMaxFileTitle = sizeof(caption);
		fileInfo.Flags = OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;

		if(GetSaveFileName(&fileInfo))
		{
			return TRUE;
		}

		return FALSE;

}