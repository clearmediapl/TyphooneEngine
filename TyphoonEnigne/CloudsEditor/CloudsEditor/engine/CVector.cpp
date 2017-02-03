#include "CVector.h"

// ---------------------------------------------------------
// CVector::CVector()
// constructor
// ---------------------------------------------------------
//
CVector::CVector()
{

}
// ---------------------------------------------------------
// CVector::CVector(float x, float y)
// constructor
// ---------------------------------------------------------
//
CVector::CVector(float x, float y)
{
	m_x = x;
	m_y = y;

}
// ---------------------------------------------------------
// CVector::CVector(float x, float y, float z)
// constructor
// ---------------------------------------------------------
//
CVector::CVector(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;

}
// ---------------------------------------------------------
// CVector::CVector(float x, float y, float z, float w)
// constructor
// ---------------------------------------------------------
//
CVector::CVector(float x, float y, float z, float w)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;

}
// ---------------------------------------------------------
// CVector::operator +(CVector &v2)
// addition 2 vectors
// ---------------------------------------------------------
//
CVector CVector::operator +(CVector &v2)
{
	return CVector(m_x + v2.m_x, m_y + v2.m_y, m_z + v2.m_z, m_w);
}
// ---------------------------------------------------------
// CVector::operator -(CVector &v2)
// subtition 2 vectors
// ---------------------------------------------------------
//
CVector CVector::operator -(CVector &v2)
{
	return CVector(m_x - v2.m_x, m_y - v2.m_y, m_z - v2.m_z, m_w);
}
// ---------------------------------------------------------
// CVector::getLenght(CVector v)
// get lenght of vector
// ---------------------------------------------------------
//
float CVector::getLenght(CVector v)
{
	lenght = sqrt(v.m_x*v.m_x + v.m_y*v.m_y + v.m_z*v.m_z );

	return lenght;
}
// ---------------------------------------------------------
// CVector::CrossProduct(CVector a, CVector b)
// cross product of 2 vectors
// ---------------------------------------------------------
//
CVector CVector::CrossProduct(CVector a, CVector b)
{
	CVector final;
	final.m_x = (a.m_y * b.m_z)  -  (b.m_y * a.m_z);
	final.m_y = (b.m_x * a.m_z)  -  (a.m_x * b.m_z);
	final.m_z = (a.m_x * b.m_y)  -  (b.m_x * a.m_y);
 
	return final;
}
// ---------------------------------------------------------
// CVector::Normalize(CVector v)
// Normalize the vector
// ---------------------------------------------------------
//
CVector CVector::Normalize(CVector v)
{
	float lenght = getLenght(v);

	return CVector( (v.m_x / lenght),
					(v.m_y / lenght),
					(v.m_y / lenght));
}
