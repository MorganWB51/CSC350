/**
* Morgan Williams-Burrell
* CSC 350
* Notes:
*   - Make demo will remove the program and recompile, 
*   after that use "MESA_GL_VERSION_OVERRIDE=4.5 ./hw3" to run program
**/
#include <iostream>
#include <GL/glew.h> // Core OpenGL
#include <GL/glut.h> // Display Window
#include "hw4.h"
#include "Matrix.h"
#include "Vector3.h"
#include "ShapeGenerator.h"
#include "ShapeData.h"
#include <vector>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
using namespace std;

void checkForShaderError(GLuint shader);
void checkForProgramError(GLuint programID);
ShapeGenerator gen;
/*
* Reads in a shader from a file
* @Param filename - The name of the shader file
*/
char* readShaderCode(const char* filename)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
    {
        cout <<  "File failed to load..." << filename;
        exit(1);
    }
    fseek(fp, 0L, SEEK_END);
    int res = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* data = (char*)calloc(res+1, sizeof(char));
    fread(data, sizeof(char),res, fp);
    //cout << data << endl; //commented out to reduce terminal clutter
    fclose(fp);
    return data;
}


GLuint programID;
/*
* Enables the use of both vertex and fragment shader
*/
void linkShaders(void) {
    // Read in the shader for the given files
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER); // VSO
    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER); // FSO
    
    const char* adapter[1];
    adapter[0] = readShaderCode("vertex_shader.glsl");
    glShaderSource(vertexShaderID, 1, adapter, 0);

    adapter[0] = readShaderCode("frag_shader.glsl");
    glShaderSource(fragShaderID, 1, adapter, 0);

    // Compile Shaders and check for errors
    glCompileShader(vertexShaderID);
    checkForShaderError(vertexShaderID);
    glCompileShader(fragShaderID);
    checkForShaderError(fragShaderID);
    
    // Link the shaders to the program
    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragShaderID);
    glLinkProgram(programID);
    checkForProgramError(programID);

    glUseProgram(programID);

}

/*
* Starts the code for openGL (Just shaders now)
*/
void init(void)
{    
    linkShaders();
}

void loadShape(ShapeData a) {
    GLuint vPosition = 0;
    GLuint vColor = 1;
    GLuint vNorm = 2;
    GLuint buffer;
    vector<GLfloat> points = a.verts;
    vector<GLfloat> normals = a.normals;
    GLuint normBuffer;
    
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(GLfloat), &points.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), BUFFER_OFFSET(0));
    
    
    glGenBuffers(1, &normBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(GLfloat), &normals.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(vNorm);
    glVertexAttribPointer(vNorm, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), BUFFER_OFFSET(0));
}

/*
* Code to display the window
* And the transfromation matrix code
*/
void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
     GLfloat colorData[] = {
      0.25f , 0.25f, 0.28f, // Gray
      1.00f , 1.0f, 1.0f, // white
      0.32f , 0.67f, 0.55f, // Light Green
      0.81f , 0.35f, 0.40f, // Dark Green
      0.70f , 0.18f, 0.25f, // Dark Red
      0.18f , 0.34f, 0.44f, // Dark Blue
      1.00f , 0.00f, 0.00f, // Red
      };

//---------------------------CUBE WORK----------------------------------------------------------------------------------------------------      
    ShapeData cube = gen.makeCube();
    loadShape(cube);
    for(int i=0; i<5; i++) {
    
    Matrix Scale;
    Scale = Scale.scaleXYZ(1); // Matrix for scaling the points uniformly by the given amount
    
    Matrix rX;
    rX = rX.rotateX(0+(i*20));
    Matrix rY;
    rY = rY.rotateY(0+(i*20));
    Matrix rZ;
    rZ = rZ.rotateZ(0);
    Matrix Rotation = rX * rY * rZ; // Matrix for rotating the points by a given amount
    
    Matrix Translate;
    Translate = Translate.translateXYZ(-4+(2*i),4.5,6); // Matrix for translating the points a given amount
   
    Matrix perspective;
    perspective = perspective.perspective(1,100,90); // Matrix for changing perspective
    
    //Send to the shader as uniform
    GLint scaleMat = glGetUniformLocation(programID, "scaleMat"); 
    glUniformMatrix4fv(scaleMat, 1, GL_TRUE, &Scale[0][0]);
    
    GLint rotateMat = glGetUniformLocation(programID, "rotateMat"); 
    glUniformMatrix4fv(rotateMat, 1, GL_TRUE, &Rotation[0][0]);
    
    GLint translateMat = glGetUniformLocation(programID, "translateMat"); 
    glUniformMatrix4fv(translateMat, 1, GL_TRUE, &Translate[0][0]);
    
    GLint perspectiveMat = glGetUniformLocation(programID, "perspectiveMat"); 
    glUniformMatrix4fv(perspectiveMat, 1, GL_TRUE, &perspective[0][0]);
    
    GLint cl = glGetUniformLocation(programID, "cl"); 
    glUniform3f(cl, colorData[0], colorData[1], colorData[2]);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    }
//---------------------------SPHERE WORK----------------------------------------------------------------------------------------------------     
    ShapeData sphere = gen.makeSphere();
    loadShape(sphere);
    for(int i=0; i<5; i++) {
    
    Matrix Scale;
    Scale = Scale.scaleXYZ(1); // Matrix for scaling the points uniformly by the given amount
    
    Matrix rX;
    rX = rX.rotateX(0+(i*20));
    Matrix rY;
    rY = rY.rotateY(0+(i*20));
    Matrix rZ;
    rZ = rZ.rotateZ(0);
    Matrix Rotation = rX * rY * rZ; // Matrix for rotating the points by a given amount
    
    Matrix Translate;
    Translate = Translate.translateXYZ(1+(3*i),4,6); // Matrix for translating the points a given amount
   
    Matrix perspective;
    perspective = perspective.perspective(1,100,90); // Matrix for changing perspective
    
    //Send to the shader as uniform
    GLint scaleMat = glGetUniformLocation(programID, "scaleMat"); 
    glUniformMatrix4fv(scaleMat, 1, GL_TRUE, &Scale[0][0]);
    
    GLint rotateMat = glGetUniformLocation(programID, "rotateMat"); 
    glUniformMatrix4fv(rotateMat, 1, GL_TRUE, &Rotation[0][0]);
    
    GLint translateMat = glGetUniformLocation(programID, "translateMat"); 
    glUniformMatrix4fv(translateMat, 1, GL_TRUE, &Translate[0][0]);
    
    GLint perspectiveMat = glGetUniformLocation(programID, "perspectiveMat"); 
    glUniformMatrix4fv(perspectiveMat, 1, GL_TRUE, &perspective[0][0]);
    
    GLint cl = glGetUniformLocation(programID, "cl"); 
    glUniform3f(cl, colorData[3], colorData[4], colorData[5]);
    
    glDrawArrays(GL_TRIANGLES, 0, 5000);
    
    }
    
    //---------------------------Octo WORK----------------------------------------------------------------------------------------------------      
    ShapeData Octo = gen.makeOcto();
    loadShape(Octo);
    for(int i=0; i<5; i++) {
    
    Matrix Scale;
    Scale = Scale.scaleXYZ(1); // Matrix for scaling the points uniformly by the given amount
    
    Matrix rX;
    rX = rX.rotateX(0+(i*20));
    Matrix rY;
    rY = rY.rotateY(0+(i*20));
    Matrix rZ;
    rZ = rZ.rotateZ(0);
    Matrix Rotation = rX * rY * rZ; // Matrix for rotating the points by a given amount
    
    Matrix Translate;
    Translate = Translate.translateXYZ(-4+(3*i),1.5,6); // Matrix for translating the points a given amount
   
    Matrix perspective;
    perspective = perspective.perspective(1,100,90); // Matrix for changing perspective
    
    //Send to the shader as uniform
    GLint scaleMat = glGetUniformLocation(programID, "scaleMat"); 
    glUniformMatrix4fv(scaleMat, 1, GL_TRUE, &Scale[0][0]);
    
    GLint rotateMat = glGetUniformLocation(programID, "rotateMat"); 
    glUniformMatrix4fv(rotateMat, 1, GL_TRUE, &Rotation[0][0]);
    
    GLint translateMat = glGetUniformLocation(programID, "translateMat"); 
    glUniformMatrix4fv(translateMat, 1, GL_TRUE, &Translate[0][0]);
    
    GLint perspectiveMat = glGetUniformLocation(programID, "perspectiveMat"); 
    glUniformMatrix4fv(perspectiveMat, 1, GL_TRUE, &perspective[0][0]);
    
    GLint cl = glGetUniformLocation(programID, "cl"); 
    glUniform3f(cl, colorData[6], colorData[7], colorData[8]);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    }
//---------------------------Cylinder WORK----------------------------------------------------------------------------------------------------     
    ShapeData Cylinder = gen.makeCylinder();
    loadShape(Cylinder);
    for(int i=0; i<5; i++) {
    
    Matrix Scale;
    Scale = Scale.scaleXYZ(1); // Matrix for scaling the points uniformly by the given amount
    
    Matrix rX;
    rX = rX.rotateX(0+(i*90));
    Matrix rY;
    rY = rY.rotateY(0+(i*20));
    Matrix rZ;
    rZ = rZ.rotateZ(0);
    Matrix Rotation = rX * rY * rZ; // Matrix for rotating the points by a given amount
    
    Matrix Translate;
    Translate = Translate.translateXYZ(1+(3*i),-1,5); // Matrix for translating the points a given amount
   
    Matrix perspective;
    perspective = perspective.perspective(1,100,90); // Matrix for changing perspective
    
    //Send to the shader as uniform
    GLint scaleMat = glGetUniformLocation(programID, "scaleMat"); 
    glUniformMatrix4fv(scaleMat, 1, GL_TRUE, &Scale[0][0]);
    
    GLint rotateMat = glGetUniformLocation(programID, "rotateMat"); 
    glUniformMatrix4fv(rotateMat, 1, GL_TRUE, &Rotation[0][0]);
    
    GLint translateMat = glGetUniformLocation(programID, "translateMat"); 
    glUniformMatrix4fv(translateMat, 1, GL_TRUE, &Translate[0][0]);
    
    GLint perspectiveMat = glGetUniformLocation(programID, "perspectiveMat"); 
    glUniformMatrix4fv(perspectiveMat, 1, GL_TRUE, &perspective[0][0]);
    
    GLint cl = glGetUniformLocation(programID, "cl"); 
    glUniform3f(cl, colorData[9], colorData[10], colorData[11]);
    
    glDrawArrays(GL_TRIANGLES, 0, 5000);
    
    }
    //---------------------------Square WORK----------------------------------------------------------------------------------------------------      
    ShapeData Square = gen.makeSquare();
    loadShape(Square);
    for(int i=0; i<5; i++) {
    
    Matrix Scale;
    Scale = Scale.scaleXYZ(10); // Matrix for scaling the points uniformly by the given amount
    
    Matrix rX;
    rX = rX.rotateX(0+(i*20));
    Matrix rY;
    rY = rY.rotateY(0+(i*20));
    Matrix rZ;
    rZ = rZ.rotateZ(0);
    Matrix Rotation = rX * rY * rZ; // Matrix for rotating the points by a given amount
    
    Matrix Translate;
    Translate = Translate.translateXYZ(-5+(10*i),-3,10); // Matrix for translating the points a given amount
   
    Matrix perspective;
    perspective = perspective.perspective(1,100,90); // Matrix for changing perspective
    
    //Send to the shader as uniform
    GLint scaleMat = glGetUniformLocation(programID, "scaleMat"); 
    glUniformMatrix4fv(scaleMat, 1, GL_TRUE, &Scale[0][0]);
    
    GLint rotateMat = glGetUniformLocation(programID, "rotateMat"); 
    glUniformMatrix4fv(rotateMat, 1, GL_TRUE, &Rotation[0][0]);
    
    GLint translateMat = glGetUniformLocation(programID, "translateMat"); 
    glUniformMatrix4fv(translateMat, 1, GL_TRUE, &Translate[0][0]);
    
    GLint perspectiveMat = glGetUniformLocation(programID, "perspectiveMat"); 
    glUniformMatrix4fv(perspectiveMat, 1, GL_TRUE, &perspective[0][0]);
    
    GLint cl = glGetUniformLocation(programID, "cl"); 
    glUniform3f(cl, colorData[12], colorData[13], colorData[14]);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    }
//---------------------------Triangle WORK----------------------------------------------------------------------------------------------------     
    ShapeData Triangle = gen.makeTriangle();
    loadShape(Triangle);
    for(int i=0; i<5; i++) {
    
    Matrix Scale;
    Scale = Scale.scaleXYZ(1.5); // Matrix for scaling the points uniformly by the given amount
    
    Matrix rX;
    rX = rX.rotateX(0+(i*20));
    Matrix rY;
    rY = rY.rotateY(0+(i*20));
    Matrix rZ;
    rZ = rZ.rotateZ(0);
    Matrix Rotation = rX * rY * rZ; // Matrix for rotating the points by a given amount
    
    Matrix Translate;
    Translate = Translate.translateXYZ(0+(3*i),-4,6); // Matrix for translating the points a given amount
   
    Matrix perspective;
    perspective = perspective.perspective(1,100,90); // Matrix for changing perspective
    
    //Send to the shader as uniform
    GLint scaleMat = glGetUniformLocation(programID, "scaleMat"); 
    glUniformMatrix4fv(scaleMat, 1, GL_TRUE, &Scale[0][0]);
    
    GLint rotateMat = glGetUniformLocation(programID, "rotateMat"); 
    glUniformMatrix4fv(rotateMat, 1, GL_TRUE, &Rotation[0][0]);
    
    GLint translateMat = glGetUniformLocation(programID, "translateMat"); 
    glUniformMatrix4fv(translateMat, 1, GL_TRUE, &Translate[0][0]);
    
    GLint perspectiveMat = glGetUniformLocation(programID, "perspectiveMat"); 
    glUniformMatrix4fv(perspectiveMat, 1, GL_TRUE, &perspective[0][0]);
    
    GLint cl = glGetUniformLocation(programID, "cl"); 
    glUniform3f(cl, colorData[15], colorData[16], colorData[17]);
    
    glDrawArrays(GL_TRIANGLES, 0, 5000);
    
    }
    glFlush();
    
}

/* 
* Video Guys Code - Jamie King
* Detects errors in shader files
*/
void checkForShaderError(GLuint shader)
{
    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE)
    {
        cout << compileStatus << endl;
        GLint maxLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        cout << maxLength << endl;
        GLchar* errorLog = new GLchar[maxLength];
        GLsizei bufferSize;
        glGetShaderInfoLog(shader, maxLength, &bufferSize, errorLog);
        cout << errorLog << endl;
        delete [] errorLog;
    }
}

/*
* Video Guys Code - Jamie King
* Detects errors in the openGL program
*/
void checkForProgramError(GLuint programID)
{
    GLint linkStatus;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE)
    {
        GLint maxLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
        GLchar* errorLog = new GLchar[maxLength];
        GLsizei bufferSize;
        glGetProgramInfoLog(programID, maxLength, &bufferSize, errorLog);
        cout << errorLog << endl;
        delete [] errorLog;
    }
}

/*
* The main method
*/
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(512, 512);
    glutCreateWindow(argv[0]);
    glEnable(GL_DEPTH_TEST);

    if (glewInit()) 
    {
	    cerr << "Unable to initialize GLEW ... exiting" << endl;
	    exit(EXIT_FAILURE);
    }
    
    cout << glGetString(GL_VERSION) << endl;

    init();

    glutDisplayFunc(display);

    glutMainLoop();
}

