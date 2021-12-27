/**
* Morgan Williams-Burrell
* CSC 350
* Notes:
*   - Make demo will remove the program and recompile, 
*   after that use "MESA_GL_VERSION_OVERRIDE=4.5 ./hw2" to run program
**/
#include <iostream>
#include <GL/glew.h> // Core OpenGL
#include <GL/glut.h> // Display Window
#include "hw2.h"
#include "Matrix.h"
#include <vector>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
using namespace std;

void checkForShaderError(GLuint shader);
void checkForProgramError(GLuint programID);

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



/*
* Reads in the color mapping data for "imageArray" in the "hw1.h" header file
* and stores it in a vector named "points"
* @return - a vector containing the color and position data for the image
*/
vector<GLfloat> loadVector(void) {
    int colorPos = 0;
    GLfloat square_size = 1; //Size needed to display a 32x32 image
    vector<GLfloat> points;
    GLfloat near = 0;
    GLfloat far = 32;
    //Fill "points" with GLfloats corresponding to the proper location and color
    for (GLfloat y = 16.0; y > -16.0; y = y - square_size) {
        for (GLfloat x = -16.0; x < 16.0; x = x + square_size) {
            GLfloat red = imageArray[colorPos].r;
            GLfloat green = imageArray[colorPos].g;
            GLfloat blue = imageArray[colorPos].b;
            
            // Use the position and color data to make a "pixle"
            GLfloat cube[] ={
            
              // Front
	            x,  y, near,     // Location - T1
	            red,   green, blue, // Color

	            x+square_size, y, near,
	            red,   green, blue,

              x+square_size,  y-square_size, near,
	            red,   green, blue,

	            x,   y, near,    // Location - T2
	            red,   green, blue, // Color

              x+square_size,  y-square_size, near,
              red,   green, blue,

              x,  y-square_size, near,
              red,   green, blue,
              
              // Back
              x,  y, far,     // Location - T1
	            red,   green, blue, // Color

	            x+square_size, y, far,
	            red,   green, blue,

              x+square_size,  y-square_size, far,
	            red,   green, blue,

	            x,   y, far,    // Location - T2
	            red,   green, blue, // Color

              x+square_size,  y-square_size, far,
              red,   green, blue,

              x,  y-square_size, far,
              red,   green, blue,
              
              // Left
	            x,   y, far,    // Location - T1
	            1,   0, 1, // Color

              x, y, near,
              1,   0, 1,
              
              x,  y-square_size, near,
              1,   0, 1,
              
              x,   y, far,    // Location - T2
	            1,   0, 1, // Color

              x,  y-square_size, near,
              1,   0, 1,
              
              x,  y-square_size, far,
              1,   0, 1,
              
              //Right
              x+square_size, y, far,  // Location - T1
	            1,   1, 0, // Color
              
              x+square_size, y, near, 
	            1,   1, 0,
              
              x+square_size,  y-square_size, near,
	            1,   1, 0,  
              
              x+square_size, y, far,  // Location - T2
	             1,   1, 0, // Color
             
              x+square_size,  y-square_size, near,
	             1,   1, 0,
                         
              x+square_size,  y-square_size, far,
               1,   1, 0,
              
              //Top
              x,  y, far,     // Location - T1
	            0,   1, 1, // Color

	            x+square_size, y, far,
	            0,   1, 1,
             
              x+square_size, y, near,
	            0,   1, 1,
                         
              x,  y, far,     // Location - T2
	            0,   1, 1, // Color
                         
              x+square_size, y, near,
	            0,   1, 1,
              
              x,  y, near,     
	            0,   1, 1, 
               
              //Bottom
              x,  y-square_size, far, // Location - T1
              0,   0, 1, // Color
              
              x+square_size,  y-square_size, far,
              0,   0, 1,
              
              x+square_size,  y-square_size,near,
              0,   0, 1,
              
              x,  y-square_size, far, // Location - T2
              0,   0, 1, // Color
              
              x+square_size,  y-square_size,near,
              0,   0, 1,
              
              x,  y-square_size, near,
              0,   0, 1,
              
            };
            
            for (int i = 0; i < 36*6; i++){
                points.push_back(cube[i]); //adds the floats into the vector
            }
            colorPos++;
        }
    } 
    return points; 
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
    //GLuint programID = glCreateProgram();
    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragShaderID);
    glLinkProgram(programID);
    checkForProgramError(programID);

    glUseProgram(programID);

}

/*
* Starts the code for openGL
*/
void init(void)
{
    GLuint vPosition = 0;
    GLuint vColor = 1;
    GLuint buffer;
    vector<GLfloat> points = loadVector();
    
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(GLfloat), &points.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), BUFFER_OFFSET(3*sizeof(GLfloat))); 
    
    linkShaders();
}

/*
* Code to display the window
* And the transfromation matrix code
*/
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Matrix Scale;
    Scale = Scale.scaleXYZ(.25); // Matrix for scaling the points uniformly by the given amount

    
    Matrix rX;
    rX = rX.rotateX(45);
    Matrix rY;
    rY = rY.rotateY(0);
    Matrix rZ;
    rZ = rZ.rotateZ(45);
    
    Matrix Rotation = rX * rY * rZ; // Matrix for rotating the points by a given amount
    
    Matrix Translate;
    Translate = Translate.translateXYZ(0,2,10); // Matrix for translating the points a given amount
    
    Matrix Tranformation;
    
    /* Debugging prints block
    Scale.print();
    Rotation.print();
    Translate.print();
    */
    
    Matrix perspective;
    perspective = perspective.perspective(1,100,90); // Matrix for changing perspective
    Tranformation =  perspective * Translate * Scale * Rotation; // puts all tranformation together
    Tranformation.print();    
    
    GLint trans = glGetUniformLocation(programID, "trans"); 
    glUniformMatrix4fv(trans, 1, GL_TRUE, &Tranformation[0][0]);// put it in shader as "trans" and links it with shader

    glDrawArrays(GL_TRIANGLES, 0, 6144*6);

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

