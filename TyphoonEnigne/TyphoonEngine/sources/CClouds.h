#include "bibloteki.h"


class CTexture;
class CLwo;
class CCamera;

class CClouds
{
private:
	unsigned int texture[2]; //textures
	CTexture *backTex;       //background texture

	CLwo *obj;               //sky object 
	CCamera *camera;         //camera 

	TCHAR path1[64];         //path of first texture
	TCHAR path2[64];         //path of second texture
 
	
	float s,t; 

	FILE *openClouds;
	FILE *saveClouds;
public:
	float scale;             //scale
	float speed;             //speed of clouds
	TPoint3f size;           //size of clouds
	float height;            //height of sky
	float brightness;
	float backgroundBrightness;
	
public:
	CTexture *tex;           //


	CClouds();
	~CClouds();
		
			float alpha;


	void SetScale(float value);
	void SetSize(float x, float y, float z);
	void SetSpeed(int value);
	void SetHeight(float value);
	void SetAlpha(float value);
	void SetCamera(CCamera *cam);
	void SetBrightness(float value); // from 0 to 255
	void SetBackgroundBrightness(float value); // from 0 to 255
	void SetTexture1(TCHAR *path);
	void SetTexture2(TCHAR *path);

	void SaveClouds(const TCHAR *path);
	void LoadClouds(const TCHAR *path);


	void Init();
	void Render();
	void Update();

};