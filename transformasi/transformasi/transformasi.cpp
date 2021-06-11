#include <Windows.h>
#include <GL/glut.h>

void myInit(void) {
	gluOrtho2D(0, 640, 0, 480);
	glPointSize(50);
	glEnable(GL_POINT_SMOOTH);
}

void myDisplay(void) {
	glColor3f(0.0, 0.5, 0.5);
	glRectf(300, 200, 400, 300);//x1, y1, x2, y2

	glPushMatrix();//menyimpan titik pusat awal

	glTranslatef(150, 150, 0);//koord x, y, z

	glColor3f(1.0, 0.0, 0.0);
	glRectf(300, 200, 400, 300);//x1, y1, x2, y2

	glPopMatrix();//mengembalikan ke titik pusat sebelumnya

	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Transformasi");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}