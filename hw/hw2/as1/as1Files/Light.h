// Light Class

#ifndef LIGHT_H
#define LIGHT_H


class Light {
    public:
        int lightID;   // Light ID Num
        float pos[3];   // Vector Position from center of Sphere
                        // x is Horizontal distance (right => +)
                        // y is Vertical distance (up => +)
                        // z is Depth distance (toward viewer => +)
        float scaledPos[3]; // Position scaled by unit length of measurement
        float color[3]; // RGB Intensity of Light
    
        // Constructors
        Light();
        Light(int ID);
    
        // Print Light Properties
        void print();
        // Set RGB values of one of the Material Color Vectors
        int setVals(float x, float y, float z, float r, float g, float b);
        // Update the ScaledPos with the current window scale
        int updateScale(float scale);
};


#endif