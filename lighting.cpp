#include <iostream>
#include <stdlib.h>

#include <GL/glut.h>

using namespace std;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
		case 27: //Escape key
			exit(0);
	}
}

//Initializes 3D rendering
void initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//glShadeModel(GL_SMOOTH); //Enable smooth shading
}

// Called when the window is resized
void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float angle = -70.0f;

// Draws the 3D scene
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
    // Move camera forward by 8 units in Z direction
	glTranslatef(0.0f, 0.0f, -8.0f);
	
	//Add ambient light
    // These color intensity values can even be greater than 1 (so not technically RGB values)
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	//Add positioned light
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	//Add directed light
    // Difference between positioned and directed light is the 4th component
    // 1.0f for positioned, 0.0f for directed
	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	
	//Front
    glNormal3f(0.0f, 0.0f, 1.0f);  // normal towards viewer
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, 1.0f, 1.5f);
	
    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);   // normal away from viewer
    //glNormal3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.5f, -1.0f, -1.5f);
    //glNormal3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.5f, 1.0f, -1.5f);
    //glNormal3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.5f, 1.0f, -1.5f);
    //glNormal3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.5f, -1.0f, -1.5f);
		
	//Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, 1.0f, -1.5f);

    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    //glNormal3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.5f, -1.0f, -1.5f);
    //glNormal3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.5f, 1.0f, -1.5f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.5f, 1.0f, 1.5f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.5f, -1.0f, 1.5f);
	glEnd();
	
	glutSwapBuffers();
}

void update(int value)
{
    angle += 1.5f;
    if (angle > 360)
    {
        angle -= 360;
	}
	
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv)
{
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(1000,250);
	glutInitWindowSize(400, 400);
	
	//Create the window
    glutCreateWindow("Lighting");
	initRendering();
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(25, update, 0); //Add a timer
	
	glutMainLoop();
	return 0;
}








