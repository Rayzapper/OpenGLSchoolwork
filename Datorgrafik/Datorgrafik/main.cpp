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



// Vår egen underfunktion som initierar det som behövs innan renderingen börjar
void initialize()
{
	shared.time = 0;
	shared.pause = false;
}



// Vår egen underfunktion som ritar ut ett golv
void drawFloor()
{
	glPolygonMode(GL_FRONT, GL_LINE);		// Definierar hur primitiv ska rasteriseras
	glPolygonMode(GL_BACK, GL_LINE);

	glColor3f(0, 0, 0);		// Definierar en färg som primitiverna ska ritas ut i (detta fall floats) med RGB

	glBegin(GL_QUADS);		// Definierar vilken sorts primitiv som ska ritas ut mellan glBegin och glEnd (fyrkanter här)
	glVertex3f(10, -10, 10);	// Definierar punkter som en primitiv ska ritas mellan
	glVertex3f(10, -10, -10);
	glVertex3f(-10, -10, -10);
	glVertex3f(-10, -10, 10);
	glEnd();
}



// GLUT-hanterad funktion som anropas varje gång en tangent trycks ned
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:   // Esc-tangenten
		exit(0);   // Ett abrupt slut behövs eftersom vi använder GLUT
		break;
	case 'p':
		shared.pause = !shared.pause;
		break;
	}
}



// GLUT-hanterad funktion som anropas efter att en angiven tid har löpt ut (ofta kallad timer)
void timer(int timeout)
{
	glutTimerFunc(timeout, timer, timeout);   // Vi måste starta om timern varje gång

	if (!shared.pause)
		shared.time += 0.01f;
}

// GLUT-hanterad funktion som anropas en gång för varje bildruta (frame)
void display()
{
	glClearColor(1, 1, 1, 1);	// Definierar bakgrundsfärgen med RGB och alpha
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Vi vill rensa både skärmbufferten och z-bufferten
	// Rensar buffrar och sätter bakgrundsfärgen

	glMatrixMode(GL_MODELVIEW);	// Bestämmer den nuvarande matrisen som matrisoperationer hanterar
	glLoadIdentity();	// Byter ut den nuvarande matrisen till identitetmatrisen
	gluLookAt(cos(shared.time) * 40, 10, sin(shared.time) * 40, 0, 0, 0, 0, 1, 0);   // Roterar kameran kring origo genom att skapa en ny vymatris varje bildruta
	
	drawFloor();

	glutSwapBuffers();
}



// GLUT-hanterad funktion som anropas en gång när fönstret öppnas och sedan varje gång fönstret förstoras eller förminskas
void reshape(int width, int height)
{
	glViewport(0, 0, width, height); // Definierar positionen och storleken på vyporten

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, float(width) / float(height), 0.1f, 100.0f);   // Skapar en projektionsmatris
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

	glutTimerFunc(1000 / 60, timer, 1000 / 60);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
