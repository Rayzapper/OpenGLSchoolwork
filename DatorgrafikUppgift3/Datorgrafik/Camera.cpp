#include "Camera.h"



Camera::Camera()
{
	up.assign(0, 1, 0);
	right.assign(1, 0, 0);
	forward.assign(0, 0, -1);

	targetDistance = 50;
	position.assign(0, 5, 50);
	target.assign(position + forward * targetDistance);
}



void Camera::movePosition(float distanceX, float distanceY, float distanceZ)
{
	Vector3f direction(distanceX, distanceY, distanceZ);
	position += direction;
}



void Camera::moveTarget(float distanceX, float distanceY, float distanceZ)
{
	Vector3f direction(distanceX, distanceY, distanceZ);
	target += direction;
}



void Camera::strafeRight(float distance)
{
	position += right * distance;
	target += right * distance;
}



void Camera::strafeUp(float distance)
{
	position += up * distance;
	target += up * distance;
}



void Camera::strafeForward(float distance)
{
	position += forward * distance;
	target += forward * distance;
}



void Camera::tumbleYaw(float angle)
{
	Quaternionf rotation((angle * PIdiv180), up);
	right = rotation.matrix() * right;
	forward = rotation.matrix() * forward;

	target = position + forward * targetDistance;
}



void Camera::tumblePitch(float angle)
{
	Quaternionf rotation((angle * PIdiv180), right);
	forward = rotation.matrix() * forward;
	up = rotation.matrix() * up;

	target = position + forward * targetDistance;
}



void Camera::orbitYaw(float angle)
{
	Quaternionf rotation((angle * PIdiv180), up);
	right = rotation.matrix() * right;
	forward = rotation.matrix() * forward;

	position = target - forward * targetDistance;
}



void Camera::orbitPitch(float angle)
{
	Quaternionf rotation((angle * PIdiv180), right);
	forward = rotation.matrix() * forward;
	up = rotation.matrix() * up;

	position = target - forward * targetDistance;
}



void Camera::roll(float angle)
{
	Quaternionf rotation((angle * PIdiv180), forward);
	up = rotation.matrix() * up;
	right = rotation.matrix() * right;

	target = position + forward * targetDistance;
}



void Camera::lookAt()
{	
	gluLookAt(
		position.x(), position.y(), position.z(), 
		target.x(), target.y(), target.z(), 
		up.x(), up.y(), up.z()
	);	
}



Vector3f Camera::GetCamPos(){ return position; }		// Hjälpfunktioner för att hämta kameraposition och kameramål.

Vector3f Camera::GetTarPos(){ return target; }