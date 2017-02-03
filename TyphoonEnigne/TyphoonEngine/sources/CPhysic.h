#include "bibloteki.h"
#include <newton/newton.h>


class CPhysic
{
protected:
	NewtonWorld *m_physicWorld;


public:
	CPhysic();
	~CPhysic();

	void SetWorldSize(int size);
	

};
