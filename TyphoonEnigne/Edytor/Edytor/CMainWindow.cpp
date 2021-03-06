#include "CMainWindow.h"



#include "CGroupBox.h"
#include "CTab.h"
#include "CListBox.h"
#include "CPushButton.h"
#include "COpenDialog.h"
#include "CSaveDialog.h"
#include "CPropertyObject.h"

CEdit *t;

COpenDialog *openDialog;
CSaveDialog *saveDialog;
COpenDialog *OaddSky;

CTab *tab; // main tab pages

CGroupBox *gObject; // "object" group box
CGroupBox *gObjectControl; // "Object control" group box
CGroupBox *gGridAxis; // "Grid axis" group box
CGroupBox *gViewMode; //"View Mode" group box
CGroupBox *gDrawMode; //"Draw Mode" group box
CGroupBox *gControl; //"Control" group box

CButton *baddObject; // "add object" button
CButton *bdeleteObject; // "delete object" button
CButton *bSaveMap; // "Save map" button
CButton *bLoadMap; // "Load map" button
CButton *bLoadClouds; //"Load Clouds" button
CButton *bAddPlayer; //"Add player" button
CButton *bMoveToCamera; //"Move to camera" button


//------------
CPushButton *bMoveObject; //"move" button in object tag
CPushButton *bRotateObject; //"rotate" button in object tag
CPushButton *bScaleObject; //"scale" button in object tag
CPushButton *bModifyX; //"modify X" button in object tag
CPushButton *bModifyY; //"modify Y" button in object tag
CPushButton *bModifyZ; //"modify Z" button in object tag
CPushButton *bModifyCamera; // "Camera control" push button in object tag
CPushButton *bModifyObject; // "Camera control" push button in object tag

CCheckBox *cDrawXAxis; //"draw x axis" checkbox
CCheckBox *cDrawYAxis; //"draw y axis" checkbox
CCheckBox *cDrawZAxis; //"draw z axis" checkbox
CCheckBox *rPerspectiveView; //"perspective  view" radiobutton
CCheckBox *rTopView; //"top view" radiobutton
CCheckBox *rFreeLook; //"free look camera" radiobutton
CCheckBox *rSolidDrawMode; //"perspective  view" radiobutton
CCheckBox *rWireDrawMode; //"top view" radiobutton


CListBox *lObjectList; //"objects" list


CPropertyObject *m_propertyObject;
// ---------------------------------------------------------
// CWindow::CWindow()
// constructor
// ---------------------------------------------------------
//
CMainWindow::CMainWindow()
{


	index = 0;
	objIndex = 0;

	openDialog = new COpenDialog();
	saveDialog = new CSaveDialog();
	OaddSky = new COpenDialog();
	renderPerspective = new COpenglWindow();
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
	renderPerspective = new COpenglWindow();
	renderPerspective->SetParentHwnd(WindowHWND);
	renderPerspective->CreateOpenglWindow(0,0,724,784);
	renderPerspective->InitOpengl();
	renderPerspective->cameraID = 0;

	//392





	//main tab
	tab = new CTab();
	tab->SetParentHwnd(WindowHWND);
	tab->GetParentWindowSize(rc.right, rc.bottom);
	tab->SetID(100);
	tab->SetPosition(724,0);
	tab->SetSize(300,768);
	tab->Draw();
	tab->AddTab(TEXT("Objects"));
	tab->AddTab(TEXT("Setup"));
	tab->AddTab(TEXT("View"));


	//group box "object"
	gObject = new CGroupBox();
	gObject->SetParentHwnd(WindowHWND);
	gObject->SetPosition(730,20);
	gObject->SetSize(250,180);
	gObject->Draw(TEXT("Object"));
	// group box "object control"
	gObjectControl = new CGroupBox();
	gObjectControl->SetParentHwnd(WindowHWND);
	gObjectControl->SetPosition(730,450); //420
	gObjectControl->SetSize(129,150);
	gObjectControl->Draw(TEXT("Object control"));
	// group box "control"
	gControl = new CGroupBox();
	gControl->SetParentHwnd(WindowHWND);
	gControl->SetPosition(865,450);
	gControl->SetSize(129,150);
	gControl->Draw(TEXT("Control"));
	// group box "Grid axis"
	gGridAxis = new CGroupBox();
	gGridAxis->SetParentHwnd(WindowHWND);
	gGridAxis->SetPosition(730,20);
	gGridAxis->SetSize(130,135);
	gGridAxis->Draw(TEXT("Grid Axis"));
	gGridAxis->SetVisible(false);
	// group box "View mode"
	gViewMode = new CGroupBox();
	gViewMode->SetParentHwnd(WindowHWND);
	gViewMode->SetPosition(870,20);
	gViewMode->SetSize(130,135);
	gViewMode->Draw(TEXT("View mode"));
	gViewMode->SetVisible(false);
	// group box "Draw mode"
	gDrawMode = new CGroupBox();
	gDrawMode->SetParentHwnd(WindowHWND);
	gDrawMode->SetPosition(730,155);
	gDrawMode->SetSize(130,80);
	gDrawMode->Draw(TEXT("View mode"));
	gDrawMode->SetVisible(false);

	/*
	       BUTTONS

		   */

	//add object
	baddObject = new CButton();
	baddObject->SetParentHwnd(WindowHWND);
	baddObject->GetParentWindowSize(rc.right, rc.bottom);
	baddObject->SetID(101);
	baddObject->SetPosition(744,45);
	baddObject->SetSize(100,30);
	baddObject->Draw(TEXT("Add object"));
	//delete object
	bdeleteObject = new CButton();
	bdeleteObject->SetParentHwnd(WindowHWND);
	bdeleteObject->GetParentWindowSize(rc.right, rc.bottom);
	bdeleteObject->SetID(1112);
	bdeleteObject->SetPosition(864,45);
	bdeleteObject->SetSize(100,30);
	bdeleteObject->Draw(TEXT("Delete object"));
	//load clouds button
	bLoadClouds = new CButton();
	bLoadClouds->SetParentHwnd(WindowHWND);
	bLoadClouds->GetParentWindowSize(rc.right, rc.bottom);
	bLoadClouds->SetID(22);
	bLoadClouds->SetPosition(744,85);
	bLoadClouds->SetSize(100,30);
	bLoadClouds->Draw(TEXT("Add sky"));
	//add player button
	bAddPlayer = new CButton();
	bAddPlayer->SetParentHwnd(WindowHWND);
	bAddPlayer->GetParentWindowSize(rc.right, rc.bottom);
	bAddPlayer->SetID(221);
	bAddPlayer->SetPosition(744,125);
	bAddPlayer->SetSize(100,30);
	bAddPlayer->Draw(TEXT("Add player"));

		

	//move object push like button
	bMoveObject = new CPushButton();
	bMoveObject->SetParentHwnd(WindowHWND);
	bMoveObject->GetParentWindowSize(rc.right, rc.bottom);
	bMoveObject->SetNewGroup();
	bMoveObject->SetID(103);
	bMoveObject->SetPosition(744,472);
	bMoveObject->SetSize(100,30);
	bMoveObject->Draw(TEXT("Move object"));
	//rotate object push like button
	bRotateObject = new CPushButton();
	bRotateObject->SetParentHwnd(WindowHWND);
	bRotateObject->GetParentWindowSize(rc.right, rc.bottom);
	bRotateObject->SetID(104);
	bRotateObject->SetPosition(744,510);
	bRotateObject->SetSize(100,30);
	bRotateObject->Draw(TEXT("Rotate object"));
	//scale object push like button
	bScaleObject = new CPushButton();
	bScaleObject->SetParentHwnd(WindowHWND);
	bScaleObject->GetParentWindowSize(rc.right, rc.bottom);
	bScaleObject->SetID(105);
	bScaleObject->SetPosition(744,548);
	bScaleObject->SetSize(100,30);
	bScaleObject->Draw(TEXT("Scale object"));
	//"Camera control" push button
	bModifyCamera = new CPushButton();
	bModifyCamera->SetParentHwnd(WindowHWND);
	bModifyCamera->GetParentWindowSize(rc.right, rc.bottom);
	bModifyCamera->SetNewGroup();
	bModifyCamera->SetID(1019);
	bModifyCamera->SetPosition(875,483);
	bModifyCamera->SetSize(110,30);
	bModifyCamera->Draw(TEXT("Camera control"));
	bModifyCamera->SetCheck(false);
	//"Object control" push button
	bModifyObject = new CPushButton();
	bModifyObject->SetParentHwnd(WindowHWND);
	bModifyObject->GetParentWindowSize(rc.right, rc.bottom);
	bModifyObject->SetID(1019);
	bModifyObject->SetPosition(875,523);
	bModifyObject->SetSize(110,30);
	bModifyObject->Draw(TEXT("Object control"));
	bModifyObject->SetCheck(true);

	//move to camera button
	bMoveToCamera = new CButton();
	bMoveToCamera->SetParentHwnd(WindowHWND);
	bMoveToCamera->GetParentWindowSize(rc.right, rc.bottom);
	bMoveToCamera->SetID(18);
	bMoveToCamera->SetPosition(744,620); //530
	bMoveToCamera->SetSize(120,30);
	bMoveToCamera->Draw(TEXT("Move to Camera"));

	// save map
	bSaveMap = new CButton();
	bSaveMap->SetParentHwnd(WindowHWND);
	bSaveMap->GetParentWindowSize(rc.right, rc.bottom);
	bSaveMap->SetID(1201);
	bSaveMap->SetPosition(744,300);
	bSaveMap->SetSize(100,30);
	bSaveMap->Draw(TEXT("Save Map"));
	bSaveMap->SetVisible(false);
	// load map
	bLoadMap = new CButton();
	bLoadMap->SetParentHwnd(WindowHWND);
	bLoadMap->GetParentWindowSize(rc.right, rc.bottom);
	bLoadMap->SetID(1202);
	bLoadMap->SetPosition(864,300);
	bLoadMap->SetSize(100,30);
	bLoadMap->Draw(TEXT("Load Map"));
	bLoadMap->SetVisible(false);


	//modify x axis push like button
	bModifyX = new CPushButton();
	bModifyX->SetParentHwnd(WindowHWND);
	bModifyX->GetParentWindowSize(rc.right, rc.bottom);
	bModifyX->SetCheckBoxStyle();
	bModifyX->SetID(106);
	bModifyX->SetPosition(855,660);
	bModifyX->SetSize(20,20);
	bModifyX->Draw(TEXT("X"));
	//modify y axist push like button
	bModifyY = new CPushButton();
	bModifyY->SetParentHwnd(WindowHWND);
	bModifyY->GetParentWindowSize(rc.right, rc.bottom);
	bModifyY->SetCheckBoxStyle();
	bModifyY->SetID(107);
	bModifyY->SetPosition(875,660);
	bModifyY->SetSize(20,20);
	bModifyY->Draw(TEXT("Y"));
	//modify z axis push like button
	bModifyZ = new CPushButton();
	bModifyZ->SetParentHwnd(WindowHWND);
	bModifyZ->GetParentWindowSize(rc.right, rc.bottom);
	bModifyZ->SetCheckBoxStyle();
	bModifyZ->SetID(108);
	bModifyZ->SetPosition(895,660);
	bModifyZ->SetSize(20,20);
	bModifyZ->Draw(TEXT("Z"));

	
	

		/*
	      LIST BOX

		   */




	lObjectList= new CListBox();
	lObjectList->SetParentHwnd(WindowHWND);
	lObjectList->GetParentWindowSize(rc.right, rc.bottom);
	lObjectList->SetID(9549);
	lObjectList->SetPosition(790,230);
	lObjectList->SetSize(150,200);
	lObjectList->Draw();

	

	/*
	       CHECK BOXS

		   */


	//draw x axis
	cDrawXAxis = new CCheckBox();
	cDrawXAxis->SetParentHwnd(WindowHWND);
	cDrawXAxis->SetPosition(744,50);
	cDrawXAxis->SetSize(100,30);
	cDrawXAxis->SetID(200);
	cDrawXAxis->Draw(TEXT("Draw X axis"));
	cDrawXAxis->SetVisible(false);
	cDrawXAxis->SetCheck(true);
	//draw y axis
	cDrawYAxis = new CCheckBox();
	cDrawYAxis->SetParentHwnd(WindowHWND);
	cDrawYAxis->SetPosition(744,85);
	cDrawYAxis->SetSize(100,30);
	cDrawYAxis->SetID(201);
	cDrawYAxis->Draw(TEXT("Draw Y axis"));
	cDrawYAxis->SetVisible(false);
	//draw z axis
	cDrawZAxis = new CCheckBox();
	cDrawZAxis->SetParentHwnd(WindowHWND);
	cDrawZAxis->SetPosition(744,123);
	cDrawZAxis->SetSize(100,30);
	cDrawZAxis->SetID(202);
	cDrawZAxis->Draw(TEXT("Draw Z axis"));
	cDrawZAxis->SetVisible(false);
	//perspective view
	rPerspectiveView = new CCheckBox();
	rPerspectiveView->SetParentHwnd(WindowHWND);
	rPerspectiveView->SetPosition(880,50);
	rPerspectiveView->SetSize(100,30);
	rPerspectiveView->SetID(203);
	rPerspectiveView->SetRadioButton();
	rPerspectiveView->SetGroup(); //start new group
	rPerspectiveView->Draw(TEXT("Perspective View"));
	rPerspectiveView->SetVisible(false);
	rPerspectiveView->SetCheck(true);
	//top view
	rTopView = new CCheckBox();
	rTopView->SetParentHwnd(WindowHWND);
	rTopView->SetPosition(880,85);
	rTopView->SetSize(100,30);
	rTopView->SetID(205);
	rTopView->SetRadioButton();
	rTopView->Draw(TEXT("Top View"));
	rTopView->SetVisible(false);
	rTopView->SetCheck(false);
	//free look camaera
	rFreeLook = new CCheckBox();
	rFreeLook->SetParentHwnd(WindowHWND);
	rFreeLook->SetPosition(880,120);
	rFreeLook->SetSize(100,30);
	rFreeLook->SetID(288);
	rFreeLook->SetRadioButton();
	rFreeLook->Draw(TEXT("Free Look"));
	rFreeLook->SetVisible(false);
	rFreeLook->SetCheck(false);
	//solid draw mode
	rSolidDrawMode = new CCheckBox();
	rSolidDrawMode->SetParentHwnd(WindowHWND);
	rSolidDrawMode->SetPosition(744,170);
	rSolidDrawMode->SetSize(100,30);
	rSolidDrawMode->SetID(206);
	rSolidDrawMode->SetRadioButton();
	rSolidDrawMode->SetGroup(); // start new group
	rSolidDrawMode->Draw(TEXT("Solid"));
	rSolidDrawMode->SetVisible(false);
	rSolidDrawMode->SetCheck(true);
	//wire draw mode
	rWireDrawMode = new CCheckBox();
	rWireDrawMode->SetParentHwnd(WindowHWND);
	rWireDrawMode->SetPosition(744,200);
	rWireDrawMode->SetSize(100,30);
	rWireDrawMode->SetID(207);
	rWireDrawMode->SetRadioButton();
	rWireDrawMode->Draw(TEXT("Wire"));
	rWireDrawMode->SetVisible(false);
	rWireDrawMode->SetCheck(false);


	m_propertyObject = new CPropertyObject();
	m_propertyObject->SetParentHwnd(WindowHWND);
	m_propertyObject->Draw();
	m_propertyObject->Visable(false);


	t = new CEdit();
	t->SetParentHwnd(WindowHWND);
	t->SetID(524);
	t->SetSize(50,50);
	t->SetPosition(760,230);

	
	

//	return TRUE;						

}
// ---------------------------------------------------------
// CWindow::OnSize(int height, int width)
// refresh size of control
// ---------------------------------------------------------
//
void CMainWindow::OnSize(int height, int width)
{
	tab->RefreshSize(width, height);

}
// ---------------------------------------------------------
// CWindow::OnEvent(int myWparam)
// Events
// ---------------------------------------------------------
//
void CMainWindow::OnEvent(int myWparam)
{	
			
		
	
	/*8

		GRID DRAW OPTIONS

	*/
	if(cDrawXAxis->Check()) //check draw x axis
	{
		renderPerspective->drawXAxis = true; //draw x axis in grid
	} else  renderPerspective->drawXAxis = false;
	if(cDrawYAxis->Check())//check draw y axis
	{
		renderPerspective->drawYAxis = true;//draw y axis in grid
	} else  renderPerspective->drawYAxis = false;
	if(cDrawZAxis->Check())//check draw z axis
	{
		renderPerspective->drawZAxis = true;//draw z axis in grid
	} else  renderPerspective->drawZAxis = false;
	 
	/*8

		VIEW OPTIONS

	*/
	
	// set perspective view
	if(rPerspectiveView->Check())
	{
		renderPerspective->cameraID = 0;
	
	}
	// set top view
	if(rTopView->Check())
	{
		renderPerspective->cameraID = 1;
		
	}
	// set free look view
	if(rFreeLook->Check())
	{
		renderPerspective->cameraID = 2;
		
	}
	
	/*8

		Open OBJECT DIALOG

	*/

	//add object
	if(baddObject->Check(myWparam)==true)
	{
	
		renderPerspective->loadMesh = false;

		openDialog->SetCaption(TEXT("Open the object"));
		openDialog->SetFilter(_T("3ds max object(*.3ds)\0 *.3ds\0")
			                  _T("Lightwave files(*.lwo)\0 *.lwo\0\0"));
		openDialog->SetParentHwnd(baddObject->cHwnd);

		
		if(openDialog->getPath())
		{

		    wcscpy_s(renderPerspective->path,openDialog->path);
			renderPerspective->loadMesh = true;
		    lObjectList->AddElement(openDialog->getFileName()); //add new object to list
			lObjectList->SetItemData(index,objIndex); //set data to element of list
			lObjectList->SetSelected(index); //secelct active object
			index++;
			objIndex++;
		//	renderPerspective->editor->LoadMap(openDialog->path);
			
		
			
		}
			
				
	}
	//delete object
	if(bdeleteObject->Check(myWparam)==true)
	{
	    nDelete = lObjectList->GetSelected(); //get selected object
		s = lObjectList->GetItemData(nDelete);

		renderPerspective->editor->DeleteObject(s);
		lObjectList->DeleteElement(nDelete); //delete object from list
		index--;

		if(s==0)
		{

		MessageBox(WindowHWND,_T("as"),_T(""),MB_OK);
		}
	}

	if(bAddPlayer->Check(myWparam)==true)
	{
		renderPerspective->editor->AddPlayer(_T("path"));


	    lObjectList->AddElement(_T("Player")); //add new object to list
		lObjectList->SetItemData(index,objIndex); //set data to element of list
		lObjectList->SetSelected(index); //secelct active object
		index++;
		objIndex++;
	}


	//save map
	if(bSaveMap->Check(myWparam)==true)
	{
		saveDialog->SetParentHwnd(baddObject->cHwnd);
		saveDialog->SetCaption(TEXT("Save the map"));
		saveDialog->SetFilter(_T("*.bmf \0 *.bmf \0\0"));
	
	
		if(saveDialog->getPath()==true)
		{
			renderPerspective->editor->SaveMap(saveDialog->path);	
		}


	}
	//load map
	if(bLoadMap->Check(myWparam)==true)
	{
		index=0;
		objIndex = 0;
		openDialog->SetCaption(TEXT("Load the map"));
		openDialog->SetFilter(_T("Map file (*.bmf) \0 *.bmf"));
		openDialog->SetParentHwnd(bLoadMap->cHwnd);
		if(openDialog->getPath()==true)
		{
			renderPerspective->editor->LoadMap(openDialog->path);
			for(int i=0;i<renderPerspective->editor->nObj;i++)
			{
				lObjectList->AddElement(_T("object"));
				lObjectList->SetItemData(index,objIndex); //set data to element of list
				lObjectList->SetSelected(index); //secelct active object
				index++;
				objIndex++;
			}
		}
	
		

	}
	//add sky
	if(bLoadClouds->Check(myWparam)==true)
	{
		if(!renderPerspective->editor->sky)
		{
		renderPerspective->loadSky = false;
		OaddSky->SetCaption(TEXT("Load the sky"));
		OaddSky->SetFilter(TEXT("Sky format (*.sky) \0 *.sky"));
		OaddSky->SetParentHwnd(bLoadClouds->cHwnd);
		
		if(OaddSky->getPath())
		{

			wcscpy_s(renderPerspective->skyPath, OaddSky->path);
			renderPerspective->loadSky = true;
		    lObjectList->AddElement(_T("sky")); //add new object to list
			lObjectList->SetItemData(index,objIndex); //set data to element of list
			lObjectList->SetSelected(index); //secelct active object
			index++;
			objIndex++;
		}
		}
	
				
	}
	//move to camera
	if(bMoveToCamera->Check(myWparam)==true)
	{
		renderPerspective->m_moveToCamera = true;
					
	}
		

	/*8

		MODIFY OBJECT

	*/

	if(bMoveObject->Check() || m_shortcuts == SHORT_OBJECTMOVING) // move now?
	{
		renderPerspective->moveObj = true;

	}else renderPerspective->moveObj = false;
	if(bRotateObject->Check())// rotate now?
	{
		renderPerspective->rotateObj = true;
	}else renderPerspective->rotateObj = false;
	if(bScaleObject->Check())// scale now?
	{
		renderPerspective->scaleObj = true;

	}else renderPerspective->scaleObj = false;

	//------------------------------------------
	if(bModifyX->Check())
	{
		renderPerspective->modifyXAxis = true;
	}else renderPerspective->modifyXAxis = false;
	if(bModifyY->Check())
	{
		renderPerspective->modifyYAxis = true;
	}else renderPerspective->modifyYAxis = false; 
	if(bModifyZ->Check())
	{
		renderPerspective->modifyZAxis = true;
	}else renderPerspective->modifyZAxis = false; 
	//////////
	/*8

		MODIFY CAMERA

	*/

	if(bModifyCamera->Check() || m_shortcuts == SHORT_CAMERAMOVING)
	{
		renderPerspective->modifyCamera = true;
	}else renderPerspective->modifyCamera = false;
	

	/*

		DRAW MODE
		*/
	if(rSolidDrawMode->Check()) //check solid draw mode
	{
		renderPerspective->solidDrawMode = true; //draw in solid mode
	} else  renderPerspective->solidDrawMode = false;
	if(rWireDrawMode->Check())//check solid draw mode
	{
		renderPerspective->wireDrawMode = true;//draw in wire mode
	} else  renderPerspective->wireDrawMode = false;


	

	/*


		PROPERTY OBJECT


	*/

	//get collision type of object
	if(m_propertyObject->m_cCollisionType->isChange(myWparam)==true)
	{
		renderPerspective->editor->m_obj[renderPerspective->activeObj]->m_collisionType =(CObject::collision) m_propertyObject->getCollisionType();
	}

	//get collidable og object
	if(m_propertyObject->m_cCollidable->isChange(myWparam)==true)
	{
		renderPerspective->editor->m_obj[renderPerspective->activeObj]->m_collidable = m_propertyObject->getCollidable();
	}

	if(lObjectList->isChange(myWparam)==true)
	{
		renderPerspective->activeObj = lObjectList->GetItemData(lObjectList->GetSelected()); // get active object
		m_propertyObject->SetCollidable(renderPerspective->editor->m_obj[renderPerspective->activeObj]->m_collidable);
		m_propertyObject->SetCollisionType(renderPerspective->editor->m_obj[renderPerspective->activeObj]->m_collisionType);
	}

	
	
	
	//is object collidable
//	renderPerspective->editor->m_obj[renderPerspective->activeObj]->m_collidable = m_propertyObject->getCollidable();
	//collision type
//	renderPerspective->editor->m_obj[renderPerspective->activeObj]->m_collisionType = m_propertyObject->getCollisionType();
	
	
      

	
	
}
void CMainWindow::OnNotify(NMHDR *nmhr)
{	

	//tabs and visible
	n_tab = tab->GetSelected(nmhr);

	if(n_tab==0) //object
	{
		baddObject->SetVisible(true); // "add object" button
		bdeleteObject->SetVisible(true); // "delete object" button
		bLoadClouds->SetVisible(true); // "load clouds" button
		bMoveToCamera->SetVisible(true); // "move to camera" button
		lObjectList->SetVisible(true); // object list
		gObject->SetVisible(true); // object group box
		gObjectControl->SetVisible(true); // object control group box
		gControl->SetVisible(true); //control group box
		bMoveObject->SetVisible(true); // "move object" button
		bRotateObject->SetVisible(true); // "rotate object" button
		bScaleObject->SetVisible(true); // "scale object" button
		bModifyX->SetVisible(true); // "modify x axis" push button
		bModifyY->SetVisible(true); // "modify y axis" push button
		bModifyZ->SetVisible(true); // "modify z axis" push button
		bModifyCamera->SetVisible(true);//"camera control" push button
		bModifyObject->SetVisible(true);//"object control" push button

	
		//editor
		bSaveMap->SetVisible(false); //"Save map" button
		bLoadMap->SetVisible(false); //"load map" button
		gGridAxis->SetVisible(false); // "grid draw" group box
		cDrawXAxis->SetVisible(false); //"draw x axis" checkbox
		cDrawYAxis->SetVisible(false);//"draw y axis" checkbox
		cDrawZAxis->SetVisible(false);//"draw z axis" checkbox
		gViewMode->SetVisible(false); // "view mode " groupbox
		rPerspectiveView->SetVisible(false); //"Perspective view" radiobutton
		rTopView->SetVisible(false); // "top view" radiobuttn
		rFreeLook->SetVisible(false);//"free look camera"radiobutton
		gDrawMode->SetVisible(false); // draw mode group box
		rSolidDrawMode->SetVisible(false); //solid draw mode radiobutton
		rWireDrawMode->SetVisible(false); //wire draw mode radiobutton
		m_propertyObject->Visable(false);

	

	}
	if(n_tab==1) //lights
	{
		//object
		baddObject->SetVisible(false); // "add object" button
		bLoadMap->SetVisible(false); //"load map" button
		bLoadClouds->SetVisible(false); // "add sky" button
		bdeleteObject->SetVisible(false); // "delete object" button
		bMoveToCamera->SetVisible(false); // "move to camera" button

		lObjectList->SetVisible(true); // object list
		m_propertyObject->Visable(true);

		gObject->SetVisible(false); // object group box
		gObjectControl->SetVisible(false); // object control group box
		gControl->SetVisible(false); //control group box
		bMoveObject->SetVisible(false); // "move object" button
		bRotateObject->SetVisible(false); // "rotate object" button
		bScaleObject->SetVisible(false); // "scale object" button
		bModifyX->SetVisible(false); // "modify x axis" push button
		bModifyY->SetVisible(false); // "modify y axis" push button
		bModifyZ->SetVisible(false); // "modify z axis" push button
		
		
		//editor
		bSaveMap->SetVisible(false); //"Save map" button
		gGridAxis->SetVisible(false); // "grid draw" group box
		cDrawXAxis->SetVisible(false); //"draw x axis" checkbox
		cDrawYAxis->SetVisible(false);//"draw y axis" checkbox
		cDrawZAxis->SetVisible(false);//"draw z axis" checkbox
		gViewMode->SetVisible(false); // "view mode " groupbox
		rPerspectiveView->SetVisible(false); //"Perspective view" radiobutton
		rTopView->SetVisible(false); // "top view" radiobuttn
		rFreeLook->SetVisible(false);//"free look camera"radiobutton
		gDrawMode->SetVisible(false); // draw mode group box
		rSolidDrawMode->SetVisible(false); //solid draw mode radiobutton
		rWireDrawMode->SetVisible(false); //wire draw mode radiobutton
		bModifyCamera->SetVisible(false);//"camera control" push button
		bModifyObject->SetVisible(false);//"object control" push button
	
		

	}
	if(n_tab==2) // editor
	{
		bSaveMap->SetVisible(true); //"Save map" button
		bLoadMap->SetVisible(true); //"load map" button
		gGridAxis->SetVisible(true); // "grid draw" group box
		cDrawXAxis->SetVisible(true); //"draw x axis" checkbox
		cDrawYAxis->SetVisible(true);//"draw y axis" checkbox
		cDrawZAxis->SetVisible(true);//"draw z axis" checkbox
		gViewMode->SetVisible(true); // "view mode " groupbox
		rPerspectiveView->SetVisible(true); //"Perspective view" radiobutton
		rTopView->SetVisible(true); // "top view" radiobuttn
		rFreeLook->SetVisible(true);//"free look camera"radiobutton
		gDrawMode->SetVisible(true); // draw mode group box
		rSolidDrawMode->SetVisible(true); //solid draw mode radiobutton
		rWireDrawMode->SetVisible(true); //wire draw mode radiobutton

		

		//object
		baddObject->SetVisible(false); // "add object" button
		bdeleteObject->SetVisible(false); // "delete object" button
		bLoadClouds->SetVisible(false); // "add sky" button
		bMoveToCamera->SetVisible(false); // "move to camera" button
		lObjectList->SetVisible(false); // object list
		gObject->SetVisible(false); // object group box
		gObjectControl->SetVisible(false); // object control group box
		gControl->SetVisible(false); //control group box
		bMoveObject->SetVisible(false); // "move object" button
		bRotateObject->SetVisible(false); // "rotate object" button
		bScaleObject->SetVisible(false); // "scale object" button
		bModifyX->SetVisible(false); // "modify x axis" push button
		bModifyY->SetVisible(false); // "modify y axis" push button
		bModifyZ->SetVisible(false); // "modify z axis" push button
		bModifyCamera->SetVisible(false);//"camera control" push button
		bModifyObject->SetVisible(false);//"object control" push button
		m_propertyObject->Visable(false);

		
			
	}


}
// ---------------------------------------------------------
// CWindow::OnPress()
// Keyboard
// ---------------------------------------------------------
//
void CMainWindow::onMouseMove()
{
	SetFocus(renderPerspective->hWnd); //set focus do opengl window
}
void CMainWindow::OnMouseClick()
{
	
	
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
	
	

	renderPerspective->DrawOpengl();
	

}
// ---------------------------------------------------------
// CWindow::OnKill()
// Kill window
// ---------------------------------------------------------
//
void CMainWindow::OnKill()
{
	
	//destroy opengl window render
	renderPerspective->DestroyOpenglWindow();

	delete renderPerspective;
	delete openDialog;
delete saveDialog;
delete OaddSky;

delete tab; // main tab pages

delete gObject; // "object" group box
delete gObjectControl; // "Object control" group box
delete gGridAxis; // "Grid axis" group box
delete gViewMode; //"View Mode" group box
delete gDrawMode; //"Draw Mode" group box
delete gControl; //"Control" group box

delete baddObject; // "add object" button
delete bdeleteObject; // "delete object" button
delete bSaveMap; // "Save map" button
delete bLoadMap; // "Load map" button
delete bLoadClouds; //"Load Clouds" button
delete bMoveToCamera; //"Move to camera" button


//------------
delete bMoveObject; //"move" button in object tag
delete bRotateObject; //"rotate" button in object tag
delete bScaleObject; //"scale" button in object tag
delete bModifyX; //"modify X" button in object tag
delete bModifyY; //"modify Y" button in object tag
delete bModifyZ; //"modify Z" button in object tag
delete bModifyCamera; // "Camera control" push button in object tag
delete bModifyObject; // "Camera control" push button in object tag

delete cDrawXAxis; //"draw x axis" checkbox
delete cDrawYAxis; //"draw y axis" checkbox
delete cDrawZAxis; //"draw z axis" checkbox
delete rPerspectiveView; //"perspective  view" radiobutton
delete rTopView; //"top view" radiobutton
delete rFreeLook; //"free look camera" radiobutton
delete rSolidDrawMode; //"perspective  view" radiobutton
delete rWireDrawMode; //"top view" radiobutton


delete lObjectList; //"objects" list


delete m_propertyObject;

}