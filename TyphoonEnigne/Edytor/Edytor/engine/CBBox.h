#ifndef _CBBOX_H_
#define _CBBOX_H_


#include "bibloteki.h"
#include "CVector.h"

struct tVector
{
	float x,y,z;
};

class CBBox
{
private:
	CVector m_min, m_max;

public:
	CVector m_size;

public:

	CBBox();
	

	void MIN(tVector *v, int n);
	void MAX(tVector *v, int n);
	void CalcBBOX();

	
};

#endif