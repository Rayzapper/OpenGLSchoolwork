#include "Support.h"
#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif



// Data som delas mellan programmets olika delar
struct Shared
{
	float time;
	bool pause;
	float distance, distanceDelta;
	GLUquadric *quadric;
	GLuint sunTexture, planetTexture, gasPlanetTexture, gasPlanetTexture2, moonTexture1,
		moonTexture2, earthPlanetTexture, earthCloudTexture, ringsTexture;
};

struct Shared shared;



// Vår egen underfunktion som initierar det som behövs innan renderingen börjar
void initialize()
{
	shared.time = 0;
	shared.pause = false;
	shared.distance = 50;
	shared.distanceDelta = 0;

	shared.quadric = gluNewQuadric();
	gluQuadricTexture(shared.quadric, true);

	loadTexture("Sun.png", &shared.sunTexture);
	loadTexture("RockyPlanet2.png", &shared.planetTexture);			// Jag laddar alla texturer.
	loadTexture("GasPlanet1.png", &shared.gasPlanetTexture);
	loadTexture("GasPlanet2.png", &shared.gasPlanetTexture2);
	loadTexture("RockyPlanet1.png", &shared.moonTexture1);
	loadTexture("Earth.png", &shared.earthPlanetTexture);
	loadTexture("EarthClouds.png", &shared.earthCloudTexture);
	loadTexture("RockyPlanet3.png", &shared.moonTexture2);
	loadTexture("Rings.png", &shared.ringsTexture);

	glEnable(GL_DEPTH_TEST);										// Jag ser till att Z-buffern är aktiverad.
	glEnable(GL_COLOR_MATERIAL);									// Jag aktiverar material.
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);		// Definierar material
}



// Vår egen underfunktion som ritar ut scenen
void drawScene()
{
	// Initiala renderingstillstånd
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);								// Jag aktiverar ljussystemet.
	glEnable(GL_LIGHT1);								// Aktiverar ljus med index 1.
	glEnable(GL_BLEND);									// Aktiverar Alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Definierar blending.
	glColor4f(1, 1, 1, 1);
	GLfloat lightColor[] = { 1.0, 1.0, 1.0 };			// Definierar ljus
	GLfloat lightPosition[] = { 0, 0, 0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

	// Rita planet
	glRotatef(shared.time * 50, 0, 1, 0);	// Transformationer till planeten
	glTranslatef(20, 0, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(shared.time * -50, 0, 0, 1);

	glBindTexture(GL_TEXTURE_2D, shared.planetTexture);
	gluSphere(shared.quadric, 3, 32, 32);

	glRotatef(shared.time * 50, 0, 0, 1);	// Jag ogör alla transformationer till planeten efter den har ritats ut.
	glRotatef(-90, 1, 0, 0);
	glTranslatef(-20, 0, 0);
	glRotatef(shared.time * -50, 0, 1, 0);

	// Planet 2
	glPushMatrix();											// Jag använder hierarkiska transformationer

	glRotatef(shared.time * 40, 0, 1, 0);
	glTranslatef(10, 0, 35);

	glPushMatrix();

	glRotatef(shared.time * 20, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, shared.gasPlanetTexture);
	gluSphere(shared.quadric, 5, 32, 32);

	glPopMatrix();

	// Planet 2 Måne 1
	glPushMatrix();

	glRotatef(shared.time * 70, 1, 1, 0);			// Månen roterar 45 grader mot y planet
	glTranslatef(0, 0, 8);
	glRotatef(90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, shared.moonTexture1);
	gluSphere(shared.quadric, 1, 32, 32);

	glPopMatrix();

	// Planet 2 Måne 2
	glPushMatrix();

	glRotatef(shared.time * 20, 1, 0, 0);				// roterar kring x, y och z i olika hastighet
	glRotatef(shared.time * 90, 0, 1, 0);
	glRotatef(shared.time * 60, 0, 0, 1);
	glTranslatef(10, 0, 0);
	glRotatef(90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, shared.moonTexture1);
	gluSphere(shared.quadric, 0.7, 32, 32);

	glPopMatrix();
	glPopMatrix();

	// Planet 3
	glPushMatrix();

	glRotatef(shared.time * 70, 0, 1, 0);
	glTranslatef(0, 0, 55);

	glPushMatrix();

	glRotatef(shared.time * -30, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, shared.earthPlanetTexture);
	gluSphere(shared.quadric, 3, 32, 32);
	glRotatef(shared.time * 40, 0, 0, 1);
	glColor4f(1, 1, 1, 0.5);
	glBindTexture(GL_TEXTURE_2D, shared.earthCloudTexture);		// Moln som roterar mot planetens rotation
	gluSphere(shared.quadric, 3.1, 32, 32);
	glColor4f(1, 1, 1, 1);

	glPopMatrix();

	// Planet 3 Måne
	glRotatef(shared.time * -100, 0, 0, 1);
	glTranslatef(0, 5, 0);
	glRotatef(90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, shared.moonTexture2);
	gluSphere(shared.quadric, 0.8, 32, 32);

	glPopMatrix();

	// Planet 4
	glPushMatrix();

	glRotatef(shared.time * 40, 0, 1, 0);
	glTranslatef(-40, 0, -75);

	glPushMatrix();

	glRotatef(shared.time * -30, 0, 1, 0);
	glScalef(1, 1.2, 1);					// Jag använder en skalnings transformation i y ledet.
	glRotatef(90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, shared.gasPlanetTexture2);
	gluSphere(shared.quadric, 6, 32, 32);

	glPopMatrix();

	// Planet 4 Måne
	glPushMatrix();

	glRotatef(shared.time * 70, 0, 1, 0);
	glTranslatef(0, 0, 8);
	glRotatef(90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, shared.moonTexture1);
	gluSphere(shared.quadric, 1, 32, 32);

	glPopMatrix();

	// Planet 4 Ringar
	glDisable(GL_LIGHT1);	// Jag avaktiverar ljuset.
	glBindTexture(GL_TEXTURE_2D, shared.ringsTexture);	// Jag binder en textur till en kvadrat som spinner runt planeten
	glRotatef(shared.time * -30, 0, 1, 0);
	glBegin(GL_QUADS);

	// Toppen
	glTexCoord2f(0, 0);
	glVertex3f(-20.0, 0, -20.0);
	glTexCoord2f(1.0, 0);
	glVertex3f(-20.0, 0, 20.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(20.0, 0, 20.0);
	glTexCoord2f(0, 1.0);
	glVertex3f(20.0, 0, -20.0);

	// Botten
	glTexCoord2f(0, 0);
	glVertex3f(-20.0, 0, -20.0);
	glTexCoord2f(1.0, 0);
	glVertex3f(20.0, 0, -20.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(20.0, 0, 20.0);
	glTexCoord2f(0, 1.0);
	glVertex3f(-20.0, 0, 20.0);

	glEnd();

	glPopMatrix();

	// Rita solen (sist)
	drawSun(shared.sunTexture);
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
	case '1':
		shared.distanceDelta = 1;
		break;
	case '4':
		shared.distanceDelta = -1;
		break;
	}
}



// GLUT-hanterad funktion som anropas varje gång en tangent släpps upp
void keyboardUp(unsigned char key, int x, int y)
{
	switch(key)
	{
	case '1':
	case '4':
		shared.distanceDelta = 0;
		break;
	}
}



// GLUT-hanterad funktion som anropas efter att en angiven tid har löpt ut (ofta kallad timer)
void timer(int timeout)
{
	glutTimerFunc(timeout, timer, timeout);   // Vi måste starta om timern varje gång

	if(!shared.pause)
		shared.time += 0.01f;

	shared.distance += shared.distanceDelta;
}



// GLUT-hanterad funktion som anropas en gång för varje bildruta (frame)
void display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Vi vill rensa både skärmbuffert och z-buffert

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 10, shared.distance, 0, 0, 0, 0, 1, 0);   // Roterar kameran kring origo genom att skapa en ny vymatris varje bildruta

	drawScene();

	glutSwapBuffers();
}



// GLUT-hanterad funktion som anropas en gång när fönstret öppnas och sedan varje gång fönstret förstoras eller förminskas
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, float(width) / float(height), 0.1f, 500.0f);   // Skapar en projektionsmatris
}



// GLUT-hanterad funktion som anropas när ingen händelse (tangentbord, utritning etc) sker 
void idle()
{
	glutPostRedisplay();
}



// Startpunkt för programmet
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);   // Vi vill ha dubbelbuffring och z-buffert (depth buffer)
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
	glutMainLoop();

	return 0;
}
