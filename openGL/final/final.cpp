/**
* Morgan Williams-Burrell
* CSC 350
* Notes:
*   - Make demo will remove the program and recompile, 
*   after that use "MESA_GL_VERSION_OVERRIDE=4.5 ./final" to run program
**/
#include <iostream>
#include <GL/glew.h> // Core OpenGL
#include <GL/glut.h> // Display Window
#include "final.h"
#include "Matrix.h"
#include "Vector3.h"
#include "ShapeGenerator.h"
#include "ShapeData.h"
#include "component.h"
#include <vector>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
using namespace std;

void checkForShaderError(GLuint shader);
void checkForProgramError(GLuint programID);
ShapeGenerator gen;
vector<Component> Helicopter; // contains the shapes that make up the helicopter
vector<Component> World;  // contains the shapes that make up the world

//used to control the helicopters hover
float h = 0;
float control;
int up = 0;

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

//take in information stored in a component and links/sends it to the shader
void loadShape(Component a) {
    GLuint vPosition = 0;
    GLuint vNorm = 2;
    
    //get shape data from component
    ShapeData dat = a.getShapeData();
    vector<GLfloat> points = dat.verts;
    vector<GLfloat> normals = dat.normals;
    
    //send in the position
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(GLfloat), &points.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), BUFFER_OFFSET(0));
    
    //send in the normals
    GLuint normBuffer;
    glGenBuffers(1, &normBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(GLfloat), &normals.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(vNorm);
    glVertexAttribPointer(vNorm, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), BUFFER_OFFSET(0));
    
    //Make the tranformation matrixs
    Matrix Perspective = Perspective.perspective(1,100,90); // Matrix for changing perspective
    Matrix Trans = a.getTransformationMatrix();
    Matrix Rotate = a.getRotationMatrix();
    
    //Send to the shader as uniform
    GLint transMat = glGetUniformLocation(programID, "transMat"); 
    glUniformMatrix4fv(transMat, 1, GL_TRUE, &Trans[0][0]);
    
    GLint perspectiveMat = glGetUniformLocation(programID, "perspectiveMat"); 
    glUniformMatrix4fv(perspectiveMat, 1, GL_TRUE, &Perspective[0][0]);
    
    GLint rotateMat = glGetUniformLocation(programID, "rotateMat"); 
    glUniformMatrix4fv(rotateMat, 1, GL_TRUE, &Rotate[0][0]);
    
    GLint cl = glGetUniformLocation(programID, "cl"); 
    glUniform3f(cl, a.red, a.green, a.blue);    
    
    GLint center = glGetUniformLocation(programID, "center"); 
    glUniform3f(center, 0, h, 7);    
}

void construct(void) {

    Helicopter.push_back(Component(Cube,1,0,0)); //Core   0
    Helicopter.push_back(Component(Sphere,1,0,0)); //Body 1
    Helicopter.push_back(Component(Cylinder,0,0,1)); //Rod 2
    Helicopter.push_back(Component(Cylinder,0,1,0)); // Spinny 3
    Helicopter.push_back(Component(Cube,1,1,0)); // Top Blade1 4
    Helicopter.push_back(Component(Cube,1,1,0)); // Top Blade2 5
    Helicopter.push_back(Component(Cylinder,1,0,0)); // Tail 6
    Helicopter.push_back(Component(Cube,0,0,1)); // Leg1 7
    Helicopter.push_back(Component(Cube,0,0,1)); // Foot1 8
    Helicopter.push_back(Component(Cube,0,0,1)); // Leg2 9
    Helicopter.push_back(Component(Cube,0,0,1)); // Foot2 10
    
    
    
    Helicopter[0].translate(0,0,7);
    
    Helicopter[1].scale(1,.75,.75);
    
    Helicopter[2].translate(.3,1,0);
    Helicopter[2].scale(.25,1.5,.25);
    Helicopter[2].rotate(-90,0,0);
    
    Helicopter[3].translate(0,0,.40);
    Helicopter[3].scale(1.2,1.2,(1/1.5)*.25);
    
    Helicopter[4].scale(1,9,.25);
    
    Helicopter[5].scale(9,1,.25); 
    
    Helicopter[6].rotate(0,90,0);
    Helicopter[6].translate(.75,.15,0);
    Helicopter[6].scale(2,.20,.15);
    
    Helicopter[7].scale(.25,1.5,.25);
    Helicopter[7].translate(0,-.75,-.5);
    
    Helicopter[8].translate(0,-.5,0);
    Helicopter[8].scale((1/.25)*1.5,(1/1.5)*.25,1);
    
    Helicopter[9].scale(.25,1.5,.25);
    Helicopter[9].translate(0,-.75,.5);
    
    Helicopter[10].translate(0,-.5,0);
    Helicopter[10].scale((1/.25)*1.5,(1/1.5)*.25,1);
    
    //core to body
    Helicopter[1].linkParent(&Helicopter[0]); 
    //propeller 
    Helicopter[2].linkParent(&Helicopter[0]); 
    Helicopter[3].linkParent(&Helicopter[2]);
    Helicopter[4].linkParent(&Helicopter[3]); 
    Helicopter[5].linkParent(&Helicopter[3]); 
    //tail to body
    Helicopter[6].linkParent(&Helicopter[1]); 
    //feet stuff
    Helicopter[7].linkParent(&Helicopter[1]); 
    Helicopter[8].linkParent(&Helicopter[7]);
    Helicopter[9].linkParent(&Helicopter[1]);
    Helicopter[10].linkParent(&Helicopter[9]);
  
  
  
    World.push_back(Component(Cube,0,0,0)); //Core 0
    World.push_back(Component(Cube,0.3,.8,.3)); // Ground 1
    World.push_back(Component(Cylinder,244.0/255,192.0/255,134.0/255)); // Landpad 2
    World.push_back(Component(Cylinder, 145.0/255, 78.0/255, 51.0/255)); // Tree Trunk 3
    World.push_back(Component(Octahedron,92.0/255,104.0/255,39.0/255)); // Tree Leaves1 4
    World.push_back(Component(Octahedron,92.0/255,104.0/255,39.0/255)); // Tree Leaves2 5
    World.push_back(Component(Sphere,127.0/255,152.0/255,174.0/255)); // Rock 6
    
    
    
    World[0].translate(0,-4,7);
    
    World[1].scale(100,1,100);
    
    World[2].translate(0,0,0);
    World[2].rotate(90,0,0);
    World[2].scale(3,3,2);
    
    World[3].translate(-8,3,5);
    World[3].rotate(90,0,0);
    World[3].scale(.5,5,.5);
    
    World[4].rotate(-90,0,0);
    World[4].translate(0,0,-.5);
    World[4].scale(2,2,.25);
    
    World[5].rotate(-90,0,0);
    World[5].translate(0,0,-.75);
    World[5].scale(2,2,.25);
    
    World[6].translate(2,0,-3);
    
    World[1].linkParent(&World[0]); //ground to core
    World[2].linkParent(&World[0]); //landingpad to core
    //tree
    World[3].linkParent(&World[0]); 
    World[4].linkParent(&World[3]); 
    World[5].linkParent(&World[3]);
    //rock
    World[6].linkParent(&World[0]);
}

/*
* Code to display the window
* And the transfromation matrix code
*/
void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    
    //Draw the helicopter
    for(int i = 1; i < Helicopter.size(); i++) { 
      loadShape(Helicopter[i]);
      glDrawArrays(GL_TRIANGLES, 0, Helicopter[i].vertices);
    }

    //Draw the world
    for(int i = 1; i < World.size(); i++) { 
      loadShape(World[i]);
      glDrawArrays(GL_TRIANGLES, 0, World[i].vertices);
    }
    
    //Rotate helicopter[3] (Spinny) to spin the blades
    Matrix looper = looper.rotateZ(5);
    Helicopter[3].rotationM = Helicopter[3].rotationM * looper;
    
  
   //FLIGHT CONTROL
   Matrix flight; 
  
   switch(up){
     case 1:
        flight = looper.translateXYZ(0,.02,0);
        control = .02;
        break;
     case 0:
        flight = looper.translateXYZ(0,-.02,0);
        control = -.02;
        break;
    }
    //Translates helicopter[0] (core) to make the helicopter hover
    Helicopter[0].translateM = Helicopter[0].translateM * flight;
    h+=control;
    
    //flips the flight direction at certain hight
    if((int)h == 1.0){
       up = 0;
    }
   
    if((int)h == -1.0){
       up = 1;
    }
  

    glFlush();
    glutPostRedisplay(); //Redraw the scence
    
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
    construct();
    init();

    glutDisplayFunc(display);

    glutMainLoop();
}

