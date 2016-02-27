// Line Class

#include "Point.h"

#ifndef LINE_H
#define LINE_H

class Line {
    public:
        struct Point p1;    // Start Point
        struct Point p2;    // End Point
    
        // Constructors
        Line();
        Line(struct Point tmpP1, struct Point tmpP2);
        Line(float x1, float y1, float x2, float y2);
    
        void drawLine();
        int intersects(Line otherLine);
        int intersects(struct Point lineP1, struct Point lineP2);
        int intersects(float lineX1, float lineY1, float lineX2, float lineY2);
    
};


#endif




