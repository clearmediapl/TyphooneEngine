#include "Libraries.h"
#include "CWindow.h"

class CTrackBar : public CWindow
{
private:
	int max;
	int min;

public:
	CTrackBar();

	void SetMaxValue(int value);
	void SetMinValue(int value);
	void SetTrackPos(int value);
	
	int getValue();

	void Draw();

};