#include "bibloteki.h"

#include "CLwo.h"
#include "C3ds.h"

class CObject
{
public:
	enum type
	{
		ID_MESH     = 0,
		ID_SKY      = 1,
		ID_PLAYER   = 2,
		
	};
	enum collision
	{
		ID_BBOX   = 0,
		ID_PERFACE = 1,
	};

	//----------
	// to draw
	int index;
	type ID;
	
	bool init;
	bool draw;
	bool live;

	CVector Position; //position of obj
	CVector Rotation; //rotation of obj
	CVector Scale;    //scale of obj

	CLwo *m_lwoMesh;
	C3ds *m_3dsMesh;
	TCHAR path[128];
	//------------



	//------------
	// to collision
	collision m_collisionType;
	bool      m_collidable;
	//------------

public:

	CObject();
	~CObject();

	void SetID(type value);
	int getID();

};