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

#include "Line.h"

using namespace std;

//****************************************************
// Constructors
//****************************************************
Line::Line() {
    p1.x = 0.0f;
    p1.y = 0.0f;
    p2.x = 0.0f;
    p2.y = 0.0f;
}

Line::Line(struct Point tmpP1, struct Point tmpP2) {
    p1 = tmpP1;
    p2 = tmpP2;
}

Line::Line(float x1, float y1, float x2, float y2) {
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
}

//****************************************************
// Draw Line
//****************************************************
void Line::drawLine() {
    glVertex3f(p1.x,p1.y,0.0f);
    glVertex3f(p2.x,p2.y,0.0f);
}

//====================================================
// Intersection Check Methodology
//====================================================
// We will use the cross product to determine if the two line segments intersect.
// This Object's Line is described by vectors p1,p2
// The Other Line is described by vectors op1,op2
// The lines intersect iff:
//      (1) p1 and p2 lie on different sides of line through op1 and op2
//      (2) op1 and op2 lie on different sides of line through p1 and p2
// (1) is true iff vec(op1,p1)xvec(op1,op2) and vec(op1,p2)xvec(op1,op2) have different sign
// => ((p1-op1)x(op2-op1)) * ((p2-op1)x(op2-op1)) <= 0
// => ((p1x-op1x)(op2y-op1y)-(p1y-op1y)(op2x-op1x)) * ((p2x-op1x)(op2y-op1y)-(p2y-op1y)(op2x-op1x)) <= 0
// (2) is true iff vec(p1,op1)xvec(p1,p2) and vec(p1,op2)xvec(p1,p2) have different sign
// => ((op1-p1)x(p2-p1)) * ((op2-p1)x(p2-p1)) <= 0
// => ((op1x-p1x)(p2y-p1y)-(op1y-p1y)(p2x-p1x)) * ((op2x-p1x)(p2y-p1y)-(op2y-p1y)(p2x-p1x)) <= 0


//****************************************************
// Check for Intersection - 0=>No Collision; 1=>Collision
//****************************************************
int Line::intersects(Line otherLine) {
    // Return from subfunction
    return intersects(otherLine.p1, otherLine.p2);
}

int Line::intersects(struct Point lineP1, struct Point lineP2) {
    // (1)
    float cp1 = (p1.x-lineP1.x)*(lineP2.y-lineP1.y) - (p1.y-lineP1.y)*(lineP2.x-lineP1.x);
    float cp2 = (p2.x-lineP1.x)*(lineP2.y-lineP1.y) - (p2.y-lineP1.y)*(lineP2.x-lineP1.x);
    // (2)
    float cp3 = (lineP1.x-p1.x)*(p2.y-p1.y) - (lineP1.y-p1.y)*(p2.x-p1.x);
    float cp4 = (lineP2.x-p1.x)*(p2.y-p1.y) - (lineP2.y-p1.y)*(p2.x-p1.x);
    
    // Compare
    if ((cp1*cp2 <= 0) && (cp3*cp4 <= 0)) {
        printf("Line Collision\n");
        return 1;
    }
    
    // Return
    return 0;
}

int Line::intersects(float lineX1, float lineY1, float lineX2, float lineY2) {
    // Return
    return 0;
}
