#include "Support.h"
#include "Camera.h"
#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <ApplicationServices/ApplicationServices.h>
#else
#include <glut.h>
#endif



// Data som delas mellan programmets olika delar
struct Shared
{
	float time;
	bool pause;
	bool mouseWarped;
	GLuint floorTexture, pillarTexture;
	Camera camera;
	bool tumble = true;				// en bool för att byta mellan tumble och orbit.
	bool roll = false;				// en bool som aktiverar roll.
	bool viewports = false;			// en bool som aktiverar viewports.
	int screenWidth, screenHeight;	// Jag använder ett par ints för att spara fönsterstorleken.
	bool cameraBall = false;		// en bool som aktiverar kamerabollen och målbollen.
	GLUquadric *quadric;			// Jag tog den här från uppgift 2 för att rita svärer.
};

struct Shared shared;



// Vår egen underfunktion som initierar det som behövs innan renderingen börjar
void initialize()
{
	shared.time = 0;
	shared.pause = false;
	shared.mouseWarped = false;

	shared.quadric = gluNewQuadric();
	gluQuadricTexture(shared.quadric, true);

	loadTexture("Floor.png", &shared.floorTexture);
	loadTexture("Pillar.png", &shared.pillarTexture);
}



// Vår egen underfunktion som ritar ut scenen
void drawScene()
{
	// Initiala renderingstillstånd
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPolygonMode(GL_FRONT, GL_FILL);

	// Rita golv och pelare
	drawFloor(shared.floorTexture);
	drawPillars(shared.pillarTexture);

	// Rita referensobjekt
	glPushMatrix();														// Jag ritar ut två referensobjekt med diverse transformationer.
	glTranslatef(sin(shared.time) * 10, sin(shared.time * 4) * 4, 0);
	glRotatef(shared.time * 100, 1, 0, 0);
	drawDiamond();
	glPopMatrix();

	glPushMatrix();
	glRotatef(shared.time * -40, 0, 1, 0);
	glTranslatef(14, 0, 0);
	glRotatef(shared.time * 40, 0, 1, 0);
	drawBox();
	glPopMatrix();

	// Rita kameraboll, målboll och linje
	if (shared.cameraBall)
	{
		glPushMatrix();									// Jag ritar ut två bollar med samma positioner som
														// kameran och kameramålet. Jag ritar också ut en linje mellan dem.
		glColor3f(1, 0, 0);
		Vector3f camPos = shared.camera.GetCamPos();
		float cX = camPos.x();
		float cY = camPos.y();
		float cZ = camPos.z();
		glTranslatef(cX, cY, cZ);
		gluSphere(shared.quadric, 1, 32, 32);

		glPopMatrix();

		glPushMatrix();

		glColor3f(0, 0, 1);
		Vector3f tarPos = shared.camera.GetTarPos();
		float tX = tarPos.x();
		float tY = tarPos.y();
		float tZ = tarPos.z();
		glTranslatef(tX, tY, tZ);
		gluSphere(shared.quadric, 0.5, 32, 32);

		glPopMatrix();

		glColor3f(0, 1, 0);
		glBegin(GL_LINES);
		glVertex3f(cX, cY, cZ);
		glVertex3f(tX, tY, tZ);
		glEnd();
	}
}



// GLUT-hanterad funktion som anropas varje gång en tangent trycks ned
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:   // Esc-tangenten
		exit(0);   // Ett abrupt slut behövs eftersom vi använder GLUT
		break;
	case 'p':
		shared.pause = !shared.pause;
		break;
	case 'r':								// håll r för att aktivera roll.
		shared.roll = true;
		break;
	case 'z':								// z för att byta mellan toggle och orbit.
		shared.tumble = !shared.tumble;
		break;
	case 'w':								//wasd, x och spacebar kontrollerar strafe
		shared.camera.strafeForward(1);
		break;
	case 'a':
		shared.camera.strafeRight(-1);
		break;
	case 's':
		shared.camera.strafeForward(-1);
		break;
	case 'd':
		shared.camera.strafeRight(1);
		break;
	case 32:
		shared.camera.strafeUp(1);
		break;
	case 'x':
		shared.camera.strafeUp(-1);
		break;
	case 'h':									// Dessa knappar kan flytta runt kameran och kameramålet i alla axlar.
		shared.camera.movePosition(1, 0, 0);
		shared.camera.moveTarget(1, 0, 0);
		break;
	case 'j':
		shared.camera.movePosition(-1, 0, 0);
		shared.camera.moveTarget(-1, 0, 0);
		break;
	case 'y':
		shared.camera.movePosition(0, 1, 0);
		shared.camera.moveTarget(0, 1, 0);
		break;
	case 'u':
		shared.camera.movePosition(0, -1, 0);
		shared.camera.moveTarget(0, -1, 0);
		break;
	case 'n':
		shared.camera.movePosition(0, 0, 1);
		shared.camera.moveTarget(0, 0, 1);
		break;
	case 'm':
		shared.camera.movePosition(0, 0, -1);
		shared.camera.moveTarget(0, 0, -1);
		break;
	case 'c':									// c togglar mellan vyporterna.
		shared.viewports = !shared.viewports;
		break;
	}
}



// GLUT-hanterad funktion som anropas varje gång en tangent släpps upp
void keyboardUp(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'r':
		shared.roll = false;
		break;
	}
}



// GLUT-hanterad funktion som anropas efter att en angiven tid har löpt ut (ofta kallad timer)
void timer(int timeout)
{
	glutTimerFunc(timeout, timer, timeout);   // Vi måste starta om timern varje gång

	if(!shared.pause)
	{
		shared.time += 0.01f;
	}
}



// GLUT-hanterad funktion som anropas en gång för varje bildruta (frame)
void display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   // Vi vill rensa både skärmbuffert och z-buffert

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	shared.camera.lookAt();   // Skapar vymatris via kameraklassen
	if (!shared.viewports)													// En vanlig vyport
	{
		glViewport(0, 0, shared.screenWidth, shared.screenHeight);
		drawScene();
	}
	else
	{
		glViewport(0, 0, shared.screenWidth / 2, shared.screenHeight / 2);					// fyra vyportar
		drawScene();
		glLoadIdentity();
		shared.cameraBall = true;
		gluLookAt(50, 5, 0, 0, 0, 0, 0, 1, 0);
		glViewport(0, shared.screenHeight / 2, shared.screenWidth / 2, shared.screenHeight / 2);
		drawScene();
		glLoadIdentity();
		gluLookAt(0, 50, 0, 0, 0, 0, 0, 0, 1);
		glViewport(shared.screenWidth / 2, 0, shared.screenWidth / 2, shared.screenHeight / 2);
		drawScene();
		glLoadIdentity();
		gluLookAt(0, 5, 50, 0, 0, 0, 0, 1, 0);
		glViewport(shared.screenWidth / 2, shared.screenHeight / 2, shared.screenWidth / 2, shared.screenHeight / 2);
		drawScene();
		shared.cameraBall = false;
	}

	glutSwapBuffers();
}



// GLUT-hanterad funktion som anropas en gång n‰r fönstret öppnas och sedan varje gång fönstret förstoras eller förminskas
void reshape(int width, int height)
{
	shared.screenWidth = width;
	shared.screenHeight = height;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, float(width) / float(height), 0.1f, 100.0f);   // Skapar en projektionsmatris
}



// GLUT-hanterad funktion som anropas när ingen händelse (tangentbord, utritning etc) sker 
void idle()
{
	glutPostRedisplay();
}



// GLUT-hanterad funktion som anropas när muspekaren flyttas
void passiveMotion(int x, int y)
{
	if(shared.mouseWarped)
	{
		shared.mouseWarped = false;
	}
	else
	{
		int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
		int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
		float scale = 0.3f;
		float deltaX = float(x - centerX) * scale;
		float deltaY = float(y - centerY) * scale;
		
		glutWarpPointer(centerX, centerY);
		shared.mouseWarped = true;
		if (!shared.roll)
		{
			if (shared.tumble)							// Kontrollerar kamera rörelserna
			{
				shared.camera.tumbleYaw(-deltaX);
				shared.camera.tumblePitch(-deltaY);
			}
			else
			{
				shared.camera.orbitYaw(-deltaX);
				shared.camera.orbitPitch(-deltaY);
			}
		}
		else
		{
			shared.camera.roll(deltaX);
		}
	}
}



// Startpunkt för programmet
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);   // Vi vill ha dubbelbuffring och z-buffert (depth buffer)
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Datorgrafik");

	initialize();

	glutTimerFunc(1000/60, timer, 1000/60);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	#ifdef __APPLE__
	CGSetLocalEventsSuppressionInterval(0);
	#endif
	glutPassiveMotionFunc(passiveMotion);
	
	glutMainLoop();

	return 0;
}
