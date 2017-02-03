/*******************************************************************/
/* Filename:                  CTexture.h                           */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         17.10.2004                           */
/* Last revision:             17.10.2004                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/

#include <olectl.h>	
#ifndef _CTEXTURE_H_
#define _CTEXTURE_H_


#define TGA_RGB		 2		// This tells us it's a normal RGB (really BGR) file
#define TGA_A		 3		// This tells us it's a ALPHA file
#define TGA_RLE		10		// This tells us that the targa is Run-Length Encoded (RLE)

struct tImageTGA
{
	int channels;			// The channels in the image (3 = RGB : 4 = RGBA)
	int sizeX;				// The width of the image in pixels
	int sizeY;				// The height of the image in pixels
	unsigned char *data;	// The image pixel data
};
struct tImageJPG
{
											// Holds The Bitmap Temporarily
	IPicture	*pPicture;	

};

class CTexture
{
private:
			tImageJPG *test;

public:
	CTexture();
	bool defaultPath;

	int LoadJPG(const TCHAR *szPathName, GLuint &texid);
	tImageTGA *LoadTGA(const char *filename);
	void CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID);


	~CTexture();
};

#endif