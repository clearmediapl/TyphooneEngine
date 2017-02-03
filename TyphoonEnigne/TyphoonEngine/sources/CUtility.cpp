/*******************************************************************/
/* Filename:                  CUtility.cpp                         */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         20.05.2006                           */
/* Last revision:             20.05.2006                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/
#include "CUtility.h"

CUtility::CUtility()
{

}

TCHAR *CUtility::AnsiToUnicode(char *src)
{
	int size = strlen(src);
	TCHAR *result = new TCHAR[size+1];
	mbstowcs(result, src, size+1);

	return result;
}
char *CUtility::UnicodeToAnsi(TCHAR *src)
{
	char *cPath = new char[255];
	WideCharToMultiByte( CP_ACP, 0, src, -1,
       cPath, 256, NULL, NULL ); //convert UNICODE to ANSI

	return cPath;
}


CUtility::~CUtility()
{

}
