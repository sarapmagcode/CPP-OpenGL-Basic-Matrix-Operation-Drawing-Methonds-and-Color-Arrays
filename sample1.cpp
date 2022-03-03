#define GLEW_STATIC

#include<GL/glew.h>
#include<GL/glut.h>
#include <GL/freeglut_ext.h>
#include<iostream>

using namespace std;

void display();
void translate(float x, float y, float z, int startindex);

GLfloat polygonvertices[] = {
	-0.5f,0.5f,0.0f, //first vertex
	0.5f,0.5f,0.0f, //second vertex
	1.0f,0.0f,0.0f, //third vertex
	0.5f,-0.5f,0.0f, //fourth vertex
	-0.5f,-0.5f,0.0f, //fifth vertex
	-1.0f,0.0f,0.0f //sixth vertex
};

GLfloat *mapV = NULL;
int forUpdate = 0;
int ctr = 0;
GLuint VBOid;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL Setup Test");
	glutDisplayFunc(display);
	GLenum err = glewInit();
	if (err == GLEW_OK) {
		glutMainLoop();
	} else {
		cout << "Error in initializing GLEW extension library...";
	}
	return 0;
}

void polygon(){
	if (!forUpdate) {
		// use vertex buffer objects
		glGenBuffers(1, &VBOid);
		glBindBuffer(GL_ARRAY_BUFFER, VBOid);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, polygonvertices, GL_DYNAMIC_DRAW);
		// draw the polygon
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glDrawArrays(GL_POLYGON, 0, 18);
		glDisableClientState(GL_VERTEX_ARRAY);
	} else {
		// redraw the polygon (no need to use VBO again)
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glDrawArrays(GL_POLYGON, 0, 18);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void modifyPolygon(int value) {
	if (value == 10) {
		// bind with 0, so, switch back to normal pointer operation
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &VBOid);
		exit(0);
	}
	forUpdate = 1;
	mapV = (GLfloat *) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	
	// translate the polygon moving it to the right 10 times per second increasing the X’s value to .025f
	for (int i = 0; i < 18; i += 3) {
		translate(.025f, 0.0f, 0.0f, i); // translate(x, y, z, index)
	}
	
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glutPostRedisplay();
}

void translate(float x, float y, float z, int startindex){
	GLfloat w = 1.0f;
	// Translation Matrix Template
	GLfloat ta[] = {
		1.0f, 0.0f, 0.0f, x,
		0.0f, 1.0f, 0.0f, y,
		0.0f, 0.0f, 1.0f, z,
		0.0f, 0.0f, 0.0f, 1
	};
	// Using the traditional Matrix to Matrix Multiplication of 4x4 to 4x1 matrix 
	// with no simplification included
	GLfloat tx, ty, tz;
	tx = (ta[0] * mapV[startindex]) + (ta[1] * mapV[startindex+1]) + (ta[2] * mapV[startindex+2]) + (ta[3] * w);
	ty = (ta[4] * mapV[startindex]) + (ta[5] * mapV[startindex+1]) + (ta[6] *mapV[startindex+2]) + (ta[7] * w);
	tz = (ta[8] * mapV[startindex]) + (ta[9] * mapV[startindex+1]) + (ta[10] * mapV[startindex+2]) + (ta[11] * w);
	mapV[startindex] = tx;
	mapV[startindex+1] = ty;
	mapV[startindex+2] = tz;
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(.16f,.72f,.08f,1.0f);
	polygon();
	glFlush();
	glutTimerFunc(1000, modifyPolygon, ctr++);
}
