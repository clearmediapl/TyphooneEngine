#include "bibloteki.h"


class CCamera
{
public:
	TPoint3f Position;
	TPoint3f Rotate;
	
public:
	CCamera();

	void SetPerspective();
	void SetTop();
	
	
	void SetRotation(float x, float y, float z);
	void SetPosition(float x, float y, float z);

	void Render();

};