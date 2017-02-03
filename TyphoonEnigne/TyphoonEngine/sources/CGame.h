/*******************************************************************/
/* Filename:                  CGame.h                              */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         17.05.2006                           */
/* Last revision:             17.05.2006                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/

#include "CTexture.h"
#include "CLwo.h"
#include "CShadowMap.h"
class CLogger;

class CGame : public CShadowMap
{
private:

	CTexture *tex;
	CLwo *lwo;
		
	float rot;
	float rot2;

	////////////////////
	DWORD time;

public:
	bool keys[256]; //keyboard

	 float MouseX, MouseY;
	 float newMouseX, newMouseY;
	 float oldMouseX, oldMouseY;

	 bool isClicked;


public:
	CLogger *log;

	CGame();
	~CGame();

	void Init();
	void Draw();
	void Update(double frameTime);
	void Kill();
	

};