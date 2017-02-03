#ifndef _CWINDOW_H_
#define _CWINDOW_H_

#include "Libraries.h"

class CWindow
{

public:
 
      HWND pHwnd;  //parend's HWND
	  HWND cHwnd;  //control's HWND
 
	  int ID; //  ID 
	  int posX, posY; // position

	  TSize Size; // orginal size
	  TSize orginalSize; //org size
	  TSize newSize; // old size
	
	  
	int delta;
 
public:
	  CWindow();
	  
	  void SetParentHwnd(HWND hWnd);
	  void SetID(int cID);
      void SetPosition(int positionX, int positionY);
      void SetSize(int sizeX, int sizeY);
	  void SetVisible(bool state);

	  void GetParentWindowSize(int x, int y);
	  void RefreshSize(int x, int y);
	  
 
 
};
#endif