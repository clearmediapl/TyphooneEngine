#include "CVector.h"

// ---------------------------------------------------------
// CVector::CVector()
// constructor
// ---------------------------------------------------------
//
CVector::CVector()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_w = 0;

	value[0] = 0;
	value[1] = 0;
	value[2] = 0;
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

	value[0] = m_x;
	value[1] = m_y;
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

	value[0] = x;
	value[1] = y;
	value[2] = z;

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

	value[0] = x;
	value[1] = y;
	value[2] = z;
	value[3] = w;

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
// CVector::getLenght()
// get lenght of vector
// ---------------------------------------------------------
//
float CVector::getLenght()
{
	lenght = sqrt(m_x*m_x + m_y*m_y + m_z*m_z );

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
// CVector::Normalize()
// Normalize the vector
// ---------------------------------------------------------
//
CVector CVector::Normalize()
{
	float lenght = getLenght();

	return CVector( (m_x / lenght),
					(m_y / lenght),
					(m_z / lenght));
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
					(v.m_z / lenght));
}
