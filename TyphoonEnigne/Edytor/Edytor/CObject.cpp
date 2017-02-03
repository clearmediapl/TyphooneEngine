#include "CObject.h"

// ---------------------------------------------------------
// CObject::CObject()
// constructor
// ---------------------------------------------------------
//
CObject::CObject()
{
	draw = false;
	init = false;
	live = false;

	Scale.x = 1;
	Scale.y = 1;
	Scale.z = 1;

	m_lwoMesh = NULL;
	m_3dsMesh = NULL;

	ID = ID_MESH;
	m_collisionType = ID_BBOX;
	memset(path,0,sizeof(path));
}
// ---------------------------------------------------------
// CObject::getID()
// get ID of object
// ---------------------------------------------------------
//
int CObject::getID()
{
	return ID;
}
// CObject::SetId()
// set ID of object
// ---------------------------------------------------------
//
void CObject::SetID(type value)
{
	 ID = value;
}
// ---------------------------------------------------------
// CObject::~CObject()
// destructor
// ---------------------------------------------------------
//
CObject::~CObject()
{
	free(path);
	delete m_lwoMesh;
	delete m_3dsMesh;
}