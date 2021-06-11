#include <windows.h>  
#include <gl/Gl.h>  
#include <gl/glut.h>  

int screenheight = 300;
int screenwidth = 400;
bool flag = true;

int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
int xmin; int ymin; int xmax; int ymax;

void DrawRect(int x0, int y0, int x1, int y1)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRecti(x0, y0, x1, y1);
    glFlush();
}

void DrawLineSegment(int x0, int y0, int x1, int y1) {
    glColor3d(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(x0, y0);
    glVertex2i(x1, y1);
    glEnd();
    glFlush();
}

typedef int OutCode;

const int INSIDE = 0; // 0000  
const int BOTTOM = 1;  // 0001  
const int RIGHT = 2; // 0010  
const int TOP = 4; // 0100  
const int LEFT = 8;  // 1000  

OutCode ComputeOutCode(int x, int y)
{
    OutCode code;

    code = INSIDE;     // initialised as being inside of clip window  

    if (x < xmin)      // to the left of clip window  
        code |= LEFT;
    else if (x > xmax)      // to the left of clip window  
        code |= RIGHT;
    else if (y < ymin)      // to the left of clip window  
        code |= BOTTOM;// Complete the code segment here  
    else if (y > ymax)      // to the left of clip window  
        code |= TOP;
    return(code);
}

void CohenSutherlandLineClip(int x0, int y0, int x1, int y1)
{
    // Complete the code segment here  
    OutCode outcode0 = ComputeOutCode(x0, y0);
    OutCode outcode1 = ComputeOutCode(x1, y1);

    bool accept = false;

    while (true) {
        if (!(outcode0 | outcode1)) {//Bitwise OR is 0. Trivially accept  
            accept = true;
            break;
        }
        else if (outcode0 & outcode1) {
            // Bitwise AND is not 0. Trivially reject  
            break;
        }
        else {
            // failed both tests, so calculate the line segment to clip  
            // from an outside point to an intersection with clip edge  
            double x, y;
            // At least one endpoint is outside the clip rectangle; pick it.  
            OutCode outcodeOut = outcode0 ? outcode0 : outcode1;
            // Now find the intersection point;  
            if (outcodeOut & TOP) {// point is above the window  
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            }
            else if (outcodeOut & BOTTOM) {// point is below the window  
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            }
            else if (outcodeOut & RIGHT) { // point is to the right of window  
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                x = xmax;
            }
            else { // point is to the left of window  
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                x = xmin;
            }
            //Now move outside point to intersection point and get ready for next pass.  
            if (outcodeOut == outcode0) {
                x0 = x; y0 = y;
                outcode0 = ComputeOutCode(x0, y0);
            }
            else {
                x1 = x; y1 = y;
                outcode1 = ComputeOutCode(x1, y1);
            }
        }
    }
    if (accept)
        DrawLineSegment(x0, y0, x1, y1);
}

void myMouse(int button, int state, int x, int y) {
    glPointSize(5.0);
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            if (flag) {
                x0 = x;
                y0 = screenheight - y;
                flag = false;
            }
            else {
                x1 = x;
                y1 = screenheight - y;
                CohenSutherlandLineClip(x0, y0, x1, y1);
                flag = true;
            }
        }
        else if (button == GLUT_RIGHT_BUTTON)
        {  // KLIK KANAN di dua titik akan muncul kotak kuning
            if (flag) {
                x0 = x;
                y0 = screenheight - y;
                flag = false;
            }
            else {
                x1 = x;
                y1 = screenheight - y;
                glColor3d(1, 1, 0);
                DrawRect(x0, y0, x1, y1);
                xmin = x0;
                xmax = x1;
                ymin = y0;
                ymax = y1;
                flag = true;
            }
        }
    }
}


void myDisplay()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //black  
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);

    // create window  
    glutCreateWindow("Cohen-Sutherland Line Clipping");

    // set the view frustum  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    // clear rendering surface  
    glViewport(0, 0, 800, 600);

    glutMouseFunc(myMouse);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return(0);
}