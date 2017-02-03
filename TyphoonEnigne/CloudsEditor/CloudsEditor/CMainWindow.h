#include "Libraries.h"

#include "CButton.h"
#include "CCheckBox.h"
#include "COpenglWindow.h"

class CMainWindow
{
private:
	HWND WindowHWND; //hwnd of window

	
	//edytor
public:
	bool keys2[256];
	COpenglWindow *editor;
	

public:

	CMainWindow();

	void GetWindowHwnd(HWND hwnd);

	void OnInit();
	void OnEvent(int myWparam);
	void OnNotify(NMHDR *nmhr);
	void OnKill();
	void OnMouseClick();
	void OnPress();
	void OnSize(int height, int width);
		
	void MainLoop();//l();

};