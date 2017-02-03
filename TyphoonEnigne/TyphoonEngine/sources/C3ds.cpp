#include "C3ds.h"
#include "CMatrix.h"
#include "CUtility.h"

#define PRIMARY_ID   0x4D4D

// Main Chunks
#define OBJECTINFO    0x3D3D	
#define OBJECTNAME	  0x4000

#define TRIANGULAR_MESH  0x4100  


#define OBJECT_VERTICES     0x4110	
#define OBJECT_FACES        0x4120 
#define OBJECT_MATERIAL     0x4130 
#define OBJECT_UV			0x4140			

#define MATERIAL_BLOCK 0xAFFF
//material chunks
#define MATMAPFILE    0xA300
#define MATNAME       0xA000				
#define MATDIFFUSE    0xA020				
#define MATMAP        0xA200				
#define MATMAPFILE    0xA300


CUtility *utl = new CUtility();


int buffer[50000] = {0};
// ---------------------------------------------------------
// C3ds::C3ds(TCHAR *path)
// constructor
// ---------------------------------------------------------
//
C3ds::C3ds(TCHAR *path) : CExtension()
{
	//default values
	bytesRead        = 0;
	m_NumberOfVertex = 0;
	m_NumberOfFace   = 0;
	m_NumberOfCoord  = 0;
	index            = 0;

	m_texturing      = false;

	PointsBuffor =0 ;
	CoordBuffor = 0;
	IndexBuffor = 0;

	//create mesh
	m_Mesh = new Mesh();
	m_bbox = new CBBox();

	
	m_file = _wfopen(path,TEXT("rb")); // open the 3ds file

	ReadChunk(&m_MainChunk); //read first chunk
	bytesRead += 6;

	if(m_MainChunk.ID != PRIMARY_ID) //are we have 3ds?
	{
		MessageBox(NULL,_T("Can't read 3ds file"),_T("Typhoon Engine"),MB_OK | MB_ICONSTOP);
	}
	else //yes
	{
		Read3ds(); //read 3ds file
	}
	
	fclose(m_file); //close file


}
// ---------------------------------------------------------
// C3ds::GetString(char *pBuffer)
// get string from file
// ---------------------------------------------------------
//
int C3ds::GetString(TCHAR *pBuffer)
{
	int index = 0;
	
	fread(pBuffer, 1, 1, m_file);
	
	while (*(pBuffer + index++) != 0) 
	{
		fread(pBuffer + index, 1, 1, m_file);
	}
	
	return wcslen(pBuffer) + 1;
}
// ---------------------------------------------------------
// C3ds::Read3ds()
// Read 3ds data
// ---------------------------------------------------------
//
bool C3ds::Read3ds()
{
	
	
	m_Current = new Chunk();
	
	//main loop of load
	while(bytesRead < m_MainChunk.lenght) // we have data to read?
	{
		ReadChunk(m_Current); // read chunk header
		

		printf("current chunk size : %d \n", m_Current->lenght);

		switch(m_Current->ID) // read chunks
		{
			/*
				MATERIAL CHUNKS
			*/
			case OBJECT_MATERIAL :
				SkipChunk(m_Current);
				break;
			case OBJECT_UV:
				ReadUV();
				break;
			case MATERIAL_BLOCK: //start material block
				break;
			case MATNAME : //skip mateiral name
				SkipChunk(m_Current);
				break;
			case MATMAP :
				break;
			case MATMAPFILE :
				bytesRead += 6;
				bytesRead += GetString(m_Mesh->m_textureName);
							break;
			/*
				OBJECT CHUNKS
			*/
			case OBJECTINFO : //start read mesh chubks
				break;
			case OBJECTNAME :
				bytesRead += 6;
				bytesRead += GetString(m_Mesh->m_name); //read object name
				break;
			case TRIANGULAR_MESH:
				break;
			case OBJECT_VERTICES :
				ReadVertex(); //read vertices
				break;
			case OBJECT_FACES :
				ReadFaces(); // read faces
				break;


			default :
				SkipChunk(m_Current);	
				break;
		}
	}


	return true;
}
// ---------------------------------------------------------
// C3ds::ReadChunk(Chunk *src)
// read chunk header
// ---------------------------------------------------------
//
bool C3ds::ReadChunk(Chunk *src)
{
	fread(&src->ID, 1, 2, m_file); // read id of chunk
	fread(&src->lenght, 1, 4, m_file); // read lenght of chunk

	return true;
}
// ---------------------------------------------------------
// C3ds::SkipChunk(Chunk *src)
// Skip chunk
// ---------------------------------------------------------
//
void C3ds::SkipChunk(Chunk *src)
{
	  bytesRead += 6;
	  bytesRead += fread(buffer, 1, m_Current->lenght - 6, m_file); 
}
// ---------------------------------------------------------
// C3ds::ReadVertex()
// Read vertex
// ---------------------------------------------------------
//
bool C3ds::ReadVertex()
{
	bytesRead += 6;
	bytesRead += fread(&m_NumberOfVertex, 1, 2, m_file); // number of vertex in chunk

	m_Mesh->m_vertex = new tVector[m_NumberOfVertex]; //create place for vertex
	//and read all vertex	
	bytesRead += fread(m_Mesh->m_vertex, 1, m_NumberOfVertex * sizeof(tVector) ,m_file);

	//calc bbox

	m_bbox->MIN(m_Mesh->m_vertex, m_NumberOfVertex);
	m_bbox->MAX(m_Mesh->m_vertex, m_NumberOfVertex);
	m_bbox->CalcBBOX();


	return TRUE;
}
// ---------------------------------------------------------
// C3ds::ReadFaces()
// Read faces
// ---------------------------------------------------------
//
void C3ds::ReadFaces()
{
	  bytesRead += 6;
	  bytesRead += fread(&m_NumberOfFace, 1, 2, m_file); // number of faces in chunk
	
	  m_Mesh->m_indices = new tFace [m_NumberOfFace]; // create place for chunk

	  for(int i = 0; i < m_NumberOfFace; i++)
	  {
			
					bytesRead += fread(&m_Mesh->m_indices[i].f1, 1,2, m_file);
					bytesRead += fread(&m_Mesh->m_indices[i].f2, 1,2, m_file);
					bytesRead += fread(&m_Mesh->m_indices[i].f3, 1,2, m_file);
					bytesRead += fread(buffer, 1,2, m_file);										
			
	  }			
}
// ---------------------------------------------------------
// C3ds::ReadUv()
// Render coords
// ---------------------------------------------------------
//
void C3ds::ReadUV()
{
	 bytesRead += 6;
	 bytesRead += fread(&m_NumberOfCoord,1,2,m_file); // number of coords in chunk

	 m_Mesh->m_coords = new tUV[m_NumberOfCoord]; //create place for coords

	 bytesRead+= fread(m_Mesh->m_coords, 1, m_NumberOfCoord *8,m_file); //read all coords

	


}
void C3ds::CountNormals()
{
	m_Mesh->m_normals = new CVector[m_NumberOfVertex];

	for(int i = 0; i < m_NumberOfVertex; i++)
	{
		m_Mesh->m_normals[i].m_x = m_Mesh->m_vertex[i].x;
		m_Mesh->m_normals[i].m_y = m_Mesh->m_vertex[i].y;
		m_Mesh->m_normals[i].m_z = m_Mesh->m_vertex[i].z;


		m_Mesh->m_normals[i].Normalize();
	}
	

}
// ---------------------------------------------------------
// C3ds::InitVBO()
// Init vbo
// ---------------------------------------------------------
//
void C3ds::InitVBO()
{

	EXT_EnableVBO(); //enable VBO extension


	

	int AllocationSize = m_NumberOfVertex * sizeof(tVector);
	int ArrayObjectSize = 0;


 
   glGenBuffersARB(1, &PointsBuffor);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, PointsBuffor);
   glBufferDataARB(GL_ARRAY_BUFFER_ARB, AllocationSize, m_Mesh->m_vertex, GL_STATIC_DRAW_ARB);
   glGetBufferParameterivARB(GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &ArrayObjectSize);


   AllocationSize = sizeof(tUV) * m_NumberOfCoord ;
   ArrayObjectSize = 0;

   glGenBuffersARB(1, &CoordBuffor);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, CoordBuffor);
   glBufferDataARB(GL_ARRAY_BUFFER_ARB, AllocationSize, m_Mesh->m_coords, GL_STATIC_DRAW_ARB);
   glGetBufferParameterivARB(GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &ArrayObjectSize);

	if(ArrayObjectSize <= 0)
      {
		  MessageBox(NULL,_T("VBO index buffor"), _T("Typhoon Error"), MB_OK );
      }


	
   AllocationSize = sizeof(tFace) * m_NumberOfFace;
   ArrayObjectSize = 0;

   glGenBuffersARB(1, &IndexBuffor);
   glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IndexBuffor);
   glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, AllocationSize, m_Mesh->m_indices, GL_STATIC_DRAW_ARB);
   glGetBufferParameterivARB(GL_ELEMENT_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &ArrayObjectSize);


   // Error checking...
   if(ArrayObjectSize <= 0)
      {
		  MessageBox(NULL,_T("VBO index buffor"), _T("Typhoon Error"), MB_OK );
      }

   //normals
   CountNormals(); //count normals 

   AllocationSize = 12 * m_NumberOfVertex;
   ArrayObjectSize = 0;

   glGenBuffersARB(1, &NormalBuffor);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, NormalBuffor);
   glBufferDataARB(GL_ARRAY_BUFFER_ARB, AllocationSize, m_Mesh->m_normals, GL_STATIC_DRAW_ARB);
   glGetBufferParameterivARB(GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &ArrayObjectSize);

	if(ArrayObjectSize <= 0)
      {
		  MessageBox(NULL,_T("VBO index buffor"), _T("Typhoon Error"), MB_OK );
      }


   // Since we are done loading lets unbind everything.
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, NULL);
   glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, NULL);
 
    sizeVBO = m_NumberOfFace * 3 ;
	sizeSimple =  m_NumberOfFace*3;

}
void Forces(const NewtonBody* body)
{
	float mass;
	float Ixx;
	float Iyy;
	float Izz;

	NewtonBodyGetMassMatrix (body, &mass, &Ixx, &Iyy, &Izz);
	float  force[4] = {0 ,0, 0.0f};
	NewtonBodySetForce (body, force);

	
}
void C3ds::ApplyBBoxCollision(NewtonWorld *nWorld, CVector startPos, CVector rotation)
{
	NewtonCollision* collision2; // new collision object
	
	collision2 = NewtonCreateBox(nWorld, m_bbox->m_size.m_x, m_bbox->m_size.m_y, m_bbox->m_size.m_z, NULL); //create collision figure

	m_body = NewtonCreateBody(nWorld, collision2); //create body for collision
	
	NewtonReleaseCollision(nWorld, collision2); // releases collision

	NewtonBodySetMassMatrix (m_body, 0, 10.0f, 10.0f, 10); // mass and intereia
	
		
	CMatrix matrix3;
	matrix3.Reset();
	matrix3.Translate(startPos);
	matrix3.Rotate(rotation.m_x,0,1,0);
	
	NewtonBodySetMatrix(m_body, matrix3.matrix); //set matrix





}
// ---------------------------------------------------------
// C3ds::Init()
// Init mesh
// ---------------------------------------------------------
//
void C3ds::Init()
{	
	glEnable(GL_TEXTURE_2D);

	char *path = utl->UnicodeToAnsi(m_Mesh->m_textureName); //convert texture path to asci


	m_texture = new CTexture();
	m_texture->defaultPath = true;
	

	TCHAR tempPath[128];
	wcsncpy(tempPath, m_Mesh->m_textureName+wcslen(m_Mesh->m_textureName)-3, 4);

	//check extension of texture file
	if((wcscmp(tempPath,_T("jpg"))==0) || (wcscmp(tempPath,_T("JPG"))==0)) //if jpg
	{
		m_texture->LoadJPG(m_Mesh->m_textureName, m_texID[0]); // load jpg file texture
	}
	else
		if(!wcscmp(tempPath,_T("tga")) || !wcscmp(tempPath,_T("TGA"))) //if tga
		{
			m_texture->CreateTexture(m_texID, path, 0); // load tga file texture
		}
		else
		{
			MessageBox(NULL, _T("Can't read texture file"),_T("3ds error"), MB_OK );
		}


	
	
	InitVBO();

	
	
	EXT_EnableARB_Multitexturing(); // enable multitexturing extension
	

}
// ---------------------------------------------------------
// C3ds::Render()
// Render mesh
// ---------------------------------------------------------
//
void C3ds::Render()
{
	
		  glBindTexture(GL_TEXTURE_2D, m_texID[0]); //bind texture 
	
		
		 glBindBufferARB(GL_ARRAY_BUFFER_ARB, PointsBuffor);
         glVertexPointer(3, GL_FLOAT, 0, 0);
         glEnableClientState(GL_VERTEX_ARRAY);
  
		 glBindBufferARB(GL_ARRAY_BUFFER_ARB, CoordBuffor);
         glTexCoordPointer(2, GL_FLOAT, 0, 0);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         
		
         glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IndexBuffor);
		 glDrawElements(GL_TRIANGLES, sizeVBO, GL_UNSIGNED_SHORT, 0);

		 glDisableClientState(GL_VERTEX_ARRAY);
		 glDisableClientState(GL_TEXTURE_COORD_ARRAY);
       
       
         glBindBufferARB(GL_ARRAY_BUFFER_ARB, NULL);
         glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, NULL);
  


}
void C3ds::Render2()
{
	 //texture
		 //enable multitexturing
	 glActiveTextureARB(GL_TEXTURE0_ARB);
	 glEnable (GL_TEXTURE_2D);
	 glBindTexture (GL_TEXTURE_2D, m_texID[0]);

			 //vertex
		 glBindBufferARB(GL_ARRAY_BUFFER_ARB, PointsBuffor);
         glVertexPointer(3, GL_FLOAT, 0, 0);
         glEnableClientState(GL_VERTEX_ARRAY);
  
		  //normals
	//	 glBindBufferARB(GL_ARRAY_BUFFER_ARB, NormalBuffor);
	///	 glNormalPointer(GL_FLOAT, 0, 0);
	//	 glEnableClientState(GL_NORMAL_ARRAY); 

		
		 //coord
		 glBindBufferARB(GL_ARRAY_BUFFER_ARB, CoordBuffor);
         glTexCoordPointer(2, GL_FLOAT, 0, 0);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		
         
		 //draw mesh
         glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IndexBuffor);
		 glDrawElements(GL_TRIANGLES, sizeVBO, GL_UNSIGNED_SHORT, 0);

		 glDisableClientState(GL_VERTEX_ARRAY);
		 glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		 glDisableClientState(GL_NORMAL_ARRAY);
       
       
         glBindBufferARB(GL_ARRAY_BUFFER_ARB, NULL);
         glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, NULL);


}
void C3ds::DrawBBOX()
{
	glDisable(GL_TEXTURE_2D);
	glColor3ub(255,0,0);
	auxWireBox(m_bbox->m_size.m_x, m_bbox->m_size.m_y, m_bbox->m_size.m_z);
	glColor3ub(255,255,255);
	glEnable(GL_TEXTURE_2D);

}
// ---------------------------------------------------------
// C3ds::~C3ds()
// deconstructor
// ---------------------------------------------------------
//
C3ds::~C3ds()
{
	delete m_Mesh;


}
