#include "CMainWindow.h"


#include "engine/CUtility.h"
#include "CGroupBox.h"
#include "CTab.h"
#include "CListBox.h"
#include "CPushButton.h"
#include "COpenDialog.h"
#include "CSaveDialog.h"
#include "CTrackBar.h"
#include "CEdit.h"

CUtility *utils = new CUtility();


COpenDialog *openTexture1 = new COpenDialog();
COpenDialog *openTexture2 = new COpenDialog();
COpenDialog *loadClouds = new COpenDialog();
CSaveDialog *saveClouds = new CSaveDialog();


CGroupBox *gSetup = new CGroupBox;                  //setup groupbox
CGroupBox *gTextures = new CGroupBox;               //textures groupbox
 
CEdit *eScale = new CEdit;                          //scale edit
CEdit *eSpeed = new CEdit;                          //speed edit
CEdit *eHeight = new CEdit;                         //height edit
CEdit *eAlpha = new CEdit;                          //alpha edit
CEdit *eBackBrightness = new CEdit;                 //Y size edit
CEdit *eBrightness = new CEdit;                     //background color edit

CTrackBar *tScale = new CTrackBar();                //scale trackbar
CTrackBar *tSpeed = new CTrackBar();                //Speed trackbar
CTrackBar *tHeight = new CTrackBar();               //height trackbar
CTrackBar *tAlpha = new CTrackBar();                //alphatrackbar
CTrackBar *tBackBrightness = new CTrackBar();       //background color trackbar
CTrackBar *tBrightness = new CTrackBar();           //Brightness trackbar

CButton *bAddTexture1 = new CButton();               //load texture 1 button
CButton *bAddTexture2 = new CButton();               //load texture 2 button
CButton *bSaveClouds  = new CButton();               //save clouds file
CButton *bLoadClouds  = new CButton();               //load clouds file


// ---------------------------------------------------------
// CWindow::CWindow()
// constructor
// ---------------------------------------------------------
//
CMainWindow::CMainWindow()
{
	editor = new COpenglWindow();
}
// ---------------------------------------------------------
// CWindow::GetWindowHwnd(HWND hwnd)
// get hwnd of parent window
// ---------------------------------------------------------
//

void CMainWindow::GetWindowHwnd(HWND hwnd)
{
	WindowHWND = hwnd;
}
	
// ---------------------------------------------------------
// CWindow::OnInit()
// On init window
// ---------------------------------------------------------
//
void CMainWindow::OnInit()
{
	RECT rc;
	GetWindowRect(WindowHWND,&rc);

	
	
	//Creat opengl windowe render 1
	editor = new COpenglWindow();
	editor->SetParentHwnd(WindowHWND);
	editor->CreateOpenglWindow(0,0,724,784);
	editor->InitOpengl();


	/*
			GROUP BOX'S
	*/

	//setup groupbox
	gSetup->SetParentHwnd(WindowHWND);
	gSetup->SetID(0);
	gSetup->SetPosition(740,20);
	gSetup->SetSize(270,380);
	gSetup->SetVisible(true);
	gSetup->Draw(_T("Setup"));

	//textures groupbox
	gTextures->SetParentHwnd(WindowHWND);
	gTextures->SetID(1);
	gTextures->SetPosition(740,415);
	gTextures->SetSize(270,90);
	gTextures->SetVisible(true);
	gTextures->Draw(_T("Textures"));


	/*
			TRACKBAR'S
	*/

	//scale trackbbar
	tScale->SetParentHwnd(WindowHWND);
	tScale->SetID(2);
	tScale->SetPosition(810,50);
	tScale->SetSize(185,20);
	tScale->SetMinValue(0);
	tScale->SetMaxValue(30);
	tScale->SetVisible(true);
	tScale->Draw();
	tScale->SetTrackPos(15);
	//speed trackbbar
	tSpeed->SetParentHwnd(WindowHWND);
	tSpeed->SetID(4);
	tSpeed->SetPosition(810,75);
	tSpeed->SetSize(185,20);
	tSpeed->SetMinValue(0);
	tSpeed->SetMaxValue(20);
	tSpeed->SetVisible(true);
	tSpeed->Draw();
	tSpeed->SetTrackPos(8);
	//height trackbbar
	tHeight->SetParentHwnd(WindowHWND);
	tHeight->SetID(6);
	tHeight->SetPosition(810,100);
	tHeight->SetSize(185,20);
	tHeight->SetMinValue(0);
	tHeight->SetMaxValue(5);
	tHeight->SetVisible(true);
	tHeight->Draw();
	//alpha trackbbar
	tAlpha->SetParentHwnd(WindowHWND);
	tAlpha->SetID(8);
	tAlpha->SetPosition(810,150);
	tAlpha->SetSize(185,20);
	tAlpha->SetMinValue(0);
	tAlpha->SetMaxValue(255);
	tAlpha->SetVisible(true);
	tAlpha->Draw();
	tAlpha->SetTrackPos(100);
	//size Y trackbbar
	tBackBrightness->SetParentHwnd(WindowHWND);
	tBackBrightness->SetID(10);
	tBackBrightness->SetPosition(810,185);
	tBackBrightness->SetSize(185,20);
	tBackBrightness->SetMinValue(0);
	tBackBrightness->SetMaxValue(255);
	tBackBrightness->SetVisible(true);
	tBackBrightness->Draw();
	tBackBrightness->SetTrackPos(120);

	//Brightness trackbbar
	tBrightness->SetParentHwnd(WindowHWND);
	tBrightness->SetID(12);
	tBrightness->SetPosition(833,209);
	tBrightness->SetSize(160,20);
	tBrightness->SetMinValue(0);
	tBrightness->SetMaxValue(255);
	tBrightness->SetVisible(true);
	tBrightness->Draw();
	tBrightness->SetTrackPos(160);

	/*
			EDIT'S
	*/
	//scale edit
	eScale->SetParentHwnd(WindowHWND);
	eScale->SetID(3);
	eScale->SetPosition(750,51);
	eScale->SetSize(50,17);
	eScale->SetVisible(true);
	eScale->Draw(_T("Scale"));
	// speed edit
	eSpeed->SetParentHwnd(WindowHWND);
	eSpeed->SetID(5);
	eSpeed->SetPosition(750,76);
	eSpeed->SetSize(50,17);
	eSpeed->SetVisible(true);
	eSpeed->Draw(_T("Speed"));
	// height edit
	eHeight->SetParentHwnd(WindowHWND);
	eHeight->SetID(7);
	eHeight->SetPosition(750,101);
	eHeight->SetSize(50,17);
	eHeight->SetVisible(true);
	eHeight->Draw(_T("Height"));
	// depth edit
	eAlpha->SetParentHwnd(WindowHWND);
	eAlpha->SetID(9);
	eAlpha->SetPosition(750,151);
	eAlpha->SetSize(50,17);
	eAlpha->SetVisible(false);
	eAlpha->Draw(_T("Alpha"));
	// size Y edit
	eBackBrightness->SetParentHwnd(WindowHWND);
	eBackBrightness->SetID(11);
	eBackBrightness->SetPosition(750,186);
	eBackBrightness->SetSize(50,30);
	eBackBrightness->SetVisible(true);
	eBackBrightness->Draw(_T("Back color"));
	// brightness edit
	eBrightness->SetParentHwnd(WindowHWND);
	eBrightness->SetID(13);
	eBrightness->SetPosition(750,210);
	eBrightness->SetSize(75,17);
	eBrightness->SetVisible(true);
	eBrightness->Draw(_T("Brightness"));

	/*
			BUTTON'S
	*/
	//add texture layer 1
	bAddTexture1->SetParentHwnd(WindowHWND);
	bAddTexture1->SetID(15);
	bAddTexture1->SetPosition(750,445);
	bAddTexture1->SetSize(100,20);
	bAddTexture1->SetVisible(true);
	bAddTexture1->Draw(_T("Add layer 1"));
	//add texture layer 2
	bAddTexture2->SetParentHwnd(WindowHWND);
	bAddTexture2->SetID(17);
	bAddTexture2->SetPosition(750,470);
	bAddTexture2->SetSize(100,20);
	bAddTexture2->SetVisible(true);
	bAddTexture2->Draw(_T("Add layer 2"));
	//load clouds file
	bSaveClouds->SetParentHwnd(WindowHWND);
	bSaveClouds->SetID(19);
	bSaveClouds->SetPosition(770,550);
	bSaveClouds->SetSize(100,20);
	bSaveClouds->SetVisible(true);
	bSaveClouds->Draw(_T("Save Clouds"));
	//load clouds file
	bLoadClouds->SetParentHwnd(WindowHWND);
	bLoadClouds->SetID(21);
	bLoadClouds->SetPosition(880,550);
	bLoadClouds->SetSize(100,20);
	bLoadClouds->SetVisible(true);
	bLoadClouds->Draw(_T("Load Clouds"));
	


	

//	return TRUE;						

}
// ---------------------------------------------------------
// CWindow::OnSize(int height, int width)
// refresh size of control
// ---------------------------------------------------------
//
void CMainWindow::OnSize(int height, int width)
{

}
// ---------------------------------------------------------
// CWindow::OnEvent(int myWparam)
// Events
// ---------------------------------------------------------
//

void CMainWindow::OnEvent(int myWparam)
{
	// load texture 1
	if(bAddTexture1->Check(myWparam)==true)
	{
		openTexture1->SetCaption(TEXT("Open the texture for first layer"));
	//	openTexture1->SetFilter(_T("*.jpg *.jpg\0"));
		openTexture1->SetParentHwnd(bAddTexture1->cHwnd);

		if(openTexture1->getPath())
		{
			editor->loadtex1 = true;
			editor->path1 = openTexture1->path;
		}
			


	}
	// load texture 2
	if(bAddTexture2->Check(myWparam)==true)
	{
		openTexture2->SetCaption(TEXT("Open the texture for second layer"));
	//	openTexture2->SetFilter(TEXT("*.jpg\0*.jpg\0"));
		openTexture2->SetParentHwnd(bAddTexture2->cHwnd);

		if(openTexture2->getPath())
		{
			editor->loadtex2 = true;
			editor->path2 = openTexture2->path;
		}
	}
	// save clouds file
	if(bSaveClouds->Check(myWparam)==true)
	{
		saveClouds->SetCaption(TEXT("Save the clouds file"));
		saveClouds->SetFilter(_T("*.cfr *.cfr\0"));
		saveClouds->SetParentHwnd(bSaveClouds->cHwnd);

		if(saveClouds->getPath())
		{
			editor->clouds->SaveClouds(saveClouds->path);
		}
		editor->loadclouds = true;
	}
	// load clouds file
	if(bLoadClouds->Check(myWparam)==true)
	{
		loadClouds->SetCaption(TEXT("Open the clouds file"));
	//	openTexture2->SetFilter(TEXT("*.jpg\0*.jpg\0"));
		loadClouds->SetParentHwnd(bLoadClouds->cHwnd);

		if(loadClouds->getPath())
		{
			editor->clouds->LoadClouds(loadClouds->path);
			
			//set load values to tracker bar
			tBackBrightness->SetTrackPos(utils->ftoi(editor->clouds->backgroundBrightness*255));
			tScale->SetTrackPos(utils->ftoi(editor->clouds->scale*30));
			tSpeed->SetTrackPos(utils->ftoi(editor->clouds->speed*10100));
			tHeight->SetTrackPos(utils->ftoi(editor->clouds->height));
			tBrightness->SetTrackPos(utils->ftoi(editor->clouds->brightness*255));
			
		}
	}

	
		

}
void CMainWindow::OnNotify(NMHDR *nmhr)
{	
	

}
// ---------------------------------------------------------
// CWindow::OnPress()
// Keyboard
// ---------------------------------------------------------
//
void CMainWindow::OnMouseClick()
{
	SetFocus(editor->hWnd); //set focus do opengl window
	
	
}
void CMainWindow::OnPress()
{
		
	
}
// ---------------------------------------------------------
// CWindow::MainLoop()
// Main loop
// ---------------------------------------------------------
//
void CMainWindow::MainLoop()
{
	

	
	editor->DrawOpengl(); //draw opengl window | main loop


	//add proparties to clouds system
	editor->brightness = tBrightness->getValue();
	editor->speed = tSpeed->getValue();
	editor->height = tHeight->getValue();
	editor->scale = tScale->getValue();
	editor->alpha = tAlpha->getValue();
	editor->backgroundBrightness = tBackBrightness->getValue();

}
// ---------------------------------------------------------
// CWindow::OnKill()
// Kill window
// ---------------------------------------------------------
//
void CMainWindow::OnKill()
{
	
	//destroy opengl window render
	editor->DestroyOpenglWindow();

	delete editor;
	delete utils;


	delete openTexture1;
	delete openTexture2;
	delete loadClouds;
	delete saveClouds;


	delete gSetup;                  //setup groupbox
	delete gTextures;               //textures groupbox
 
	delete eScale;                          //scale edit
	delete eSpeed;                          //speed edit
	delete eHeight;                         //height edit
	delete eAlpha;                          //alpha edit
	delete eBackBrightness;                 //Y size edit
	delete eBrightness;                     //background color edit

	delete tScale;                //scale trackbar
	delete tSpeed;                //Speed trackbar
	delete tHeight;               //height trackbar
	delete tAlpha;                //alphatrackbar
	delete tBackBrightness;       //background color trackbar
	delete tBrightness;           //Brightness trackbar

	delete bAddTexture1;               //load texture 1 button
	delete bAddTexture2;               //load texture 2 button
	delete bSaveClouds;               //save clouds file
	delete bLoadClouds;               //load clouds file
}