// CS184 Simple OpenGL Example

#ifdef OSX
    #include <GLUT/glut.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
    #include <GL/glu.h>
#endif

#include "Maze.h"

using namespace std;

float ALLVERTICES [2*2*36] = {
      1.0f, -1.0f,  1.0f, 0.75f,   // Outer Bounds
     -1.0f,  1.0f, -1.0f,-0.75f,
     -1.0f, -1.0f,  1.0f, -1.0f,
      1.0f,  1.0f, -1.0f,  1.0f,
    
      0.0f,  0.0f,  0.0f, -0.5f,   // On Axes
      0.0f,  1.0f,  0.0f, 0.75f,
      0.0f,  0.5f,  0.0f, 0.25f,
    -0.25f,  0.0f,  0.0f,  0.0f,
      0.5f,  0.0f, 0.75f,  0.0f,
    
    -0.75f, -1.0f,-0.75f,-0.75f,   // -,- Quadrant
    -0.25f,-0.75f,-0.25f,-0.25f,
    -0.75f,-0.25f,-0.75f,  0.0f,
    -0.75f,-0.75f, -0.5f,-0.75f,
     -1.0f, -0.5f, -0.5f, -0.5f,
    -0.25f,-0.75f,  0.0f,-0.75f,
    -0.25f,-0.25f,-0.75f,-0.25f,
    
    -0.75f,  0.0f,-0.75f, 0.75f,   // -,+ Quadrant
     -0.5f,  1.0f, -0.5f,  0.0f,
    -0.25f, 0.75f,-0.25f,  0.5f,
     -0.5f, 0.25f,-0.25f, 0.25f,
    -0.25f,  0.5f,  0.0f,  0.5f,
    
     0.25f,  0.0f, 0.25f,-0.25f,   // +,- Quadrant
     0.25f, -0.5f, 0.25f, -1.0f,
      0.5f, -0.5f,  0.5f,-0.75f,
     0.75f,-0.75f, 0.75f, -1.0f,
      0.0f, -0.5f, 0.25f, -0.5f,
     0.25f,-0.25f,  0.5f,-0.25f,
      0.5f, -0.5f, 0.75f, -0.5f,
     0.75f,-0.25f,  1.0f,-0.25f,
    
     0.25f, 0.75f, 0.25f,  0.5f,   // +,+ Quadrant
     0.25f, 0.25f, 0.25f,  0.0f,
      0.5f,  1.0f,  0.5f,  0.0f,
      0.0f, 0.25f, 0.25f, 0.25f,
     0.25f,  0.5f, 0.75f,  0.5f,
     0.75f, 0.25f,  1.0f, 0.25f,
     0.75f, 0.75f,  1.0f, 0.75f
};

//****************************************************
// Constructors
//****************************************************
Maze::Maze() {
    walls.resize(36);
    for (int i = 0; i < walls.size(); i++) {
        walls[i] = Line(ALLVERTICES[4*i],ALLVERTICES[4*i+1],ALLVERTICES[4*i+2],ALLVERTICES[4*i+3]);
    }
}

//****************************************************
// Draw Line
//****************************************************
void Maze::drawMaze() {
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
    
    // Maze Walls
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3f(0.75f,0.0f,0.75f);
    for (int i = 0; i < walls.size(); i++) {
        walls[i].drawLine();
    }
    glEnd();
}

//****************************************************
// Check for Intersection - 0=>No Collision; 1=>Collision
//****************************************************
int Maze::intersects(struct Point lineP1, struct Point lineP2) {
    for (int i = 0; i < walls.size(); i++) {
        if (walls[i].intersects(lineP1,lineP2)) {
            printf("Intersected with wall[%d]\n",i);
            return 1;
        }
    }
    // Return
    return 0;
}

int Maze::intersects(float lineX1, float lineY1, float lineX2, float lineY2) {
    for (int i = 0; i < walls.size(); i++) {
        if (walls[i].intersects(lineX1,lineY1,lineX2,lineY2)) {
            printf("Intersected with wall[%d]\n",i);
            return 1;
        }
    }
    // Return
    return 0;
}
