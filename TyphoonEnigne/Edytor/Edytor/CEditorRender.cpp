#include "CEditorRender.h"

#define DEGTORAD(x) x* (3.1415 / 180)
// ---------------------------------------------------------
// CEditorRender::Init()
// Init editor render
// ---------------------------------------------------------
//
void CEditorRender::Init()
{
	

	m_camera = new CCamera();
	m_camera->SetPosition(0,0,-30);
	m_camera->SetRotation(0,0,0);


	m_sky = new CClouds();
	m_sky->Init();
	m_sky->SetCamera(m_camera);

	m_player = new CPlayer();

	nObj = 0;

	
	for(int i=0;i<MAX_OBJ;i++)
	{
		m_obj[i] = new CObject();
	}
	
}
// ---------------------------------------------------------
// CEditorRender::SetMousePos(float xPos, float yPos)
// get mouse position
// ---------------------------------------------------------
//
void CEditorRender::SetMousePos(float xPos, float yPos)
{
	MousePosX = xPos*0.3;
	MousePosY = yPos*0.3;
}
void CEditorRender::MoveToCamera()
{
	CVector cam_vec;

//	cam_vec.m_x = m_obj[actualyObj]->Position.x = - m_camera->Position.x;
	//cam_vec.m_y = m_obj[actualyObj]->Position.y = - m_camera->Position.y;
	//cam_vec.m_z = m_obj[actualyObj]->Position.z = - m_camera->Position.z - 30;

	//m_player->SetPosition(cam_vec);

	
}
// ---------------------------------------------------------
// CEditorRender::AddMesh(TCHAR *path)
// Add new mesh to scene
// ---------------------------------------------------------
//

void CEditorRender::AddMesh(TCHAR *path)
{
	wcscpy(m_obj[nObj]->path, path); // copy path to object structure

	//extension of mesh
	TCHAR tempPath[128];
	wcsncpy(tempPath,m_obj[nObj]->path+wcslen(m_obj[nObj]->path)-3,4);

	
	MessageBox(NULL, m_obj[nObj]->path, _T(""),MB_OK);

	
	char *cPath = new char[255];
	cPath = m_utils->UnicodeToAnsi(m_obj[nObj]->path);

	if((wcscmp(tempPath,_T("3ds"))==0) || (wcscmp(tempPath,_T("3DS"))==0)) //3ds
	{
		m_obj[nObj]->m_3dsMesh = new C3ds(m_obj[nObj]->path);
	}
	else
		if(!wcscmp(tempPath,_T("lwo"))) //3ds //lwo
		{
			m_obj[nObj]->m_lwoMesh = new CLwo(cPath); // load the mesh
		}
		else
		{
			MessageBox(NULL, _T("Can't read mesh"),_T("Editor error"), MB_OK );
		}

	m_obj[nObj]->ID = CObject::ID_MESH;
	m_obj[nObj]->draw = true; //draw actualy object
	m_obj[nObj]->init = true; // init actualy object
	m_obj[nObj]->live = true; // set live for object

	nObj++; //add new number of objects
	m_obj[nObj]->index++;

//	delete cPath;
}
// ---------------------------------------------------------
// CEditorRender::AddSky(TCHAR *path)
// Add  sky to scene
// ---------------------------------------------------------
//
void CEditorRender::AddSky(TCHAR *path)
{
	m_skyPath = path;


	sky = true;
	m_sky->LoadClouds(path);

	m_obj[nObj]->ID = CObject::ID_SKY;
	m_obj[nObj]->draw = true; //draw actualy object
	m_obj[nObj]->live = true; // init actualy object
	

	nObj++; //add new number of objects
	m_obj[nObj]->index++;


}
// ---------------------------------------------------------
// CEditorRender::AddPlayer(TCHAR *path)
// Add  player to scene
// ---------------------------------------------------------
//
void CEditorRender::AddPlayer(TCHAR *path)
{
	
	m_player->Init();
	m_player->SetPosition(CVector(3,0,-10));

	player = true;

	m_obj[nObj]->ID = CObject::ID_PLAYER;
	m_obj[nObj]->draw = true; //draw actualy object
	m_obj[nObj]->live = true; // init actualy object

	nObj++; //add new number of objects
	m_obj[nObj]->index++;

}
// ---------------------------------------------------------
// CEditorRender::DeleteObject(int number)
// Delete object from map
// ---------------------------------------------------------
//
void CEditorRender::DeleteObject(int number)
{
	m_obj[number]->live = false;
	m_obj[number]->draw = false;
	switch(m_obj[number]->ID)
	{
		case CObject::ID_MESH:
		{
//			delete m_obj[number]->mesh;
			break;
		}
		case CObject::ID_SKY:
		{
			sky = false;
		//	delete sky;
			break;
		}
		case CObject::ID_PLAYER:
		{
			player = false;
			//delete m_player;
			m_player->SetPosition(CVector(0,0,0));
			break;
		}
	}
	
}
// ---------------------------------------------------------
// CEditorRender::DrawGrid(bool xAxis, bool yAxis, bool zAxis)
// draw axis grid
// ---------------------------------------------------------
//
void CEditorRender::DrawGrid(bool xAxis, bool yAxis, bool zAxis)
{
	
	glDisable(GL_TEXTURE_2D);
	glColor3ub(90, 130, 90);
	
if(xAxis)
{
	for(int i=-100;i<100;i++)
	{

		m_camera->Render();
	
		glPushMatrix();
	
		glTranslatef(i,0,0);
		glScalef(1,1,100);
		glBegin(GL_LINES);
			glVertex3f(-1,0,-1);
			glVertex3f(-1,0,1);
		glEnd();

		glPopMatrix();
	}
	for(float i=-100;i<100;i+=0.5)
	{
	
		m_camera->Render();
	
		glPushMatrix();
	
		glTranslatef(0,0,i);
		glScalef(100,1,1);
		glBegin(GL_LINES);
			glVertex3f(-1,0,-1);
			glVertex3f(1,0,-1);
		glEnd();

		glPopMatrix();
	
		
	}
	
}

	/*

		AXES Y
	*/
if(yAxis)
{
	for(float i=-100;i<100;i+=0.5)
	{
		
		m_camera->Render();
		glPushMatrix();
	
		glTranslatef(0,i,0);
		glScalef(100,1,1);
		glBegin(GL_LINES);
			glVertex3f(-1,0,-1);
			glVertex3f(1,0,-1);
		glEnd();
		glPopMatrix();
	}
	for(float i=-100;i<100;i+=0.5)
	{		
		m_camera->Render();
		glPushMatrix();

		glTranslatef(i,0,0);
		glScalef(1,100,1);
		glBegin(GL_LINES);
			glVertex3f(-1,1,-1);
			glVertex3f(-1,-1,-1);
		glEnd();
		glPopMatrix();
	}
}
	/*

		AXES Z
	*/
	
if(zAxis)
{
	for(float i=-100;i<100;i+=0.5)
	{
		m_camera->Render();
		glPushMatrix();
	
		glTranslatef(0,i,0);
		glScalef(1,1,100);
		glBegin(GL_LINES);
			glVertex3f(0,0,-1);
			glVertex3f(0,0,1);
		glEnd();
		glPopMatrix();
	}
	for(float i=-100;i<100;i+=0.5)
	{		
		m_camera->Render();
		glPushMatrix();
				  

		glTranslatef(0,0,i);
		glScalef(1,100,1);
		glBegin(GL_LINES);
			glVertex3f(0,-1,-1);
			glVertex3f(0,1,-1);
		glEnd();
		glPopMatrix();
	}

}

	glColor3ub(255,255,255);
	glEnable(GL_TEXTURE_2D);
	


}
// ---------------------------------------------------------
// CEditorRender::DrawObjects()
// Draw all objects in map
// ---------------------------------------------------------
//
void CEditorRender::DrawMesh(CObject *obj)
{
		m_camera->Render();

		
		glPushMatrix();
	
		//setup and draw
		glTranslatef(obj->Position.x, obj->Position.y, obj->Position.z);
		glRotatef(obj->Rotation.x,0,1,0);
		glRotatef(obj->Rotation.y,1,0,0);
		glScalef(obj->Scale.x, obj->Scale.y, obj->Scale.z);
		if(obj->m_lwoMesh) // lwo mesh
		{
			if(wireDraw)  obj->m_lwoMesh->SetDrawMode(GL_LINES) ;
			if(solidDraw) obj->m_lwoMesh->SetDrawMode(GL_TRIANGLES);
			              obj->m_lwoMesh->Render();
		}
		if(obj->m_3dsMesh) // lwo mesh
		{
		//	if(wireDraw)  obj->m_LWOmesh->SetDrawMode(GL_LINES) ;
		//	if(solidDraw) obj->m_LWOmesh->SetDrawMode(GL_TRIANGLES);
			              obj->m_3dsMesh->Render();
		}
		
	   

		glPopMatrix();

		

}
// ---------------------------------------------------------
// CEditorRender::DrawSky()
// DrawSky
// ---------------------------------------------------------
//
void CEditorRender::DrawSky()
{
	glPushMatrix();
		glEnable(GL_DEPTH_TEST);
		m_sky->Render();
		glDisable(GL_BLEND);
	glPopMatrix();

}
void CEditorRender::DrawObjects()
{


	if(solidDraw) // if we draw in solid mode....
	{
		glEnable(GL_TEXTURE_2D); /// enable texturing
	} else glDisable(GL_TEXTURE_2D); // but when other draw mode disable texturing

		for(int i=0;i<nObj;i++)//draw all obiects
		{
			if(m_obj[i]->init==true && m_obj[i]->live==true) //init?
			{
				if(m_obj[i]->ID == CObject::ID_MESH)
				{
					if(m_obj[i]->m_lwoMesh) m_obj[i]->m_lwoMesh->Init(); //init mesh 
					if(m_obj[i]->m_3dsMesh)
					{
						m_obj[i]->m_3dsMesh->Init(); //init mesh 
					}
					
				}
				m_obj[i]->init = false; //end of init
			}
			
			switch(m_obj[i]->ID)
			{
				case CObject::ID_MESH:
				{	//DRAW MESHES
					if(m_obj[i]->draw==true && m_obj[i]->live==true)//draw
					{
						DrawMesh(m_obj[i]);
					}
					break;
				}
				case CObject::ID_SKY:
				{
					if(m_obj[i]->draw==true && m_obj[i]->live==true)//draw
					{
					 	DrawSky();
					}
					break;
				}
				case CObject::ID_PLAYER:
				{
					if(m_obj[i]->draw==true && m_obj[i]->live==true && player)//draw
					{
						m_camera->Render();
						glPushMatrix();
						m_player->Render();
						glPopMatrix();
					}
					break;
				}
			}
			
		}

		

	//draw bbox
	if(actualyObj >= 0)
	{
		m_camera->Render();
		glPushMatrix();
		
		//setup and draw
		glTranslatef(m_obj[actualyObj]->Position.x, m_obj[actualyObj]->Position.y, m_obj[actualyObj]->Position.z);
		glRotatef(m_obj[actualyObj]->Rotation.x,0,1,0);
		glRotatef(m_obj[actualyObj]->Rotation.y,1,0,0);
		glScalef(m_obj[actualyObj]->Scale.x, m_obj[actualyObj]->Scale.y, m_obj[actualyObj]->Scale.z);
		
		if(m_obj[actualyObj]->m_lwoMesh) m_obj[actualyObj]->m_lwoMesh->DrawBBOX();
		if(m_obj[actualyObj]->m_3dsMesh) m_obj[actualyObj]->m_3dsMesh->DrawBBOX();

		glPopMatrix();
	}
	
}


// ---------------------------------------------------------
// CEditorRender::Update()
// update map
// ---------------------------------------------------------
//
float vx,vy,vz;
void CEditorRender::Update(bool move,    bool rotate,  bool scale,
						   bool xModify, bool yModify, bool zModify)
{
	if((timeGetTime() -time ) >= 5)
	{
		if(sky!=NULL)
		{
			m_sky->Update();
			m_sky->SetCamera(m_camera);
		}
	
		if(actualyObj>=0 && m_obj[actualyObj]->live==true &&!cameraMoving ) //if objects exist and isn't freelook
		{
			if(move) // we move obj?
			{
				if(xModify)	m_obj[actualyObj]->Position.x+= MousePosX;
				if(yModify)	m_obj[actualyObj]->Position.y+= -MousePosY;
				if(zModify)	m_obj[actualyObj]->Position.z+= MousePosY;
			}
			if(rotate) //we rotate objj?
			{
				if(xModify)m_obj[actualyObj]->Rotation.x+= MousePosX;
				if(yModify)m_obj[actualyObj]->Rotation.y+= MousePosY;
			    if(zModify)m_obj[actualyObj]->Rotation.z+= MousePosY;
			}
			if(scale)
			{
				if(xModify)m_obj[actualyObj]->Scale.x+= MousePosX;
				if(yModify)m_obj[actualyObj]->Scale.y+= MousePosX;
				if(zModify)m_obj[actualyObj]->Scale.z+= MousePosX;
			}
			if(m_obj[actualyObj]->getID() == CObject::ID_PLAYER)
			{
				m_player->SetPosition(CVector(m_obj[actualyObj]->Position.x,
			                                  m_obj[actualyObj]->Position.y,
										      m_obj[actualyObj]->Position.z));
			}
		}

		/*
			FREE LOOK CAMERA
		*/
	if(freeLook && cameraMoving)
	{
		m_camera->Rotate.y+= MousePosX;
		m_camera->Rotate.x+= MousePosY;

		if(keys['W'])
		{
			vx = -sin(DEGTORAD(m_camera->Rotate.y))*cos(DEGTORAD(m_camera->Rotate.x));
			vy = sin(DEGTORAD(m_camera->Rotate.x));
			vz = cos(DEGTORAD(m_camera->Rotate.y))*cos(DEGTORAD(m_camera->Rotate.x));
	

			m_camera->Position.x+=vx*0.5;
			m_camera->Position.y+=vy*0.5;
			m_camera->Position.z+=vz*0.5;
		}
		if(keys['S'])
		{
			vx = -sin(DEGTORAD(m_camera->Rotate.y))*cos(DEGTORAD(m_camera->Rotate.x));
			vy = sin(DEGTORAD(m_camera->Rotate.x));
			vz = cos(DEGTORAD(m_camera->Rotate.y))*cos(DEGTORAD(m_camera->Rotate.x));
	

			m_camera->Position.x-=vx*0.5;
			m_camera->Position.y-=vy*0.5;
			m_camera->Position.z-=vz*0.5;
		}	
		
	
	}


	
	

		time = timeGetTime();
	}
		
}




// ---------------------------------------------------------
// CEditorRender::Kill()
// Kill editor render
// ---------------------------------------------------------
//
void CEditorRender::Kill()
{
	delete [] m_obj;
	delete m_camera;
	delete m_sky;
}