#include "CExtension.h"

// ---------------------------------------------------------
// CExtension::CExtension()
// constructor
// ---------------------------------------------------------
//
CExtension::CExtension() 
{
	//multitexturing
	glMultiTexCoord2fARB=NULL;
	glActiveTextureARB=NULL;

	//vbo
	 glBindBufferARB = NULL;
	 glDeleteBuffersARB = NULL ;
	 glGenBuffersARB = NULL ;
	 glBufferDataARB = NULL;
     glGetBufferParameterivARB = NULL;
	 glClientActiveTextureARB = NULL;

	 //point sprites
	 glPointParameterfARB  = NULL;
	 glPointParameterfvARB = NULL;
}
// ---------------------------------------------------------
// CExtension::IsExtensionSupported(char *szTargetExtension)
// 
// ---------------------------------------------------------
//
bool CExtension::IsExtensionSupported(char *szTargetExtension)
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
// ---------------------------------------------------------
// CExtension::EXT_EnableVBO()
// 
// ---------------------------------------------------------
//
bool CExtension::EXT_EnableVBO()
{
	if (IsExtensionSupported("GL_ARB_vertex_buffer_object"))
	{
		glBindBufferARB = (PFNGLBINDBUFFERARBPROC)wglGetProcAddress("glBindBufferARB");
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)wglGetProcAddress("glDeleteBuffersARB");
		glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");
	    glBufferDataARB = (PFNGLBUFFERDATAARBPROC)wglGetProcAddress("glBufferDataARB");
		glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC)wglGetProcAddress("glGetBufferParameterivARB");
		return TRUE;
	}
	else
	{
		MessageBox(NULL,_T("GL_ARB_vertex_buffer_object extension was not found"),_T("Extension error"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
}
// ---------------------------------------------------------
// CExtension::EXT_EnableARB_Multitexturing()
// 
// ---------------------------------------------------------
//
bool CExtension::EXT_EnableARB_Multitexturing()
{
	//if (IsExtensionSupported("GL_ARBmultitexture"))
//	{
	  glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)		wglGetProcAddress("glActiveTextureARB");
	  glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)		wglGetProcAddress("glMultiTexCoord2fARB");
	  glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC) wglGetProcAddress("glClientActiveTextureARB");
	  return TRUE;
/*	}
	else
		return FALSE;*/


}
// ---------------------------------------------------------
// CExtension::EXT_EnableARB_Shadow()
// 
// ---------------------------------------------------------
//
bool CExtension::EXT_EnableARB_Shadow()
{
	if(IsExtensionSupported("GL_ARB_shadow"))
	{

		return TRUE;
	}
	else
	{
		MessageBox(NULL,_T("GL_ARB_shadow extension was not found"),_T("Extension error"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
}
// ---------------------------------------------------------
// CExtension::EXT_EnableARB_Depth_Texture()
// 
// ---------------------------------------------------------
//
bool CExtension::EXT_EnableARB_Depth_Texture()
{
	if(IsExtensionSupported("GL_ARB_depth_texture"))
	{
		return TRUE;
	}
	else
	{
		MessageBox(NULL,_T("GL_ARB_depth_texture extension was not found"),_T("Extension error"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
}
// ---------------------------------------------------------
// CExtension::EXT_EnableARB_Point_Sprites()()
// 
// ---------------------------------------------------------
//
bool CExtension::EXT_EnableARB_Point_Sprites()
{
	if(IsExtensionSupported("GL_ARB_point_parameters"))
	{
		glPointParameterfARB  = (PFNGLPOINTPARAMETERFARBPROC)wglGetProcAddress("glPointParameterfARB");
        glPointParameterfvARB = (PFNGLPOINTPARAMETERFVARBPROC)wglGetProcAddress("glPointParameterfvARB");

		return TRUE;
	}
	else
	{
		MessageBox(NULL,_T("GL_ARB_point_parameters extension was not found"),_T("Extension error"),MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
}
// ---------------------------------------------------------
// CExtension::~CExtension()
// destructor
// ---------------------------------------------------------
//
CExtension::~CExtension()
{
  

}