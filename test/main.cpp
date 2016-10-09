// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#include <GL/glew.h>
#include <GL/glut.h>
#include <NobelEngine.h>

using namespace NobelLib;
using namespace NobelEngine;

Form* form;

void DrawNet(GLfloat size, GLint LinesX, GLint LinesZ)
{
	glBegin(GL_LINES);
	for (int xc = 0; xc < LinesX; xc++)
	{
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
					0.0,
					size / 2.0);
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
					0.0,
					size / -2.0);
	}
	for (int zc = 0; zc < LinesX; zc++)
	{
		glVertex3f(	size / 2.0,
					0.0,
					-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
		glVertex3f(	size / -2.0,
					0.0,
					-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
	}
	glEnd();
}


void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//Draw the "world" (which consists of six "nets" forming a cuboid
	glTranslatef(0.0,-0.5,-6.0);

	glScalef(3.0,1.0,3.0);

	GLfloat size = 2.0;
	GLint LinesX = 30;
	GLint LinesZ = 30;

	GLfloat halfsize = size / 2.0;
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
		glTranslatef(0.0,-halfsize ,0.0);
		DrawNet(size,LinesX,LinesZ);
		glTranslatef(0.0,size,0.0);
		DrawNet(size,LinesX,LinesZ);
	glPopMatrix();
	glColor3f(0.0,0.0,1.0);
	glPushMatrix();
		glTranslatef(-halfsize,0.0,0.0);
		glRotatef(90.0,0.0,0.0,halfsize);
		DrawNet(size,LinesX,LinesZ);
		glTranslatef(0.0,-size,0.0);
		DrawNet(size,LinesX,LinesZ);
	glPopMatrix();
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
		glTranslatef(0.0,0.0,-halfsize);
		glRotatef(90.0,halfsize,0.0,0.0);
		DrawNet(size,LinesX,LinesZ);
		glTranslatef(0.0,size,0.0);
		DrawNet(size,LinesX,LinesZ);
	glPopMatrix();


	//finish rendering:
	glFlush();
	glutSwapBuffers();

}



//handles the key down events
void KeyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':		//ESC
		exit(0);
		break;
    case 'f':
        form->FullScreen();
    case 'g':
        form->Windowed(Resolution(800,600),Point(100,100));

	}
}

int main(int argc, char** argv)
{
    Program("Nobel OpenGL Engine", "0.01", argc, argv);
    form = new Form();

    form->Init();
    form->Windowed(Resolution(800,600),Point(100,100));
    form->Show();
//    form->FullScreen();
    glutKeyboardFunc(KeyDown);
    glutDisplayFunc(Display);

    fwrite("bella\n", 1, 6, stderr);
    glutMainLoop();

    glutDestroyWindow(1);

    return 0;
}
