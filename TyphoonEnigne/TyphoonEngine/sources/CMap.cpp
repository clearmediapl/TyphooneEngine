#include "CMap.h"
#include "CCamera.h"
#include "CLogger.h"
#include "CClouds.h"


// ---------------------------------------------------------
// CMap::CMap()
// constructor
// ---------------------------------------------------------
//
CLogger *test;
CClouds *m_clouds;

CMap::CMap() : CPhysic()
{
	m_utils = new CUtility(); // utils funcions
	
	m_clouds = new CClouds(); //create clouds object
	m_player = new CPlayer(); //create player object
	m_camera2 = new CCamera(); //create camera object

	for(int i=0;i<MAX_OBJ;i++)
	{
		m_obj[i] = new CObject(); //create objects
	}

	

	test   = new CLogger();
	test->Create(_T("physicTest"));
	test->NewSection(_T("physisc"));

}
// ---------------------------------------------------------
// CMap::ReadObject(CObject *obj)
// Read object
// ---------------------------------------------------------
//
void CMap::ReadObject(CObject *obj)
{
	TCHAR path[64];

	fwscanf(loadMap, _T("Object \n"));
	fwscanf(loadMap, _T("{ \n"));
	fwscanf(loadMap, _T("%d %d \n"), &obj->m_collidable, &obj->m_collisionType);
	fwscanf(loadMap, _T("%s \n"), path);
	fwscanf(loadMap, _T("%f %f %f \n"), &obj->Position.m_x, &obj->Position.m_y, &obj->Position.m_z);
	fwscanf(loadMap, _T("%f %f %f \n"), &obj->Rotation.m_x, &obj->Rotation.m_y, &obj->Rotation.m_z);
	fwscanf(loadMap, _T("%f %f %f \n"), &obj->Scale.m_x, &obj->Scale.m_y, &obj->Scale.m_z);
	fwscanf(loadMap, _T("} \n"));



	
	TCHAR tempPath[128];
	wcsncpy(tempPath,path+wcslen(path)-3,4);
	MessageBox(NULL, path,_T("Editor error"), MB_OK );

	
	char *cPath;
	cPath = m_utils->UnicodeToAnsi(path); // convert path from unicode to ansi

	if((wcscmp(tempPath,_T("3ds"))==0)) //3ds
	{
		obj->m_3dsMesh = new C3ds(path);
		m_Is3ds = true;
	}
	else
		if(!wcscmp(tempPath,_T("lwo"))) //3ds //lwo
		{
			obj->m_lwoMesh = new CLwo(cPath); // load the mesh
		}
		else
		{
			MessageBox(NULL, _T("Can't read mesh"),_T("Editor error"), MB_OK );
		}

	
	obj->live = true;
	obj->draw = true;

}
// ---------------------------------------------------------
// CIOEditor::ReadPlayer()
// Write sky object to file
// ---------------------------------------------------------
//
void CMap::ReadPlayer()
{
	float x,y,z;
	fwscanf(loadMap, _T("Player \n"));
	fwscanf(loadMap, _T("{ \n"));
	fwscanf(loadMap, _T("%f %f %f \n"), &x, &y, &z);
//	fwscanf(saveMap, _T("%s \n"), player_path_object);
	fwscanf(loadMap, _T("} \n"));

	m_player->SetPosition(CVector(x,y,z));


}

// ---------------------------------------------------------
// CMap::Load(TCHAR *path)
// Load map
// ---------------------------------------------------------
//
void CMap::Load(TCHAR *path)
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
	fwscanf(loadMap, _T("Objects %d \n"), &nObj);
	fwscanf(loadMap, _T("Sky %d \n"), &m_IsSky);
	fwscanf(loadMap, _T("Player %d \n"), &m_IsPlayer);
	fwscanf(loadMap, _T("} \n"));
	fwscanf(loadMap, _T("\n"));
	

	//player info
	if(m_IsPlayer)
	{
		ReadPlayer();
	}
	//objects info
	for(int i=0;i<nObj;i++)
	{	
		ReadObject(m_obj[i]);
	}
	fclose(loadMap);




}


// ---------------------------------------------------------
// CMap::Init()
// Init  map
// ---------------------------------------------------------
//
void LevelCollisionCallback (
	const NewtonBody* bodyWithTreeCollision, 
	const NewtonBody* body,
	const dFloat* vertex, 
	int vertexstrideInBytes, 
	int indexCount, 
	const int* indexArray)
{
}
void CMap::Init()
{	
	
	
	SetWorldSize(500); // set physic World size
	

//	m_clouds->Init();
//	m_clouds->LoadClouds(_T("sky"));
	
	
	if(m_IsPlayer)//we hava player in map?
	{
		m_player->SetPhysicWorld(m_physicWorld); //set physic world
		m_player->Init(); //init player 
	}
	//init all objects in map
	for(int i=0;i<nObj;i++)
	{
		if(m_Is3ds) 
		{
			m_obj[i]->m_3dsMesh->Init(); // init MESH

			//scale bbox
			m_obj[i]->m_3dsMesh->m_bbox->m_size.m_x *= m_obj[i]->Scale.m_x;
			m_obj[i]->m_3dsMesh->m_bbox->m_size.m_y *= m_obj[i]->Scale.m_y;
			m_obj[i]->m_3dsMesh->m_bbox->m_size.m_z *= m_obj[i]->Scale.m_z;


		}
		if(m_IsLwo)
		{
			m_obj[i]->m_lwoMesh->Init(); 
			m_obj[i]->m_lwoMesh->SetDrawMode(GL_TRIANGLES); //draw in triangles

			//scale bbox
			m_obj[i]->m_lwoMesh->m_size.m_x *= m_obj[i]->Scale.m_x;
			m_obj[i]->m_lwoMesh->m_size.m_y *= m_obj[i]->Scale.m_y;
			m_obj[i]->m_lwoMesh->m_size.m_z *= m_obj[i]->Scale.m_z;
			
		}

		
		switch(m_obj[i]->m_collisionType)//init collision by type
		{
			case CObject::ID_PERFACE : //per triangles collision [1]
			{
				if(m_IsLwo)m_obj[i]->m_lwoMesh->CreateCollisionTree(m_physicWorld, LevelCollisionCallback , m_obj[i]->Position);
				break;
			}
			case CObject::ID_BBOX : //bbox collision [0]
			{
				if(m_IsLwo)m_obj[i]->m_lwoMesh->CreateCollisionBBOX(m_physicWorld, m_obj[i]->Position, m_obj[i]->Rotation);
				if(m_Is3ds)m_obj[i]->m_3dsMesh->ApplyBBoxCollision(m_physicWorld, m_obj[i]->Position, m_obj[i]->Rotation);
				break;
			}
		}
		
	}
	

	glEnable(GL_TEXTURE_2D);
	
}

// ---------------------------------------------------------
// CMap::Render()
// Render the map
// ---------------------------------------------------------
//
void CMap::Render()
{
		m_camera2 = m_player->getCamera(); //get camera of player
	//	m_clouds->SetCamera(m_camera2); //set to clouds main camera

	//	m_clouds->Render(); //render clouds


		//glColor4f(0.7, 0.7, 0.7, 0.7);
		
		glLoadIdentity();

		for(int i=0;i<nObj;i++)//draw all obiects
		{
			
			if(m_obj[i]->draw==true && m_obj[i]->live==true)//is object live?
			{
				
				m_camera2->Render(); //set camera
				

				//setup and draw
				glTranslatef(m_obj[i]->Position.m_x, m_obj[i]->Position.m_y, m_obj[i]->Position.m_z);
				glRotatef(m_obj[i]->Rotation.m_x,0,1,0);
				glRotatef(m_obj[i]->Rotation.m_y,1,0,0);
				glScalef(m_obj[i]->Scale.m_x, m_obj[i]->Scale.m_y, m_obj[i]->Scale.m_z);
				if(m_Is3ds) m_obj[i]->m_3dsMesh->Render();
				if(m_IsLwo) m_obj[i]->m_lwoMesh->Render();
				glLoadIdentity();
							
			}
			
		}
	
		m_player->Render(); // render player

	
		
}
// ---------------------------------------------------------
// CMap::Update()
// Update the map
// ---------------------------------------------------------
//
void CMap::Update()
{
	NewtonUpdate(m_physicWorld, 0.9); //update physic
	m_player->Update(); //update player
//	m_clouds->Update(); //update clouds

}
// ---------------------------------------------------------
// CMap::~CMap()
// destructor
// ---------------------------------------------------------
//
CMap::~CMap()
{
	delete [] m_obj; //delete all objects
	delete m_player; //delete player object
}