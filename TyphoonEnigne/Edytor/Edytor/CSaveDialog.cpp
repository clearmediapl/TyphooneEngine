#include "CSaveDialog.h"

// ---------------------------------------------------------
// CSaveDialog::CSaveDialog()
// constructor
// ---------------------------------------------------------
//
CSaveDialog::CSaveDialog()
{
	memset(path,0,sizeof(path));
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
void CSaveDialog::SetFilter(LPCWSTR data)
{
	filter = data;


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
		fileInfo.lpstrFilter = _T("sadsa\0 *.ext\0\0");
		fileInfo.nMaxFile = 255;
		fileInfo.nFilterIndex = 1;
		fileInfo.nMaxFile = 255;
//		fileInfo.nMaxFileTitle = 64;
		fileInfo.lpstrTitle = caption;
//		fileInfo.nMaxFileTitle = sizeof(caption);
		fileInfo.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;


		if(GetSaveFileName(&fileInfo))
		{
			return TRUE;
		}

		return FALSE;

}