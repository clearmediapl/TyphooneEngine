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


CLwo::CLwo(char *name)
{
	VBOenable = false;
	multitex = false;

	log = new CLogger();
	log->Append(_T("main.log"));
	log->NewSection(_T("LWO testing"));

	
	obj=(LWO_object*)malloc(sizeof(LWO_object));

	file = open(name, O_BINARY); 
	if(file<0)
	{
		MessageBox(NULL,TEXT("Can't open the object"),TEXT("Error"),MB_OK |MB_ICONWARNING );
		log->LogError(_T("Lwo load"));
	}
	size = filelength(file); 
	dane = (char*)malloc(size);
	read(file,dane,size);

	

	tex = new CTexture();
	utils = new CUtility();

	Load(size,dane);
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






}
PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;
PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;
PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;
PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB = NULL;



void CLwo::initvbo()
{

   glBindBufferARB = (PFNGLBINDBUFFERARBPROC)wglGetProcAddress("glBindBufferARB");
   glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)wglGetProcAddress("glDeleteBuffersARB");
   glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");
   glBufferDataARB = (PFNGLBUFFERDATAARBPROC)wglGetProcAddress("glBufferDataARB");
   glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC)wglGetProcAddress("glGetBufferParameterivARB");

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
	if(utils->IsExtensionSupported( "GL_ARB_vertex_buffer_object" ))
	{
		VBOenable = true;
		initvbo();
		log->LogSucces(_T("Render in VBO (vertex buffor object)"));
	}else
	{
		log->LogSucces(_T("Render in draw arrays"));
		VBOenable = false;
		MessageBox(NULL,TEXT("GL_ARB_vertex_buffer_object not supported\n Drawing by draw arrays."),TEXT("Typhoon error"),MB_OK|MB_ICONEXCLAMATION);
	
	}
	
    ///////////////////////
	 /// convert from char to TCHAR
	 char *test = new char[128];
	 strcpy(test, obj->texture_name);
	 TCHAR *path  = utils->AnsiToUnicode(test);
	//////////////////////////////////////////////
	
	
	 if(!tex->LoadJPG(path,texture[0]))
			 log->LogError(_T("Texture loading"));	
		log->CheckChar(TEXT("path"), path);
		
		//set poly size
	sizeVBO = obj->n_pols*3;
	sizeSimple = obj->n_pols*3;

	

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



CLwo::~CLwo()
{
	unsigned int Buffers[3] = { PointsBuffor, CoordBuffor, IndexBuffor };
	glDeleteBuffersARB( 3, Buffers );

	delete log;
	delete tex;
	delete utils;

	free(obj);
	
}

