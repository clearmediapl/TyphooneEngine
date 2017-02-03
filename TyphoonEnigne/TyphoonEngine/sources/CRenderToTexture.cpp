#include "CRenderToTexture.h"

// ---------------------------------------------------------
// CRenderToTexture::CRenderToTexture()
// constructor
// ---------------------------------------------------------
//
CRenderToTexture::CRenderToTexture()
{

}

// ---------------------------------------------------------
// CRenderToTexture::SetSize(TSize size)
// Set texture render size
// ---------------------------------------------------------
//
void CRenderToTexture::SetSize(CVector size)
{
	tsize = size;
	textureSize = new unsigned char[3 * size.m_x * size.m_y];
}

// ---------------------------------------------------------
// CRenderToTexture::CreateRenderTexture()
// Create Render Texture
// ---------------------------------------------------------
//
void CRenderToTexture::CreateRenderTexture()
{
	glEnable (GL_TEXTURE_2D);
	glGenTextures (1, &textureRender);
    
	glBindTexture (GL_TEXTURE_2D, textureRender);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tsize.m_x, tsize.m_y, 0, GL_RGB, GL_UNSIGNED_BYTE, textureSize);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
  
}
// ---------------------------------------------------------
// CRenderToTexture::Begin()
// Start render to texture
// ---------------------------------------------------------
//
void CRenderToTexture::Begin()
{
	
  /* Render to buffer */
    glClearColor (0.2, 0.2, 1, 0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glViewport(0, 0, 256, 256);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (45, 1, 5, 300);
  
    glMatrixMode(GL_MODELVIEW);
 
  

}
// ---------------------------------------------------------
// CRenderToTexture::End
// end render to texture
// ---------------------------------------------------------
//
void CRenderToTexture::End()
{
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 5, 5, 0, 0, tsize.m_x - 10, tsize.m_y - 10);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (46, 800 / (float) 600, 0.01, 300);
    glViewport(0, 0, 800,600);
    glMatrixMode(GL_MODELVIEW);
    glClearColor (0, 0, 0, 0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity();
    glFlush (); 

}

CRenderToTexture::~CRenderToTexture()
{
	delete []  textureSize;
}