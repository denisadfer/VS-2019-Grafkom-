/*************************************************\
|	            Grafika Komputer - Teksture
|	                      Eko, Asp, & Hin
|
|   Press 'c' to draw the cube or press 'b' to draw a flat box
|   (Cube is drawn on default)
/*************************************************/

#include <GL\Glut.h>
//#include <IOSTREAM.h>	
//#include "TextureObjects.h"
#define FILE_TEXTURE1 "PicFTI.bmp"

TextureSystem Textures;
float	xy_aspect;			//aspect ratio variable
GLfloat	RotateX;				// X Rotation
GLfloat	RotateY;				// Y Rotation
GLfloat	RotateZ;				// Z Rotation 
UINT	TextureObjects[1];		// Storage for the Texture(s) 

bool Draw_Cube = true;
bool Draw_Box = false;

GLvoid DrawBox(UINT mTexture)
{
	glPushMatrix();

	//Rotate the matrix by the rotation variables
	glRotatef(RotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(RotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(RotateZ, 0.0f, 0.0f, 1.0f);
	//bind the texture
	glBindTexture(GL_TEXTURE_2D, mTexture);

	// Display a quad texture to the screen
	glBegin(GL_QUADS);
	// Display the top left vertice
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1, 1, 0);
	// Display the bottom left vertice
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1, -1, 0);
	// Display the bottom right vertice
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, -1, 0);
	// Display the top right vertice
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, 1, 0);
	glEnd();
	glPopMatrix();
}

GLvoid DrawCube(UINT mTexture)
{
	//Push on the matrix so we can change it then pop it off in the end
	glPushMatrix();
	//Rotate the matrix by the rotation variables
	glRotatef(RotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(RotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(RotateZ, 0.0f, 0.0f, 1.0f);
	//bind the texture to the object
	glBindTexture(GL_TEXTURE_2D, mTexture);

	glBegin(GL_QUADS);
	// Front Side
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// Back Side
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// Top Side
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	// Bottom Side
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// Right Side
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// Left Side
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glPopMatrix();
}

void myIdle()
{
	glutPostRedisplay();
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0 * xy_aspect, 2.0 * xy_aspect, -2.0, 2.0, 0.01, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//Draw the cube to the screen
	if (Draw_Cube) { DrawCube(TextureObjects[0]); }
	if (Draw_Box) { DrawBox(TextureObjects[0]); }

	//set the rotation a little more
	RotateX += 0.4f;
	RotateY += 0.3f;
	RotateZ += 0.5f;

	glutSwapBuffers();
}

void myResize(int width, int height)
{
	glViewport(0, 0, width, height);
	//figure out aspect ratio
	xy_aspect = (float)width / (float)height;
	if (DEBUG) { cout << "Window Changed to (x,y): " << width << ", " << height << endl; }
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:			//Escape
	case 'q':			//Q - Key
		exit(0);
		break;
	case 'c':
		Draw_Cube = true;
		Draw_Box = false;
		break;
	case 'b':
		Draw_Cube = false;
		Draw_Box = true;
		break;
	default:
		break;
	}
	if (DEBUG) { cout << "Keypress Occured: " << key << endl; }
}

void main(int argc, char** argv)
{
	cout << "================================" << endl;
	cout << "|                                                                        |" << endl;
	cout << "| Program: Texture Objects.cpp                            |" << endl;
	cout << "|     By: Eko, Asp, Hin                                          |" << endl;
	cout << "|                                                                        |" << endl;
	cout << "================================" << endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(800, 600);
	glutCreateWindow("TextureObjects - Simple Texture Loading");

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);		// Black Background
	glEnable(GL_TEXTURE_2D);		// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);		// Enable Smooth Shading
	glClearDepth(1.0f);			// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);		// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myResize);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKeyboard);

	if (!Textures.LoadTexture(TextureObjects[0], FILE_TEXTURE1))
	{
		cout << "TEXTURE FAILED TO LOAD!!!" << endl;
	}
	glutMainLoop();
}