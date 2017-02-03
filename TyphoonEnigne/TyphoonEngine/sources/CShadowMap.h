#include "bibloteki.h"
#include "CExtension.h"
#include "CMatrix.h"
#include "CCamera.h"

class  CShadowMap : public CExtension
{
protected:
	int m_shadowMapSize;
	GLuint m_shadowMapTexture;

	CMatrix lightProjectionMatrix;
	CMatrix lightViewMatrix;
	CMatrix cameraProjectionMatrix;
	CMatrix cameraViewMatrix;
//	CMatrix m_textureMatrix;

private:
	


	CCamera *m_cam; // camera position
	CVector m_lightPos; // light pos



public:
	void InitShadows();
	void DrawFromLight();
	void DrawFromCamera();
	void ProjectShadows();
	void Clean();



	void GetCameraPos(CCamera *cam);
	void SetLightPos(float x, float y, float z);
	unsigned int getShadowMap();

	CShadowMap();
	~CShadowMap();


};