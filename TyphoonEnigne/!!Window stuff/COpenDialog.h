#include "Libraries.h"
#include "CWindow.h"

class COpenDialog : public CWindow
{
private:

	TCHAR filter[32];
	TCHAR caption[32];


public:
	TCHAR path[255];
	TCHAR filename[255];

public:
	COpenDialog();


	void SetFilter(LPCWSTR filters);
	void SetCaption(TCHAR *name);
	
	TCHAR *getFileName();
	bool getPath();
};