#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;
#define  PI 3.14

int bgPos[4][3] = {
	{-3000, -2500, -1000},
	{-3000, 2500, -1000},
	{3000, 2500, -1000},
	{3000, -2500, -1000}
};
int textPos[] = { -190, 100, -100 };

void myInitial() {
	glClearColor(1, 1, 1, 1);
	glLineWidth(2.5);
	glClearDepth(1.0f);
}

void textRender(float x, float y, float z, void* font, char* nim) {
	char* c;
	glRasterPos3f(x, y, z);
	for (c = nim; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void warna(int r = 1, int g = 1, int b = 1, float a = 1) {
	glColor4f(r / 255.0f, g / 255.0f, b / 255.0f, a);
}

void bgSimple() {

	glBegin(GL_QUADS);
	warna(28, 59, 14);
	glVertex3f(bgPos[0][0], bgPos[0][1], bgPos[0][2]);
	warna(43, 14, 59);
	glVertex3f(bgPos[1][0], bgPos[1][1], bgPos[1][2]);
	warna(26, 74, 62);
	glVertex3f(bgPos[2][0], bgPos[2][1], bgPos[2][2]);
	warna(74, 26, 36);
	glVertex3f(bgPos[3][0], bgPos[3][1], bgPos[3][2]);
	glEnd();

	//show text
	char te[] = { "asdfasdfasdf" };
	char command[6][20] = {
		{"Atas : w / W" },
		{"Bawah : s / S" },
		{"Kanan : d / D"},
		{"Kiri : a / A"},
		{"Zoom in : q / Q"},
		{"Zoom out : e / E"}
	};
	int yy = textPos[1];
	warna(241, 237, 242);
	for (int i = 0; i < 6; i++) {
		textRender(textPos[0], textPos[1], textPos[2], GLUT_BITMAP_TIMES_ROMAN_24, command[i]);
		std::cout << command[i] << i << std::endl;
		textPos[1] -= 10;
	}
	textPos[1] = yy;
}

void circ(float x, float y, float z, float rad) {
	int i;
	int tJum = 100;
	GLfloat pi_2 = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, z);
	for (i = 0; i <= tJum; i++) {
		glVertex3f(
			x + (rad * cos(i * pi_2 / tJum)),
			y + (rad * sin(i * pi_2 / tJum)),
			z
		);
	}
	glEnd();
}

void Rcirc(float x, float y, float z, float rad) {
	int i;
	int tJum = 100;
	GLfloat pi_2 = 2.0f * PI;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= tJum; i++) {
		glVertex3f(
			x + (rad * cos(i * pi_2 / tJum)),
			y + (rad * sin(i * pi_2 / tJum)),
			z
		);
	}
	glEnd();
}

void disp() {
	glClear(GL_COLOR_BUFFER_BIT);

	bgSimple();

	//kaki kanan
	warna(237, 199, 152);
	glBegin(GL_QUADS);
	glVertex3f(0, -55, -100);
	glVertex3f(22, -55, -100);
	glVertex3f(13, -75, -100);
	glVertex3f(3, -75, -100);
	glEnd();

	//kaki kiri
	warna(237, 199, 152);
	glBegin(GL_QUADS);
	glVertex3f(0, -55, -100);
	glVertex3f(-22, -55, -100);
	glVertex3f(-13, -75, -100);
	glVertex3f(-3, -75, -100);
	glEnd();

	//tangan kanan
	warna(237, 199, 152);
	glBegin(GL_QUADS);
	glVertex3f(23, -25, -100);
	glVertex3f(38, -45, -100);
	glVertex3f(31, -50, -100);
	glVertex3f(23, -50, -100);
	glEnd();

	//tangan kanan
	warna(237, 199, 152);
	glBegin(GL_QUADS);
	glVertex3f(-23, -25, -100);
	glVertex3f(-38, -45, -100);
	glVertex3f(-31, -50, -100);
	glVertex3f(-23, -50, -100);
	glEnd();

	//badan
	warna(245, 209, 164);
	circ(0, -40, -100, 28);
	warna(255, 232, 204);
	circ(0, -43, -100, 22);

	//telinga kanan
	warna(255, 174, 74);
	circ(23, 23, -100, 15);
	warna(255, 196, 122);
	circ(23, 23, -100, 12);

	//telinga kiri
	warna(255, 174, 74);
	circ(-23, 23, -100, 15);
	warna(255, 196, 122);
	circ(-23, 23, -100, 12);

	//kepala
	warna(255, 222, 181);
	circ(0, 0, -100, 30);

	//mulut
	warna(0, 0, 0);
	Rcirc(5, -13, -100, 5);
	warna(0, 0, 0);
	Rcirc(-5, -13, -100, 5);
	warna(255, 222, 181);
	glBegin(GL_QUADS);
	glVertex3f(-10, 5, -100);
	glVertex3f(10, 5, -100);
	glVertex3f(10, -13, -100);
	glVertex3f(-10, -13, -100);
	glEnd();

	//mata kanan
	warna(64, 92, 91);
	circ(15, 0, -100, 8);
	warna(106, 151, 153);
	circ(15, 0, -100, 6);
	warna(64, 92, 91);
	circ(15, 0, -100, 2);
	warna(252, 255, 255);
	circ(12, 4, -100, 3);

	//mata kiri
	warna(64, 92, 91);
	circ(-15, 0, -100, 8);
	warna(106, 151, 153);
	circ(-15, 0, -100, 6);
	warna(64, 92, 91);
	circ(-15, 0, -100, 2);
	warna(252, 255, 255);
	circ(-18, 4, -100, 3);

	glutSwapBuffers();
}

void aspRR(int w, int h) {
	if (h == 0) h = 1;
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0f, aspect, 0.1f, -100.0f);
}

void key(unsigned char k, int x, int y) {
	switch (k) {
	case 'w':
	case 'W':
		glTranslatef(0.0, 1.0, 0.0);
		for (int i = 0; i < 4; i++) {
			bgPos[i][1] -= 1;
		}
		textPos[1] -= 1;
		break;
	case 'a':
	case 'A':
		glTranslatef(-1.0, 0.0, 0.0);
		for (int i = 0; i < 4; i++) {
			bgPos[i][0] += 1;
		}
		textPos[0] += 1;
		break;
	case 's':
	case 'S':
		glTranslatef(0.0, -1.0, 0.0);
		for (int i = 0; i < 4; i++) {
			bgPos[i][1] += 1;
		}
		textPos[1] += 1;
		break;
	case 'd':
	case 'D':
		glTranslatef(1.0, 0.0, 0.0);
		for (int i = 0; i < 4; i++) {
			bgPos[i][0] -= 1;
		}
		textPos[0] -= 1;
		break;
	case 'q':
	case 'Q':
		glTranslatef(0.0, 0.0, 1.0);
		for (int i = 0; i < 4; i++) {
			bgPos[i][2] -= 1;
		}
		textPos[2] -= 1;
		break;
	case 'e':
	case 'E':
		glTranslatef(0.0, 0.0, -1.0);
		for (int i = 0; i < 4; i++) {
			bgPos[i][2] += 1;
		}
		textPos[2] += 1;
		break;
	}
	disp();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(133, 84);

	glutCreateWindow("Hamtaro");
	glutDisplayFunc(disp);
	glutReshapeFunc(aspRR);
	glutKeyboardFunc(key);

	myInitial();
	glutMainLoop();
}