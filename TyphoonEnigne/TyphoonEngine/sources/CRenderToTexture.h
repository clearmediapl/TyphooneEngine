#include "bibloteki.h"
#include "CVector.h"

class CRenderToTexture
{
private:
	unsigned char *textureSize; //size of texture render
	CVector tsize; //size of texture render

public:
	unsigned int textureRender; //texture render

public:

	CRenderToTexture(); //constructor
	~CRenderToTexture(); //deconstructor

	void SetSize(CVector size); //set size of texture render
	void CreateRenderTexture(); //create texture render
	void Begin(); //begin render to texture 
	void End(); //end render to texture



};