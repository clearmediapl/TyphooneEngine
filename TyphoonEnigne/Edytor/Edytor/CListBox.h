#include "Libraries.h"
#include "CWindow.h"

class CWindow;

class CListBox : public CWindow
{
private:
		int selected;
public:

	CListBox();

	void Draw();
	void AddElement(TCHAR *caption); // add new element to list
	void DeleteElement(int number);  // delete element from list
	void SetSelected(int index);   // select elemtnt

	void SetItemData(int index, int number); // set data to element of list
	int  GetItemData(int index); // get data from element

	int  GetSelected(); //get selected element
	bool isChange(WPARAM wParam);
};