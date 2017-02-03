#include "Libraries.h"

#include "engine/CLwo.h"
#include "engine/C3ds.h"

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

	TPoint3f Position; //position of obj
	TPoint3f Rotation; //rotation of obj
	TPoint3f Scale;    //scale of obj

	CLwo *m_lwoMesh;
	C3ds *m_3dsMesh;
	TCHAR path[128];
	//------------





	//------------
	// to collision
	collision m_collisionType;
	int      m_collidable;
	//------------

public:

	CObject();
	~CObject();

	void SetID(type value);
	int getID();

};