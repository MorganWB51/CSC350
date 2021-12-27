#include <iostream>
#include "ShapeData.h"
using namespace std;


ShapeData::ShapeData(){}

void ShapeData::addVert(GLfloat i){
  verts.push_back(i);
}

void ShapeData::addNormal(GLfloat i){
  normals.push_back(i);
}
