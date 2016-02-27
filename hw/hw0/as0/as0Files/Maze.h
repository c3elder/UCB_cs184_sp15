// Maze Class

#ifndef MAZE_H
#define MAZE_H

#include <vector>

#include "Point.h"
#include "Line.h"

class Maze {
    public:
        std::vector<Line> walls; // All Maze Wall Line Segments
    
        // Constructors
        Maze();
    
        void drawMaze();
        int intersects(struct Point lineP1, struct Point lineP2);
        int intersects(float lineX1, float lineY1, float lineX2, float lineY2);
    
};


#endif




