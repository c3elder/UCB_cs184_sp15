
#include <iostream>
#include <fstream>

#include "Sphere.h"


using namespace std;

//****************************************************
// Constructors
//****************************************************
Sphere::Sphere() {
    for (int i = 0; i < 3; i++) {
        ka[i] = 0.0f;
        kd[i] = 0.0f;
        ks[i] = 0.0f;
    }
    sp = 0.0f;
}


//****************************************************
// Print Sphere Material Attributes
//****************************************************
void Sphere::print() {
    printf("Sphere Attributes:\n");
    printf("\tAmbient Color  (%0.03f, %0.03f, %0.03f)\n",ka[0],ka[1],ka[2]);
    printf("\tDiffuse Color  (%0.03f, %0.03f, %0.03f)\n",kd[0],kd[1],kd[2]);
    printf("\tSpecular Color (%0.03f, %0.03f, %0.03f)\n",ks[0],ks[1],ks[2]);
    printf("\tSpecular Power %0.03f\n",sp);
}


//****************************************************
// Set Color Values for One of the Sphere's colors
//****************************************************
// WhichColor determines which material property to be modified
//      0 => Updating Ambient Color (ka)
//      1 => Updating Diffuse Color (kd)
//      2 => Updating Specular Color (ks)
//      Any other value is invalid => Return code -1
// r,g,b are expected to be [0,1]
//      Any other value is invalid => Return code -2,-3,-4 respectively
int Sphere::setKvals(int whichColor, float r, float g, float b) {
    // Make sure whichColor is valid
    if ((whichColor < 0) || (whichColor > 2)) {
        printf("SPHERE::SETKVALS - INVALID WHICHCOLOR INPUT <%d>\n",whichColor);
        return -1;
    }
    
    // Verify R in [0,1]
    if ((r < 0.0f) || (r > 1.0f)) {
        printf("SPHERE::SETKVALS - INVALID R INPUT <%f>\n",r);
        return -2;
    }
    // Verify G in [0,1]
    if ((g < 0.0f) || (g > 1.0f)) {
        printf("SPHERE::SETKVALS - INVALID G INPUT <%f>\n",g);
        return -3;
    }
    // Verify B in [0,1]
    if ((b < 0.0f) || (b > 1.0f)) {
        printf("SPHERE::SETKVALS - INVALID B INPUT <%f>\n",b);
        return -4;
    }
    
    // Set Sphere Material Properties
    switch (whichColor) {
        case 0: // Update Ambient Color (ka)
            ka[0] = r;
            ka[1] = g;
            ka[2] = b;
            break;
        case 1: // Update Diffuse Color (kd)
            kd[0] = r;
            kd[1] = g;
            kd[2] = b;
            break;
        case 2: // Update Specular Color (ks)
            ks[0] = r;
            ks[1] = g;
            ks[2] = b;
            break;
        default:
            return -5;
    }
    
    // Return
    return 0;
}


//****************************************************
// Set Specular Power Coefficient
//****************************************************
int Sphere::setSP(float spVal) {
    // Verify spVal >= 0
    if (spVal < 0) {
        printf("SPHERE::SETSP - INVALID SPVAL INPUT <%f>\n",spVal);
        return -1;
    }
    
    // Set Specular Power Coefficient
    sp = spVal;
    
    // Return
    return 0;
}