#include "CAddObject.h"

CAddObject::CAddObject()
{

}
TCHAR *CAddObject::getFileName()
{
	OPENFILENAME fileInfo;
	fileInfo.hwndOwner = pHwnd;
	fileInfo.lpstrFile = fileName;

	GetOpenFileName(&fileInfo);

	return fileName;
}

void CAddObject::Init()
{


}
void CAddObject::Draw()
{


}
