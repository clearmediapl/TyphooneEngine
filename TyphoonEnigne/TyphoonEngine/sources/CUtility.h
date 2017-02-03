/*******************************************************************/
/* Filename:                  CUtility.h                           */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         20.05.2006                           */
/* Last revision:             20.05.2006                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/
#ifndef _CUTILITY_H_
#define _CUTILITY_H_


#include "bibloteki.h"

class CUtility
{
private:

public:
	CUtility();
	~CUtility();

	TCHAR *AnsiToUnicode(char *src);
	char *UnicodeToAnsi(TCHAR *src);



	

};
#endif
