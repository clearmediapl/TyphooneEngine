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
	static TCHAR lpszAppName[] = TEXT( "Clouds editor " ); 

//	#include "engine/CLogger.h"
//	CLogger *g = new CLogger();

HBRUSH hBrush1 ;
	bool keys[256];
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{ 
	
	switch (uMsg) 
	{ 
		case WM_CREATE: 
		
			hBrush1 = CreateSolidBrush(RGB(63,128,192)); //brush for background of controls



			//g->Create(TEXT("window.log"));
			////////////////////
			myWindow = new CMainWindow();
			myWindow->GetWindowHwnd(hWnd);
			myWindow->OnInit();
		    ////////////////////////
		
	
			break; 
		case WM_DESTROY: 
		
			////////////////////////
			myWindow->OnKill();
			delete myWindow;
			PostQuitMessage(0);
			/////////////////////

			break; 
		case WM_LBUTTONDOWN:
				myWindow->OnMouseClick();
				break;
		case WM_KEYDOWN:

			/////////
			keys[wParam] = TRUE;	
				
		
			////////

			return 0; 
		case WM_KEYUP:

			keys[wParam] = FALSE;	
		

			return 0; 
		case WM_COMMAND:
			MywParam = (int) LOWORD(wParam);    // identifier of button 
			MylParam = (HWND) lParam; 
			
			//////////////////
			myWindow->OnEvent(MywParam);
			////////////////
			break;
		case WM_CTLCOLORSTATIC:
			
			
			 SetBkColor((HDC)wParam,RGB(63,128,192));

			return (LRESULT) hBrush1;
		case WM_NOTIFY:

			pnmhdr = (LPNMHDR)lParam;

			//////////////////
			myWindow->OnNotify(pnmhdr);
			////////////////
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
		wndclass.hIcon = (HICON)LoadImage(NULL,_T("2.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); 
		wndclass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(63,128,192));
		wndclass.lpszMenuName = NULL; 
		wndclass.lpszClassName = lpszAppName; 

		if(RegisterClass(&wndclass) == 0) 
		return FALSE; 

		hWnd = CreateWindow(lpszAppName, lpszAppName, 
		WS_OVERLAPPEDWINDOW | WS_MAXIMIZE | WS_CLIPSIBLINGS  , 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL); 
	
	
		


		if(hWnd == NULL) 
			return FALSE; 

		ShowWindow(hWnd, SW_SHOW); 
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


