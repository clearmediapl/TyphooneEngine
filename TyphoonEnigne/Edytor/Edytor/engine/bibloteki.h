#ifndef _LIBRARIES_H_
#define _LIBRARIES_H_


#ifdef UNICODE
#define _T(x) L##x
#else
#define _T(x) x
#endif

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <gl\glext.h>



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <io.h>
#include <time.h>
#include <cstdio>
#include <mmsystem.h>
#include <iostream>
#include <fstream>
//#include <bass.h>


#include <fcntl.h>

struct TPoint3f
{
	float x;
	float y;
	float z;
};

#endif