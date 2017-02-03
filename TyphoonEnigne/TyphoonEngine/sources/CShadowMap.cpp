#include "CShadowMap.h"


float lightPos[3] = { 2.0f, 3.0f,-2.0f};

float white[4] = { 1,1,1,1};
float gray[4] = { 0.1, 0.1, 0.1, 0.1};
float black[4] = { 0,0,0,0};

CShadowMap::CShadowMap()
{
	m_shadowMapSize = 512;

	//lightProjectionMatrix.Reset();
//	lightViewMatrix.Reset();

//	m_textureMatrix.Reset();

	m_cam = new CCamera();

}
void CShadowMap::GetCameraPos(CCamera *cam)
{
	m_cam = cam;
}
void CShadowMap::SetLightPos(float x, float y, float z)
{
	m_lightPos.m_x = x;  
	m_lightPos.m_y = y;
	m_lightPos.m_z = z;
}

void CShadowMap::InitShadows()
{
	
	EXT_EnableARB_Multitexturing(); // enable mulitexturing extension
	if(!EXT_EnableARB_Shadow())
	{
		MessageBox(NULL, _T("Shadow Maps : Can't load shadow extension"), _T("Typhoon Engin"), MB_OK);
	}

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Depth states
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	//We use glScale when drawing the scene
	glEnable(GL_NORMALIZE);


	//create shadow map texture
	glGenTextures(1, &m_shadowMapTexture);
	glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_shadowMapSize, m_shadowMapSize, 0,
				 GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//Use the color as the ambient and diffuse material
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	//White specular material color, shininess 16
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);


		

	m_cam->SetPosition(-7,-10,-6);
	m_cam->SetRotation(45,-60,0);

	
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 2.0f, 100.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, lightProjectionMatrix.matrix);

	glLoadIdentity();
	gluLookAt(	7.0f, 8.0f,0.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, lightViewMatrix.matrix);
	glPopMatrix();





	
	
	
	

}
void CShadowMap::DrawFromLight()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(lightProjectionMatrix.matrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(lightViewMatrix.matrix);

	//Use viewport the same size as the shadow map
	glViewport(0, 0, m_shadowMapSize, m_shadowMapSize);

	//Draw back faces into the shadow map
	glCullFace(GL_FRONT);

	//Disable color writes, and use flat shading for speed
	glShadeModel(GL_FLAT);
	glColorMask(0, 0, 0, 0);
}
void CShadowMap::DrawFromCamera()
{
	//save data from light eye
	//Read the depth buffer into the shadow map texture
	glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, m_shadowMapSize, m_shadowMapSize);


	//restore states
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glColorMask(1, 1, 1, 1);
	


	//2nd pass - Draw from camera's point of view
	glClear(GL_DEPTH_BUFFER_BIT);

	m_cam->Render();

	glViewport(0, 0, 800, 600);

	float amb[] = {0.5, 0.5, 0.5, 0.5};
	
	//Use dim light to represent shadowed areas
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, amb);
	glLightfv(GL_LIGHT1, GL_SPECULAR, black);
	glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);




}
void CShadowMap::ProjectShadows()
{
	//3rd pass
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);

	//Calculate texture matrix for projection
	//This matrix takes us from eye space to the light's clip space
	//It is postmultiplied by the inverse of the current view matrix when specifying texgen
	static CMatrix biasMatrix(CVector(0.5f, 0.0f, 0.0f, 0.0f),
							  CVector(0.0f, 0.5f, 0.0f, 0.0f),
							  CVector(0.0f, 0.0f, 0.5f, 0.0f),
							  CVector(0.5f, 0.5f, 0.5f, 1.0f));	
	
	CMatrix m_textureMatrix=biasMatrix*lightProjectionMatrix*lightViewMatrix;
	
	
	//Bind & enable shadow map texture
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);

	//Set up texture coordinate generation.
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_S, GL_EYE_PLANE, m_textureMatrix.GetRow(0).value);
	glEnable(GL_TEXTURE_GEN_S);

	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_T, GL_EYE_PLANE, m_textureMatrix.GetRow(1).value);
	glEnable(GL_TEXTURE_GEN_T);

	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_R, GL_EYE_PLANE, m_textureMatrix.GetRow(2).value);
	glEnable(GL_TEXTURE_GEN_R);

	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_Q, GL_EYE_PLANE, m_textureMatrix.GetRow(3).value);
	glEnable(GL_TEXTURE_GEN_Q);

	glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture);
	glEnable(GL_TEXTURE_2D);
	


	//Enable shadow comparison
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

	//Shadow comparison should be true (ie not in shadow) if r<=texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

	//Shadow comparison should generate an INTENSITY result
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

	//Set alpha test to discard false comparisons
	glAlphaFunc(GL_GEQUAL, 0.99f);
	glEnable(GL_ALPHA_TEST);

	

}
void CShadowMap::Clean()
{
	//disable multitexturing
	glDisable(GL_TEXTURE_2D);




	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);

	//Restore other states
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);


}
unsigned int CShadowMap::getShadowMap()
{
	return m_shadowMapTexture;
}
CShadowMap::~CShadowMap()
{
	delete m_cam;

}