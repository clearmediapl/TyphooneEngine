#include "Libraries.h"

#include "CButton.h"
#include "CCheckBox.h"
#include "COpenglWindow.h"

class CMainWindow
{
private:
	//shortcuts
	enum ShortKeys
	{
		SHORT_CAMERAMOVING = 0, //camera moving
		SHORT_OBJECTMOVING = 1, //object movie
	};
	ShortKeys m_shortcuts;

	HWND WindowHWND; //hwnd of window

	int n_tab; //number of active tab
	int index, objIndex;
	
	
	int s;
	int nDelete; //number of delete object
	//edytor
public:
	bool keys2[256];
	COpenglWindow *renderPerspective;
	

public:

	CMainWindow();

	void GetWindowHwnd(HWND hwnd);

	void OnInit();
	void OnEvent(int myWparam);
	void OnNotify(NMHDR *nmhr);
	void OnKill();
	void onMouseMove();
	void OnMouseClick();
	void OnPress();
	void OnSize(int height, int width);
		
	void MainLoop();//l();

};