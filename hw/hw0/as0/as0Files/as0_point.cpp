// CS184 Simple OpenGL Example
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/time.h>
#endif

#ifdef OSX
    #include <GLUT/glut.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
    #include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>

#ifdef _WIN32
    static DWORD lastTime;
#else
    static struct timeval lastTime;
#endif

#define PI 3.14159265
#define LINESEGMENT(x1,y1,x2,y2) { \
    glVertex3f(x1,y1,0.0f); \
    glVertex3f(x2,y2,0.0f); \
}
using namespace std;

//****************************************************
// Some Classes
//****************************************************
class Viewport {
    public:
        int w, h; // width and height
};

struct Point {
    float x;
    float y;
};

class Spiff {
    public:
        struct Point center;    // Spiff's center coordinates
        float shipLen;          // Length of ship from nose to tail
        float shipWid;          // Width of ship from wing to wing
        float speed;            // Step length for each keypress
        int orientation;        // 0 Up; 1 Down; 2 Right; 3 Left
        struct Point getTip(struct Point centerPoint, int shipOrientation);
        void drawSpiff();
};

struct Point Spiff::getTip(struct Point centerPoint, int shipOrientation) {
    // Initialize
    struct Point tip;
    // Determine which way ship is oriented
    switch (shipOrientation) {
        case 0:
            tip.x = centerPoint.x;
            tip.y = centerPoint.y + 0.5*shipLen;
            break;
        case 1:
            tip.x = centerPoint.x;
            tip.y = centerPoint.y - 0.5*shipLen;
            break;
        case 2:
            tip.x = centerPoint.x + 0.5*shipLen;
            tip.y = centerPoint.y;
            break;
        case 3:
            tip.x = centerPoint.x - 0.5*shipLen;
            tip.y = centerPoint.y;
            break;
        default:
            printf("Uhhhh... we had an invalid orientation (X) <%d>",orientation);
            tip.x = 0;
            tip.y = 0;
    }
    // Return
    return tip;
}
void Spiff::drawSpiff() {
    
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_POLYGON);
    switch (orientation) {
        case 0:     // Up
            glVertex3f(center.x,center.y+0.5*shipLen,0.0f);
            glVertex3f(center.x-0.5*shipWid,center.y-0.5*shipLen,0.0f);
            glVertex3f(center.x+0.5*shipWid,center.y-0.5*shipLen,0.0f);
            break;
        case 1:     // Down
            glVertex3f(center.x,center.y-0.5*shipLen,0.0f);
            glVertex3f(center.x-0.5*shipWid,center.y+0.5*shipLen,0.0f);
            glVertex3f(center.x+0.5*shipWid,center.y+0.5*shipLen,0.0f);
            break;
        case 2:     // Right
            glVertex3f(center.x+0.5*shipLen,center.y,0.0f);
            glVertex3f(center.x-0.5*shipLen,center.y-0.5*shipWid,0.0f);
            glVertex3f(center.x-0.5*shipLen,center.y+0.5*shipWid,0.0f);
            break;
        case 3:     // Left
            glVertex3f(center.x-0.5*shipLen,center.y,0.0f);
            glVertex3f(center.x+0.5*shipLen,center.y-0.5*shipWid,0.0f);
            glVertex3f(center.x+0.5*shipLen,center.y+0.5*shipWid,0.0f);
            break;
        default:
            printf("How the fuck'd you manage to get an orientation of <%d>?\n",orientation);
    }
    glEnd();
}

//****************************************************
// Global Variables
//****************************************************
Viewport    viewport;
Spiff spiff;


//****************************************************
// Collision Detection
//****************************************************
int checkCollision(struct Point oldTip, struct Point newTip) {
    // Initialize
    if (newTip.x > -0.5f) {
        printf("Collision: Old (%.02f,%.02f); New (%.02f,%.02f)\n",oldTip.x,oldTip.y,newTip.x,newTip.y);
        return 1;
    }
    
    // Return
    return 0;
}

//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
    viewport.w = w;
    viewport.h = h;

    glViewport(0,0,viewport.w,viewport.h);// sets the rectangle that will be the window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                // loading the identity matrix for the screen

    //----------- setting the projection -------------------------
    // glOrtho sets left, right, bottom, top, zNear, zFar of the chord system


    // glOrtho(-1, 1 + (w-400)/200.0 , -1 -(h-400)/200.0, 1, 1, -1); // resize type = add
    // glOrtho(-w/400.0, w/400.0, -h/400.0, h/400.0, 1, -1); // resize type = center

    glOrtho(-1, 1, -1, 1, 1, -1);    // resize type = stretch

    //------------------------------------------------------------
}


//****************************************************
// sets the window up
//****************************************************
void initScene(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear to black, fully transparent

    myReshape(viewport.w,viewport.h);
}


//***************************************************
// function that does the actual drawing
//***************************************************
void myDisplay() {


    //----------------------- ----------------------- -----------------------
    // This is a quick hack to add a little bit of animation.
    static float tip = 0.5f;
    const  float stp = 0.01f;
    const  float beg = 0.1f;
    const  float end = 0.9f;
    static float dir = 1.0f;
    
    if (tip + dir*stp > end) {
        dir = -1.0f;
    } else if (tip + dir*stp < beg) {
        dir = 1.0f;
    }

    tip += dir*stp;
    //----------------------- ----------------------- -----------------------


    glClear(GL_COLOR_BUFFER_BIT);                // clear the color buffer (sets everything to black)

    glMatrixMode(GL_MODELVIEW);                  // indicate we are specifying camera transformations
    glLoadIdentity();                            // make sure transformation is "zero'd"

    //----------------------- code to draw objects --------------------------
    // Background Bollocks
    {
        // Rectangle Code
        //glColor3f(red component, green component, blue component);
        glColor3f(1.0f,0.0f,0.0f);                   // setting the color to pure red 90% for the rect
        glBegin(GL_POLYGON);                         // draw rectangle 
        //glVertex3f(x val, y val, z val (won't change the point because of the projection type));
        glVertex3f(-0.8f, 0.0f, 0.0f);               // bottom left corner of rectangle
        glVertex3f(-0.8f, 0.5f, 0.0f);               // top left corner of rectangle
        glVertex3f( 0.0f, 0.5f, 0.0f);               // top right corner of rectangle
        glVertex3f( 0.0f, 0.0f, 0.0f);               // bottom right corner of rectangle
        glEnd();
        
        // Triangle Code
        glColor3f(1.0f,0.5f,0.0f);                   // setting the color to orange for the triangle
        float basey = -sqrt(0.48f);                  // height of triangle = sqrt(.8^2-.4^2)
        glBegin(GL_POLYGON);
        glVertex3f(tip,  0.0f, tip);                // top tip of triangle
        glVertex3f(0.1f, basey, 0.0f);               // lower left corner of triangle
        glVertex3f(0.9f, basey, 0.0f);               // lower right corner of triangle
        glEnd();
        
        glColor3f(0.0f,0.25f,1.0f);
        glBegin(GL_POLYGON);
        glVertex3f(0.0f,1.0f,0.5f);
        glVertex3f(1.0f,-1.0f,0.5f);
        glVertex3f(-1.0f,-1.0f,0.5f);
        glEnd();
    }
    
    // Maze Definition
    {
        // Start/Stop Areas
        glColor3f(0.0f,1.0f,0.0f);
        glBegin(GL_POLYGON);
        glVertex3f( -1.0f, -1.0f,0.0f);
        glVertex3f( -1.0f,-0.75f,0.0f);
        glVertex3f(-0.75f,-0.75f,0.0f);
        glVertex3f(-0.75f, -1.0f,0.0f);
        glEnd();
        
        glColor3f(1.0f,0.0f,0.0f);
        glBegin(GL_POLYGON);
        glVertex3f( 1.0f, 1.0f,0.0f);
        glVertex3f( 1.0f,0.75f,0.0f);
        glVertex3f(0.75f,0.75f,0.0f);
        glVertex3f(0.75f, 1.0f,0.0f);
        glEnd();
        
        glLineWidth(4.0f);
        glBegin(GL_LINES);
        glColor3f(0.75f,0.0f,0.75f);
        // Outer Bounds
        LINESEGMENT(  1.0f, -1.0f,  1.0f, 0.75f);   // Vertical Lines
        LINESEGMENT( -1.0f,  1.0f, -1.0f,-0.75f);
        LINESEGMENT( -1.0f, -1.0f,  1.0f, -1.0f);   // Horizontal Lines
        LINESEGMENT(  1.0f,  1.0f, -1.0f,  1.0f);
        // On Axes
        LINESEGMENT(  0.0f,  0.0f,  0.0f, -0.5f);   // Vertical Lines
        LINESEGMENT(  0.0f,  1.0f,  0.0f, 0.75f);
        LINESEGMENT(  0.0f,  0.5f,  0.0f, 0.25f);
        LINESEGMENT(-0.25f,  0.0f,  0.0f,  0.0f);   // Horizontal Lines
        LINESEGMENT(  0.5f,  0.0f, 0.75f,  0.0f);
        // -,- Quadrant
        LINESEGMENT(-0.75f, -1.0f,-0.75f,-0.75f);   // Vertical Lines
        LINESEGMENT(-0.25f,-0.75f,-0.25f,-0.25f);
        LINESEGMENT(-0.75f,-0.25f,-0.75f,  0.0f);
        LINESEGMENT(-0.75f,-0.75f, -0.5f,-0.75f);   // Horizontal Lines
        LINESEGMENT( -1.0f, -0.5f, -0.5f, -0.5f);
        LINESEGMENT(-0.25f,-0.75f,  0.0f,-0.75f);
        LINESEGMENT(-0.25f,-0.25f,-0.75f,-0.25f);
        // -,+ Quadrant
        LINESEGMENT(-0.75f,  0.0f,-0.75f, 0.75f);   // Vertical Lines
        LINESEGMENT( -0.5f,  1.0f, -0.5f,  0.0f);
        LINESEGMENT(-0.25f, 0.75f,-0.25f,  0.5f);
        LINESEGMENT( -0.5f, 0.25f,-0.25f, 0.25f);   // Horizontal Lines
        LINESEGMENT(-0.25f,  0.5f,  0.0f,  0.5f);
        // +,- Quadrant
        LINESEGMENT( 0.25f,  0.0f, 0.25f,-0.25f);   // Vertical Lines
        LINESEGMENT( 0.25f, -0.5f, 0.25f, -1.0f);
        LINESEGMENT(  0.5f, -0.5f,  0.5f,-0.75f);
        LINESEGMENT( 0.75f,-0.75f, 0.75f, -1.0f);
        LINESEGMENT(  0.0f, -0.5f, 0.25f, -0.5f);   // Horizontal Lines
        LINESEGMENT( 0.25f,-0.25f,  0.5f,-0.25f);
        LINESEGMENT(  0.5f, -0.5f, 0.75f, -0.5f);
        LINESEGMENT( 0.75f,-0.25f,  1.0f,-0.25f);
        // +,+ Quadrant
        LINESEGMENT( 0.25f, 0.75f, 0.25f,  0.5f);   // Vertical Lines
        LINESEGMENT( 0.25f, 0.25f, 0.25f,  0.0f);
        LINESEGMENT(  0.5f,  1.0f,  0.5f,  0.0f);
        LINESEGMENT(  0.0f, 0.25f, 0.25f, 0.25f);   // Horizontal Lines
        LINESEGMENT( 0.25f,  0.5f, 0.75f,  0.5f);
        LINESEGMENT( 0.75f, 0.25f,  1.0f, 0.25f);
        LINESEGMENT( 0.75f, 0.75f,  1.0f, 0.75f);
        glEnd();
    }
    
    // Spaceman Spiff
    spiff.drawSpiff();
    //-----------------------------------------------------------------------

    glFlush();
    glutSwapBuffers();                           // swap buffers (we earlier set double buffer)
}


//***************************************************
// function that does the keyboard interaction
//***************************************************
void myKeyboard(int key, int x, int y) {
    // Initialize
    struct Point newCenter = spiff.center;
    float newOrient = spiff.orientation;
    // Read Key
    switch (key) {
        case GLUT_KEY_UP:
            if (newOrient == 0) {
                newCenter.y += spiff.speed;
            } else {
                newOrient = 0;
            }
            break;
        case GLUT_KEY_DOWN:
            if (newOrient == 1) {
                newCenter.y -= spiff.speed;
            } else {
                newOrient = 1;
            }
            break;
        case GLUT_KEY_RIGHT:
            if (newOrient == 2) {
                newCenter.x += spiff.speed;
            } else {
                newOrient = 2;
            }
            break;
        case GLUT_KEY_LEFT:
            if (newOrient == 3) {
                newCenter.x -= spiff.speed;
            } else {
                newOrient = 3;
            }
            break;
        default:
            printf("Wrong Key, fucko! Arrows only\n");
    }
    
    // Get Old and New Tips
    struct Point oldTip = spiff.getTip(spiff.center,spiff.orientation);
    struct Point newTip = spiff.getTip(newCenter, newOrient);
    
    // Check for collision
    if (checkCollision(oldTip,newTip)) {
        printf("Aw fuck, you ran into something...\n");
    } else {
        spiff.center = newCenter;
        spiff.orientation = newOrient;
    }
}


//****************************************************
// called by glut when there are no messages to handle
//****************************************************
void myFrameMove() {
    //nothing here for now
    #ifdef _WIN32
    Sleep(10);                                   //give ~10ms back to OS (so as not to waste the CPU)
    #endif
    glutPostRedisplay(); // forces glut to call the display function (myDisplay())
}


//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
    //This initializes glut
    glutInit(&argc, argv);

    //This tells glut to use a double-buffered window with red, green, and blue channels 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Initalize theviewport size
    viewport.w = 400;
    viewport.h = 400;
    
    // Initialize Spaceman Spiff
    spiff.center.x = -1.0f;
    spiff.center.y = -0.87f;
    spiff.shipLen = 0.1f;
    spiff.shipWid = 0.05f;
    spiff.speed = 0.05f;
    spiff.orientation = 2;

    //The size and position of the window
    glutInitWindowSize(viewport.w, viewport.h);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("THE ADVENTURES OF SPACEMAN SPIFF!");

    initScene();                                 // quick function to set up scene

    glutDisplayFunc(myDisplay);                  // function to run when its time to draw something
    glutReshapeFunc(myReshape);                  // function to run when the window gets resized
    glutIdleFunc(myFrameMove);                   // function to run when not handling any other task
    glutSpecialFunc(myKeyboard);
    glutMainLoop();                              // infinite loop that will keep drawing and resizing and whatever else

    return 0;
}








