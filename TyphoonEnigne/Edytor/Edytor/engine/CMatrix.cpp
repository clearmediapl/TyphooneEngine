#include "CMatrix.h"

#define DEGTORAD(x) x * (3.1415 / 180)

CMatrix::CMatrix()
{
	Reset();

}
CMatrix::CMatrix(CVector r1, CVector r2, CVector r3, CVector r4)
{
	matrix[0] = r1.m_x;
	matrix[1] = r1.m_y;
	matrix[2] = r1.m_z;
	matrix[3] = r1.m_w;

	matrix[4] = r2.m_x;
	matrix[5] = r2.m_y;
	matrix[6] = r2.m_z;
	matrix[7] = r2.m_w;

	matrix[8]  = r3.m_x;
	matrix[9]  = r3.m_y;
	matrix[10] = r3.m_z;
	matrix[11] = r3.m_w;

	matrix[12] = r4.m_x;
	matrix[13] = r4.m_y;
	matrix[14] = r4.m_z;
	matrix[15] = r4.m_w;
	
	

}
CMatrix CMatrix::operator= (CMatrix &m)
{
	matrix[0] = m.matrix[0];
	matrix[1] = m.matrix[1];
	matrix[2] = m.matrix[2];
	matrix[3] = m.matrix[3];

	matrix[4] = m.matrix[4];
	matrix[5] = m.matrix[5];
	matrix[6] = m.matrix[6];
	matrix[7] = m.matrix[7];

	matrix[8]  = m.matrix[8];
	matrix[9]  = m.matrix[9];
	matrix[10] = m.matrix[10];
	matrix[11] = m.matrix[11];

	matrix[12] = m.matrix[12];
	matrix[13] = m.matrix[13];
	matrix[14] = m.matrix[14];
	matrix[15] = m.matrix[15];
	return *this;
}
void CMatrix::Reset()
{
	matrix[0]  = 1; matrix[1]  = 0; matrix[2]  = 0; matrix[3]  = 0;
	matrix[4]  = 0; matrix[5]  = 1; matrix[6]  = 0; matrix[7]  = 0;
	matrix[8]  = 0; matrix[9]  = 0; matrix[10] = 1; matrix[11] = 0;
	matrix[12] = 0; matrix[13] = 0; matrix[14] = 0; matrix[15] = 1;
}
void CMatrix::Translate(CVector v)
{
   matrix[12] = v.m_x;
   matrix[13] = v.m_y;
   matrix[14] = v.m_z;
   matrix[15] = 1.0f;
}
void CMatrix::Translate(float x, float y, float z)
{
   matrix[12] = x;
   matrix[13] = y;
   matrix[14] = z;
   matrix[15] = 1.0f;
}
void CMatrix::Rotate(float angle, float x, float y, float z)
{
   float sine = (float)sin(DEGTORAD(angle));
   float cosine = (float)cos(DEGTORAD(angle));

   if(x)
      {
	      matrix[5] = cosine;
	      matrix[6] = sine;
	      matrix[9] = -sine;
	      matrix[10] = cosine;
      }

   if(y)
      {
	      matrix[0] = cosine;
	      matrix[2] = -sine;
	      matrix[8] = sine;
	      matrix[10] = cosine;
      }

   if(z)
      {
	      matrix[0] = cosine;
	      matrix[1] = sine;
	      matrix[4] = -sine;
	      matrix[5] = cosine;
      }
}
