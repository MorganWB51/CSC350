#version 450

in layout(location=0) vec3 Position;
in layout(location = 1) vec3 vecColor;
uniform mat4 trans;
out vec3 glColor;
void main()
{
    vec4 v = vec4(Position, 1.0);
    gl_Position= trans * v;
    glColor = vecColor;
};