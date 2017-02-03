
#ifndef _CCHECKBOX_H_
#define _CCHECKBOX_H_

#include "Libraries.h"
#include "CWindow.h"

class CWindow;


class CCheckBox : public CWindow
{
private:

	int check; // was checked?

	bool radiobutton; // maybe we want radiobutton?
	
	DWORD group;

public:
	CCheckBox();

	
	void SetGroup();
	void SetRadioButton();
	void Draw(TCHAR *text);
	bool Check();
	void SetCheck(bool stage);

};
#endif