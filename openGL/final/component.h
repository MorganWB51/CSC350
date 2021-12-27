/**
* Morgan Williams-Burrell
* CSC 350
* Notes:
*   - This file is the header file for the componet class
**/
#ifndef COMPONENT_H
#define COMPONENT_H
#include <cstddef>
#include <vector>
#include "matrix.h"
#include "ShapeGenerator.h"
using namespace std;

//what shape are you
enum shape{
    Sphere, Cube, Cylinder, Octahedron
};

class Component {

    private:
    bool hasParent;
    Component* parent;
    ShapeData data;
   
    
    public:
    //Relative mats
    Matrix rotationM;
    Matrix translateM;
    Matrix scaleM;
    //color
    float red;
    float green;
    float blue;
    //number of verts
    int vertices;
    
    Component(shape,float, float, float); //constructor
    void linkParent(Component*);
    
    //setters for matrixs
    void rotate(float x, float y, float z);
    void scale(float x, float y, float z);
    void translate(float x, float y, float z);
    
    //Getters
    ShapeData getShapeData();
    Matrix getTransformationMatrix();
    Matrix getRotationMatrix();
    
};

#endif