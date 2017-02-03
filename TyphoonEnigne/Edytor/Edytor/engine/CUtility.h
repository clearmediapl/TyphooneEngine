/*******************************************************************/
/* Filename:                  CUtility.h                           */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         20.05.2006                           */
/* Last revision:             20.05.2006                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/
#include "bibloteki.h"

class CUtility
{
private:

public:

	TCHAR *AnsiToUnicode(char *src);
	char *UnicodeToAnsi(TCHAR *src);

	bool IsExtensionSupported( char* szTargetExtension );


	CUtility();
	~CUtility();

};