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

ShapeData ShapeGenerator::makeTriangle() {
  ShapeData Tri;
  
  vector<Vector3> Arr ={
    Vector3(0,(sqrt(3)/4.0),0),
    Vector3(.5,-(sqrt(3)/4.0),0),
    Vector3(-.5,-(sqrt(3)/4.0),0),
  };
  
  
  vector<Vector3> norm = ShapeGenerator::computeNormals(Arr);
   //Load into shapedata
    for (auto &vec : norm){
     Tri.addNormal(vec.x);
     Tri.addNormal(vec.y);
     Tri.addNormal(vec.z);
    }
   //Load into shapedata
   for (int i = 0; i < Arr.size(); i++){
     Tri.addVert(Arr[i].x);
     Tri.addVert(Arr[i].y);
     Tri.addVert(Arr[i].z);
   }
  
  return Tri;
}

ShapeData ShapeGenerator::makeSquare() {
  ShapeData Square;
  vector<Vector3> Arr ={ // basic points for a cube
              //front
              Vector3(0.5, 0.5, 0),
              Vector3(0.5, -0.5, 0),
              Vector3(-0.5, -0.5, 0),
              
              Vector3(-0.5, -0.5,0),
              Vector3(-0.5, 0.5, 0),
              Vector3(0.5, 0.5, 0),
  };
  
    vector<Vector3> norm = ShapeGenerator::computeNormals(Arr);
    
    
    //Load into shapedata
    for (auto &vec : norm){
     Square.addNormal(vec.x);
     Square.addNormal(vec.y);
     Square.addNormal(vec.z);
    }
   //Load into shapedata
   for (int i = 0; i < Arr.size(); i++){
     Square.addVert(Arr[i].x);
     Square.addVert(Arr[i].y);
     Square.addVert(Arr[i].z);
   }
  
  
  
  return Square;
}

ShapeData ShapeGenerator::makeOcto() {

  ShapeData Octo;
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
    
    //Calc the normals
    vector<Vector3> norm = ShapeGenerator::computeNormals(Arr);
    
    
    //Load into shapedata
    for (auto &vec : norm){
     Octo.addNormal(vec.x);
     Octo.addNormal(vec.y);
     Octo.addNormal(vec.z);
    }
   //Load into shapedata
   for (int i = 0; i < Arr.size(); i++){
     Octo.addVert(Arr[i].x);
     Octo.addVert(Arr[i].y);
     Octo.addVert(Arr[i].z);
   }
   
   return Octo; 
    
}

ShapeData ShapeGenerator::makeCylinder() {
  ShapeData Cylinder;
  vector<Vector3> square = {
      Vector3(1, 0, 0),
      Vector3(0, -1, 0),
      Vector3(-1, 0, 0),
      Vector3(0, 1, 0),
      Vector3(1, 0, 0),
  };

  vector<Vector3> n;
  for (int i = 0; i < 4; i++)
  {
    n.clear();
    for (int j = 0; j < square.size() - 1; j++)
    {
      Vector3 mid = square[j + 1].midpoint(square[j]);
      n.push_back(square[j]);
      n.push_back(mid);
    }
    n.push_back(square[square.size() - 1]);
    square = n;
  }

  for (int i = 0; i < n.size(); i++){
     n[i].normalize();
   }
  vector<Vector3> top;
  vector<Vector3> bottom;
  for (int i = 0; i < n.size(); i++)
  {
    top.push_back(Vector3(n[i].x, n[i].y, 0.5));
    bottom.push_back(Vector3(n[i].x, n[i].y, -0.5));
  }

  vector<Vector3> vertices;
  for (int i = 0; i < n.size() - 1; i++)
  {
    vertices.push_back(Vector3(n[i + 1].x, n[i + 1].y, 0.5));
    vertices.push_back(Vector3(n[i].x, n[i].y, -0.5));
    vertices.push_back(Vector3(n[i].x, n[i].y, 0.5));
    vertices.push_back(Vector3(n[i + 1].x, n[i + 1].y, 0.5));
    vertices.push_back(Vector3(n[i + 1].x, n[i + 1].y, -0.5));
    vertices.push_back(Vector3(n[i].x, n[i].y, -0.5));
  }

  for (int i = 0; i < top.size() - 1; i++)
  {
    
    vertices.push_back(top[i + 1]);
    vertices.push_back(top[i]);
    vertices.push_back(Vector3(0, 0, 0.5));
  }

  for (int i = 0; i < bottom.size() - 1; i++)
  {
    vertices.push_back(Vector3(0, 0, -0.5));
    vertices.push_back(bottom[i]);
    vertices.push_back(bottom[i + 1]);
  }

     //Calc the normals
    vector<Vector3> norm = ShapeGenerator::computeNormals(vertices);
    
    
    //Load into shapedata
    for (auto &vec : norm){
     Cylinder.addNormal(vec.x);
     Cylinder.addNormal(vec.y);
     Cylinder.addNormal(vec.z);
    }
   //Load into shapedata
   for (int i = 0; i < vertices.size(); i++){
     Cylinder.addVert(vertices[i].x);
     Cylinder.addVert(vertices[i].y);
     Cylinder.addVert(vertices[i].z);
   }

  return Cylinder;
}
