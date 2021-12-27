/*
* Morgan Williams-Burrell
* CSC 350
* This file contains the function for the matrix class
* additionally it allows for the overloading of '*' and '[]'
*/

#include <iostream>
#include "Matrix.h"
#include <cmath>
using namespace std;

/*
* Basic constructor
*/
Matrix::Matrix(void) {
  for(int i=0; i<SIZE; i++)
    for(int j=0; j<SIZE; j++)
      data[i][j] = 0;
}

/*
* Makes and identity matrix
*/
Matrix Matrix::identity(void){
  float id[4][4] = {
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1},
  };

  Matrix Mid = Matrix(id);
  return Mid;
}

/*
* Converts an array of floats to the matrix class
*/
Matrix::Matrix(float convert[SIZE][SIZE]){
  for(int i=0; i<SIZE; i++)
    for(int j=0; j<SIZE; j++)
      data[i][j] = convert[i][j];
}

/*
* overload the reference operator for the matrix class
*/
float* Matrix::operator [](int i) {
  return data[i];
}

/*
* overload the * operator for the matrix class
*/
Matrix Matrix::operator *(Matrix &obj)  {
  
  Matrix mult;
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      for(int k = 0; k < 4; k++) {
          mult[i][j] += data[i][k] * obj[k][j];
      }
    }
  }
  
  return mult;
}

/*
* prints the contents of the matrix
*/
void Matrix::print() {
  for(int i=0; i<SIZE; i++){
    for(int j=0; j<SIZE; j++){
      cout << data[i][j] << " ";
    }
    cout << endl;
    }
}

/*
* Returns a matrix that is scaled by i uniformly
*/
Matrix Matrix::scaleXYZ(float i) {
  float scale[4][4] = {
    {i,0,0,0},
    {0,i,0,0},
    {0,0,i,0},
    {0,0,0,1},
  };
  
  Matrix converted = Matrix(scale);
  return converted;
}

/*
* Returns a matrix that is rotated by i on the X axis
*/
Matrix Matrix::rotateX(float i) {
    float rads = i * (M_PI / 180);
    float RotateX[4][4] = {
    {1,0,0,0},
    {0,cos(rads),-sin(rads),0},
    {0,sin(rads), cos(rads),0},
    {0,0,0,1},
  };
  
  Matrix converted = Matrix(RotateX);
  return converted;
}

/*
* Returns a matrix that is rotated by i on the Y axis
*/
Matrix Matrix::rotateY(float i){
float rads = i * (M_PI / 180);
float RotateY[4][4] = {
    {cos(rads),0,sin(rads),0},
    {0,1,0,0},
    {-sin(rads),0,cos(rads),0},
    {0,0,0,1},
  };
  
  Matrix converted = Matrix(RotateY);
  return converted;
}

/*
* Returns a matrix that is rotated by i on the Z axis
*/
Matrix Matrix::rotateZ(float i){
float rads = i * (M_PI / 180);
float RotateZ[4][4] = {
    {cos(rads),-sin(rads),0,0},
    {sin(rads),cos(rads),0,0},
    {0,0,1,0},
    {0,0,0,1},
  };
  
  Matrix converted = Matrix(RotateZ);
  return converted;
}

/*
* Returns a matrix that is translate by x, y, and z by the given amount 
*/
Matrix Matrix::translateXYZ(float x, float y, float z){
float trans[4][4] = {
    {1,0,0,x},
    {0,1,0,y},
    {0,0,1,z},
    {0,0,0,1},
  };
  
  Matrix converted = Matrix(trans);
  return converted;
}

/*
* Returns a perspective matrix give a near, far, and angle
*/
Matrix Matrix::perspective(float near, float far, float degrees) {
  float tan_half_angle = tan((degrees*M_PI)/360);
  float a = 1 / tan_half_angle; 
  float b = 1 /tan_half_angle;
  float c = (-far-near)/(near-far);
  float d = (2*far*near)/(near-far);
  float e = 1.0;
  
  float pro[4][4] = {
    {a,0,0,0},
    {0,b,0,0},
    {0,0,c,d},
    {0,0,e,0},
  };
  
  Matrix converted = Matrix(pro);
  return converted;
}

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  