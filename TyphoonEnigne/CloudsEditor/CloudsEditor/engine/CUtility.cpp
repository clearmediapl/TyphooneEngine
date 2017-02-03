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
int CUtility::ftoi(float flt)
{
    int i;
    _asm
    {
        mov  eax,flt; //loaded mem to acc
        rcl  eax,1;   //left shift acc to remove the sign
        mov  ebx,eax; //save the acc
        mov  edx,4278190080; //clear reg edx;
        and  eax,edx; //and acc to retrieve the exponent
        shr  eax,24;
        sub  eax,7fh; //subtract 7fh(127) to get the actual power 
        mov  edx,eax; //save acc val power
        mov  eax,ebx; //retrieve from ebx
        rcl  eax,8;     //trim the left 8 bits that contain the power
        mov  ebx,eax; //store
        mov  ecx, 1fh; //subtract 17 h
        sub  ecx,edx; 
        mov  edx,00000000h;
        cmp  ecx,0;
        je   loop2;
        shr  eax,1;
        or   eax,80000000h;        
loop1:    
        shr  eax,1; //shift (total bits - power bits);
        sub  ecx,1;
        add  edx,1;
        cmp  ecx,0;
        ja   loop1;
loop2:  
        mov  i, eax;        
    
//check sign +/-        
sign:
        mov  eax,flt;
        and  eax,80000000h;
        cmp  eax,80000000h;
        je     putsign;
    }

    return i;

putsign:
    return -i;
}
CUtility::~CUtility()
{

}
