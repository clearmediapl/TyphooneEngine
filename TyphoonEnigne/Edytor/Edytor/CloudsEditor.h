#ifdef UNICODE
#define _T(x) L##x
#else
#define _T(x) x
#endif

#include <windows.h> 


HWND cloudshWnd; 
	
	static TCHAR clpszAppName[] = TEXT( "xxxx" ); 


	
LRESULT CALLBACK MainWndProc2(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 

{ 
switch (uMsg) 
{ 

case WM_CREATE: 

break; 

case WM_DESTROY: 

PostQuitMessage(0);
break; 

case WM_KEYDOWN: 

break; 

default: 

return (DefWindowProc(hWnd, uMsg, wParam, lParam)); 

} 
return(0L); 
}



	
	
	
bool CreateWindowClouds(HINSTANCE hInstance)
{ 

		
	MSG msg;
WNDCLASS wndclass;


wndclass.style = CS_HREDRAW | CS_VREDRAW; 
wndclass.lpfnWndProc = MainWndProc2; 
wndclass.cbClsExtra = 0; 
wndclass.cbWndExtra = 0; 
wndclass.hInstance = hInstance; 
wndclass.hIcon = NULL; 
wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); 
wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); 
wndclass.lpszMenuName = NULL; 
wndclass.lpszClassName = clpszAppName; 

if(RegisterClass(&wndclass) == 0) 

return FALSE; 

cloudshWnd = CreateWindow(clpszAppName, clpszAppName, 
WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 
CW_USEDEFAULT, CW_USEDEFAULT,
CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL); 
if(cloudshWnd == NULL) 
return FALSE; 

ShowWindow(cloudshWnd, SW_SHOW); 
UpdateWindow(cloudshWnd); 

while(GetMessage(&msg, NULL, 0, 0)) 
{ 
      TranslateMessage(&msg); 
      DispatchMessage(&msg); 
} 

return msg.wParam;

}
