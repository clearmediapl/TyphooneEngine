#include "Libraries.h"
#include "CWindow.h"

class CPushButton : public CWindow
{
private:

	DWORD style;
	DWORD group;
public:
	CPushButton();

	void SetNewGroup();
	void SetCheckBoxStyle();
	void SetCheck(bool stage);
	void Draw(TCHAR *caption);
	bool Check();
		
};