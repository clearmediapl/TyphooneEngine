#ifndef _CCAMERA_H_
#define _CCAMERA_H_

#include "bibloteki.h"
#include "CMatrix.h"


class CCamera
{
public:
	TPoint3f Position;
	TPoint3f Rotate;
	
public:
	CCamera();
	~CCamera();
	CMatrix *m;

	void SetPerspective();
	void SetTop();
	
	
	void SetRotation(float x, float y, float z);
	void SetPosition(float x, float y, float z);

	CCamera operator= (CCamera &camera);

	CMatrix *getMatrix();

	void Render();

};

#endif