#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "CVector.h"
#include "bibloteki.h"

class Chunk
{
public:
	unsigned short int ID;
	unsigned int lenght;


};
class SubChunk
{
public:


};
struct tFace
{
	unsigned short f1,f2,f3;						
					
};
struct v3{
	float x,y,z;
};
struct uv
{
	float u ,v;
};
class Mesh
{
public:
	v3 *m_vertex;
	tFace    *indices;
	uv  *coord;
	char     name[32];
};



class C3ds
{
private:
	FILE *m_file;

	Chunk m_MainChunk;
	Chunk *m_Current;
	Chunk *m_Current2;


	int bytesRead;
	int bytesRead2;

	int vert ;
	int face ;
	unsigned short int index;

public:
	C3ds(TCHAR *path);
	~C3ds();
	Mesh *m_Mesh;
	unsigned short int n_uv;

	bool Read3ds();
	bool ReadChunk(Chunk *src);
	bool ReadObjectChunk(Chunk *src);
	bool ReadVertex(CVector *vertex);

	int GetString(char *pBuffer);


	void Render();

};