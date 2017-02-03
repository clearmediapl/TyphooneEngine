#include "Libraries.h"

#include "CObject.h"
#include "engine/CCamera.h"
#include "engine/CClouds.h"
#include "engine/CPlayer.h"
//#include "engine/CUtility.h"

#define MAX_OBJ 50

class CUtility;

class CIOEditor
{
public:
	CUtility *m_utils;

	/////////////////////
	char *cPath; //temp path to object
	TCHAR *m_skyPath; // temp path to sky
	/////////////////////
	FILE *saveMap;
	FILE *loadMap;

public:
	CCamera *m_camera; // camera 
	CClouds *m_sky;    //sky
	CObject *m_obj[MAX_OBJ]; //information for objects
	CPlayer *m_player;


		

	int nObj; //number of objects

	bool sky;  //we have actualy sky in scene?
	bool player; //we have actualy player in scene?


public:
	CIOEditor();
	~CIOEditor();

	void WriteObject(CObject *obj);
	void WriteSky();
	void WritePlayer();
	void ReadObject(CObject *obj);
	void ReadSky();
	void ReadPlayer();
	void SaveMap(TCHAR *path);
	void LoadMap(TCHAR *path);

};