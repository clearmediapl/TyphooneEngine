#ifndef _LIBRARIES_H_
#define _LIBRARIES_H_


#ifdef UNICODE
#define _T(x) L##x
#else
#define _T(x) x
#endif



#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Commctrl.h>

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <gl\glext.h>


struct TSize
{
	int width;
	int height;
};

struct TPoint3f
{
	float x;
	float y;
	float z;
};

#endif