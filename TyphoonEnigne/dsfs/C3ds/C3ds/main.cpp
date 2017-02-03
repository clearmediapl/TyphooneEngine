#include <stdio.h>

#include "C3ds.h"
#include "CMatrix.h"

int main()
{
	CMatrix main;

	CMatrix m1(CVector(2,4,6,7),
			   CVector(3,6,5,5),
			   CVector(4,2,3,2),
			   CVector(5,1,2,6));

	CMatrix m2(CVector(1,2,3,4),
			   CVector(5,4,2,5),
			   CVector(2,5,6,3),
			   CVector(8,4,1,3));

	main = m1 * m2;


	printf("%f %f %f %f \n", main.matrix[0], main.matrix[1], main.matrix[2], main.matrix[3]);
	printf("%f %f %f %f \n", main.matrix[4], main.matrix[5], main.matrix[6], main.matrix[7]);
	printf("%f %f %f %f \n", main.matrix[8], main.matrix[9], main.matrix[10], main.matrix[11]);
	printf("%f %f %f %f \n", main.matrix[12], main.matrix[13], main.matrix[14], main.matrix[15]);



	return 0;
}