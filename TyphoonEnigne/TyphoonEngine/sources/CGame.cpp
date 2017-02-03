/*******************************************************************/
/* Filename:                  CGame.cpp                            */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         17.05.2006                           */
/* Last revision:             17.05.2006                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/


#include "bibloteki.h"
#include "CMap.h"
#include "CGame.h"
#include "CLogger.h"
#include "CVector.h"
#include "CWater.h"
#include "CCamera.h"
#include "CRenderToTexture.h"
#include "CClouds.h"
#include "CMatrix.h"

#include "C3ds.h"

unsigned int a[13];



#include "CParticleSystem.h"




C3ds *obj = new C3ds(_T("drzewo_1.3ds"));
CParticleSystem *part = new CParticleSystem();

// ---------------------------------------------------------
// CGame::CGame()
// constructor
// ---------------------------------------------------------
//
CGame::CGame() : CShadowMap()
{
	isClicked=false;
	rot = 0;
	log = new CLogger();
	tex = new CTexture();



//	map = new CMap();



}
// ---------------------------------------------------------
// CGame::Init()
// Init game
// ---------------------------------------------------------
//


CLogger *log3;


float rot;
	float s=-2.5;
void quad(float x, float y, float z)
{


	glScalef(x,y,z);
	
	glBegin(GL_QUADS);
	
		
	
		
		glTexCoord2f(1.0, 0.0f); glNormal3f(-1.0f, -1.0f,  -1.0f);glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glNormal3f(-1.0f, 1.0f,  -1.0f);glVertex3f(1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glNormal3f(1.0f, 1.0f,  -1.0f);glVertex3f( 1.0f,  -1.0f,1.0f);
		glTexCoord2f(0.0f, 0.0f); glNormal3f(1.0f, -1.0f,  1.0f);glVertex3f( -1.0f, -1.0f, 1.0f);
		
	glEnd();
}

void CGame::Init()
{
	
	log3 = new CLogger();

	log->Create(_T("main.htm"));
	log->NewSection(_T("Textures"));
	log->LogSucces(_T("test"));
	log->LogError(_T("test"));



	//map->Load(_T("3"));
	//map->Init();

	
	glEnable(GL_TEXTURE_2D);
	tex->defaultPath = true;
	if(!tex->LoadJPG(_T("terrain.jpg"),a[0]))
	{}


	//InitShadows();
	


		//part->SetParticleNumber(2000);
	//	part->SetGravity(CVector(4, 4, 3));
	//	part->Init();
	
		obj->Init();

}
// ---------------------------------------------------------
// CGame::Draw()
// Main loop
// ---------------------------------------------------------
//

void CGame::Draw()
{	

glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


	glBindTexture(GL_TEXTURE_2D, a[0]);
	glLoadIdentity();
	glTranslatef(0,0,-100);
	glScalef(0.2,0.2,0.2);
	glRotatef(45,-1,0,0);

	
	obj->Render();

	


		


}
// ---------------------------------------------------------
// CGame::Update(double frameTime)
// update
// ---------------------------------------------------------
//


void CGame::Update(double frameTime)
{

	
	if((timeGetTime() - time) >= 5)
	{
		if(keys['R']==true)
		{
			part->reset();
		}
		
	

		rot++;
		if(rot>360)
		{
			rot=0;
		}
	/*	
		map->m_player->SetStage(CPlayer::NONE);
	
		if(isClicked==true)
		{
			map->m_player->SetMouseRot(MouseX);
		}
		
		
		if(keys['W']==true)
		{
			map->m_player->SetStage(CPlayer::MOVE_UP);
		
		}
		if(keys['S']==true)
		{
			map->m_player->SetStage(CPlayer::MOVE_DOWN);
			
		}	
		if(keys['A']==true)
		{
			map->m_player->SetStage(CPlayer::MOVE_LEFT);
			
		}	
		if(keys['D']==true)
		{
			map->m_player->SetStage(CPlayer::MOVE_RIGHT);
		}	
	
		
		map->Update();

	*/

		
	
		time = timeGetTime();
	}
	

}
// ---------------------------------------------------------
// CGame::Kill()
// kill the game
// ---------------------------------------------------------
//
void CGame::Kill()
{
//	delete player;
//	delete cam;
//	delete lwo;
//	delete map;
//	delete tex;
	log->Finish(); delete log;
	delete log3;
	
}
CGame::~CGame()
{
	delete part;
}