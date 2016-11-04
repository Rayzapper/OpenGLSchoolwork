#ifndef CAMERA_H
#define CAMERA_H



#include "MathUtils.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif



#define PI 3.1415926535897932384626433832795
#define PIdiv180 (PI/180.0)



class Camera
{
public:
	Camera();

	void movePosition(float distanceX, float distanceY, float distanceZ);
	void moveTarget(float distanceX, float distanceY, float distanceZ);

	void strafeRight(float distance);
	void strafeUp(float distance);
	void strafeForward(float distance);

	void tumbleYaw(float angle);
	void tumblePitch(float angle);

	void orbitYaw(float angle);
	void orbitPitch(float angle);

	void roll(float angle);

	void lookAt();

	Vector3f GetCamPos();		// Hjälpfunktioner för att hämta kameraposition och kameramål.
	Vector3f GetTarPos();

private:
	Vector3f position, target;
	Vector3f right, up, forward;
	float targetDistance;
};



#endif
