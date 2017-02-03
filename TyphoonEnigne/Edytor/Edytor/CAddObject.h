#include "Libraries.h"
#include "CWindow.h"

class CAddObject : public CWindow
{
private:
	TCHAR *fileName;
	TCHAR filter[32];

public:
	CAddObject();

	void Init();
	void Draw();

	TCHAR *getFileName();


};