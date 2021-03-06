#include "CPlayer.h"
#include "CCamera.h"

// ---------------------------------------------------------
// CPlayer::CPlayer()
// constructor
// ---------------------------------------------------------
//

CPlayer::CPlayer()
{

	m_icon = new CLwo("data/player.lwo");
	m_icon->defaultPath = true;


	m_pos.m_x = 0;
	m_pos.m_y = 0; 
	m_pos.m_z = 0; 
}	
// ---------------------------------------------------------
// CPlayer::SetPosition(CVector pos)
// 
// ---------------------------------------------------------
//
void CPlayer::SetPosition(CVector pos)
{
	m_pos.m_x = pos.m_x;
	m_pos.m_y = pos.m_y;
	m_pos.m_z = pos.m_z;

}
// ---------------------------------------------------------
// CPlayer::Init()
// 
// ---------------------------------------------------------
//
void CPlayer::Init()
{
	m_icon->Init();
	m_icon->SetDrawMode(GL_TRIANGLES);
	
}
// ---------------------------------------------------------
// CPlayer::Render()
// 
// ---------------------------------------------------------
//
void CPlayer::Render()
{
	glPushMatrix();
	glTranslatef(m_pos.m_x, m_pos.m_y, m_pos.m_z);
	m_icon->Render();
	glPopMatrix();
}
CPlayer::~CPlayer()
{
	delete m_icon;
}