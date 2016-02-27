
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

#include "Sphere.h"
#include "Light.h"

#ifndef DEBUG
#define DEBUG 1
#endif


#define PI 3.14159265  // Should be used from mathlib
inline float sqr(float x) { return x*x; }
inline float dot(float *v, float *w) { return v[0]*w[0] + v[1]*w[1] + v[2]*w[2]; }
inline float mag(float *v) { return sqrt(dot(v,v)); }

using namespace std;

//****************************************************
// Some Classes
//****************************************************

class Viewport;

class Viewport {
    public:
        int w, h;   // width and height
};


//****************************************************
// Global Variables
//****************************************************
Viewport	viewport;

Sphere sphere;

int numDLs;
vector<Light> dls;  // Directional Lights
int numPLs;
vector<Light> pls;  // Point Lights




//****************************************************
// Simple init function
//****************************************************
void initScene(){

  // Nothing to do here for this simple example.

}


//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
    viewport.w = w;
    viewport.h = h;

    glViewport (0,0,viewport.w,viewport.h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, viewport.w, 0, viewport.h);

}


//****************************************************
// A routine to set a pixel by drawing a GL point.  This is not a
// general purpose routine as it assumes a lot of stuff specific to
// this example.
//****************************************************

void setPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b);
    glVertex2f(x + 0.5, y + 0.5);   // The 0.5 is to target pixel
    // centers 
    // Note: Need to check for gap
    // bug on inst machines.
}


//****************************************************
// Draw a filled circle.  
//****************************************************
void circle(float centerX, float centerY, float radius) {
    // Draw inner circle
    glBegin(GL_POINTS);

    
    // Update Light Positions in the current window scaling
    for (int i = 0; i < numDLs; i++) {
        dls[i].updateScale(radius);
    }
    for (int i = 0; i < numPLs; i++) {
        pls[i].updateScale(radius);
    }
    
    
    // We could eliminate wasted work by only looping over the pixels
    // inside the sphere's radius.  But the example is more clear this
    // way.  In general drawing an object by looping over the whole
    // screen is wasteful.

    int i,j;  // Pixel indices

    int minI = max(0,(int)floor(centerX-radius));
    int maxI = min(viewport.w-1,(int)ceil(centerX+radius));

    int minJ = max(0,(int)floor(centerY-radius));
    int maxJ = min(viewport.h-1,(int)ceil(centerY+radius));

    int maxIColor = 0;
    int maxJColor = 0;
    int maxCam = 0;
    float maxLambert = 0.0f;
    
    for (i=0;i<viewport.w;i++) {
        for (j=0;j<viewport.h;j++) {

            // Location of the center of pixel relative to center of sphere
            float pos[3];
            pos[0] = (i+0.5-centerX);   // Pixel's x coordinate
            pos[1] = (j+0.5-centerY);   // Pixel's y coordinate

            float dist = sqrt(sqr(pos[0]) + sqr(pos[1]));

            if (dist<=radius) {

                // This is the front-facing Z coordinate
                pos[2] = sqrt(radius*radius-dist*dist);

                // Initialize Color Values
                float rgbFinal[3] = {0.0f,0.0f,0.0f};
                
                // Compute the Shading for each channel
                // Ambient Light
                for (int cInd = 0; cInd < 3; cInd++) {
                    rgbFinal[cInd] += sphere.kd[cInd]*sphere.ka[cInd];
                }
                
                // Diffuse Shading
                for (int lightInd = 0; lightInd < numDLs; lightInd++) {
                    // Compute Light Reflectance
                    float lambertCos = dot(pos,dls[lightInd].pos);
                    lambertCos /= mag(pos);
                    lambertCos /= mag(dls[lightInd].pos);
                    if (lambertCos > maxLambert) {
                        maxIColor = i;
                        maxJColor = j;
                        maxCam = dls[lightInd].lightID;
                        maxLambert = lambertCos;
                    }
                    for (int cInd = 0; cInd < 3; cInd++) {
                        rgbFinal[cInd] += sphere.kd[cInd]*dls[lightInd].color[cInd]*fmax(0,lambertCos);
                    }
                    
                }
                for (int lightInd = 0; lightInd < numPLs; lightInd++) {
                    // Compute Light Reflectance
                    float lambertCos = dot(pos,pls[lightInd].pos);
                    lambertCos /= mag(pos);
                    lambertCos /= mag(pls[lightInd].pos);
                    if (lambertCos > maxLambert) {
                        maxIColor = i;
                        maxJColor = j;
                        maxCam = pls[lightInd].lightID;
                        maxLambert = lambertCos;
                    }
                    for (int cInd = 0; cInd < 3; cInd++) {
                        rgbFinal[cInd] += sphere.kd[cInd]*pls[lightInd].color[cInd]*fmax(0,lambertCos);
                    }
                    
                }
                    
                // Specular Shading - Remember to scale from [0,255] to [0,1]
                float rVec[3];
                float eVec[3] = {0.0f, 0.0f, 1.0f};
                for (int lightInd = 0; lightInd < numPLs; lightInd++) {
                    Light light = pls[lightInd];
                    for (int k = 0; k < 3; k++) {
                        rVec[k] = -light.pos[k]/mag(light.pos) + 2*dot(light.pos,pos)/(mag(light.pos)*sqr(mag(pos)))*pos[k];
                    }
                    float phongVal = pow(fmax(0,dot(eVec,rVec)),sphere.sp);
                    for (int cInd = 0; cInd < 3; cInd++) {
                        rgbFinal[cInd] += sphere.ks[cInd]*light.color[cInd]*phongVal;
                    }
                }
                    
                // Clip to [0,1] range
                for (int cInd = 0; cInd < 3; cInd++) {
                    rgbFinal[cInd] = fmin(rgbFinal[cInd],1);
                }
                
                setPixel(i,j,rgbFinal[0],rgbFinal[1],rgbFinal[2]);
            }


        }
    }

    printf("Max Value:\n");
    printf("\t(%d,%d) - Cam %d - %f\n",maxIColor,maxJColor,maxCam,maxLambert);

    glEnd();
}
//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void myDisplay() {

    glClear(GL_COLOR_BUFFER_BIT);				// clear the color buffer

    glMatrixMode(GL_MODELVIEW);			        // indicate we are specifying camera transformations
    glLoadIdentity();				        // make sure transformation is "zero'd"


    // Start drawing
    circle(viewport.w / 2.0 , viewport.h / 2.0 , min(viewport.w, viewport.h) / 3.0);

    glFlush();
    glutSwapBuffers();					// swap buffers (we earlier set double buffer)
}

//***************************************************
// function that does the keyboard interaction
//***************************************************
void myKeyboard(unsigned char key, int x, int y) {
    // Read Key
    switch (key) {
        case 32:    // Spacebar
            printf("Exiting!\n");
            exit(0);
            break;
        
    }
}




// Print Usage Statement
void usage(int arg) {
    printf("\n\nUSAGE:\t[ALL VALUES MUST BE FLOATS]\n");
    printf("\t./as1 [-ka r g b] [-kd r g b] [-ks r g b] [-sp v] \t\\\n\t\t[-pl x y z r g b] [-dl x y z r g b]\n\n");
    switch (arg) {
        case 1: // Print -ka
            printf("\t-ka r g b      \tAmbient Color Coefficients  [0.0, 1.0]\n");
            break;
        case 2: // Print -kd
            printf("\t-kd r g b      \tDiffuse Color Coefficients  [0.0, 1.0]\n");
            break;
        case 3: // Print -ks
            printf("\t-ks r g b      \tSpecular Color Coefficients [0.0, 1.0]\n");
            break;
        case 4: // Print -sp
            printf("\t-sp v          \tSpecular Power Coefficient  [0.0, inf]\n");
            break;
        case 5: // Print -pl
            printf("\t-pl x y z r g b\tPoint Light\n");
            break;
        case 6: // Print -dl
            printf("\t-dl x y z r g b\tDirectional Light\n");
            break;
        default: // Print all
            printf("\t-ka r g b      \tAmbient Color Coefficients  [0.0, 1.0]\n");
            printf("\t-kd r g b      \tDiffuse Color Coefficients  [0.0, 1.0]\n");
            printf("\t-ks r g b      \tSpecular Color Coefficients [0.0, 1.0]\n");
            printf("\t-sp v          \tSpecular Power Coefficient  [0.0, inf]\n");
            printf("\t-pl x y z r g b\tPoint Light\n");
            printf("\t-dl x y z r g b\tDirectional Light\n");
            break;
    }
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
    // Initialize
    numDLs = 0;
    numPLs = 0;
    dls.resize(5);
    pls.resize(5);
    
    // Parse Command Line Arguments
    printf("===============================================\n");
    printf("Loading Command Line Arguments\n");
    printf("===============================================\n");
    printf("NumArgs: %d\n",argc);
    int argInd = 1;
    while (argInd < argc) {
        // Check for Valid Command Line Args
        if (!strcmp(argv[argInd],"-ka"))        // Ambient Sphere Color
        {
            printf("Found Ambient Color (-ka)\n");
            // Verify Correct Number of Following Arguments
            if (argInd + 3 >= argc) {
                printf("ERROR - Invalid number of args\n");
                usage(1);
                return -1;
            }
            // Convert RGB from char to float
            float r = atof(argv[argInd+1]);
            float g = atof(argv[argInd+2]);
            float b = atof(argv[argInd+3]);
            if (sphere.setKvals(0,r,g,b)) {
                usage(1);
                return -1;
            }
            // Increment Active Argument
            argInd += 4;
        }
        else if (!strcmp(argv[argInd],"-kd"))   // Diffuse Sphere Color
        {
            printf("Found Diffuse Color (-kd)\n");
            // Verify Correct Number of Following Arguments
            if (argInd + 3 >= argc) {
                printf("ERROR - Invalid number of args\n");
                usage(2);
                return -1;
            }
            // Convert RGB from char to float
            float r = atof(argv[argInd+1]);
            float g = atof(argv[argInd+2]);
            float b = atof(argv[argInd+3]);
            if (sphere.setKvals(1,r,g,b)) {
                usage(2);
                return -1;
            }
            // Increment Active Argument
            argInd += 4;
        }
        else if (!strcmp(argv[argInd],"-ks"))   // Specular Sphere Color
        {
            printf("Found Specular Color (-ks)\n");
            // Verify Correct Number of Following Arguments
            if (argInd + 3 >= argc) {
                printf("ERROR - Invalid number of args\n");
                usage(3);
                return -1;
            }
            // Convert RGB from char to float
            float r = atof(argv[argInd+1]);
            float g = atof(argv[argInd+2]);
            float b = atof(argv[argInd+3]);
            if (sphere.setKvals(2,r,g,b)) {
                usage(3);
                return -1;
            }
            // Increment Active Argument
            argInd += 4;
        }
        else if (!strcmp(argv[argInd],"-sp"))   // Specular Power Coefficient
        {
            printf("Found Specular Power (-sp)\n");
            // Verify Correct Number of Following Arguments
            if (argInd + 1 >= argc) {
                printf("ERROR - Invalid number of args\n");
                usage(4);
                return -1;
            }
            // Convert RGB from char to float
            float spVal = atof(argv[argInd+1]);
            if (sphere.setSP(spVal)) {
                usage(4);
                return -1;
            }
            // Increment Active Argument
            argInd += 2;
        }
        else if (!strcmp(argv[argInd],"-pl"))   // Point Light
        {
            printf("Found Point Light (-pl) - %d\n",numPLs);
            // Verify still room for more lights
            if (numPLs == 5) {
                printf("ERROR - Max number of point lights is 5\n");
                return -1;
            }
            // Verify Correct Number of Following Arguments
            if (argInd + 6 >= argc) {
                printf("ERROR - Invalid number of args\n");
                usage(5);
                return -1;
            }
            // Convert XYZ,RGB from char to float
            float x = atof(argv[argInd+1]);
            float y = atof(argv[argInd+2]);
            float z = atof(argv[argInd+3]);
            float r = atof(argv[argInd+4]);
            float g = atof(argv[argInd+5]);
            float b = atof(argv[argInd+6]);
            pls[numPLs] = Light(numPLs);
            if (pls[numPLs].setVals(x,y,z,r,g,b)) {
                usage(5);
                return -1;
            }
            // Increment numPLs
            numPLs++;
            // Increment Active Argument
            argInd += 7;
        }
        else if (!strcmp(argv[argInd],"-dl"))   // Directional Light
        {
            printf("Found Directional Light (-dl) - %d\n",numDLs);
            // Verify still room for more lights
            if (numDLs == 5) {
                printf("ERROR - Max number of directional lights is 5\n");
                return -1;
            }
            // Verify Correct Number of Following Arguments
            if (argInd + 6 >= argc) {
                printf("ERROR - Invalid number of args\n");
                usage(6);
                return -1;
            }
            // Convert XYZ,RGB from char to float
            float x = atof(argv[argInd+1]);
            float y = atof(argv[argInd+2]);
            float z = atof(argv[argInd+3]);
            float r = atof(argv[argInd+4]);
            float g = atof(argv[argInd+5]);
            float b = atof(argv[argInd+6]);
            dls[numDLs] = Light(numDLs);
            if (dls[numDLs].setVals(x,y,z,r,g,b)) {
                usage(6);
                return -1;
            }
            // Increment numPLs
            numDLs++;
            // Increment Active Argument
            argInd += 7;
        } else {
            printf("Skipping <%s>\n",argv[argInd]);
            argInd++;
        }
    }

#if DEBUG
    printf("===============================================\n");
    printf("Loaded Parameters\n");
    printf("===============================================\n");
    sphere.print();
    printf("Num Point Lights: %d\n",numPLs);
    for (int i = 0; i < numPLs; i++) {
        pls[i].print();
    }
    printf("Num Directional Lights: %d\n",numDLs);
    for (int i = 0; i < numDLs; i++) {
        dls[i].print();
    }
    
    
    printf("===============================================\n");
    printf("Starting OpenGL\n");
    printf("===============================================\n");
#endif
    
    //This initializes glut
    glutInit(&argc, argv);

    //This tells glut to use a double-buffered window with red, green, and blue channels 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Initalize theviewport size
    viewport.w = 400;
    viewport.h = 400;

    //The size and position of the window
    glutInitWindowSize(viewport.w, viewport.h);
    glutInitWindowPosition(0,0);
    glutCreateWindow(argv[0]);

    initScene();							// quick function to set up scene

    glutDisplayFunc(myDisplay);				// function to run when its time to draw something
    glutReshapeFunc(myReshape);				// function to run when the window gets resized
    
    glutKeyboardFunc(myKeyboard);           // Handle Keyboard Input

    glutMainLoop();							// infinite loop that will keep drawing and resizing
    // and whatever else

    return 0;
}








