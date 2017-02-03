#include "CPropertyObject.h"

// ---------------------------------------------------------
// CPropertyObject::CPropertyObject()
// constructor
// ---------------------------------------------------------
//
CPropertyObject::CPropertyObject()
{	
	m_box = new CGroupBox();

	m_cCollidable =    new CComboBox();
	m_cCollisionType = new CComboBox();

	m_eCollidable =    new CEdit();
	m_eCollisionType = new CEdit();


}
// ---------------------------------------------------------
// CPropertyObject::CPropertyObject()
// constructor
// ---------------------------------------------------------
//
void CPropertyObject::Draw()
{
	m_box->SetParentHwnd(pHwnd);
	m_box->SetPosition(770,420);
	m_box->SetSize(190,90);
	m_box->Draw(_T(""));


	//EDIT's
	//collidable
	m_eCollidable->SetParentHwnd(pHwnd);
	m_eCollidable->SetPosition(780,442);
	m_eCollidable->SetSize(70,20);
	m_eCollidable->Draw(_T("Collidable"));
	//collision type
	m_eCollisionType = new CEdit();
	m_eCollisionType->SetParentHwnd(pHwnd);
	m_eCollisionType->SetPosition(780,467);
	m_eCollisionType->SetSize(100,20);
	m_eCollisionType->Draw(_T("Collision type"));

	//COMBO BOX's
	//collidable
	m_cCollidable = new CComboBox();
	m_cCollidable->SetParentHwnd(pHwnd);
	m_cCollidable->SetPosition(880,440);
	m_cCollidable->SetSize(70,100);
	m_cCollidable->Draw();
	m_cCollidable->AddItem(_T("False"));
	m_cCollidable->AddItem(_T("True"));
	m_cCollidable->SetSelected(0);
	//collision type
	m_cCollisionType = new CComboBox();
	m_cCollisionType->SetParentHwnd(pHwnd);
	m_cCollisionType->SetPosition(880,465);
	m_cCollisionType->SetSize(70,100);
	m_cCollisionType->Draw();
	m_cCollisionType->AddItem(_T("BBOX"));
	m_cCollisionType->AddItem(_T("Per Face"));
	m_cCollisionType->SetSelected(0);


}
// ---------------------------------------------------------
// CPropertyObject::CPropertyObject()
// constructor
// ---------------------------------------------------------
//
bool CPropertyObject::getCollidable()
{
	if(m_cCollidable->getSelected() == 0)
	{
	
		return FALSE;
	}
	else
	{
			
		return TRUE;
	}

}
// ---------------------------------------------------------
// CPropertyObject::CPropertyObject()
// constructor
// ---------------------------------------------------------
//
int CPropertyObject::getCollisionType()
{
	return m_cCollisionType->getSelected();
	
}
// ---------------------------------------------------------
// CPropertyObject::CPropertyObject()
// constructor
// ---------------------------------------------------------
//
void CPropertyObject::Visable(bool stage)
{
	if(stage)
	{
		m_box->SetVisible(true);
		m_eCollidable->SetVisible(true);
		m_eCollisionType->SetVisible(true);
		m_cCollidable->SetVisible(true);
		m_cCollisionType->SetVisible(true);
	}
	else
	{
		m_box->SetVisible(false);
		m_eCollidable->SetVisible(false);
		m_eCollisionType->SetVisible(false);
		m_cCollidable->SetVisible(false);
		m_cCollisionType->SetVisible(false);
	}


}
// ---------------------------------------------------------
// CPropertyObject::SetCollisable(bool stage)
// constructor
// ---------------------------------------------------------
//
void CPropertyObject::SetCollidable(bool stage)
{
	if(stage)
	{
		m_cCollidable->SetSelected(1);
	}
	else
	{
		m_cCollidable->SetSelected(0);
	}
}
// ---------------------------------------------------------
// CPropertyObject::SetCollisionType(int ID)
// constructor
// ---------------------------------------------------------
//
void CPropertyObject::SetCollisionType(int ID)
{
	m_cCollisionType->SetSelected(ID);
}
// ---------------------------------------------------------
// CPropertyObject::CPropertyObject()
// constructor
// ---------------------------------------------------------
//

// ---------------------------------------------------------
// CPropertyObject::CPropertyObject()
// constructor
// ---------------------------------------------------------
//

// ---------------------------------------------------------
// CPropertyObject::CPropertyObject()
// constructor
// ---------------------------------------------------------
//
// ---------------------------------------------------------
// CPropertyObject::CPropertyObject()
// deconstructor
// ---------------------------------------------------------
//
CPropertyObject::~CPropertyObject()
{
	delete m_box;

	delete m_cCollidable;
	delete m_cCollisionType;

	delete m_eCollidable;
	delete m_eCollisionType;


}