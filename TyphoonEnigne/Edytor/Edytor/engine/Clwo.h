/*******************************************************************/
/* Filename:                  CLwo                                 */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         20.05.2006                           */
/* Last revision:             20.05.2006                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/
#ifndef _CLWO_H_
#define _CLWO_H_

#include "CUtility.h"


class CLogger;
class CTexture;


struct ptag
{
	unsigned short surface_nr;
	unsigned short polygon_nr;
};

struct LWO_face
{
	unsigned short v1,v2,v3;
};

struct LWO_vertex3f
{
	float x,y,z;
};
struct LWO_uv
{
		float u,v;
		//float u2,v2;
};
struct LWO_surface
{
	char name[32];

	float r,g,b;
};

struct LWO_object
{
	LWO_face     *face;
	LWO_vertex3f *point;
	LWO_uv       *uv;

	char texture_name[128];
	char texture_name2[128];

	LWO_surface surf[10];

	int n_surface;
	int n_pnts;
	int n_pols;
};




struct LWO_vmad
{
	TCHAR *name;
	unsigned int dimension;

	unsigned int *poly_index;
	unsigned int *vert_index;

	int size;

	LWO_uv *uv;


};


#include "bibloteki.h"
#include "CVector.h"
#include <newton/newton.h>
#include "CExtension.h"


class CLwo  : public CExtension
{ 
private:

	int i;
	int  file;
	int  size;
	char *dane;

	
	//lwo data
	unsigned int PointsBuffor ;
	unsigned int CoordBuffor ;
	unsigned int IndexBuffor;
	int sizeVBO;
	int sizeSimple;
	
	int ptag_size;
	bool multitex;

	CLogger *log;
	CTexture *tex;
	CUtility *utils;

	LWO_vertex3f m_bboxVertex[2];  //bbox vertex data from BBOX chunk

	
	bool VBOenable;
		

	LWO_vmad vmad;
	LWO_object *obj;

	char temp_name[128];

	unsigned int texture[2];
	GLenum drawMode;


	CVector m_size; // bbox size

public:
	
	bool defaultPath;


	float           ChunkToFloat(char *input);
	unsigned short  ChunkToShort(char *input);
	unsigned int    ChunkToInt(char *input);
	unsigned char   ChunkToChar(char *input);
	
	void            Load(int size, char *dane);
   	


	CLwo(char *name);
	~CLwo();


	void            SetDrawMode(GLenum mode);

	void            CreateCollisionTree(NewtonWorld *nWorld, NewtonTreeCollisionCallback levelCallbac);
	CVector         getSize();
	void            Init();
	void            initvbo();
	void            Render();        // main render
	void            RenderVBO();
	void            RenderSimple();

	void            RenderWT(); //without texture
	void            RenderVBOWT(); //without texture
	void            RenderSimpleWT();//without texture

	void            DrawBBOX();


};






#endif





