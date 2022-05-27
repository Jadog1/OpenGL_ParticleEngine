/* Example program for Window initialization and drawing */

#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#pragma warning(disable : 4996)
#include "PixelGeneration.h"
#include "CameraMovement.h"
#include "FireGeneration.h"
DrawPixelGenerators pixelbois;
FireBoxHandler FireBoxes;

void init_window(int argc, char** argv)
{
	glutInit(&argc, argv);				/* Initialize GLUT */
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE); 		/* Specify display mode */

	glutInitWindowSize(600, 600);		/* Set window size */
	glutInitWindowPosition(0, 0);		/* Set window position */
	glutCreateWindow("Window Creation");	/* Create Window */
}

void setProjection() {
	glMatrixMode(GL_PROJECTION);		/* Modify Projection Matrix */
	glLoadIdentity();				/* Set to identity matrix */
	gluPerspective(90, 1, 1.5, 400);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	//glOrtho(-100.0, 100.0, 100.0, -100.0, -100.0, 100.0);	/* Orthographic viewing volume */
	glMatrixMode(GL_MODELVIEW);
}

void other_init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);		/* Set background color */
	setProjection();
	glLoadIdentity();
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	glutWarpPointer(300, 300);
}

void drawfloor() {
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(-1000, 25, -1000);
	glVertex3f(1000, 25, -1000);
	glVertex3f(1000, 5, 1000);
	glVertex3f(-1000, 5, 1000);
	glEnd();
}

void display(void)
{
	setProjection();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	/* Clear color values */
	glLoadIdentity();
	cameraOrient();
	pixelbois.drawGenerators();
	FireBoxes.DrawFireBox();
	//drawfloor();
	glutSwapBuffers();						/* Clear event buffer */
}

void refreshRate(int value) {
	glutPostRedisplay();
	glutTimerFunc(50, refreshRate, 0);
}


int main(int argc, char** argv)
{
	setDefaults();
	init_window(argc, argv);			/* Initialize window */
	other_init();						/* Initialize other parameter */
	
	PixelGenerator pg(0, 15, -7, 8, 8, -4, 100);
	FireBox fb(15, 0, -7, 30, 30, 30, 1, 0.6);
	//pixelbois.addGenerator(pg);
	FireBoxes.addFireBox(fb);
	glutDisplayFunc(display); 			/* Redisplay callback event handling */
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutPassiveMotionFunc(mouseMovement);
	refreshRate(0);
	glutMainLoop();					/* Main event loop */

	return 0;
}
