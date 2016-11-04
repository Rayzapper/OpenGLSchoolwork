#ifndef SUPPORT_H
#define SUPPORT_H



#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <windows.h>
#include <GL/gl.h>
#endif



void loadTexture(const char *file, GLuint *image);
void drawSun(GLuint texture);



#endif
