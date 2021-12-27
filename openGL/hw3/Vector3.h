/*
* This is the header file for the Vec3 class
*/
#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {
  public:
    float x, y, z; // position
    //constructors
    Vector3();
    Vector3(float,float,float); 
    // Operator overloads
    Vector3 operator +(const Vector3 &) const;
    Vector3 operator -(const Vector3 &) const;
    float operator [](int i) const;
    float& operator [](int i);
    
    // Functions
    float dot(const Vector3 &) const; 
    Vector3 cross(const Vector3 &) const;
    void normalize();
    void negate();
    void print();
    Vector3 midpoint(const Vector3 &) const;
};
#endif