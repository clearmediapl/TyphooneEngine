#include "CPlayer.h"
#include "CCamera.h"

// ---------------------------------------------------------
// CPlayer::CPlayer()
// constructor
// ---------------------------------------------------------
//

CPlayer::CPlayer()
{

	gravity = -1;

	m_camera = new CCamera();

	m_pos.m_x = 0;
	m_pos.m_y = 0;
	m_pos.m_z = 0;
	m_vec = CVector(0,0,0);

	m_vx = 0;
	m_vz = 0;
	m_yRot = 0; 
	m_mouseRot = 0;

	
	
}	
// ---------------------------------------------------------
// CPlayer::SetPosition(CVector pos)
// 
// ---------------------------------------------------------
//
void CPlayer::SetPosition(CVector pos)
{
	m_pos.m_x = pos.m_x;
	m_pos.m_y = pos.m_y;
	m_pos.m_z = pos.m_z;

}
// ---------------------------------------------------------
// CPlayer::SetMouseRot(float rot)
// 
// ---------------------------------------------------------
//
void CPlayer::SetMouseRot(float rot)
{
	m_yRot += rot * 0.2;;
}
// ---------------------------------------------------------
// CPlayer::SetPhysicWorld(NewtonWorld *newton)
// 
// ---------------------------------------------------------
//
void CPlayer::SetPhysicWorld(NewtonWorld *newton)
{
	m_physicWorld = newton;
}
// ---------------------------------------------------------
// CPlayer::SetPhysicWorld(NewtonWorld *newton)
// 
// ---------------------------------------------------------
//
void CPlayer::SetStage(CPlayer::Stage stage)
{

	m_stage = stage;

}

// ---------------------------------------------------------
// CPlayer::getCamera()
// 
// ---------------------------------------------------------
//
CCamera *CPlayer::getCamera()
{
	return m_camera;
}

// ---------------------------------------------------------
// PhysicsApplyForceAndTorque
// 
// ---------------------------------------------------------
//
float forc, forcZ;
void PhysicsApplyForceAndTorque (const NewtonBody* body)
{
	float mass;
	float Ixx;
	float Iyy;
	float Izz;

	NewtonBodyGetMassMatrix (body, &mass, &Ixx, &Iyy, &Izz);
	float  force[4] = {forc ,-15, forcZ};
	NewtonBodySetForce (body, force);

	
}
// ---------------------------------------------------------
// CPlayer::Init()
// 
// ---------------------------------------------------------
//

void CPlayer::Init()
{
	NewtonCollision* collision;

	
	collision = NewtonCreateSphere(m_physicWorld, 2.0f, 2.0f, 2.0f, NULL); 
	//create collision object

	m_physicBody = NewtonCreateBody(m_physicWorld, collision);
	//create body for physic

	NewtonReleaseCollision(m_physicWorld, collision);
	//releases collision

	NewtonBodySetMassMatrix (m_physicBody, 10, 10, 10, 10); 
	// mass and intereia
		
	CMatrix matrix;
	matrix.Reset();
	matrix.Translate(m_pos);
	NewtonBodySetMatrix (m_physicBody, matrix.matrix); //set matrix

	NewtonBodySetLinearDamping (m_physicBody, 0.6f);


	NewtonBodySetForceAndTorqueCallback(m_physicBody, PhysicsApplyForceAndTorque);
	
	//set up vector
	float up[3] = { 0 ,1 ,0 };
	NewtonConstraintCreateUpVector(m_physicWorld, up, m_physicBody);
	
	NewtonBodySetAutoFreeze(m_physicBody, 0);


	m_camera->SetPosition(m_pos.m_x, m_pos.m_y -15, m_pos.m_z-40 );
	m_camera->SetRotation(15,0,0);
	
}
// ---------------------------------------------------------
// CPlayer::Render()
// 
// ---------------------------------------------------------
//
void CPlayer::Render()
{
	glLoadIdentity();
	NewtonBodyGetMatrix(m_physicBody, m_matrix.matrix);

	m_camera->Render();
	//glTranslatef(m_pos.m_x, -9, m_pos.m_z);

	m_matrix.Rotate(m_yRot,0,1,0);
	glMultMatrixf(m_matrix.matrix);
	glRotatef(90,0,1,0);

		
	glColor3ub(255,0,0);
	auxSolidTeapot(2);
	glColor3ub(255,255,255);


}
// ---------------------------------------------------------
// CPlayer::Update()
// 
// ---------------------------------------------------------
//
void CPlayer::Update()
{


	m_camera->Position.x = - m_matrix.matrix[12];
	m_camera->Position.y = - m_matrix.matrix[13] - 10;
	m_camera->Position.z = - m_matrix.matrix[14] - 30;
	
	forcZ = 0;
	forc = 0;
	
	


	
	switch(m_stage)
	{
		case MOVE_UP:
		{
			MoveForward();
			break;
			
		}
		case MOVE_DOWN:
		{
			MoveDown();
			break;
		}
	}
	


}
// ---------------------------------------------------------
// CPlayer::
// 
// ---------------------------------------------------------
//
float vv[3] = {0,0,5};
float ss[3] = {0,0,10};
float ss2[3] = {0,0,0};


void CPlayer::MoveForward()
{

	//	m_vx = -sin(DEGTORAD(m_yRot))*cos(DEGTORAD(0));
	//	m_vz = cos(DEGTORAD(m_yRot))*cos(DEGTORAD(0));
	
/*
		m_pos.m_x += m_vx*0.3;
		m_pos.m_z -= m_vz*0.3;

		m_camera->Position.x = - m_pos.m_x;
		m_camera->Position.z = - m_pos.m_z - 20;
*/
	
	
	
		forc  = -sin(DEGTORAD(m_yRot))*cos(DEGTORAD(0))*100;
		forcZ = -cos(DEGTORAD(m_yRot))*cos(DEGTORAD(0))*100 ;
	
}

// ---------------------------------------------------------
// CPlayer::
// 
// ---------------------------------------------------------
//
void CPlayer::MoveDown()
{
	forc  = -sin(DEGTORAD(m_yRot))*cos(DEGTORAD(0))*100;
	forcZ = cos(DEGTORAD(m_yRot))*cos(DEGTORAD(0))*100 ;
}
// ---------------------------------------------------------
// CPlayer::
// 
// ---------------------------------------------------------
//
void CPlayer::MoveLeft()
{
	forc = -12;

}
// ---------------------------------------------------------
// CPlayer::
// 
// ---------------------------------------------------------
//
void CPlayer::MoveRight()
{
	forc = 12;

}
// ---------------------------------------------------------
// CPlayer::
// 
// ---------------------------------------------------------
//

// ---------------------------------------------------------
// CPlayer::
// 
// ---------------------------------------------------------
//
CPlayer::~CPlayer()
{
	delete m_camera;
	delete m_physicBody;
	delete m_physicWorld;

}
// ---------------------------------------------------------
// CPlayer::
// 
// ---------------------------------------------------------
//