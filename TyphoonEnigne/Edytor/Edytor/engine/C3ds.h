#ifndef _C3DS_H_
#define _C3DS_H_

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <newton.h>
#include "CVector.h"
#include "bibloteki.h"
#include "CTexture.h"

#include "CExtension.h"

#include "CBBox.h"
//chunk class
class Chunk
{
public:
	unsigned short int ID;
	unsigned int lenght;

	Chunk()
	{
		ID = 0;
		lenght = 0;
	}


};
// information about face
struct tFace
{
	unsigned short f1, f2, f3;							
	
};
//vector

struct tUV
{
	float u,v;
};
// mesh info
class Mesh
{
public:
	tVector   *m_vertex; //vertices
	CVector   *m_normals; //vertices
	tFace     *m_indices;  //faces
	tUV       *m_coords; //cords
	TCHAR      m_name[32]; // name of object
	TCHAR      m_textureName[32]; //name of texture
};



class C3ds : public CExtension
{
private:
	FILE *m_file;
	Mesh *m_Mesh;

	//vbo 
	int sizeVBO;
	int sizeSimple;
	unsigned int PointsBuffor ;
	unsigned int CoordBuffor ;
	unsigned int IndexBuffor;
	unsigned int NormalBuffor;

	//read data
	Chunk m_MainChunk;
	Chunk m_Current;
	int bytesRead;	
	int m_NumberOfVertex ;
	int m_NumberOfFace ;
	int m_NumberOfCoord ;
	unsigned short int index;

	CTexture *m_texture;
	GLuint   m_texID[1];

	bool m_texturing;
	bool m_IsTGA;

	//physic
	NewtonBody *m_body;

public:
	CBBox    *m_bbox;

public:
	C3ds(TCHAR *path);
	~C3ds();

	bool Read3ds();
	bool ReadChunk(Chunk *src);
	void SkipChunk(Chunk *src);

	bool ReadVertex();
	void ReadFaces();
	void ReadUV();

	
	void CountNormals();
	void ApplyBBoxCollision(NewtonWorld *nWorld, CVector startPos, CVector rotation);

	int GetString(TCHAR *pBuffer);


	void InitVBO();
	void Init();

	void Render();
	void DrawBBOX();

};


#endif