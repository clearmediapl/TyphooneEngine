#ifndef _CMATRIX_H_
#define _CMATRIX_H_

#include "bibloteki.h"
#include "CVector.h"

class CMatrix
{
private:
	
public:
	float matrix[16];

	CMatrix();
	CMatrix(CVector r1,
		    CVector r2,
			CVector r3,
			CVector r4);

	CMatrix operator= (CMatrix &matrix);

	void Reset();
	void Translate(CVector v);
	void Translate(float x, float y, float z);
	void Rotate(float angle, float x, float y, float z);




};

#endif