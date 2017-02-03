/*******************************************************************/
/* Filename:                  CParticleSystem.h                    */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         17.10.2004                           */
/* Last revision:             17.10.2004                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/

#include "bibloteki.h"

#include "CParticleSystem.h"
#include "CTexture.h"

CTexture part_tex;



// ---------------------------------------------------------
// CParticleSystem::CParticleSystem()
// constructor
// ---------------------------------------------------------
//
CParticleSystem::CParticleSystem() : CExtension()
{
	MAX_PARTICLE = 500;
	m_IsPoint_sprite=true;
	m_fire=false;
	m_flow=false;
	m_expl=true;

	m_IsActive=true;

	m_speed=0.0001;

	m_part = new CParticle[MAX_PARTICLE];

	m_reset = false;
}
// ---------------------------------------------------------
// CParticleSystem::SetPosition(CVector pos)
// Set position of system
// ---------------------------------------------------------
//
void CParticleSystem::SetPosition(CVector pos)
{
	m_pos.m_x = pos.m_x;
	m_pos.m_y = pos.m_y;
	m_pos.m_z = pos.m_z;
}
// ---------------------------------------------------------
// CParticleSystem::SetGravity(CVector grav)
// Set gravity of system
// ---------------------------------------------------------
//
void CParticleSystem::SetGravity(CVector grav)
{
	m_grav.m_x = grav.m_x;
	m_grav.m_y = grav.m_y;
	m_grav.m_z = grav.m_z;
}
// ---------------------------------------------------------
// CParticleSystem::SetDirection(CVector direct)
// Set direction of system
// ---------------------------------------------------------
//
void CParticleSystem::SetDirection(CVector direct)
{
	m_direction.m_x = direct.m_x;
	m_direction.m_y = direct.m_y;
	m_direction.m_z = direct.m_z;
}
// ---------------------------------------------------------
// CParticleSystem::Init()
// Init particle system
// ---------------------------------------------------------
//
void CParticleSystem::Init()
{

	slowdown=10;



	//Setup the fire particles
	if(m_flow)
	{
		srand(time(NULL));
		for(i=0;i<MAX_PARTICLE;i++)
		{
			
			
			
			m_part[i].life=1;
			m_part[i].fade=float(rand()%100)/1000.0f+0.00f;

			m_part[i].grav.m_x=(rand()%((int)(m_grav.m_x+1))-m_grav2.m_x+1)*0.1f + 0.01;
			m_part[i].grav.m_y=(rand()%((int)(m_grav.m_y+1))-m_grav2.m_y+1)*0.1f + 0.01;
		    m_part[i].grav.m_z=(rand()%((int)(m_grav.m_z+1))-m_grav2.m_z+1)*0.1f + 0.01;
		
			m_part[i].direction.m_x=(rand()%((int)m_direction.m_x+1)-m_direction2.m_x+1);
			m_part[i].direction.m_y=(rand()%((int)m_direction.m_y+1)-m_direction2.m_y+1);
			m_part[i].direction.m_z=(rand()%((int)m_direction.m_z+1)-m_direction2.m_z+1);






			m_part[i].n_tex=0;
			m_part[i].size=10;
			m_part[i].alpha=1;
	
		}
	}
	
		if(m_expl)
		{
			
			for(i=0;i<MAX_PARTICLE;i++)
			{
				
				m_part[i].life=1;
				m_part[i].fade=float(rand()%10)/100.0f+0.01;

				m_part[i].direction.m_x=float((rand()%50)-16.0f)*m_grav.m_x;
				m_part[i].direction.m_y=float((rand()%50)-16.0f)*m_grav.m_y;
				m_part[i].direction.m_z=float((rand()%50)-15.0f)*m_grav.m_z;


				m_part[i].grav.m_x=0;
				m_part[i].grav.m_y=-0.8f;
				m_part[i].grav.m_z=0;
				
			}
		}



	//Setup the point sprites


    glTexEnvf( GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE );
	glPointSize(50);
	glHint(GL_POINT_SMOOTH_HINT,GL_FASTEST);
   


	
	
	part_tex.defaultPath = true;
	if(!part_tex.LoadJPG(_T("part.jpg"),texture[0]))
	{
	}


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE); 

}

int k,l;
// ---------------------------------------------------------
// CParticleSystem::Render_fire()
// 
// ---------------------------------------------------------
//
void CParticleSystem::Render_fire(bool flow)
{
	

	

	
	
	
	for(i=0;i<MAX_PARTICLE;i++)
	{

		float x=m_part[i].pos.m_x;
		float y=m_part[i].pos.m_y;
		float z=m_part[i].pos.m_z-44;




		


		glLoadIdentity();
		glTranslatef(x,y,z);
		

	/*

		render point sprite

	*/


 
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	
    glEnable( GL_POINT_SPRITE_ARB );
	glBegin( GL_POINTS );
    {
           
	        glVertex3f( m_part[i].pos.m_x,
				        m_part[i].pos.m_y,
						m_part[i].pos.m_z );
        
    }
	glEnd();
	glDisable( GL_POINT_SPRITE_ARB );

	/*


	*/

	if(timeGetTime() - m_part[i].time >= 5)
	{

		

		m_part[i].pos.m_x += m_part[i].direction.m_x/(m_speed);
		m_part[i].pos.m_y += m_part[i].direction.m_y/(m_speed);
		m_part[i].pos.m_z += m_part[i].direction.m_z/(m_speed);

		m_part[i].direction.m_x += m_part[i].grav.m_x;
		m_part[i].direction.m_y += m_part[i].grav.m_y;
		m_part[i].direction.m_z += m_part[i].grav.m_z;
			
		m_part[i].life -= m_part[i].fade;


		m_part[i].time=timeGetTime();
	}

		if(m_part[i].life<0 )
		{
				m_part[i].size=20;
                m_part[i].life=1.0f;
				m_part[i].fade=float(rand()%50)/100.0f+0.003f;

				x=0;
				y=0;
				z=0;
			

		

				m_part[i].pos.m_x=0;					
				m_part[i].pos.m_y=0;						
				m_part[i].pos.m_z=0.0f;	

				m_part[i].direction.m_x=(rand()%((int)m_direction.m_x)-m_direction2.m_x);
				m_part[i].direction.m_y=(rand()%((int)m_direction.m_y)-m_direction2.m_y);
				m_part[i].direction.m_z=(rand()%((int)m_direction.m_z)-m_direction2.m_z);


	

		}





	}
}

// ---------------------------------------------------------
// CParticleSystem::Render_expl()
// Render explosion
// ---------------------------------------------------------
//
void CParticleSystem::Render_expl()
{


	glBindTexture(GL_TEXTURE_2D, texture[0]);
	
	for(i=0;i<MAX_PARTICLE;i++)
	{

		float x=m_part[i].pos.m_x;
		float y=m_part[i].pos.m_y+0.2;
		float z=m_part[i].pos.m_z-10;

	

	glLoadIdentity();
	glTranslatef(x,y,z);
	

	/*

		render point sprite

	*/


 
    glEnable( GL_POINT_SPRITE_ARB );
	glBegin( GL_POINTS );
    {
           
	        glVertex3f( m_part[i].pos.m_x, 
				        m_part[i].pos.m_y,
						m_part[i].pos.m_z );
        
    }
	glEnd();
	glDisable( GL_POINT_SPRITE_ARB );

	/*


	*/


			
		if(timeGetTime() - m_part[i].time >= 2)
		{

			m_part[i].pos.m_x += m_part[i].direction.m_x*(m_speed);
			m_part[i].pos.m_y += m_part[i].direction.m_y*(m_speed);
			m_part[i].pos.m_z += m_part[i].direction.m_z*(m_speed);

			m_part[i].direction.m_x += m_part[i].grav.m_x;
			m_part[i].direction.m_y += m_part[i].grav.m_y;
			m_part[i].direction.m_z += m_part[i].grav.m_z;

			m_part[i].life -= m_part[i].fade;


				if(m_part[i].life<0 )
				{
					m_part[i].life=0.0f;
					m_part[i].pos.m_x=0;
					m_part[i].pos.m_y=-100;
					m_part[i].pos.m_z=0;
				}
			m_part[i].time = timeGetTime();
		}
	}

		





}
// ---------------------------------------------------------
// CParticleSystem::Render()
// Render efect
// ---------------------------------------------------------
//
void CParticleSystem::Render()
{
	
	if(!m_reset)
	{
		if(m_fire)Render_fire(true);
		if(m_expl)Render_expl();
	}	
}
// ---------------------------------------------------------
// CParticleSystem::reset()
// reset system
// ---------------------------------------------------------
//
void CParticleSystem::reset()
{
		m_reset = true;
		if(m_expl)
		{
			srand(time(NULL));
			
			for(i=0;i<MAX_PARTICLE;i++)
			{
				m_part[i].pos.m_x=0;
				m_part[i].pos.m_y=0;
				m_part[i].pos.m_z=0;
					
				m_part[i].life=1;
				m_part[i].fade=float(rand()%10)/100.0f+0.01;

				m_part[i].direction.m_x=float((rand()%50)-16.0f)*4.0f;
				m_part[i].direction.m_y=float((rand()%50)-16.0f)*4.0f;
				m_part[i].direction.m_z=float((rand()%50)-15.0f)*3.0f;

				m_part[i].grav.m_x=0;
				m_part[i].grav.m_y=-0.8f;
				m_part[i].grav.m_z=0;
			}
		}

	m_reset = false;
	
}
// ---------------------------------------------------------
// CParticleSystem::~CParticleSystem()
// destructor 
// ---------------------------------------------------------
//
CParticleSystem::~CParticleSystem()
{
	delete [] m_part;
}


