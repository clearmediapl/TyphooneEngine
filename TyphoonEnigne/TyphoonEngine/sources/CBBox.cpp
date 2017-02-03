#include "CBBox.h"

// ---------------------------------------------------------
// CBBox::CBBox()
// constructor
// ---------------------------------------------------------
//
CBBox::CBBox()
{
	m_max.m_x = -1000;
	m_max.m_y = -1000;
	m_max.m_z = -1000;

	m_min.m_x = 1000;
	m_min.m_y = 1000;
	m_min.m_z = 1000;

}
// ---------------------------------------------------------
// CBBox::MIN(tVector *v, int n)
// calc min value of bbox
// v - table of vertex 
// n - number of element in table
// ---------------------------------------------------------
//
void CBBox::MIN(tVector *v, int n)
{
	for(int i = 0; i < n; i++)
		{
			if(m_min.m_x > v[i].x)
			{
				m_min.m_x = v[i].x;
			}	
			if(m_min.m_y > v[i].y)
			{
				m_min.m_y = v[i].y;
			}
			if(m_min.m_z > v[i].z)
			{
				m_min.m_z = v[i].z;
			}
		}
}
// ---------------------------------------------------------
// CBBox::MAX(tVector *v, int n)
// calc max value of bbox
// v - table of vertex 
// n - number of element in table
// ---------------------------------------------------------
//
void CBBox::MAX(tVector *v, int n)
{
		for(int i = 0; i < n; i++)
		{
			if(m_max.m_x < v[i].x)
			{
				m_max.m_x = v[i].x;
			}
			if(m_max.m_y < v[i].y)
			{
				m_max.m_y = v[i].y;
			}
			if(m_max.m_z < v[i].z)
			{
				m_max.m_z = v[i].z;
			}
		}
}
// ---------------------------------------------------------
// CBBox::calcBBOX()
// calc size of bbox
// ---------------------------------------------------------
//
void CBBox::CalcBBOX()
{
	m_size = m_max - m_min ;
}