#define GLEW_STATIC
#define BUFFER_OFFSET(i) ((void*)(i))

#include<GL/glew.h>
#include<GL/glut.h>
#include <GL/freeglut_ext.h>
#include<iostream>

using namespace std;

void displayObject();

void GLAPIENTRY
MessageCallback( GLenum source,
GLenum type,
GLuint id,
GLenum severity,
GLsizei length,
const GLchar* message,
const void* userParam );

GLfloat vertices[] = {
	//---------------------- TRIANGLE
	0.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	
	0.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	
	0.0f, 1.0f, 0.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	
	0.0f, 1.0f, 0.0f,
	-1.0f,-1.0f, -1.0f,
	-1.0f,-1.0f, 1.0f,
	
	//---------------------- CUBE
	
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	
	1.0f, -1.0f, 1.0f, 
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 
	1.0f, -1.0f, -1.0f,
	
	1.0f, 1.0f, 1.0f, 
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 
	1.0f, -1.0f, 1.0f,
	
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f, 
	-1.0f, 1.0f, -1.0f, 
	1.0f, 1.0f, -1.0f,
	
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 
	-1.0f, -1.0f, -1.0f, 
	-1.0f, -1.0f, 1.0f,
	
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f, 
	1.0f, -1.0f, 1.0f, 
	1.0f, -1.0f, -1.0f, 
};

GLfloat colorssquare[] = {
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	
	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,
	
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	
	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f
};

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL Setup Test");
	glutDisplayFunc(displayObject);
	GLenum err = glewInit();
	if (err == GLEW_OK) {
		glEnable ( GL_DEBUG_OUTPUT );
		glDebugMessageCallback(MessageCallback, 0);
		printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
		printf("OpenGL vendor (%s): \n", glGetString(GL_VENDOR));
		glutMainLoop();
	} else {
		cout << "Error in initializing GLEW extension library...";
	}
	return 0;
}

void displayObject() {
	GLuint VBOid;
	glGenBuffers(1, &VBOid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glBufferData(GL_ARRAY_BUFFER, ((9 * 4) + (12 * 6) + (12 * 6)) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	// 3rd parameter is (12 * 6) for cube
	glBufferSubData(GL_ARRAY_BUFFER, ((9 * 4) + (12 * 6)) * sizeof(GLfloat), ((12 * 6) * sizeof(GLfloat)), colorssquare);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET((9 * 4) * sizeof(GLfloat) ));
	glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(((9 * 4) + (12 * 6)) * sizeof(GLfloat)));
	
	glBegin(GL_QUADS);
	// from index 12 to 15 (inclusive) of the vertices 2D array
	glArrayElement(12);
	glArrayElement(13);
	glArrayElement(14);
	glArrayElement(15);
	glEnd(); 
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBOid);
	glFlush();
}

void GLAPIENTRY
MessageCallback(GLenum source,
GLenum type,
GLuint id,
GLenum severity,
GLsizei length,
const GLchar* message,
const void* userParam) {
	fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
	( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
	type, severity, message );
}
