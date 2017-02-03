#include "bibloteki.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CPhysic.h"

#define MAX_OBJ 50

class CCamera;
class CUtility;

class CMap : public CPhysic
{
private:
	FILE *loadMap;

	CUtility *m_utils;

	//map info
	CObject *m_obj[MAX_OBJ];
	CCamera *m_camera2;

	int nObj;
	

public:
	CPlayer *m_player;

	bool m_IsSky;
	bool m_IsPlayer;
	bool m_Is3ds;
	bool m_IsLwo;

public:
	CMap();
	~CMap();

	void ReadObject(CObject *obj);
	void ReadPlayer();
	void Load(TCHAR *path);
	void Init();
	void Render();
	void Update();

};
