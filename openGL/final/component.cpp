/**
* Morgan Williams-Burrell
* CSC 350
* Notes:
*   - This files outlines the function for the component class
**/
#include "component.h"
//construct a shape of a given color
Component::Component(enum shape shape,float r, float g, float b) {
  ShapeGenerator gen;
  red = r;
  green = g;
  blue = b;
  switch(shape){
    case Sphere:
        data = gen.makeSphere();
        vertices = 1536*8;
        break;
    case Cube:
        data = gen.makeCube();
        vertices = 36;
        break;
    case Octahedron:
        data = gen.makeOcto();
        vertices = 24;
        break;
    case Cylinder:
        data = gen.makeCylinder();
        vertices = 1152;
        break;
    }
   hasParent = false;
   parent = NULL;
}

//adds a parent to a component
void Component::linkParent(Component* parent_){
  parent = parent_;
  hasParent = true;
}

//Returns the shapedata(verts + normals)
ShapeData Component::getShapeData(){
 return data;
}

//adds a rotation matrix to a component
void Component::rotate(float x, float y, float z){
  Matrix rX;
  rX = rX.rotateX(x);
  Matrix rY;
  rY = rY.rotateY(y);
  Matrix rZ;
  rZ = rZ.rotateZ(z);
  rotationM = rX * rY * rZ; // Matrix for rotating the points by a given amount
}

//adds a scale matrix to a component
void Component::scale(float x, float y, float z){
  Matrix Scale;
  scaleM = Scale.scaleXYZ(x,y,z);
}

//adds a translation matrix to a component
void Component::translate(float x, float y, float z){
  Matrix Translate;
  translateM = Translate.translateXYZ(x,y,z);
}

//Follow the parent links to build a full tranformation matrix
Matrix Component::getTransformationMatrix(){
  Matrix m;
  if(hasParent){
     Matrix p;
     p = parent->getTransformationMatrix();
  	 m =  p * translateM * scaleM * rotationM;
  }
  else{
      m = translateM * scaleM * rotationM;
  }
    
    return m;
}

//Follow the parent links to build a rotation matrix for normals
Matrix Component::getRotationMatrix(){
  if(hasParent) {
    Matrix p = parent -> getRotationMatrix();
   	return p*rotationM;	
    }else {
	    return rotationM;
    }
}
