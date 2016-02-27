
#include <iostream>
#include <fstream>

#include "Light.h"


using namespace std;

//****************************************************
// Constructors
//****************************************************
Light::Light() {
    for (int i = 0; i < 3; i++) {
        pos[i] = 0.0f;
        scaledPos[i] = 0.0f;
        color[i] = 0.0f;
    }
    lightID = 0;
}
Light::Light(int ID) {
    Light();
    lightID = ID;
}


//****************************************************
// Print Light Attributes
//****************************************************
void Light::print() {
    printf("Light %d Attributes:\n",lightID);
    printf("\tPosition (%0.03f, %0.03f, %0.03f)\n",pos[0],pos[1],pos[2]);
    printf("\tColor    (%0.03f, %0.03f, %0.03f)\n",color[0],color[1],color[2]);
}


//****************************************************
// Set Light Position and Color
//****************************************************
// r,g,b are expected to be [0,inf]
//      Any other value is invalid => Return code -1, -2, -3
int Light::setVals(float x, float y, float z, float r, float g, float b) {
    // Verify R in [0,inf]
    if (r < 0.0f) {
        printf("LIGHT::SETVALS - INVALID R INPUT <%f>\n",r);
        return -1;
    }
    // Verify G in [0,inf]
    if (g < 0.0f) {
        printf("LIGHT::SETVALS - INVALID G INPUT <%f>\n",g);
        return -2;
    }
    // Verify B in [0,inf]
    if (b < 0.0f) {
        printf("LIGHT::SETVALS - INVALID B INPUT <%f>\n",b);
        return -3;
    }
    
    // Set Light Properties
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    color[0] = r;
    color[1] = g;
    color[2] = b;
    
    // Return
    return 0;
}


//****************************************************
// Update ScaledPos
//****************************************************
int Light::updateScale(float scale) {
    // Scale each coordinate by the current unit length
    for (int i = 0; i < 3; i++) {
        scaledPos[i] = scale*pos[i];
    }
    
    // Return
    return 0;
}





