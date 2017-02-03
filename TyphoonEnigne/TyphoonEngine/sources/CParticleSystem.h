/*******************************************************************/
/* Filename:                  CParticleSystem.h                    */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         17.10.2004                           */
/* Last revision:             17.10.2004                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/

#include "CVector.h"
#include "CExtension.h"



struct CParticle
{
	CVector pos; //position 
	CVector grav; //gravity
	CVector direction; // direction
	


	int size;

	float life, fade;
	float alpha;
	int n_tex;
	DWORD time;
	


	
};



class CParticleSystem : public CExtension
{
private:
	CParticle *m_part;


	//data for file
	FILE *particle_file;

	CVector m_pos;
	CVector m_direction;
	CVector m_direction2;
	CVector m_grav;
	CVector m_grav2;

	TCHAR tex1[40];  //path for first texture
  	float m_speed;

	bool m_fire;
	bool m_expl;
	bool m_flow;

	int MAX_PARTICLE;

	

	float slowdown;

	int i;
		
	bool m_IsPoint_sprite;
	bool m_IsActive;
	bool m_reset;

	
	GLuint texture[1];

	DWORD start_time;
	DWORD actual_time;

public:

	CParticleSystem();
	~CParticleSystem();

	


	void Render_fire(bool flow); //render fire
	void Render_expl(); //render explosion
	void Render_flow(); //render flow

	void Render();
	void Init();

	void SetGravity(CVector grav);
	void SetPosition(CVector pos);
	void SetDirection(CVector direct);
//	void SetParticleNumber(int number);



	void reset();

};

