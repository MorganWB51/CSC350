#version 450

in layout(location=0) vec3 Position;
in layout(location=2) vec3 Normal;


uniform mat4 scaleMat;
uniform mat4 rotateMat;
uniform mat4 translateMat;
uniform mat4 perspectiveMat;
uniform vec3 cl;

out vec3 rotatedNormal;
out vec4 fragPos;
out vec3 glColor;

void main()
{
 //Rotated Normal
 //vec4 tempNormal = rotateMat * vec4(Normal,1.0);
 //rotatedNormal = vec3(tempNormal);
 rotatedNormal = normalize(mat3(rotateMat) * Normal);  
 //Tranform point
 vec4 v = vec4(Position, 1.0);
 vec4 loc = rotateMat * v;
 vec4 loc2 = scaleMat * loc;
 fragPos = translateMat * loc2; //real 3d location

 //hehe
 gl_Position= perspectiveMat* fragPos;
 glColor = cl;
};