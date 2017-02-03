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

	ID = ID_MESH;
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
	delete m_3dsMesh;
	delete m_lwoMesh;
}