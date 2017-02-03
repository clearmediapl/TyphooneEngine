#include "Libraries.h"
#include "CWindow.h"

class COpenDialog : public CWindow
{
private:

	LPCWSTR filter;
	TCHAR caption[255];


public:
	TCHAR path[255];
	TCHAR filename[255];

public:
	COpenDialog();


	void SetFilter(LPCWSTR data);
	void SetCaption(TCHAR *name);
	
	TCHAR *getFileName();
	bool getPath();
};