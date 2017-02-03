#include "CPhysic.h"
#include "CVector.h"

// memory allocation for Newton
void* PhysicsAlloc(int sizeInBytes)
{
	return malloc (sizeInBytes);
}

// memory de-allocation for Newton
void PhysicsFree(void *ptr, int sizeInBytes)
{
	free (ptr);
}

CPhysic::CPhysic()
{
	m_physicWorld = NewtonCreate (PhysicsAlloc, PhysicsFree);
}
void CPhysic::SetWorldSize(int size)
{
	CVector boxP0; 
	CVector boxP1; 
			
	boxP0.m_x = -size * 0.5;
	boxP0.m_y = -size * 0.5;
	boxP0.m_z = -size * 0.5;

	boxP1.m_x = size * 0.5;
	boxP1.m_y = size * 0.5;
	boxP1.m_z = size * 0.5;

	NewtonSetWorldSize (m_physicWorld, &boxP0.m_x, &boxP1.m_x); 


}
CPhysic::~CPhysic()
{
	delete m_physicWorld;
}