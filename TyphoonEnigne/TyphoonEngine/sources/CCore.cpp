/*******************************************************************/
/* Filename:                  CCore.cpp                            */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         17.05.2006                           */
/* Last revision:             17.05.2006                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/

#include "bibloteki.h"
#include "CCore.h"





//////////////////
// BEGIN: glowna funkcja
//////////////////
GLvoid CCore::WindowSet(GLsizei width, GLsizei height)
{

	if (height==0) 
	{
		height =1;
	}

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity(); //wyzerowanie macierzy

	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,1,1000.0f);
	 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLvoid CCore::WindowKill(GLvoid)
{


	if (pelen_ekran) 
	{
		ChangeDisplaySettings(NULL,0); 
		ShowCursor(TRUE);  
	}

	///////////////////////
	// Oblsluga bledow
    ///////////////////////

	if (hRC)
	{
		if (!wglMakeCurrent(NULL,NULL)) 
		{
			MessageBox(NULL,TEXT("Release Of DC And RC Failed."),TEXT("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);  //blad
		}

		hRC=NULL;
	}
	if (hDC && !ReleaseDC(hWnd,hDC))
	{
		MessageBox(NULL,TEXT("Release Device Context Failed."),TEXT("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
        hDC=NULL;
	}

	if (hWnd && !DestroyWindow(hWnd))					
	{
		MessageBox(NULL,TEXT("Could Not Release hWnd."),TEXT("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;									
	}

	if (!UnregisterClass(TEXT("Typhoon Engine"),hInstance))			
	{
		MessageBox(NULL,TEXT("Could Not Unregister Class."),TEXT("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									
	}

	
}

int CCore::WindowInit(GLvoid)
{

	//////////////////////
	game = new CGame();
	//////////////////////

	
	game->Init();

	
	return TRUE;
	
}
int CCore::WindowDraw(GLvoid) //Funkcja rysujaca 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czysc kolor i bufor glebokosci
	glLoadIdentity(); //czysc macierze


	game->Draw();
	game->Update(frameTime);
	

	return TRUE;
}


BOOL CCore::WindowCreate(LPCWSTR name,int width,int height,int bits,bool fullscreenflag)
{
 
	GLuint		PixelFormat;
	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD       dwStyle;
	RECT WindowRect;
	WindowRect.left=(long)0;
	WindowRect.right=(long)width;
	WindowRect.top=(long)0;
	WindowRect.bottom=(long)height;

	pelen_ekran=fullscreenflag;

	hInstance	      	= GetModuleHandle(NULL);
	wc.style	    	= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon	    	= LoadIcon(NULL, IDI_WINLOGO);  //ikonka
	wc.hCursor          = LoadCursor(NULL, IDC_ARROW);  //cursor
	wc.hbrBackground	= NULL;	
	wc.lpszMenuName		= NULL;	 // nie ma menu
	wc.lpszClassName	= TEXT("Typhoon Engine"); // nazwa classy


	if (!RegisterClass(&wc)) //jesli nie zarejestruje classy ..
	{
		MessageBox(NULL,TEXT("Failed To Register The Window Class."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION); //..wywal blad
		

	}

	if (pelen_ekran) //jesli pelen ekran...
    {
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth	= width; 
		dmScreenSettings.dmPelsHeight	= height;
		dmScreenSettings.dmBitsPerPel	= bits;	
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

        if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
            if (MessageBox(NULL,TEXT("The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?"),TEXT("Typhoon Engine"),MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				pelen_ekran=FALSE;	
			}
			
		
		else
		{
			MessageBox(NULL,TEXT("Program Will Now Close."),TEXT("ERROR"),MB_OK|MB_ICONSTOP);
            return FALSE;
		}
	}
}

if (pelen_ekran)
{
	dwExStyle=WS_EX_APPWINDOW;
	dwStyle=WS_POPUP;
	ShowCursor(FALSE);
}
else
{
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	dwStyle=WS_OVERLAPPEDWINDOW;
}

AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);


if (!(hWnd=CreateWindowEx(              dwExStyle,	
	                                    TEXT("Typhoon Engine"),
						            	name,
						             	dwStyle|
							            WS_CLIPSIBLINGS |
						             	WS_CLIPCHILDREN ,	
						               	0, 0,
						             	WindowRect.right-WindowRect.left,
						              	WindowRect.bottom-WindowRect.top,
						              	NULL,
						            	NULL, //bez menu
						            	hInstance,
						            	NULL)))

{
	WindowKill();	
	MessageBox(NULL,TEXT("Window error."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
    return FALSE;
}

	SetTimer(hWnd,1,1000,NULL);


    static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				
		1,											
		PFD_DRAW_TO_WINDOW |						
		PFD_SUPPORT_OPENGL |					
		PFD_DOUBLEBUFFER,							
		PFD_TYPE_RGBA,							
		bits,									
		0, 0, 0, 0, 0, 0,							
		0,											
		0,										
		0,											
		0, 0, 0, 0,									
		16,											// 16Bit Z-Buffer   
		0,										
		0,										
		PFD_MAIN_PLANE,								
		0,										
		0, 0, 0										
	};


 
  
    if (!(hDC=GetDC(hWnd)))							
	{
		WindowKill();								
		MessageBox(NULL,TEXT("Can't Create A GL Device Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	
	{
		WindowKill();								
		MessageBox(NULL,TEXT("Can't Find A Suitable PixelFormat."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		
	{
	    WindowKill();									
		MessageBox(NULL,TEXT("Can't Set The PixelFormat."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}

	if (!(hRC=wglCreateContext(hDC)))				
	{
		WindowKill();								
		MessageBox(NULL,TEXT("Can't Create A GL Rendering Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if(!wglMakeCurrent(hDC,hRC))					
	{
		WindowKill();								
		MessageBox(NULL,TEXT("Can't Activate The GL Rendering Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}

	ShowWindow(hWnd,SW_SHOW);						
	SetForegroundWindow(hWnd);						
	SetFocus(hWnd);									
	WindowSet(width,height);				

	
	if (!WindowInit())									
	{
		WindowKill();							
		MessageBox(NULL,TEXT("Initialization Failed."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}


	return TRUE;						

}





