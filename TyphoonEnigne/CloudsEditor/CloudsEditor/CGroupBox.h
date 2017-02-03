#ifndef _CTAB_H_
#define _CTAB_H_

#include "Libraries.h"
#include "CWindow.h"

class CWindow;

class CGroupBox : public CWindow
{
private:
	
public:
	CGroupBox();

	void Draw(TCHAR *text);

};

#endif