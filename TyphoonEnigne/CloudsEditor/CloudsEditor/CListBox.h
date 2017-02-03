#include "Libraries.h"
#include "CWindow.h"

class CWindow;

class CListBox : public CWindow
{
private:
	
public:

	CListBox();

	void Draw();
	void AddElement(TCHAR *caption);
	void DeleteElement(int number);
	void SetSelected(int index);

	void SetItemData(int index, int number);
	int  GetItemData(int index);

	int  GetSelected();
};