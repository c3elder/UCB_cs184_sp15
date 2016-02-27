// Sphere Material Class

#ifndef SPHERE_H
#define SPHERE_H


class Sphere {
    public:
        float ka[3];    // Ambient Color of Sphere Material
        float kd[3];    // Diffuse Color of Sphere Material
        float ks[3];    // Specular Color of Sphere Material
        float sp;       // Power Coefficient of specular color
    
        // Constructors
        Sphere();
    
        // Print Sphere Material Properties
        void print();
        // Set RGB values of one of the Material Color Vectors
        int setKvals(int whichColor, float r, float g, float b);
        // Set Specular Power Coefficient
        int setSP(float spVal);
};


#endif