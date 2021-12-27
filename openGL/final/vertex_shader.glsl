#version 450

in layout(location=0) vec3 Position;
in layout(location=2) vec3 Normal;


uniform mat4 transMat;
uniform mat4 perspectiveMat;
uniform mat4 rotateMat;
uniform vec3 cl;
uniform vec3 center;

out vec3 rotatedNormal;
out vec4 fragPos;
out vec3 glColor;
out vec3 s;

void main()
{
 //Rotated Normal
 rotatedNormal = normalize(transpose(inverse(mat3(rotateMat))) * Normal); 
 
 //Tranform point
 vec4 v = vec4(Position, 1.0);
 fragPos = transMat* v; //real 3d location

 //hehe
 gl_Position= perspectiveMat* fragPos;
 glColor = cl;
 s = center; // used for the spotlights location
};