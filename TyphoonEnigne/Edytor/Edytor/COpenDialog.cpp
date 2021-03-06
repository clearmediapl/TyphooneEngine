#include "COpenDialog.h"

// ---------------------------------------------------------
// COpenDialog::COpenDialog()
// constructor
// ---------------------------------------------------------
//
COpenDialog::COpenDialog()
{

	memset(filename,0,sizeof(filename));
	memset(path,0,sizeof(path));
//	memset(filter,0,sizeof(filter));


}
// ---------------------------------------------------------
// COpenDialog::SetFilter(TCHAR *filters)
// SetFilter to open dialog
// ---------------------------------------------------------
//
void COpenDialog::SetFilter(LPCWSTR data)
{
	filter = data;
}
// ---------------------------------------------------------
// COpenDialog::SetCaption(TCHAR *name)
// Set the caption of open dialog
// ---------------------------------------------------------
//
void COpenDialog::SetCaption(TCHAR *name)
{

	wcscpy_s(caption,name);
}
// ---------------------------------------------------------
// COpenDialog::getPath()
// get path of file open in open dialog
// ---------------------------------------------------------
//
bool COpenDialog::getPath()
{


	
		OPENFILENAME fileInfo;
		ZeroMemory(&fileInfo,sizeof(fileInfo));

		fileInfo.lStructSize = sizeof(fileInfo);
		fileInfo.hwndOwner = pHwnd;
		fileInfo.lpstrFile = path;
		fileInfo.lpstrFilter = filter;
		fileInfo.nFilterIndex = 1;
		fileInfo.nMaxFile = 255;
		fileInfo.lpstrFileTitle = filename;
		fileInfo.nMaxFileTitle = 255;
		fileInfo.lpstrTitle = caption;
		fileInfo.nMaxFileTitle = sizeof(caption);
		fileInfo.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_ENABLESIZING | OFN_NONETWORKBUTTON | OFN_NOREADONLYRETURN | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;      



	    if(GetOpenFileName(&fileInfo)!=0)
		{	
			

			return TRUE;
		}


		return FALSE;


}
// ---------------------------------------------------------
// COpenDialog::getFileName()
// get file name of file open in open dialog
// ---------------------------------------------------------
//
TCHAR *COpenDialog::getFileName()
{

	return filename;
}