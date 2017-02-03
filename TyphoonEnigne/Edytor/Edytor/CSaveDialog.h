#include "Libraries.h"
#include "CWindow.h"


class CSaveDialog : public CWindow
{
private:

	LPCWSTR filter;
	TCHAR caption[255];

public:
	TCHAR path[255];

	CSaveDialog();

	void SetCaption(TCHAR *text);
	void SetFilter(LPCWSTR data);
	bool getPath();

};