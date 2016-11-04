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
};

struct Shared shared;



// V�r egen underfunktion som initierar det som beh�vs innan renderingen b�rjar
void initialize()
{
	shared.time = 0;
	shared.pause = false;
}



// V�r egen underfunktion som ritar ut ett golv
void drawFloor()
{
	glPolygonMode(GL_FRONT, GL_LINE);		// Definierar hur primitiv ska rasteriseras
	glPolygonMode(GL_BACK, GL_LINE);

	glColor3f(0, 0, 0);		// Definierar en f�rg som primitiverna ska ritas ut i (detta fall floats) med RGB

	glBegin(GL_QUADS);		// Definierar vilken sorts primitiv som ska ritas ut mellan glBegin och glEnd (fyrkanter h�r)
	glVertex3f(10, -10, 10);	// Definierar punkter som en primitiv ska ritas mellan
	glVertex3f(10, -10, -10);
	glVertex3f(-10, -10, -10);
	glVertex3f(-10, -10, 10);
	glEnd();
}



// GLUT-hanterad funktion som anropas varje g�ng en tangent trycks ned
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:   // Esc-tangenten
		exit(0);   // Ett abrupt slut beh�vs eftersom vi anv�nder GLUT
		break;
	case 'p':
		shared.pause = !shared.pause;
		break;
	}
}



// GLUT-hanterad funktion som anropas efter att en angiven tid har l�pt ut (ofta kallad timer)
void timer(int timeout)
{
	glutTimerFunc(timeout, timer, timeout);   // Vi m�ste starta om timern varje g�ng

	if (!shared.pause)
		shared.time += 0.01f;
}

// GLUT-hanterad funktion som anropas en g�ng f�r varje bildruta (frame)
void display()
{
	glClearColor(1, 1, 1, 1);	// Definierar bakgrundsf�rgen med RGB och alpha
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Vi vill rensa b�de sk�rmbufferten och z-bufferten
	// Rensar buffrar och s�tter bakgrundsf�rgen

	glMatrixMode(GL_MODELVIEW);	// Best�mmer den nuvarande matrisen som matrisoperationer hanterar
	glLoadIdentity();	// Byter ut den nuvarande matrisen till identitetmatrisen
	gluLookAt(cos(shared.time) * 40, 10, sin(shared.time) * 40, 0, 0, 0, 0, 1, 0);   // Roterar kameran kring origo genom att skapa en ny vymatris varje bildruta
	
	drawFloor();

	glutSwapBuffers();
}



// GLUT-hanterad funktion som anropas en g�ng n�r f�nstret �ppnas och sedan varje g�ng f�nstret f�rstoras eller f�rminskas
void reshape(int width, int height)
{
	glViewport(0, 0, width, height); // Definierar positionen och storleken p� vyporten

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, float(width) / float(height), 0.1f, 100.0f);   // Skapar en projektionsmatris
}



// GLUT-hanterad funktion som anropas n�r ingen h�ndelse (tangentbord, utritning etc) sker 
void idle()
{
	glutPostRedisplay();
}



// Startpunkt f�r programmet
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);   // Vi vill ha dubbelbuffring och z-buffert (depth buffer)
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Datorgrafik");

	initialize();

	glutTimerFunc(1000 / 60, timer, 1000 / 60);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
