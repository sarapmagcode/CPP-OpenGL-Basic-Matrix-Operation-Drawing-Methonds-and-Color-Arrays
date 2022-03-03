#define GLEW_STATIC

#include<GL/glew.h>
#include<GL/glut.h>
#include <GL/freeglut_ext.h>
#include<iostream>

using namespace std;

void displayCube();
void displayTriangle();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL Setup Test");
	// placement of camera (default position: 0, 0, 0)
	glutDisplayFunc(displayTriangle); // swap with displayCube() to see the box
	glutMainLoop();
	return 0;
}

void displayCube() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS); // Begin drawing the color cube with 6 quads
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f( 1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f( 1.0f, 1.0f, 1.0f);
	
	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f); // Orange
	glVertex3f( 1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f, -1.0f, -1.0f);
	// Front face (z = 1.0f)
	
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f( 1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f( 1.0f, -1.0f, 1.0f);
	
	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex3f( 1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f( 1.0f, 1.0f, -1.0f);
	
	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	
	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f); // Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	
	glEnd(); // End of drawing color-cube
	glFlush();
}

void displayTriangle(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES); // Begin drawing the pyramid with 4 triangles
	// Front
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f( 0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);
	
	// Right
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(1.0f, -1.0f, -1.0f);
	
	// Back
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);
	
	// Left
	glColor3f(1.0f,0.0f,0.0f); // Red
	glVertex3f( 0.0f, 1.0f, 0.0f);
	glColor3f(0.0f,0.0f,1.0f); // Blue
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glColor3f(0.0f,1.0f,0.0f); // Green
	glVertex3f(-1.0f,-1.0f, 1.0f);
	
	glEnd(); // Done drawing the pyramid
	glFlush();
}

