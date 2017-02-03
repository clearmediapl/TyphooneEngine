/*******************************************************************/
/* Filename:                  CPlayer.h                           */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         09.08.2006                           */
/* Last revision:             27.07.2006                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/

#include "bibloteki.h"
#include "CVector.h"
#include "CLwo.h"

class CPlayer
{
public:

	
	CVector m_pos; //position of player
	CLwo *m_icon; 


public:
	CPlayer();
	~CPlayer();

	void SetPosition(CVector pos);
	
	void Init();
	void Render();
	

};
