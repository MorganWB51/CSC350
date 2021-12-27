/*
* This is the header file for the Matrix class
*/
#ifndef MATRIX_H
#define MATRIX_H
#define SIZE 4

class Matrix {
  private:
    float data[SIZE][SIZE]; // 2d array the hold the values
    
  public: // Functions at the matrix class can use
    Matrix();
    Matrix(float[][SIZE]);
    Matrix identity(void);
    // Operator overload 
    Matrix operator *(Matrix&) ;
    float* operator [](int);
    void print(void);
    // Function for scaling
    Matrix scaleXYZ(float);
    // Functions for rotating 
    Matrix rotateX(float);
    Matrix rotateY(float);
    Matrix rotateZ(float);
    // Function for translation
    Matrix translateXYZ(float,float,float);
    Matrix perspective(float,float,float);
    
};

#endif
