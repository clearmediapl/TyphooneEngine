/*******************************************************************/
/* Filename:                  CLwo                                 */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         20.05.2006                           */
/* Last revision:             16.06.2005                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/

#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <fstream>
#include "bibloteki.h"

#include "CLwo.h"

#include "bibloteki.h"
#include "CTexture.h"
#include "CLogger.h"
#include "CMatrix.h"






float CLwo::ChunkToFloat(char *input)
{
	union {
		float                      temp;
		unsigned char              byte_4[4];
	} swp;

	swp.byte_4[0] = input[3];
	swp.byte_4[1] = input[2];
	swp.byte_4[2] = input[1];
	swp.byte_4[3] = input[0];

	return swp.temp;
}
unsigned short CLwo::ChunkToShort(char *input)
{
	 union {
		 unsigned short             temp;
		 unsigned char              byte_2[2];
	 } swp;

	 swp.byte_2[0] = input[1];
     swp.byte_2[1] = input[0];

  return swp.temp;
}
unsigned char CLwo::ChunkToChar(char *input)
{
	 union {
		 unsigned char             temp;
		 unsigned char              byte_2[1];
	 } swp;

	 swp.byte_2[0] = input[1];
    

  return swp.temp;
}
unsigned int CLwo::ChunkToInt(char *input)
{
	
	union {
		unsigned int               temp;
		unsigned char              byte_4[4];
	} swp;

    swp.byte_4[0] = input[3];
    swp.byte_4[1] = input[2];
    swp.byte_4[2] = input[1];
    swp.byte_4[3] = input[0];

    return swp.temp;
}


CLwo::CLwo(char *name) : CExtension()
{
	VBOenable = false;
	multitex = false;
	m_size.m_x = 0;
	m_size.m_y = 0;
	m_size.m_z = 0;



	log = new CLogger();
	log->Append(_T("main.htm"));
	log->NewSection(_T("LWO testing"));

	
	obj=(LWO_object*)malloc(sizeof(LWO_object));

	file = open(name, O_BINARY); 
	if(file<0)
	{
		MessageBox(NULL,TEXT("Can't open the object"),TEXT("Error"),MB_OK |MB_ICONWARNING );
		log->LogError(_T("Lwo load"));
	}
	else
	{
		size = filelength(file); 
		dane = (char*)malloc(size);
		read(file,dane,size);

	

		tex = new CTexture();
		utils = new CUtility();

		Load(size,dane);
	}
}
void CLwo::Load(int size, char *dane)
{



	int i;

	/////////////////////////////////////////////////////////////
	////
	/// CHUNKS NAME: FORM
	///
	/////////////////////////////////////////////////////////////


	for(i=0;i<size;i++)       
	{
		 if(strnicmp("FORM",dane+i,4)==0)
		 {
			 break;
		 }
	}

	



	/////////////////////////////////////////////////////////////
	////
	/// CHUNKS NAME: PNTS
	///
	/////////////////////////////////////////////////////////////


	for(i=0;i<size;i++)       
	{
		 if(strnicmp("PNTS",dane+i,4)==0)
		 {
			 break;
		 }
	}
		
		i+=4;
		obj->n_pnts=ChunkToInt(dane+i)/12;
		obj->point=(LWO_vertex3f*)malloc(obj->n_pnts*sizeof(LWO_vertex3f));

		i+=4;

		for(int j=0;j<obj->n_pnts;j++)
		{
			
			obj->point[j].x=ChunkToFloat(dane+i);
			i+=4;
			obj->point[j].y=ChunkToFloat(dane+i);
			i+=4;
			obj->point[j].z=ChunkToFloat(dane+i);
			i+=4;
		}
		
	

	/////////////////////////////////////////////////////////////
	////
	/// CHUNKS NAME: POLS
	///
	/////////////////////////////////////////////////////////////


	for(i=0;i<size;i++)       
	{
		 if(strnicmp("POLS",dane+i,4)==0)
		 {
			 break;
		 }
	}
		i+=4;
		obj->n_pols=(ChunkToInt(dane+i)-4)/8;
		obj->face=(LWO_face*)malloc(obj->n_pols*sizeof(LWO_face));
		i+=8;

		
		for(int j=0;j<obj->n_pols;j++)
		{
			i+=2;
			obj->face[j].v1=ChunkToShort(dane+i);
			i+=2;
			obj->face[j].v2=ChunkToShort(dane+i);
			i+=2;
			obj->face[j].v3=ChunkToShort(dane+i);
			i+=2;
				
		}

	



	/////////////////////////////////////////////////////////////
	////
	/// CHUNKS NAME: VMAP
	///
	/////////////////////////////////////////////////////////////
	for(i=0;i<size;i++)
	{
		 if(strnicmp("VMAP",dane+i,4)==0)
		 {
			break;
		 }
	}



	/////////////////////////////////////////////////////////////
	////
	/// CHUNKS NAME: TXUV 1
	///
	/////////////////////////////////////////////////////////////


	for(i;i<size;i++)
	{

		if(strnicmp("TXUV",dane+i,4)==0)
		{
			
			break;
		 }

 
	}


			i+=6;
			char *temp;

			if(temp=strchr(dane+i,0))
			{
				temp++;
			}
			//temp+=1;

			
			obj->uv=(LWO_uv*)malloc(obj->n_pnts*sizeof(LWO_uv));
			for(int k=0;k<obj->n_pnts;k++)
			{
			    temp+=2;
    
			    obj->uv[k].u=ChunkToFloat(temp);
		        temp+=4;
    
				obj->uv[k].v=ChunkToFloat(temp);
				temp+=4;
	
 			}


	/////////////////////////////////////////////////////////////
	////
	/// CHUNKS NAME: VMAP 2
	///
	/////////////////////////////////////////////////////////////

	for(i=0;i<size;i++)
	{
		if(strnicmp("VMAP",dane+i,4)==0)
		{					
			 break;
	    }
 	}
	

	/////////////////////////////////////////////////////////////
	////
	/// CHUNKS NAME: TXUV 2
	///
	/////////////////////////////////////////////////////////////



	for(i;i<size;i++)
	{
		if(strnicmp("TXUV",dane+i,4)==0)
		{
			
			break;
		 }
 
	}

	
			char *temp2;
			i+=6;
			
			if(temp2=strchr(dane+i,0))
			{
				temp2++;
			}
		temp2+=1;
		
			for(int k=0;k<obj->n_pnts;k++)
			{
			    temp2+=2;
    
			//    obj->uv[k].u2=ChunkToFloat(temp2);
		        temp2+=4;
    
			//	obj->uv[k].v2=ChunkToFloat(temp2);
				temp2+=4;
	
 			}
	


		

	
					



	

			
	/////////////////////////////////////////////////////////////
	////
	/// CHUNKS NAME: STIL 1
	///
	/////////////////////////////////////////////////////////////
	
	bool stil=false;
	for(i=0;i<size;i++)       
	{
		if(strnicmp("STIL",dane+i,4)==0)
		{	
		

			break;
		
		
					
		}
	}

	
			i+=6;

			char *t2;
			char temp_name[32];
			t2=strrchr(dane+i,'/');
			if(t2==0)
			{
				t2=strrchr(dane+i,':');
			}
			t2++;
			strcpy(temp_name,t2);

			strcpy(obj->texture_name,"data/");
			strcat(obj->texture_name,temp_name);
	




		

	/////////////////////////////////////////////////////////////
	////
	/// CHUNKS NAME: STIL 2
	///
	/////////////////////////////////////////////////////////////

		for(i;i<size;i++)       
		{
			if(strnicmp("STIL",dane+i,4)==0)
			{						
					
				multitex=true;
				break;
		
		
					
			}
		}
	
	if(multitex==true)
	{
			i+=6;

			char *t;
			char temp_name2[32];
			t=strrchr(dane+i,'/');
			if(t==0)
			{
				t=strrchr(dane+i,':');
			}
			t++;

			strcpy(temp_name2,t);
			strcpy(obj->texture_name2,"data/");
			strcat(obj->texture_name2,temp_name2);

		



		
	}



	for(i=0;i<size;i++)       
	{
		 if(strnicmp("BBOX",dane+i,4)==0)
		 { 
			 break;
		 }
	}
	i+=8;

		for(int j=0;j<2;j++)
		{
			m_bboxVertex[j].x=ChunkToFloat(dane+i);
			log->CheckFloat(_T("Vx"),m_bboxVertex[j].x);
			i+=4;
			m_bboxVertex[j].y=ChunkToFloat(dane+i);
			log->CheckFloat(_T("Vy"),m_bboxVertex[j].y);
			i+=4;
			m_bboxVertex[j].z=ChunkToFloat(dane+i);
			log->CheckFloat(_T("Vz"),m_bboxVertex[j].z);
			i+=4;		

		}





}


CVector CLwo::getSize()
{
	//calculate bbox size
	m_size.m_x = abs(m_bboxVertex[0].x - m_bboxVertex[1].x);
	m_size.m_y = abs(m_bboxVertex[0].y - m_bboxVertex[1].y);
	m_size.m_z = abs(m_bboxVertex[0].z - m_bboxVertex[1].z);

	return m_size;
}

void CLwo::CreateCollisionTree(NewtonWorld *nWorld, NewtonTreeCollisionCallback levelCallbac, CVector startPos)
{
	NewtonCollision *collision;
	

	collision = NewtonCreateTreeCollision(nWorld, levelCallbac);
  	NewtonTreeCollisionBeginBuild(collision);

	//add faces to collision tree

	
	for(int i=0;i<obj->n_pols;i++)
	{
		LWO_vertex3f v[3];
		v[0].x = obj->point[obj->face[i].v1].x;
		v[0].y = obj->point[obj->face[i].v1].y;
		v[0].z = obj->point[obj->face[i].v1].z;
		
		v[1].x = obj->point[obj->face[i].v2].x;
		v[1].y = obj->point[obj->face[i].v2].y;
		v[1].z = obj->point[obj->face[i].v2].z;

		v[2].x = obj->point[obj->face[i].v3].x;
		v[2].y = obj->point[obj->face[i].v3].y;
		v[2].z = obj->point[obj->face[i].v3].z;
		NewtonTreeCollisionAddFace(collision, 3, &v[0].x, 12, 1);
	}
	NewtonTreeCollisionEndBuild(collision,1); // end collision tree

	

	body = NewtonCreateBody(nWorld,collision); //create body for physic

		
	CMatrix m_matrix;
	m_matrix.Reset();
	m_matrix.Translate(startPos);
	NewtonBodySetMatrix (body, m_matrix.matrix); 


	NewtonReleaseCollision (nWorld, collision); 



	 int defaultID;

	 defaultID = NewtonMaterialGetDefaultGroupID (nWorld);

	// Set default material properties
	NewtonMaterialSetDefaultSoftness (nWorld, defaultID, defaultID, 0.005f);
	NewtonMaterialSetDefaultElasticity (nWorld, defaultID, defaultID, 0.01);
	NewtonMaterialSetDefaultCollidable (nWorld, defaultID, defaultID, 1);
	NewtonMaterialSetDefaultFriction (nWorld, defaultID, defaultID, 5, 5);



	
	NewtonBodySetMaterialGroupID(body,defaultID);

	
}
void PhysicsApplyForceAndTorque3 (const NewtonBody* body)
{
	float mass;
	float Ixx;
	float Iyy;
	float Izz;

	NewtonBodyGetMassMatrix (body, &mass, &Ixx, &Iyy, &Izz);
	float  force[4] = {0 ,0, 0.0f};
	NewtonBodySetForce (body, force);

	
}



void CLwo::initvbo()
{



   int AllocationSize = obj->n_pnts * 3 * sizeof(float);
   int ArrayObjectSize = 0;



   glGenBuffersARB(1, &PointsBuffor);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, PointsBuffor);
   glBufferDataARB(GL_ARRAY_BUFFER_ARB, AllocationSize, obj->point, GL_STATIC_DRAW_ARB);
   glGetBufferParameterivARB(GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &ArrayObjectSize);


   // Error checking to make sure the object was loaded into AGP memory correctly...
   if(ArrayObjectSize <= 0)
      {
		  log->LogError(_T("VBO : Points buffor"));
       
      }
   
   AllocationSize = obj->n_pnts * 2 * sizeof(float);
   ArrayObjectSize = 0;


     
   glGenBuffersARB(1, &CoordBuffor);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, CoordBuffor);
   glBufferDataARB(GL_ARRAY_BUFFER_ARB, AllocationSize, obj->uv, GL_STATIC_DRAW_ARB);
   glGetBufferParameterivARB(GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &ArrayObjectSize);


   // Error checking to make sure the object was loaded into AGP memory correctly...
   if(ArrayObjectSize <= 0)
      {
       log->LogError(_T("VBO : Coord buffor"));
      }


   
   AllocationSize = sizeof(LWO_face) * obj->n_pols;
   ArrayObjectSize = 0;
  

   glGenBuffersARB(1, &IndexBuffor);
   glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IndexBuffor);
   glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, AllocationSize, obj->face, GL_STATIC_DRAW_ARB);
   glGetBufferParameterivARB(GL_ELEMENT_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &ArrayObjectSize);


   // Error checking...
   if(ArrayObjectSize <= 0)
      {
		  log->LogError(_T("VBO : Index buffor"));
      }

   // Since we are done loading lets unbind everything.
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, NULL);
   glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, NULL);


	



}
void CLwo::Init()
{
	if( EXT_EnableVBO())
	{
		VBOenable = true;
		initvbo();
		log->LogSucces(_T("Render in VBO (vertex buffor object)"));
	}else
	{
		log->LogSucces(_T("Render in draw arrays"));
		VBOenable = false;
		MessageBox(NULL,TEXT("GL_ARB_vertex_buffer_object not supported\n Drawing by draw arrays."),TEXT("Typhoon error"),MB_OK|MB_ICONINFORMATION);
	
	}
	
    ///////////////////////
	 /// convert from char to TCHAR
	 char *test = new char[128];
	 strcpy(test, obj->texture_name);
	 TCHAR *path  = utils->AnsiToUnicode(test);
	//////////////////////////////////////////////
	
	 tex->defaultPath = true;
	
	 if(!tex->LoadJPG(path,texture[0]))
			 log->LogError(_T("Texture loading"));	
		log->CheckChar(TEXT("path"), path);
		
		//set poly size
	sizeVBO = obj->n_pols*3;
	sizeSimple = obj->n_pols*3;

	
	getSize(); // get size of bbox

}
void CLwo::CreateCollisionBBOX(NewtonWorld *nWorld, CVector startPos, CVector rotation)
{
	NewtonCollision* collision2; // new collision object

	
	collision2 = NewtonCreateBox(nWorld, m_size.m_x, m_size.m_y, m_size.m_z, NULL); //create collision figure

	body2 = NewtonCreateBody(nWorld, collision2); //create body for collision
	
	NewtonReleaseCollision(nWorld, collision2); // releases collision

	NewtonBodySetMassMatrix (body2, 0, 10.0f, 10.0f, 10); // mass and intereia
	
		
	CMatrix matrix3;
	matrix3.Reset();
	matrix3.Translate(startPos);
	matrix3.Rotate(rotation.m_x,0,1,0);
	
	NewtonBodySetMatrix(body2, matrix3.matrix); //set matrix



	//NewtonBodySetForceAndTorqueCallback (body2, PhysicsApplyForceAndTorque3);
	





}
void CLwo::SetDrawMode(GLenum mode)
{
	drawMode = mode;

}
void CLwo::RenderVBO()
{
	
	
		 glBindTexture(GL_TEXTURE_2D,texture[0]);	

		 glBindBufferARB(GL_ARRAY_BUFFER_ARB, PointsBuffor);
         glVertexPointer(3, GL_FLOAT, 0, 0);
         glEnableClientState(GL_VERTEX_ARRAY);
      
         glBindBufferARB(GL_ARRAY_BUFFER_ARB, CoordBuffor);
         glTexCoordPointer(2, GL_FLOAT, 0, 0);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         
        
         glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IndexBuffor);
		 glDrawElements(drawMode, sizeVBO, GL_UNSIGNED_SHORT, 0);

        
         glDisableClientState(GL_VERTEX_ARRAY);
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);

       
         glBindBufferARB(GL_ARRAY_BUFFER_ARB, NULL);
         glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, NULL);
  




}
void CLwo::RenderSimple()
{
		 glBindTexture(GL_TEXTURE_2D,texture[0]);	

		 glEnableClientState(GL_VERTEX_ARRAY);
		 glVertexPointer(3, GL_FLOAT, 0, (void**)&obj->point[0]);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		 glTexCoordPointer(2, GL_FLOAT, 0, (void**)&obj->uv[0]);
         
		 glDrawElements(drawMode, sizeSimple, GL_UNSIGNED_SHORT, obj->face);
    

}
void CLwo::RenderVBOWT() //with out texture
{
	
	
		// glBindTexture(GL_TEXTURE_2D,texture[0]);	

		 glBindBufferARB(GL_ARRAY_BUFFER_ARB, PointsBuffor);
         glVertexPointer(3, GL_FLOAT, 0, 0);
         glEnableClientState(GL_VERTEX_ARRAY);
      
         glBindBufferARB(GL_ARRAY_BUFFER_ARB, CoordBuffor);
         glTexCoordPointer(2, GL_FLOAT, 0, 0);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         
        
         glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IndexBuffor);
		 glDrawElements(drawMode, sizeVBO, GL_UNSIGNED_SHORT, 0);

        
         glDisableClientState(GL_VERTEX_ARRAY);
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);

       
         glBindBufferARB(GL_ARRAY_BUFFER_ARB, NULL);
         glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, NULL);
  




}
void CLwo::RenderSimpleWT()//with out texture
{
// glBindTexture(GL_TEXTURE_2D,texture[0]);	

		 glEnableClientState(GL_VERTEX_ARRAY);
		 glVertexPointer(3, GL_FLOAT, 0, (void**)&obj->point[0]);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		 glTexCoordPointer(2, GL_FLOAT, 0, (void**)&obj->uv[0]);
         
		 glDrawElements(drawMode, sizeSimple, GL_UNSIGNED_SHORT, obj->face);
    

}
/// main render
void CLwo::Render()
{
	if(VBOenable)
	{
		RenderVBO();
	}
	else
	{
		RenderSimple();
	}
}
/// main render without texture
void CLwo::RenderWT()
{
	if(VBOenable)
	{
		RenderVBOWT();
	}
	else
	{
		RenderSimpleWT();
	}
}

void CLwo::DrawBBOX()
{
	//glScalef(1,1,-1);
	glDisable(GL_TEXTURE_2D);
	glColor3ub(255,0,0);
	auxWireBox(m_size.m_x, m_size.m_y, m_size.m_z);
	glColor3ub(255,255,255);
	glEnable(GL_TEXTURE_2D);


}

CLwo::~CLwo()
{
	unsigned int Buffers[3] = { PointsBuffor, CoordBuffor, IndexBuffor };
	glDeleteBuffersARB( 3, Buffers );

	delete log;
	delete tex;
	delete utils;

	free(obj);
	
}

