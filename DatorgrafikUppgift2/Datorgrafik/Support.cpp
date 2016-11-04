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



void drawSun(GLuint texture)
{
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	float modelview[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
	float right[3];
	float up[3];
	float size = 5;
	right[0] = modelview[0];
	right[1] = modelview[4];
	right[2] = modelview[8];
	up[0] = modelview[1];
	up[1] = modelview[5];
	up[2] = modelview[9];

	glBegin(GL_QUADS);
		glTexCoord2f(0.01f, 0.01f);
		glVertex3f(0-((right[0]+up[0])*size)*3, 0-((right[1]+up[1])*size)*3, 0-((right[2]+up[2])*size)*3);

		glTexCoord2f(0.01f, 0.99f);
		glVertex3f(0+((right[0]-up[0])*size)*3, 0+((right[1]-up[1])*size)*3, 0+((right[2]-up[2])*size)*3);

		glTexCoord2f(0.99f, 0.99f);
		glVertex3f(0+((right[0]+up[0])*size)*3, 0+((right[1]+up[1])*size)*3, 0+((right[2]+up[2])*size)*3);

		glTexCoord2f(0.99f, 0.01f);
		glVertex3f(0-((right[0]-up[0])*size)*3, 0-((right[1]-up[1])*size)*3, 0-((right[2]-up[2])*size)*3);
	glEnd();

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
