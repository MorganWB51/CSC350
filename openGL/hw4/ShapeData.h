#ifndef SHAPEDATA_H
#define SHAPEDATA_H
#include "Vector3.h"
#include <vector>
#include <GL/gl.h>
using namespace std;

class ShapeData {

 public:
    vector<GLfloat> verts; // holds the (x,y,z) postion
    vector<GLfloat> normals; // holds the surface normals
    ShapeData();
    void addVert(GLfloat); // adds a points to the verts vector
    void addNormal(GLfloat); // adds a points to the normal vector
};
#endif