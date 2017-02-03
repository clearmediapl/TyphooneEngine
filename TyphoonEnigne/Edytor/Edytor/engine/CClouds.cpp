#include "CClouds.h"
#include "CTexture.h"
#include "CLwo.h"
#include "CCamera.h"

// ---------------------------------------------------------
// CClouds::CClouds()
// constructor
// ---------------------------------------------------------
//
CClouds::CClouds()
{
	//default values
	speed = 0;
	scale = 1;
	size.x = 1;
	size.y = 1;
	size.z = 1;
	s = 0;
	t = 0;
	alpha=0.1;




}
// ---------------------------------------------------------
// CClouds::SetScale(float value)
// Set scale to clouds
// ---------------------------------------------------------
//
void CClouds::SetScale(float value)
{
	scale = value/30;
}
// ---------------------------------------------------------
// CClouds::SetSpeed(float value)
// Set speed of cllouds
// ---------------------------------------------------------
//
void CClouds::SetSpeed(int value)
{
	(float)speed = (float(value)/10100);
}
// ---------------------------------------------------------
// CClouds::SetAlpha(float value)
// Set alpha of cllouds
// ---------------------------------------------------------
//
void CClouds::SetAlpha(float value)
{
	alpha = value/255;
}
// ---------------------------------------------------------
// CClouds::SetSize(float value)
// Set speed of cllouds
// ---------------------------------------------------------
//
void CClouds::SetSize(float x, float y, float z)
{
	size.x = x;
	size.y = y;
	size.z = z;
}
// ---------------------------------------------------------
// CClouds::SetHeight(float value)
// Set speed of cllouds
// ---------------------------------------------------------
//
void CClouds::SetHeight(float value)
{
	height = value;
}
// ---------------------------------------------------------
// CClouds::SetBrightness(float value)
// 
// ---------------------------------------------------------
//
void CClouds::SetBrightness(float value)
{
	brightness = value/255;
}
// ---------------------------------------------------------
// CClouds::SetBackgroundBrightness(float value)
// 
// ---------------------------------------------------------
//
void CClouds::SetBackgroundBrightness(float value)
{
	backgroundBrightness = value/255;
}
// ---------------------------------------------------------
// CClouds::SetTexture1(TCHAR *path)
// Set texture for  clouds
// ---------------------------------------------------------
//
void CClouds::SetTexture1(TCHAR *path)
{
	wcscpy_s(path1,path);
	tex->defaultPath = false;
	if(!tex->LoadJPG(path,texture[1]))
     	{  }
}
// ---------------------------------------------------------
// CClouds::SetTexture2(TCHAR *path)
// Set texture for  clouds
// ---------------------------------------------------------
//
void CClouds::SetTexture2(TCHAR *path)
{
	wcscpy_s(path2,path);
	tex->defaultPath = false;
	if(!tex->LoadJPG(path,texture[2]))
     	{  }

}
// ---------------------------------------------------------
// CClouds::SetCamera(CCamera cam)
// Set speed of cllouds
// ---------------------------------------------------------
//
void CClouds::SetCamera(CCamera *cam)
{
	camera = cam;
}
// ---------------------------------------------------------
// CClouds::Init()
// Init system
// ---------------------------------------------------------
//
void CClouds::Init()
{
	tex = new CTexture();
	tex->defaultPath = true;
	backTex = new CTexture();
	backTex->defaultPath = true;
	

	obj = new CLwo("data/skyobj.lwo");
	obj->Init();

	TCHAR szPath[255];
	



	if(!backTex->LoadJPG(TEXT("data/sky.jpg"),texture[0]))
     	{  }

	

	
}
// ---------------------------------------------------------
// CClouds::Render()
// Render
// ---------------------------------------------------------
//
void CClouds::Render()
{
	
	glLoadIdentity();
	camera->Render(); //set camera
	//blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE);	 

	glTranslatef(0, height, -10);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glScalef(size.x, size.y, size.z);

	///////////////////// TEXTURE MATRIX
	glMatrixMode(GL_TEXTURE);                    // Enter texture matrix.
    glLoadIdentity();                            // reset it.

    glTranslatef(0.0, 0.0, 0.0f);         //  the matrix.
	glScalef(scale,scale,scale);
	glColor4f(backgroundBrightness , backgroundBrightness , backgroundBrightness , backgroundBrightness );
    glMatrixMode(GL_MODELVIEW);                  // Leave the texture matrix.
	/////////////////////

	obj->SetDrawMode(GL_TRIANGLES);
	obj->RenderWT();


	glLoadIdentity();

	camera->Render(); //set camera

	glTranslatef(0, height-0.1, -10);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glScalef(size.x, size.y, size.z);
	glColor4f(brightness  ,brightness  ,brightness  ,0.9 );
	///////////////////// TEXTURE MATRIX
	glMatrixMode(GL_TEXTURE);                    // Enter texture matrix.
    glLoadIdentity();                            // reset it.

    glTranslatef(0.0+s, 0.0, 0.0f);         //  the matrix.
	glScalef(scale,scale,scale);
    glMatrixMode(GL_MODELVIEW);                  // Leave the texture matrix.
	/////////////////////

	obj->RenderWT();

	glLoadIdentity();

	camera->Render(); //set camera

	
	glTranslatef(0, height-0.2, -10);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glScalef(size.x, size.y, size.z);

	///////////////////// TEXTURE MATRIX
	glMatrixMode(GL_TEXTURE);                    // Enter texture matrix.
    glLoadIdentity();                            // reset it.

    glTranslatef(0+t, 0.0-t, 0.0f);         //  the matrix.
	glScalef(scale,scale,scale);
    glMatrixMode(GL_MODELVIEW);                  // Leave the texture matrix.
	/////////////////////

	obj->RenderWT();
	glLoadIdentity();

	// reset matrix texture

	glMatrixMode(GL_TEXTURE);                    // Enter texture matrix.
    glLoadIdentity();                            // reset it.

    glTranslatef(0.0, 0.0, 0.0f);         //  the matrix.
	glScalef(1,1,1);
    glMatrixMode(GL_MODELVIEW);                  // Leave the texture matrix.
	/////////////////////

	
}
// ---------------------------------------------------------
// CClouds::Update()
// Update
// ---------------------------------------------------------
//
void CClouds::Update()
{
	s += speed;
	t += speed;

}
// ---------------------------------------------------------
// CClouds::SaveClouds()
// Save clouds
// ---------------------------------------------------------
//
void CClouds::SaveClouds(const TCHAR *path)
{
	saveClouds = _wfopen(path, TEXT("w"));

	fwprintf(saveClouds, _T("Clouds File \n"));
	fwprintf(saveClouds, _T("\n"));

	fwprintf(saveClouds, _T("Clouds \n")); //name of class
	fwprintf(saveClouds, _T("{ \n")); //start class
	fwprintf(saveClouds, _T("	%s \n"), path1); //save path of texture1
	fwprintf(saveClouds, _T("	%s \n"), path2); //save path of texture2
	fwprintf(saveClouds, _T("\n")); //clean line
	fwprintf(saveClouds, _T("	%f \n"), scale); //save scale od textures
	fwprintf(saveClouds, _T("	%f \n"), speed); //speed of clouds
	fwprintf(saveClouds, _T("	%f \n"), height); //height of sky
	fwprintf(saveClouds, _T("	%f \n"), backgroundBrightness); //bacground brigthness
	fwprintf(saveClouds, _T("	%f \n"), brightness); //brightness of sky
	fwprintf(saveClouds, _T("} \n"));

	fclose(saveClouds);




}
// ---------------------------------------------------------
// CClouds::LoadClouds()
// load clouds
// ---------------------------------------------------------
//
void CClouds::LoadClouds(const TCHAR *path)
{
	memset(path1,0,sizeof(path1));
	memset(path2,0,sizeof(path2));

	openClouds = _wfopen(path, TEXT("r"));

	fwscanf(openClouds, _T("Clouds File \n"));
	fwscanf(openClouds, _T("\n"));

	fwscanf(openClouds, _T("Clouds \n")); //name of class
	fwscanf(openClouds, _T("{ \n")); //start class
	fwscanf(openClouds, _T("	%s \n"), path1); //save path of texture1
	fwscanf(openClouds, _T("	%s \n"), path2); //save path of texture2
	fwscanf(openClouds, _T("\n")); //clean line
	fwscanf(openClouds, _T("	%f \n"), &scale); //save scale od textures
	fwscanf(openClouds, _T("	%f \n"), &speed); //speed of clouds
	fwscanf(openClouds, _T("	%f \n"), &height); //height of sky
	fwscanf(openClouds, _T("	%f \n"), &backgroundBrightness); //bacground brigthness
	fwscanf(openClouds, _T("	%f \n"), &brightness); //brightness of sky
	fwscanf(openClouds, _T("} \n"));

	SetTexture1(path1);
	SetTexture2(path2);

	fclose(openClouds);




}
// ---------------------------------------------------------
// CClouds::CClouds()
// deconstructor
// ---------------------------------------------------------
//
CClouds::~CClouds()
{
	delete obj;
	delete tex;

}
