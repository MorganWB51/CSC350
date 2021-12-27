#version 450

in vec3 glColor;
out vec4 outColor;
void main()
{
    outColor = vec4(glColor,1.0);
};