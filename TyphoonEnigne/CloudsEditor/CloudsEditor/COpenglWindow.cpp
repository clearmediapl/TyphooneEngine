
#include "engine/CCamera.h"
#include "engine/CLogger.h"
#include "COpenglWindow.h"



 float MouseX, MouseY;
 float newMouseX, newMouseY;
 float oldMouseX, oldMouseY;
 bool isClicked;

bool keys2[256];

float vx,vy,vz;

CCamera *camera;


CLogger *test = new CLogger();

COpenglWindow::COpenglWindow()
{
	floor  = new CTexture();
	floor->defaultPath = true;

	camera = new CCamera();
	clouds = new CClouds();
	test->Create(_T("test"));

	speed = 0;
	alpha = 0;
	
	
}
void COpenglWindow::SetSize(int height, int width)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 

	gluPerspective(45.0f,(GLfloat)height/(GLfloat)width,0.1f,10000.0f);
	 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}
LRESULT CALLBACK WndProc(	HWND	hWnd,
							UINT	uMsg,
							WPARAM	wParam,
							LPARAM	lParam)
{

	switch (uMsg)									
	{
		case WM_ACTIVATE:						
		{
			if (!HIWORD(wParam))					
			{
			//	active=TRUE;					
			}
			else
			{
			//	active=FALSE;					
			}

			return 0;								
		}
		case WM_CREATE:
		{
				
		}

		case WM_SYSCOMMAND:							
		{
			switch (wParam)						
			{
				case SC_SCREENSAVE:					
				case SC_MONITORPOWER:				
				return 0;							
			}
			break;									
		}

		case WM_KEYDOWN:						
		{
			
			keys2[wParam] = TRUE;
			return 1;					
		}
	

		case WM_KEYUP:							
		{		
			
			keys2[wParam] = FALSE;
		
			return 1;							
		}

		case WM_CLOSE:								
		{
		
			PostQuitMessage(0);						
			return 0;							
		}

		
		case WM_MOUSEMOVE:
			{
				newMouseX = (float)LOWORD(lParam);
				newMouseY = (float)HIWORD(lParam);

				MouseX = newMouseX - oldMouseX;
				MouseY = newMouseY - oldMouseY;
				
				oldMouseX = (float)LOWORD(lParam);
				oldMouseY = (float)HIWORD(lParam);

					break;
			}
		case WM_LBUTTONUP:
			{
				isClicked = false;
				break;
			}
		case WM_LBUTTONDOWN:
			{
				 SetFocus(hWnd);
					isClicked = true;
				break;
			}


		 case WM_TIMER:
		 {
			
			break;
		 }
		case WM_SIZE:								
		{			
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity(); 

				gluPerspective(45.0f,(GLfloat)LOWORD(lParam)/(GLfloat)HIWORD(lParam),0.1f,1000.0f);
	 
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
			return 0;								
		}
	}


	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void COpenglWindow::SetParentHwnd(HWND parentHwnd)
{
	pHwnd = parentHwnd;

}
bool COpenglWindow::CreateOpenglWindow(int PosX, int PosY, int SizeX, int SizeY)
{
	unsigned int		PixelFormat;
	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD       dwStyle;
	RECT WindowRect;
	



	//hInstance	      	= GetModuleHandle(NULL);
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

	

      


    dwExStyle=WS_EX_WINDOWEDGE;
	dwStyle=WS_CHILD | WS_BORDER;




AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);


if (!(hWnd=CreateWindowEx(              dwExStyle,	
	                                    TEXT("Typhoon Engine"),
						            	TEXT("ble"),
						             	dwStyle|
							            WS_CLIPSIBLINGS |
						             	WS_CLIPCHILDREN ,	
						               	PosX, PosY,
						             	SizeX,
						              	SizeY,
						              	pHwnd,
						            	NULL, //bez menu
						            	hInstance,
						            	NULL)))

{
	//WindowKill();	
	MessageBox(NULL,TEXT("Window error."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
   
}



	//SetTimer(hWnd2,1,1000,NULL);


    static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				
		1,											
		PFD_DRAW_TO_WINDOW |						
		PFD_SUPPORT_OPENGL |					
		PFD_DOUBLEBUFFER,							
		PFD_TYPE_RGBA,							
		32,									
		0, 0, 0, 0, 0, 0,							
		0,											
		0,										
		0,											
		0, 0, 0, 0,									
		32,											// 16Bit Z-Buffer   
		0,										
		0,										
		PFD_MAIN_PLANE,								
		0,										
		0, 0, 0										
	};


 
  
    if (!(hDC=GetDC(hWnd)))							
	{
	//	WindowKill();								
		MessageBox(NULL,TEXT("Can't Create A GL Device Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
  	return FALSE;							
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	
	{
	//	WindowKill();								
		MessageBox(NULL,TEXT("Can't Find A Suitable PixelFormat."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		
	{
	 //   WindowKill();									
		MessageBox(NULL,TEXT("Can't Set The PixelFormat."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}

	if (!(hRC=wglCreateContext(hDC)))				
	{
	//	WindowKill();								
		MessageBox(NULL,TEXT("Can't Create A GL Rendering Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if(!wglMakeCurrent(hDC,hRC))					
	{
	//	WindowKill();								
		MessageBox(NULL,TEXT("Can't Activate The GL Rendering Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							
	}

	ShowWindow(hWnd,SW_SHOW);						
	SetFocus(hWnd);									

	SetSize(SizeX,SizeY);
	InitOpengl();
	
	return TRUE;
}
void COpenglWindow::InitOpengl()
{
	glClearColor(0, 0, 0,0);
	glEnable(GL_TEXTURE_2D);


	if(!floor->LoadJPG(_T("data/terrain.jpg"), floorTex))
	{

	}


	//camera setup
	camera->SetPosition(0,0,0);
	camera->SetRotation(0,0,0);
	//clouds default setup
	clouds->SetHeight(1);
	clouds->SetSize(30,12,30);
	clouds->SetScale(0.2);
	clouds->SetSpeed(0.0001);
	clouds->SetCamera(camera);
	clouds->SetBrightness(255);
	clouds->Init();
	

}
void COpenglWindow::Update()
{
	if((timeGetTime() - timer) >= 5)
	{
		clouds->SetCamera(camera);
		clouds->Update();
		//update camera
		if(isClicked==true)
		{
		camera->Rotate.y+= MouseX;
		camera->Rotate.x+= MouseY;

		


		if(keys2['W']==true)
		{
			vx = -sin(DEGTORAD(camera->Rotate.y))*cos(DEGTORAD(camera->Rotate.x));
			vy = sin(DEGTORAD(camera->Rotate.x));
			vz = cos(DEGTORAD(camera->Rotate.y))*cos(DEGTORAD(camera->Rotate.x));
	

			camera->Position.x+=vx*0.1;
			camera->Position.y+=vy*0.1;
			camera->Position.z+=vz*0.1;
		}
		if(keys2['S']==true)
		{
			vx = -sin(DEGTORAD(camera->Rotate.y))*cos(DEGTORAD(camera->Rotate.x));
			vy = sin(DEGTORAD(camera->Rotate.x));
			vz = cos(DEGTORAD(camera->Rotate.y))*cos(DEGTORAD(camera->Rotate.x));
	

			camera->Position.x-=vx*0.1;
			camera->Position.y-=vy*0.1;
			camera->Position.z-=vz*0.1;
		}	
		
	
	
		}



		timer = timeGetTime();
	}

}
void COpenglWindow::DrawOpengl()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czysc kolor i bufor glebokosci
	glLoadIdentity();
	

	glLoadIdentity();

	clouds->SetSpeed(speed);
	clouds->SetHeight((float)height);
	clouds->SetScale((float)scale);
	clouds->SetAlpha((float)alpha);
//	clouds->SetSize((float)size, (float)sizeY, (float)size);
	clouds->SetBrightness((float)brightness);
	clouds->SetBackgroundBrightness((float)backgroundBrightness);

	test->CheckFloat(_T("suwak"), (float)clouds->alpha);
	clouds->Render();

	glLoadIdentity();

	camera->Render();
	glDisable(GL_BLEND);

	//floor render
	glTranslatef(0,-2,-10);
	glColor4f(1,1,1,1);
	glBindTexture(GL_TEXTURE_2D,floorTex);
	glScalef(20,1,20);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f,  1.0f, -3.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f,  1.0f,  3.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 3.0f,  1.0f,  3.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 3.0f,  1.0f, -3.0f);
	glEnd();

	
	if(loadtex1==true) //load texture for layer1?
	{
		clouds->tex->defaultPath = false;
		clouds->SetTexture1(path1);
		loadtex1=false;
	}
	if(loadtex2==true)//load texture for layer2?
	{
		clouds->tex->defaultPath = false;
		clouds->SetTexture2(path2);
		loadtex2=false;
	}

	
	

		


	Update();
	SwapBuffers(hDC);

}

void COpenglWindow::DestroyOpenglWindow()
{

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