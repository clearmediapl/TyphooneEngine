/*******************************************************************/
/* Filename:                  CPlayer.h                           */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         09.08.2006                           */
/* Last revision:             27.07.2006                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/

#include <newton/newton.h>
#include "bibloteki.h"
#include "CVector.h"
#include "CMatrix.h"

class CCamera;

class CPlayer
{

private:
	
	
	NewtonWorld *m_physicWorld;
	NewtonBody *m_physicBody;

	CCamera *m_camera;
	CMatrix m_matrix;
	
	float gravity;

public:

	enum Stage
	{
		NONE    = 0,
		MOVE_UP    = 1,
		MOVE_DOWN  = 2,
		MOVE_LEFT  = 3,
		MOVE_RIGHT = 4
	};
	Stage m_stage;


	CVector m_pos; //position of player
	CVector m_vec; //vielocity of player

	float   m_vx, m_vz;
	float   m_yRot; //y rot of player
	float   m_mouseRot;



public:
	CPlayer();
	~CPlayer();

	void SetPhysicWorld(NewtonWorld *newton);
	void SetPosition(CVector pos);
	void SetMouseRot(float rot); //rotation of mouse
	void SetStage(Stage stage);	
	
	CCamera *getCamera();


	void InitPhysic();
	void Init();
	void Render();
	void Update();

	///////////////////

	void MoveForward();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

};
