#include "CCamera.h"
// ---------------------------------------------------------
// CCamera::CCamera()
// constructor
// ---------------------------------------------------------
//
CCamera::CCamera()
{
	m = new CMatrix();

	Position.x = 0;
	Position.x = 0;
	Position.x = 0;

	Rotate.x = 0;
	Rotate.y = 0;
	Rotate.z = 0;
}
// ---------------------------------------------------------
// CCamera::SetRotation(float x, float y, float z)
// 
// ---------------------------------------------------------
//
void CCamera::SetRotation(float x, float y, float z)
{
	Rotate.x = x;
	Rotate.y = y;
	Rotate.z = z;
}
//---------------------------------------------------------
// CCamera::SetPosition(float x, float y, float z)
// 
// ---------------------------------------------------------
//
void CCamera::SetPosition(float x, float y, float z)
{
	Position.x = x;
	Position.y = y;
	Position.z = z;
}
// ---------------------------------------------------------
// CCamera::SetPerspective()
// 
// ---------------------------------------------------------
//
void CCamera::SetPerspective()
{
	SetPosition(0,0,-30);
	SetRotation(0,0,0);
}
// ---------------------------------------------------------
// CCamera::SetTop()
// 
// ---------------------------------------------------------
//
void CCamera::SetTop()
{
	SetPosition(0,-50,1);
	SetRotation(90,0,0);
}
// ---------------------------------------------------------
// CCamera::getMatrix()
// 
// ---------------------------------------------------------
//
CMatrix *CCamera::getMatrix()
{
	
	glGetFloatv(GL_MODELVIEW_MATRIX, &m->matrix[16]);
		 
	return m;
}
//---------------------------------------------------------
// CCamera::operator=(CCamera &camera)
// 
// ---------------------------------------------------------
//
CCamera CCamera::operator= (CCamera &camera)
{
	Position.x = camera.Position.x;
	Position.y = camera.Position.y;
	Position.z = camera.Position.z;

	Rotate.x = camera.Rotate.x;
	Rotate.y = camera.Rotate.y;
	Rotate.z = camera.Rotate.z;

	return *this;
}
// ---------------------------------------------------------
// CCamera::Render()
// 
// ---------------------------------------------------------
//
void CCamera::Render()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)800/(GLfloat)600,1,100.0f);

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(Rotate.x, 1,0,0);
	glRotatef(Rotate.y, 0,1,0);
	glRotatef(Rotate.z, 0,0,1);
	glTranslatef(Position.x, Position.y, Position.z);

	
}
// ---------------------------------------------------------
// CCamera::~CCamera()
// constructor
// ---------------------------------------------------------
//
CCamera::~CCamera()
{
	delete m;
}