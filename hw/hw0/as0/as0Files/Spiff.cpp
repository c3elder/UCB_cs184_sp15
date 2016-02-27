// CS184 Simple OpenGL Example
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#ifdef OSX
    #include <GLUT/glut.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
    #include <GL/glu.h>
#endif

#include "Spiff.h"

using namespace std;

//****************************************************
// Some Classes
//****************************************************
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






