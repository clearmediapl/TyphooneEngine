#include "Libraries.h"


#include "CIOEditor.h"




class CEdit;

#include "CSaveMap.h"

class CEditorRender : public CIOEditor
{
private:
	int i; //index

	float time;

	int g;
public:
	bool keys[256];

	int actualyObj; // actualy select object
	
	float MousePosX;//mouse pos x
	float MousePosY;//mouse pos y

	bool wireDraw;// draw wire objects?
	bool solidDraw; // draw solid objects?
	bool freeLook; //free look camera?

	bool cameraMoving; // is camera moving now?
	
	float rotX,rotY;

public:
	
	void Init();
	

	void SetMousePos(float xPos, float yPos); //get mouse position
	void MoveToCamera();

	void AddMesh(TCHAR *path); //add new mesh to map
	void AddSky(TCHAR *path); //add sky do map
	void AddPlayer(TCHAR *path); //add player to map


	void DeleteObject(int number);

	void DrawGrid(bool xAxis, bool yAxis, bool zAxis);//draw grid axis
	void DrawMesh(CObject *obj);
	void DrawSky();
	void DrawObjects();
	

	void Update(bool move,    bool rotate,  bool scale,
		        bool xModify, bool yModify, bool zModify); //update


	void Kill();
};