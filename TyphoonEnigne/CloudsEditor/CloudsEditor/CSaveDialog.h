#include "Libraries.h"
#include "CWindow.h"


class CSaveDialog : public CWindow
{
private:

	TCHAR filter[32];
	TCHAR caption[32];

public:
	TCHAR path[256];

	CSaveDialog();

	void SetCaption(TCHAR *text);
	void SetFilter(TCHAR *text);
	bool getPath();

};