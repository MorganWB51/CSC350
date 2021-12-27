#include <iostream>
#include "ShapeGenerator.h"
#include "ShapeData.h"
#include <cmath>
#include "Vector3.h"

using namespace std;


// Computes the surface normals for the shape
vector<Vector3> ShapeGenerator::computeNormals(vector<Vector3> vertices){ 
  vector<Vector3> normals;
  for (int i = 0; i < vertices.size(); i += 3)
  {
    Vector3 U = vertices[i+1] - vertices[i];
    Vector3 V = vertices[i+2] - vertices[i];
    Vector3 normal = U.cross(V);
    for (int i = 0; i < 3; i++)
    {
      normals.push_back(normal);
    }
  }
  return normals;
}


// Create the verts and normals for a cube
ShapeData ShapeGenerator::makeCube() {
  ShapeData cube;
  vector<Vector3> Arr ={ // basic points for a cube
              //front
              Vector3(0.5, 0.5, -0.5),
              Vector3(0.5, -0.5, -0.5),
              Vector3(-0.5, -0.5, -0.5),
              
              Vector3(-0.5, -0.5, -0.5),
              Vector3(-0.5, 0.5, -0.5),
              Vector3(0.5, 0.5, -0.5),
              
              //back
              Vector3(0.5, 0.5, 0.5),
              Vector3(-0.5, 0.5, 0.5),
              Vector3(-0.5, -0.5, 0.5),
              
              Vector3(-0.5, -0.5, 0.5),
              Vector3(0.5, -0.5, 0.5),
              Vector3(0.5, 0.5, 0.5),
              
              //left
              Vector3(-0.5, 0.5, -0.5),
              Vector3(-0.5, -0.5, -0.5),
              Vector3(-0.5, -0.5, 0.5),
              
              Vector3(-0.5, -0.5, 0.5),
              Vector3(-0.5, 0.5, 0.5),
              Vector3(-0.5, 0.5, -0.5),
              
              
              //right
              Vector3(0.5, 0.5, 0.5),
              Vector3(0.5, -0.5, 0.5),
              Vector3(0.5, -0.5, -0.5),
              
              Vector3(0.5, -0.5, -0.5),
              Vector3(0.5, 0.5, -0.5),
              Vector3(0.5, 0.5, 0.5),
              
              //top
              Vector3(-0.5, 0.5, -0.5),
              Vector3(-0.5, 0.5, 0.5),
              Vector3(0.5, 0.5, 0.5),
              
              Vector3(0.5, 0.5, 0.5),
              Vector3(0.5, 0.5, -0.5),
              Vector3(-0.5, 0.5, -0.5),
              
              //bottom
              Vector3(-0.5, -0.5, -0.5),
              Vector3(0.5, -0.5, -0.5),
              Vector3(0.5, -0.5, 0.5),
              
              Vector3(0.5, -0.5, 0.5),
              Vector3(-0.5, -0.5, 0.5),
              Vector3(-0.5, -0.5, -0.5),  
                  
            };
            
            vector<Vector3> norm = ShapeGenerator::computeNormals(Arr); //get the normals
            
            //Load the normals into the shapedata
            for (auto &vec : norm){
              //vec.print();
              cube.addNormal(vec.x);
              cube.addNormal(vec.y);
              cube.addNormal(vec.z);
            }
            
            //Load the verts into the shapedata
            for (auto &vec : Arr){
              //vec.print();
              cube.addVert(vec.x);
              cube.addVert(vec.y);
              cube.addVert(vec.z);
            }
            
            
  return cube;
}

ShapeData ShapeGenerator::makeSphere() {
  ShapeData sphere;
  
  //NOTE: First vec is the point
  vector<Vector3> Arr ={ //Basic points for an octahedron
    // top front
    Vector3(0,1,0),
    Vector3(1,0,-1),
    Vector3(-1,0,-1),
    // top left
    Vector3(0,1,0),
    Vector3(-1,0,-1),
    Vector3(-1,0,1),
    // top right
    Vector3(0,1,0),
    Vector3(1,0,1),
    Vector3(1,0,-1),
    // top back
    Vector3(0,1,0),
    Vector3(-1,0,1),
    Vector3(1,0,1),
   
    // bottom front
    Vector3(0,-1,0),
    Vector3(-1,0,-1),
    Vector3(1,0,-1),
    // bottom left
    Vector3(0,-1,0),
    Vector3(-1,0,1),
    Vector3(-1,0,-1),
    // bottom right
    Vector3(0,-1,0),
    Vector3(1,0,-1),
    Vector3(1,0,1),
    //bottom back
    Vector3(0,-1,0),
    Vector3(1,0,1),
    Vector3(-1,0,1),
    
    };
    
    //Subdiv
    int times = 3;
    for(int i = 0; i < times; i++){
    
      vector<Vector3> result;
      for(int i = 0; i < Arr.size(); i+=3) {
        Vector3 a = Arr[i].midpoint(Arr[i+1]);
        Vector3 b = Arr[i].midpoint(Arr[i+2]);
        Vector3 c = Arr[i+1].midpoint(Arr[i+2]);
     
        result.push_back(Arr[i]);
        result.push_back(a);
        result.push_back(b);
      
        result.push_back(Arr[i+1]);
        result.push_back(c);
        result.push_back(a);
      
        result.push_back(Arr[i+2]);
        result.push_back(b);
        result.push_back(c);
      
        result.push_back(a);
        result.push_back(c);
        result.push_back(b);
      
      
      }
      Arr = result;
    }
    
   
   //Normalize the points to "blow up" the octahedron
   for (int i = 0; i < Arr.size(); i++){
     Arr[i].normalize();
   }
    
    //Calc the normals
    vector<Vector3> norm = ShapeGenerator::computeNormals(Arr);
    
    
    //Load into shapedata
    for (auto &vec : norm){
     sphere.addNormal(vec.x);
     sphere.addNormal(vec.y);
     sphere.addNormal(vec.z);
    }
   //Load into shapedata
   for (int i = 0; i < Arr.size(); i++){
     sphere.addVert(Arr[i].x);
     sphere.addVert(Arr[i].y);
     sphere.addVert(Arr[i].z);
   }
  
   
  return sphere;
}
