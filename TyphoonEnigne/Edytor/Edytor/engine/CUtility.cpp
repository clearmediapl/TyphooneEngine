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

bool CUtility::IsExtensionSupported( char* szTargetExtension )
{
	const unsigned char *pszExtensions = NULL;
	const unsigned char *pszStart;
	unsigned char *pszWhere, *pszTerminator;

	// Extension names should not have spaces
	pszWhere = (unsigned char *) strchr( szTargetExtension, ' ' );
	if( pszWhere || *szTargetExtension == '\0' )
		return false;

	// Get Extensions String
	pszExtensions = glGetString( GL_EXTENSIONS );

	// Search The Extensions String For An Exact Copy
	pszStart = pszExtensions;
	for(;;)
	{
		pszWhere = (unsigned char *) strstr( (const char *) pszStart, szTargetExtension );
		if( !pszWhere )
			break;
		pszTerminator = pszWhere + strlen( szTargetExtension );
		if( pszWhere == pszStart || *( pszWhere - 1 ) == ' ' )
			if( *pszTerminator == ' ' || *pszTerminator == '\0' )
				return true;
		pszStart = pszTerminator;
	}
	return false;




}
CUtility::~CUtility()
{

}
