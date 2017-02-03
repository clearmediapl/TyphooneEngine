#ifndef _CVECTOR_H_
#define _CVECTOR_H_

#include "bibloteki.h"

class CVector
{
private:


	float lenght;

public:
	float m_x; //x
	float m_y; //y
	float m_z; //z
	float m_w; //w

public:
	//constructors
	CVector();
	CVector(float x, float y);
	CVector(float x, float y, float z);
	CVector(float x, float y, float z, float w);

	CVector operator+ (CVector &v2); // addition 2 vectors
	CVector operator- (CVector &v2); // subtraction 2 vector
	CVector operator[] (CVector &v2); // array of vectors

	CVector CrossProduct(CVector a, CVector b); //cross product of 2 vectors
	CVector Normalize(CVector v); //normalize vector
	float getLenght(CVector v); //lenght of vector


};
#endif