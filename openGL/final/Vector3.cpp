#include <iostream>
#include "Vector3.h"
#include <cmath>
using namespace std;

//constructor
Vector3::Vector3(float _x, float _y, float _z){
  x = _x;
  y = _y;
  z = _z;
}

Vector3::Vector3() {
}

// Operator overloads
Vector3 Vector3::operator +(const Vector3 &obj) const {
  return Vector3(x + obj.x, y + obj.y, z + obj.z);
}

Vector3 Vector3::operator -(const Vector3 &obj) const {
  return Vector3(x - obj.x, y - obj.y, z - obj.z);
}
 
// Compute the dot product of two vectors
float Vector3::dot(const Vector3 &obj) const {
  float result = 0;
  
  result = (x * obj.x) + (y * obj.y) + (z * obj.z);
  
  return result;
  
}

// Compute the Cross product of two vectors
Vector3 Vector3::cross(const Vector3 &obj) const {
  Vector3 res;
  
  res.x = y*obj.z - z*obj.y;
  res.y = z*obj.x - x*obj.z;
  res.z = x*obj.y - y*obj.x;
  
  return res;
}

// Normalize a vector
void Vector3::normalize() {
  float total = sqrt(x*x + y*y + z*z);
  
  x = x / total;
  y = y / total;
  z = z / total;
}

// Flip the signs on a vector
void Vector3::negate() {
  x = -x;
  y = -y;
  z = -z;
}

// Print the contents of the vector as [x, y, z]
void Vector3::print() {
  cout << "[" << x << ", ";
  cout << y << ", ";
  cout << z << "]";
  cout << endl;
}

// Compute the midpoint between to vectors
Vector3 Vector3::midpoint(const Vector3 &obj) const {
  Vector3 res;
  
  res.x = (x + obj.x) / 2.0;
  res.y = (y + obj.y) / 2.0;
  res.z = (z + obj.z) / 2.0;

  return res;
}