#ifndef _BIBLOTEKI_H_
#define _BIBLOTEKI_H_


#ifdef UNICODE
#define _T(x) L##x
#else
#define _T(x) x
#endif

#define DEGTORAD(x) x* (3.1415 / 180)

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