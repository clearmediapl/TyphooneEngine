#ifndef _CBUTTON_H_
#define _CBUTTON_H_

#include "Libraries.h"
#include "CWindow.h"


class CButton  : public CWindow
{
private:
	
     bool press;
	

public:
	CButton();
	
	void Draw(TCHAR *text);
	bool Check(int cID); // chec when button was pressed
	
};
#endif