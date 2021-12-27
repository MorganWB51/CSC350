#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H

#include "ShapeData.h"
#include "Vector3.h"
class ShapeGenerator {
  private:
    static vector<Vector3> computeNormals(vector<Vector3>); // Computes the surface normals for the shape
    //vector<Vector3> subdiv(vector<Vector3>); // Breaks one triangle into four
  public:
    static ShapeData makeCube(); // Create the verts and normals for a cube
    static ShapeData makeSphere(); // Create the verts and normals for a Sphere
    static ShapeData makeTriangle(); // Create the verts and normals for a triangle
    static ShapeData makeSquare(); // Create the verts and normals for a Square
    static ShapeData makeOcto(); // Create the verts and normals for a Octohedron
    static ShapeData makeCylinder(); // Create the verts and normals for a Cylinder
};
#endif