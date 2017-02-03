#ifdef UNICODE
#define _T(x) L##x
#else
#define _T(x) x
#endif

#include <windows.h> 
#include "CMainWindow.h"

	HWND hWnd; 




	HDC hDC;
	bool ExitProgs;
	PAINTSTRUCT ps;
	//////////////
	int MywParam;
	HWND MylParam;
	NMHDR *pnmhdr;
	////////////////

	CMainWindow *myWindow;
	static TCHAR lpszAppName[] = TEXT("3d editor"); 

	#include "engine/CLogger.h"
	CLogger *mainLog = new CLogger();

	bool keys[256];

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{ 
	
	switch (uMsg) 
	{ 
		case WM_CREATE: 
		
			
			mainLog->Create(TEXT("Editor.log"));
			mainLog->NewSection(_T("Window"));
			mainLog->LogSucces(_T("Create Window"));
			////////////////////
			myWindow = new CMainWindow();
			myWindow->GetWindowHwnd(hWnd);
			myWindow->OnInit();
			mainLog->LogSucces(_T("Create control's"));
		    ////////////////////////
		
	
			break; 
			
		case WM_MOUSEMOVE:
				myWindow->onMouseMove();
				break;
		case WM_LBUTTONDOWN:
				myWindow->OnMouseClick();
				break;
		case WM_KEYDOWN:

			/////////
			myWindow->keys2[wParam] = TRUE;	
			////////

			return 1; 
		case WM_KEYUP:

			myWindow->keys2[wParam] = FALSE;	
		

			return 1; 
		case WM_COMMAND:
			
			MywParam = (int) LOWORD(wParam);    
			MylParam = (HWND) lParam; 
			
		
			//////////////////
			myWindow->OnEvent(wParam);
			////////////////
			break;
		case WM_NOTIFY:

			pnmhdr = (LPNMHDR)lParam;

			//////////////////
			myWindow->OnNotify(pnmhdr);
			////////////////z
			break;
		case WM_PAINT:
			hDC = BeginPaint(hWnd, &ps);
		
			EndPaint(hWnd,&ps);
			break;
		case WM_SIZE:
			/*
			fwSizeType = wParam; 
			nWidth = LOWORD(lParam); 
			nHeight = HIWORD(lParam);
			*/
			myWindow->OnSize(HIWORD(lParam), LOWORD(lParam));
						
			break;
		case WM_DESTROY: 
		
			////////////////////////
			mainLog->LogSucces(_T("Close window"));

			myWindow->OnKill();
			delete myWindow;
			delete mainLog;

			
			PostQuitMessage(0);
			/////////////////////

			break; 
		default: 
			return (DefWindowProc(hWnd, uMsg, wParam, lParam)); 
	} 
	return(0L); 
} 

// ---------------------------------------------------------
// CWindow::OnInit()
// On init window
// ---------------------------------------------------------
//


	
	

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{ 

		MSG msg;
		WNDCLASS wndclass;
	

		wndclass.style = CS_HREDRAW | CS_VREDRAW; 
		wndclass.lpfnWndProc = MainWndProc; 
		wndclass.cbClsExtra = 0; 
		wndclass.cbWndExtra = 0; 
		wndclass.hInstance = hInstance; 
		wndclass.hIcon = NULL; 
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); 
		wndclass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(63,128,192)); 
		wndclass.lpszMenuName = NULL; 
		wndclass.lpszClassName = lpszAppName; 

		if(RegisterClass(&wndclass) == 0) 
		{
			mainLog->LogError(_T("Can't register window class"));
			return FALSE; 
		}

		hWnd = CreateWindow(lpszAppName, lpszAppName, 
		WS_OVERLAPPEDWINDOW |  WS_CLIPSIBLINGS | WS_MAXIMIZE , 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL); 
	
	
		


		if(hWnd == NULL) 
		{
			mainLog->LogError(_T("Can't create hwnd"));
			return FALSE; 
		}
		ShowWindow(hWnd, SW_SHOW); 
		mainLog->LogSucces(_T("Show window"));
		UpdateWindow(hWnd); 


	
	while(!ExitProgs)								
	{
 		  
		
	
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
		{
			if (msg.message==WM_QUIT)				
			{
				ExitProgs = true;
					
				
			}
			else								
			{
				TranslateMessage(&msg);			
				DispatchMessage(&msg);				
			}
		
		}
	 else										
		{
		
			myWindow->MainLoop();

			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
				
			

		} 
	}

	return (int)msg.wParam; 
} 


