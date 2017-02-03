#include "Libraries.h"
#include "CWindow.h"

class CWindow;

class CTab : public CWindow
{
private:

	int index;
	int tab;

public:

	CTab();
	void Draw();
	void AddTab(TCHAR *name);
	int  GetSelected(NMHDR *pnmhdr);
};