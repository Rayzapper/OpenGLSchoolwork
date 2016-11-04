#include "Support.h"
#include <stdlib.h>
#include <iostream>
#ifdef __APPLE__
#include <ApplicationServices/ApplicationServices.h>
#else
#include <IL/il.h>
#endif



#ifdef __APPLE__
void loadTexture(const char *file, GLuint *image)
{
	glGenTextures(1, image);

	CFBundleRef mainBundle = CFBundleGetMainBundle();
	
	CFStringRef name = CFStringCreateWithCString(NULL, file, kCFStringEncodingUTF8);
	CFURLRef url = CFBundleCopyResourceURL(mainBundle, name, NULL, NULL);
	CFRelease(name);
	if(!url)
	{
		std::cout << "Load error: " << file << std::endl;
		return;
	}
	
	CGImageSourceRef imageSourceRef = CGImageSourceCreateWithURL(url, NULL);
	CFRelease(url);
	CGImageRef imageRef = CGImageSourceCreateImageAtIndex(imageSourceRef, 0, NULL);

	CFDataRef data = CGDataProviderCopyData(CGImageGetDataProvider(imageRef));
	void *imageData = (void*)CFDataGetBytePtr(data);
	
	glBindTexture(GL_TEXTURE_2D, *image);
	
	if(CGImageGetBitsPerPixel(imageRef) == 32)
		glTexImage2D(GL_TEXTURE_2D, 0, 4, CGImageGetWidth(imageRef), CGImageGetHeight(imageRef), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, 4, CGImageGetWidth(imageRef), CGImageGetHeight(imageRef), 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	CFRelease(imageRef);
	CFRelease(data);
}
#else
void loadTexture(const char *file, GLuint *image)
{
	ilInit();

	ILuint ilImage;
	ilGenImages(1, &ilImage);
	ilBindImage(ilImage);

	wchar_t fileW[256];
	mbstowcs_s(NULL, fileW, sizeof(fileW) / 2, file, _TRUNCATE);

	if(!ilLoadImage(fileW))
	{
		MessageBox(NULL, fileW, L"Load error", MB_OK);
		exit(0);
	}

	if(!ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
	{
		MessageBox(NULL, fileW, L"Convert error", MB_OK);
		exit(0);
	}

	glGenTextures(1, image);
	glBindTexture(GL_TEXTURE_2D, *image);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	ilDeleteImages(1, &ilImage);
}
#endif



void drawFloor(GLuint texture)
{	
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture); 
	
	glColor3f(1, 1, 1);
	
	glBegin(GL_QUADS);
	glTexCoord2f(8, 8);
	glVertex3f(25,-10,25);
	
	glTexCoord2f(8, 0.0);
	glVertex3f(25,-10,-25);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-25,-10,-25);
	
	glTexCoord2f(0.0, 8);
	glVertex3f(-25,-10,25);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
}



void drawPillar(GLuint texture)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT, GL_FILL);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glColor3f(1, 1, 1);
	
	glBegin(GL_QUADS);
	// Botten
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1,-10,1);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1,-10,-1);
	
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1,-10,-1);
	
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1,-10,1);
	
	// Toppen
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1,6,1);
	
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1,6,-1);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1,6,-1);
	
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1,6,1);
	
	// Yta 3
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1,-10,1);
	
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1,-10,-1);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1,6,-1);
	
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1,6,1);
	
	// Yta 4
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1,6,1);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1,6,-1);
	
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-1,-10,-1);
	
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1,-10,1);
	
	// Yta 5
	glColor3f(0.9f,0.9f,0.8f);
	
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1,6,1);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1,6,1);
	
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-1,-10,1);
	
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1,-10,1);
	
	// Yta 6
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1,-10,-1);
	
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-1,-10,-1);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1,6,-1);
	
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1,6,-1);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}



void drawPillars(GLuint texture)
{
	glPushMatrix();
	glTranslatef(-7, 0, -7);
	drawPillar(texture);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(7, 0, 7);
	drawPillar(texture);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-7, 0, 7);
	drawPillar(texture);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(7, 0, -7);
	drawPillar(texture);
	glPopMatrix();
}

// Arrayer som jag använder till diamantobjektet
GLfloat diamondVertices[] =
{
	0, -1, 0,
	1, 0, 0,
	-1, 0, 0,
	0, 0, 1,
	0, 0, -1,
	0, 1, 0,
};
GLubyte diamondIndices[] =
{
	0, 1, 4,  0, 4, 2,  0, 2, 3,  0, 3, 1,
	5, 4, 1,  5, 2, 4,  5, 3, 2,  5, 1, 3
};
GLfloat diamondColors[] =
{
	0, 0, 0,
	1, 0, 0,
	1, 0, 0,
	0, 0, 1,
	0, 0, 1,
	0, 0, 0
};

void drawDiamond()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, diamondColors);
	glVertexPointer(3, GL_FLOAT, 0, diamondVertices);

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_BYTE, diamondIndices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

// Arrayer som jag använder till kubobjektet
GLfloat boxVertices[] =
{
	1, -1, 1,
	1, 1, 1,
	1, 1, -1,
	1, -1, -1,
	-1, -1, -1,
	-1, 1, -1,
	-1, 1, 1,
	-1, -1, 1,
};
GLubyte boxIndices[] =
{
	2, 0, 1, 3, 0, 2,
	5, 3, 2, 4, 3, 5,
	4, 5, 6, 4, 6, 7,
	1, 7, 6, 0, 7, 1,
	0, 3, 4, 0, 4, 7,
	1, 2, 6, 2, 6, 5
};
GLfloat boxColors[] =
{
	1, 1, 0,
	1, 0, 0,
	0, 1, 0,
	0, 0, 1,
	1, 0, 0,
	1, 1, 0,
	0, 0, 1,
	0, 1, 0
};

void drawBox()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, boxColors);
	glVertexPointer(3, GL_FLOAT, 0, boxVertices);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, boxIndices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}