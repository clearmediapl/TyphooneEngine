// create by bojkar

#ifndef _CEXTENSION_H_
#define _CEXTENSION_H_


#include "bibloteki.h"

//arb_shadow
#define GL_TEXTURE_COMPARE_MODE_ARB                        0x884C
#define GL_TEXTURE_COMPARE_FUNC_ARB                        0x884D
#define GL_COMPARE_R_TO_TEXTURE_ARB                        0x884E

//arb_depth_texture
#define GL_DEPTH_COMPONENT16_ARB                           0x81A5
#define GL_DEPTH_COMPONENT24_ARB                           0x81A6
#define GL_DEPTH_COMPONENT32_ARB                           0x81A7
#define GL_TEXTURE_DEPTH_SIZE_ARB                          0x884A
#define GL_DEPTH_TEXTURE_MODE_ARB                          0x884B




class CExtension 
{
protected:
	//multiteturing
	PFNGLMULTITEXCOORD2FARBPROC		glMultiTexCoord2fARB;
	PFNGLACTIVETEXTUREARBPROC		glActiveTextureARB;
	PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;

	//vertex buffor object
	PFNGLBINDBUFFERARBPROC glBindBufferARB;
	PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB ;
	PFNGLGENBUFFERSARBPROC glGenBuffersARB ;
	PFNGLBUFFERDATAARBPROC glBufferDataARB;
	PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB;

	//point_sprites
	PFNGLPOINTPARAMETERFARBPROC  glPointParameterfARB;
	PFNGLPOINTPARAMETERFVARBPROC glPointParameterfvARB;


public:
	CExtension();
	~CExtension();

	bool IsExtensionSupported( char* szTargetExtension );

	bool EXT_EnableVBO();
	bool EXT_EnableARB_Shadow();
	bool EXT_EnableARB_Point_Sprites();
	bool EXT_EnableARB_Depth_Texture();
	bool EXT_EnableARB_Multitexturing();

};

#endif