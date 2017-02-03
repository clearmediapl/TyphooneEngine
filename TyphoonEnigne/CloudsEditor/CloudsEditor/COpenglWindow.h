
#include "Libraries.h"

#include "engine/CTexture.h"
#include "engine/CClouds.h"


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

	//////////////////	
	CClouds *clouds;
	/////////////////

	double timer;

	bool loadclouds; //load clouds button clicked?
	bool saveclouds; //save clouds button clicked?


	bool loadtex1; //load texture1 button clicked?
	bool loadtex2; //load texture2 button clicked?

	TCHAR *path1;
	TCHAR *path2;


	////////////////////
	GLuint floorTex;

	CTexture *floor;
	CTexture *background;


	int speed;
	int brightness;
	float height;
	float scale;
	int alpha;
	float sizeY;
	int backgroundBrightness;
	

public:

	

	COpenglWindow();

	void SetParentHwnd(HWND parentHwnd); 
	void SetSize(int height, int width);	

	bool CreateOpenglWindow(int PosX, int PosY, int SizeX, int SizeY);
	void DestroyOpenglWindow();

	void InitOpengl();
	void DrawOpengl();
	void Update();



};