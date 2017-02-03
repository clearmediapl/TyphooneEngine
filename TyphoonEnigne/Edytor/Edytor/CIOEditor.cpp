//created at 30 august 2006 by bojkar

#include "CIOEditor.h"
// ---------------------------------------------------------
// CIOEditor::CIOEditor()
// constructor
// ---------------------------------------------------------
//
CIOEditor::CIOEditor()
{

	nObj = 0;
	
	sky = false;
	player = false;
}
// ---------------------------------------------------------
// CIOEditor::WriteObject(CObject *obj)
// Write Object to file
// ---------------------------------------------------------
//
void CIOEditor::WriteObject(CObject *obj)
{
	fwprintf(saveMap, _T("Object \n"));
	fwprintf(saveMap, _T("{ \n"));
	fwprintf(saveMap, _T("	%d %d \n"), obj->m_collidable, obj->m_collisionType);
	fwprintf(saveMap, _T("	%s \n"), obj->path);
	fwprintf(saveMap, _T("	%f %f %f \n"), obj->Position.x, obj->Position.y, obj->Position.z);
	fwprintf(saveMap, _T("	%f %f %f \n"), obj->Rotation.x, obj->Rotation.y, obj->Rotation.z);
	fwprintf(saveMap, _T("	%f %f %f \n"), obj->Scale.x, obj->Scale.y, obj->Scale.z);
	fwprintf(saveMap, _T("} \n"));

}
// ---------------------------------------------------------
// CIOEditor::ReadObject(CObject *obj)
// Read object from file
// ---------------------------------------------------------
//
void CIOEditor::ReadObject(CObject *obj)
{
	TCHAR path[128];
	TCHAR tempPath[128];

	fwscanf(loadMap, _T("Object \n"));
	fwscanf(loadMap, _T("{ \n"));
	fwscanf(loadMap, _T("%d %d \n"), &obj->m_collidable, &obj->m_collisionType);
	fwscanf(loadMap, _T("%s \n"), path);
	fwscanf(loadMap, _T("%f %f %f \n"), &obj->Position.x, &obj->Position.y, &obj->Position.z);
	fwscanf(loadMap, _T("%f %f %f \n"), &obj->Rotation.x, &obj->Rotation.y, &obj->Rotation.z);
	fwscanf(loadMap, _T("%f %f %f \n"), &obj->Scale.x, &obj->Scale.y, &obj->Scale.z);
	fwscanf(loadMap, _T("} \n"));

	
	wcscpy_s(obj->path, path);

	
	MessageBox(NULL,path,TEXT("b"),0);

	
	wcsncpy(tempPath,path+wcslen(path)-3,4);
	
	char *cPath = new char[255];
	cPath = m_utils->UnicodeToAnsi(path);


	

	TCHAR path2[128];

	if(!wcscmp(tempPath,_T("3ds")) || !wcscmp(tempPath,_T("3DS")) ) //3ds
	{
		obj->m_3dsMesh = new C3ds(obj->path);
	}
	else
		if(!wcscmp(tempPath,_T("lwo")) || !wcscmp(tempPath,_T("LWO"))) //3ds //lwo
		{
			obj->m_lwoMesh = new CLwo(cPath); // load the mesh
		}
		else
		{

		}
		

	glEnable(GL_TEXTURE_2D);
	obj->ID = CObject::ID_MESH;
	obj->init = true;
	obj->draw = true;
	obj->live = true;
	

	//delete cPath;

}
// ---------------------------------------------------------
// CIOEditor::WriteSky()
// Write sky object to file
// ---------------------------------------------------------
//
void CIOEditor::WriteSky()
{
	fwprintf(saveMap, _T("Sky \n"));
	fwprintf(saveMap, _T("{ \n"));
	fwprintf(saveMap, _T("\t %s \n"), m_skyPath);
	fwprintf(saveMap, _T("} \n"));
}
// ---------------------------------------------------------
// CIOEditor::ReadSky()
// Read sky object from file
// ---------------------------------------------------------
//
void CIOEditor::ReadSky()
{
	fwscanf(saveMap, _T("Sky \n"));
	fwscanf(saveMap, _T("{ \n"));
//	fwscanf(saveMap, _T("%s \n"), sky_path_object);
	fwscanf(saveMap, _T("} \n"));
}
// ---------------------------------------------------------
// CIOEditor::WriteSky()
// Write sky object to file
// ---------------------------------------------------------
//
void CIOEditor::WritePlayer()
{
	fwprintf(saveMap, _T("Player \n"));
	fwprintf(saveMap, _T("{ \n"));
	fwprintf(saveMap, _T("\t %f %f %f \n"), m_player->m_pos.m_x, m_player->m_pos.m_y, m_player->m_pos.m_z);
//	fwscanf(saveMap, _T("%s \n"), player_path_object);
	fwprintf(saveMap, _T("} \n"));

}
// ---------------------------------------------------------
// CIOEditor::ReadPlayer()
// Write sky object to file
// ---------------------------------------------------------
//
void CIOEditor::ReadPlayer()
{
	fwscanf(loadMap, _T("Player \n"));
	fwscanf(loadMap, _T("{ \n"));
	fwscanf(loadMap, _T("\t %f %f %f \n"), &m_player->m_pos.m_x, &m_player->m_pos.m_y, &m_player->m_pos.m_z);
//	fwscanf(saveMap, _T("%s \n"), player_path_object);
	fwscanf(loadMap, _T("} \n"));


}
// ---------------------------------------------------------
// CIOEditor::LoadMap(TCHAR *path)
// Load map from file
// ---------------------------------------------------------
//
void CIOEditor::LoadMap(TCHAR *path)
{
	loadMap = _wfopen(path, TEXT("rt"));
	if(loadMap==NULL)
	{
		MessageBox(NULL,TEXT("fuck!"),TEXT("b"),0);
	}


	//header
	fwscanf(loadMap, _T("Map file \n"));
	fwscanf(loadMap, _T(" \n"));	

	//scene info
	fwscanf(loadMap, _T("Scene info \n"));
	fwscanf(loadMap, _T("{ \n"));
	fwscanf(loadMap, _T("Objects %d \n"),&nObj);
	fwscanf(loadMap, _T("Sky %d \n"),&sky);
	fwscanf(loadMap, _T("Player %d \n"),&player);
	fwscanf(loadMap, _T("} \n"));
	fwscanf(loadMap, _T("\n"));
	

	//objects info
	for(int i=0;i<nObj;i++)
	{	
		ReadObject(m_obj[i]);
	}
	fclose(loadMap);


}
// ---------------------------------------------------------
// CIOEditor::SaveMap(TCHAR *path)
// Save map to file
// ---------------------------------------------------------
//
void CIOEditor::SaveMap(TCHAR *path)
{
	int countObj = 0;
	//count live object
	for(int i = 0;i<nObj;i++)
	{
		if(m_obj[i]->live)
		{
			countObj++;
		}
	}

	saveMap = _wfopen(path, TEXT("w"));


	if(saveMap==NULL)
	{
		MessageBox(NULL,TEXT("fuck!"),TEXT("b"),0);
	}

	//header
	fwprintf(saveMap, _T("Map file \n"));
	fwprintf(saveMap, _T("\n"));

	//scene info
	fwprintf(saveMap, _T("Scene info \n"));
	fwprintf(saveMap, _T("{ \n"));
	fwprintf(saveMap, _T("\t Objects %d \n"), countObj);
	fwprintf(saveMap, _T("\t Sky %d \n"), sky);
	fwprintf(saveMap, _T("\t Player %d \n"), player);
	fwprintf(saveMap, _T("} \n"));
	fwprintf(saveMap, _T("\n"));

	//sky info
	if(sky)
	{
		WriteSky();
	}
	//player_info
	if(player)
	{
		WritePlayer();
	}
	//objects info
	for(int i=0;i<nObj;i++)
	{	
		if(m_obj[i]->live && m_obj[i]->ID == CObject::ID_MESH)
		{
			WriteObject(m_obj[i]);
		}
	}

	
	fclose(saveMap);




}
// ---------------------------------------------------------
// CIOEditor::~CIOEditor()
// deconstructor
// ---------------------------------------------------------
//
CIOEditor::~CIOEditor()
{


}