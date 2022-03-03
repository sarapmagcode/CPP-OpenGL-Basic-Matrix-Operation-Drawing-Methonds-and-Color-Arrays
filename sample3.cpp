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
	// (9 * 4) = triangle coordinates
	// (12 * 6) = cube coordinates
	glBufferData(GL_ARRAY_BUFFER, ((9 * 4) + (12 * 6)) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glClear(GL_COLOR_BUFFER_BIT);
	
	// print triangle:
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	
	// print cube (skip 36 indices):
//	glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(36));
//	glDrawArrays(GL_QUADS, 0, 24);
	
	glDisableClientState(GL_VERTEX_ARRAY);
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
