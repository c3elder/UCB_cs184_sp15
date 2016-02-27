// CS184 Simple OpenGL Example

#ifndef SPIFF_H
#define SPIFF_H

#ifdef OSX
    #include <GLUT/glut.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
    #include <GL/glu.h>
#endif

#include "Point.h"

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


#endif




