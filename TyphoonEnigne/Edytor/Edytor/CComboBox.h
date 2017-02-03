#include "Libraries.h"
#include "CWindow.h"

class CComboBox : public CWindow
{
private:
	int index;

public:
	CComboBox();

	void AddItem(TCHAR *text);
	void Draw();

	void SetSelected(int ID);
	int getSelected();

	bool isChange(WPARAM wParam);



};