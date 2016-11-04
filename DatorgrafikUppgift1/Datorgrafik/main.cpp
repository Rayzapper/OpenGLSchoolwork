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
	bool pause;						// Jag lägger till några variabler i Shared som håller reda på några saker.
	bool backfaceCulling = false;	// En bool som kontrollerar Backface Culling.
	bool fill = false;				// En bool som bestämmer polygonläge på diamantobjektet.
	bool transformation = true;		// En bool som bestämmer transformationsläge.
	bool cameraRotation = false;	// En bool som bestämmer kameraläge.
	bool vertArray = true;			// En bool som bestämmer om diamantobjektet ska ritas ut med eller utan en vertex array.
};

struct Point // Hjälpfunktion som skapar en punkt
{
	float x = 0, y = 0, z = 0;
};
void DefinePoint(Point& point, float x, float y, float z) // Funktion som jag använder för att definiera punkter
{
	point.x = x;
	point.y = y;
	point.z = z;
}

struct Shared shared;



// Vår egen underfunktion som initierar det som behövs innan renderingen börjar
void initialize()
{
	shared.time = 0;
	shared.pause = false;
	glEnable(GL_DEPTH_TEST);	// Aktiverar Z-bufferten
}

// Hjälpfunktion jag använder för att rita ut en vertex.
void DrawVertex(Point point)
{
	glVertex3f(point.x, point.y, point.z);
}



// Vår egen underfunktion som ritar ut ett golv
void drawFloor()
{
	glPolygonMode(GL_FRONT, GL_LINE);		// Definierar hur primitiv ska rasteriseras
	glPolygonMode(GL_BACK, GL_LINE);

	glColor3f(0, 1, 0);		// Jag sätter golvfyrhörningens färg till grön.

	glBegin(GL_QUADS);		// Definierar vilken sorts primitiv som ska ritas ut mellan glBegin och glEnd (fyrkanter här)
	glVertex3f(10, -10, 10);	// Definierar punkter som en primitiv ska ritas mellan
	glVertex3f(10, -10, -10);
	glVertex3f(-10, -10, -10);
	glVertex3f(-10, -10, 10);
	glEnd();
}

// Min funktion som ritar ut diamantobjektet
void drawDiamond()
{
	if (shared.fill)
		glPolygonMode(GL_FRONT, GL_FILL);	// Jag ändrar polygonläge till 'fill' för framsidan på polygonerna i objektet
	else
		glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	
	Point p1, p2, p3, p4, p5, p6, p7, p8, p9;

	DefinePoint(p1, 5, -5, 5);
	DefinePoint(p2, 5, 0, 5);
	DefinePoint(p3, 5, 0, -5);
	DefinePoint(p4, 5, -5, -5);
	DefinePoint(p5, -5, -5, -5);
	DefinePoint(p6, -5, 0, -5);
	DefinePoint(p7, -5, 0, 5);
	DefinePoint(p8, -5, -5, 5);
	DefinePoint(p9, 0, 10, 0);

	if (shared.transformation)	// transformation där translation sker före rotation.
	{
		glTranslatef(0, 0, sin(shared.time) * 10);	// Translation mot och från skärmen
		glRotatef(shared.time * 50, 1, 0, 0);	// Rotation kring x-axeln
		glRotatef(shared.time * 30, 0, 0, 1);	// Rotation kring z-axeln
	}
	else						// transformation där rotation sker före translation.
	{
		glRotatef(shared.time * 50, 1, 0, 0);
		glRotatef(shared.time * 30, 0, 0, 1);
		glTranslatef(0, 0, sin(shared.time) * 10);
	}

	glBegin(GL_TRIANGLES);			// Jag ritar ut varje specifik triangel med hjälp av mina Point strukter.

	glColor3f(1, 1, 1);				// Jag ser till att färgen är annorlunda på alla hörn
	DrawVertex(p1);
	glColor3f(0, 0, 1);
	DrawVertex(p3);
	glColor3f(1, 0, 1);
	DrawVertex(p2);

	glColor3f(1, 1, 1);
	DrawVertex(p1);
	glColor3f(0, 0.5, 1);
	DrawVertex(p4);
	glColor3f(0, 0, 1);
	DrawVertex(p3);

	glColor3f(0, 0.5, 1);
	DrawVertex(p4);
	glColor3f(1, 0, 0);
	DrawVertex(p5);
	glColor3f(1, 1, 0);
	DrawVertex(p6);

	glColor3f(0, 0.5, 1);
	DrawVertex(p4);
	glColor3f(1, 1, 0);
	DrawVertex(p6);
	glColor3f(0, 0, 1);
	DrawVertex(p3);

	glColor3f(1, 0, 0);
	DrawVertex(p5);
	glColor3f(0, 1, 0.5);
	DrawVertex(p8);
	glColor3f(0.5, 0, 0.5);
	DrawVertex(p7);

	glColor3f(1, 0, 0);
	DrawVertex(p5);
	glColor3f(0.5, 0, 0.5);
	DrawVertex(p7);
	glColor3f(1, 1, 0);
	DrawVertex(p6);

	glColor3f(0, 1, 0.5);
	DrawVertex(p8);
	glColor3f(1, 1, 1);
	DrawVertex(p1);
	glColor3f(1, 0, 1);
	DrawVertex(p2);

	glColor3f(0, 1, 0.5);
	DrawVertex(p8);
	glColor3f(1, 0, 1);
	DrawVertex(p2);
	glColor3f(0.5, 0, 0.5);
	DrawVertex(p7);

	glColor3f(1, 1, 1);
	DrawVertex(p1);
	glColor3f(0, 1, 0.5);
	DrawVertex(p8);
	glColor3f(1, 0, 0);
	DrawVertex(p5);

	glColor3f(1, 1, 1);
	DrawVertex(p1);
	glColor3f(1, 0, 0);
	DrawVertex(p5);
	glColor3f(0, 0.5, 1);
	DrawVertex(p4);

	glColor3f(0, 0, 1);
	DrawVertex(p3);
	glColor3f(1, 0.5, 0);
	DrawVertex(p9);
	glColor3f(1, 0, 1);
	DrawVertex(p2);

	glColor3f(1, 1, 0);
	DrawVertex(p6);
	glColor3f(1, 0.5, 0);
	DrawVertex(p9);
	glColor3f(0, 0, 1);
	DrawVertex(p3);

	glColor3f(0.5, 0, 0.5);
	DrawVertex(p7);
	glColor3f(1, 0.5, 0);
	DrawVertex(p9);
	glColor3f(1, 1, 0);
	DrawVertex(p6);

	glColor3f(1, 0, 1);
	DrawVertex(p2);
	glColor3f(1, 0.5, 0);
	DrawVertex(p9);
	glColor3f(0.5, 0, 0.5);
	DrawVertex(p7);

	glEnd();
}

// Arrayer som jag använder till diamantobjektet ritat med en vertex array
GLfloat diamondVertices[] = {
	5, -5, 5,									// vertex 0
	5, 0, 5,									// vertex 1
	5, 0, -5,									// vertex 2
	5, -5, -5,									// vertex 3
	-5, -5, -5,									// vertex 4
	-5, 0, -5,									// vertex 5
	-5, 0, 5,									// vertex 6
	-5, -5, 5,									// vertex 7
	0, 10, 0									// vertex 8
};
GLubyte diamondIndices[] = {
	2, 1, 0,  3, 2, 0,							// front faces
	5, 2, 3,  4, 5, 3,							// right faces
	6, 5, 4,  7, 6, 4,							// back faces
	1, 6, 7,  0, 1, 7,							// left faces
	4, 3, 0,  7, 4, 0,							// bottom faces
	2, 8, 1,  5, 8, 2,  6, 8, 5,  1, 8, 6		// peak faces
};
GLfloat diamondColors[] = {						// färgerna är samma som i den andra utritningen förrutom att de är mörkare.
	0.8, 0.8, 0.8,								// vertex 0 färg
	0.8, 0, 0.8,								// vertex 1 färg
	0, 0, 0.8,									// vertex 2 färg
	0, 0.4, 0.8,								// vertex 3 färg
	0.8, 0, 0,									// vertex 4 färg
	0.8, 0.8, 0,								// vertex 5 färg
	0.4, 0, 0.4,								// vertex 6 färg
	0, 0.8, 0.4,								// vertex 7 färg
	0.8, 0.4, 0									// vertex 8 färg
};

// Min funktion som ritar ut diamantobjektet med en vertex array
void drawDiamondArray()
{
	if (shared.fill)
		glPolygonMode(GL_FRONT, GL_FILL);	// Jag ändrar polygonläge till 'fill' för framsidan på polygonerna i
	else									// objektet om fill är aktiverat i shared, annars är polygonläge Line.
		glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	if (shared.transformation)	// transformation där translation sker före rotation.
	{
		glTranslatef(0, 0, sin(shared.time) * 10);	// Translation mot och från skärmen
		glRotatef(shared.time * 50, 1, 0, 0);	// Rotation kring x-axeln
		glRotatef(shared.time * 30, 0, 0, 1);	// Rotation kring z-axeln
	}
	else						// transformation där rotation sker före translation.
	{
		glRotatef(shared.time * 50, 1, 0, 0);
		glRotatef(shared.time * 30, 0, 0, 1);
		glTranslatef(0, 0, sin(shared.time) * 10);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, diamondColors);
	glVertexPointer(3, GL_FLOAT, 0, diamondVertices);

	glDrawElements(GL_TRIANGLES, 42, GL_UNSIGNED_BYTE, diamondIndices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
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
	case 'c':	// hotkey för backface culling
		shared.backfaceCulling = !shared.backfaceCulling;
		if (shared.backfaceCulling)
		{
			glEnable(GL_CULL_FACE);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
		break;
	case 'f':	// hotkey för fill
		shared.fill = !shared.fill;
		break;
	case 't':	// hotkey för transformationstyp
		shared.transformation = !shared.transformation;
		break;
	case 'r':	// hotkey för kamerarotation
		shared.cameraRotation = !shared.cameraRotation;
		break;
	case 'v':	// hotkey för vertex array
		shared.vertArray = !shared.vertArray;
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
	glClearColor(0, 0, 0, 1);	// Jag sätter bakgrundsfärgen till svart
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Vi vill rensa både skärmbufferten och z-bufferten
	// Rensar buffrar och sätter bakgrundsfärgen

	glMatrixMode(GL_MODELVIEW);	// Bestämmer den nuvarande matrisen som matrisoperationer hanterar
	glLoadIdentity();	// Byter ut den nuvarande matrisen till identitetmatrisen
	if (shared.cameraRotation)
		gluLookAt(sin(shared.time) * 40, 10, cos(shared.time) * 40, 0, 0, 0, 0, 1, 0);   // Jag sätter kamerapositionen til (0, 10, 40).
	else
		gluLookAt(0, 10, 40, 0, 0, 0, 0, 1, 0);   // Jag sätter kamerapositionen til (0, 10, 40).
	drawFloor();
	if (!shared.vertArray)
		drawDiamond();
	else
		drawDiamondArray();

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

	glShadeModel(GL_SMOOTH);	// Jag aktiverar gouraud shading (smooth shading).

	glutTimerFunc(1000 / 60, timer, 1000 / 60);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
