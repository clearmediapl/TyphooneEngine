/*******************************************************************/
/* Filename:                  CCore.h                              */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         17.05.2006                           */
/* Last revision:             17.05.2006                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/




#ifndef _CMAIN_H_
#define _CMAIN_H_

#include <windows.h>
#include "CLogger.h"
#include "CGame.h"
#include "CTimer.h"





LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


	CLogger *log2;
	HDC         hDC=NULL;
	HGLRC		hRC=NULL;
	HWND		hWnd=NULL;
	HINSTANCE	hInstance;

	bool keys[256]; 
	bool active=TRUE;
	bool pelen_ekran=TRUE;



class CCore {
public:

	double frameTime;
	//CLogger *log;
	CGame *game;	
	CTimeCounter timer;

	GLvoid WindowKill(GLvoid); 
	BOOL   WindowCreate(LPCWSTR name, int width, int height, int bits, bool fullscreenflag); 
	int    WindowInit(GLvoid); 
	int    WindowDraw(GLvoid); 
	GLvoid WindowSet(GLsizei width, GLsizei height);


};
//////////////////////
//END: glowna klasa///
//////////////////////
CCore core;


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
				active=TRUE;					
			}
			else
			{
				active=FALSE;					
			}

			return 0;								
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
		case WM_LBUTTONUP:
			{
				core.game->isClicked = false;
				break;
			}
		case WM_LBUTTONDOWN:
			{
				 SetFocus(hWnd);
					core.game->isClicked = true;
				break;
			}

		case WM_MOUSEMOVE:
			{
				core.game->newMouseX = (float)LOWORD(lParam);
				core.game->newMouseY = (float)HIWORD(lParam);

				core.game->MouseX = core.game->newMouseX - core.game->oldMouseX;
				core.game->MouseY = core.game->newMouseY - core.game->oldMouseY;
				
				core.game->oldMouseX = (float)LOWORD(lParam);
				core.game->oldMouseY = (float)HIWORD(lParam);

					break;
			}


		case WM_CLOSE:								
		{
			PostQuitMessage(0);						
			return 0;							
		}

		case WM_KEYDOWN:						
		{
			core.game->keys[wParam] = TRUE;					
			return 0;							
		}

		case WM_KEYUP:							
		{																																																
			core.game->keys[wParam] = FALSE;
		
			return 0;							
		}


	 case WM_TIMER:
		 {
			
			break;
		 }
		case WM_SIZE:								
		{
			core.WindowSet(LOWORD(lParam),HIWORD(lParam));  
			return 0;								
		}
	}


	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

///////////////////////
//BEGIN:glowna funkcja/
///////////////////////
int WINAPI WinMain(	HINSTANCE	hInstance,			
					HINSTANCE	hPrevInstance,		
					LPSTR		lpCmdLine,		
					int			nCmdShow)			
{
	MSG		msg;									
	BOOL	done=FALSE;								

 
	/////////////////////////
	// creat logging file
//	log2 = new CLogger();
//	log2->Append(_T("main.htm"));
	/////////////////////////////




	pelen_ekran=false;

	if (!core.WindowCreate(TEXT("Typhoon Engine by Bojkar"),800,600,32,pelen_ekran))
	{
		
		return 0;							
	}
	else
	{
		
	}


	int g_nFPS = 0, g_nFrames = 0;// FPS and FPS Counter
	DWORD g_dwLastFPS = 0;
 
	while(!done)								
	{
 		  
		core.timer.StartCount();
	
		core.timer.StopCount();
		core.frameTime = core.timer.GetTime();
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
		{
			
			 

			if (msg.message==WM_QUIT)				
			{
				done=TRUE;							
			}
			else								
			{
				TranslateMessage(&msg);			
				DispatchMessage(&msg);				
			}
		
		}
	 else										
		{
		

			if ((active && !core.WindowDraw()) ||keys[VK_ESCAPE])	
			{
				done=TRUE;	
			}
			else									
			{
				if( GetTickCount() - g_dwLastFPS >= 1000 )// When A Second Has Passed...
			{
				g_dwLastFPS = GetTickCount();// Update Our Time Variable
				g_nFPS = g_nFrames;// Save The FPS
				g_nFrames = 0;// Reset The FPS Counter

				TCHAR szTitle[256]={0};// Build The Title String
				swprintf( szTitle, _T("SHOW FPS - %d FPS"), g_nFPS );

				SetWindowText( hWnd, szTitle );// Set The Title
			}
				g_nFrames++;

				
				SwapBuffers(hDC);					// Swap Buffers wlacz

			}

			
		}



	}

//		log2->Load();

	// Shutdown
	core.WindowKill();
	core.game->Kill();
	

	

	// zabij okno!
	return (true);							// Exit from porogram 
}

#endif