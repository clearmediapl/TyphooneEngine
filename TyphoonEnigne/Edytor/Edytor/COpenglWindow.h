
#include "Libraries.h"

#include "CEditorRender.h"


class COpenglWindow
{
private:
	HDC         hDC;
	HGLRC		hRC;
	HWND        pHwnd;
//	HWND		hWnd;
	HINSTANCE	hInstance;


public:
	HWND		hWnd;
	CEditorRender *editor;

	int activeObj; // active object

	bool drawXAxis; // draw x axis in grid?
	bool drawYAxis;// draw y axis in grid?
	bool drawZAxis;// draw z axis in grid?

	bool modifyXAxis; // modify X axis?
	bool modifyYAxis; // modify Y axis?
	bool modifyZAxis; // modify Z axis?
	bool modifyCamera;

	bool loadMesh; 
	bool loadMap;
	bool loadSky;


	bool wireDrawMode;
	bool solidDrawMode;

	bool m_moveToCamera;

	

	


	TCHAR path[255];
	TCHAR skyPath[128];

	int cameraID; // camera ID

	bool moveObj; // now we move obj
	bool rotateObj;// now we rotate obj
	bool scaleObj; // now we scale obj

public:

	void SetKeys(bool src[255], bool dest[255]);

	COpenglWindow();

	void SetParentHwnd(HWND parentHwnd); 
	void SetSize(int height, int width);	

	bool CreateOpenglWindow(int PosX, int PosY, int SizeX, int SizeY);
	void DestroyOpenglWindow();

	void InitOpengl();
	void DrawOpengl();



};