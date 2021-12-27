#version 450

in layout(location=0) vec2 Position;
in layout(location = 1) vec3 vecColor;
out vec3 glColor;
void main()
{
    gl_Position = vec4(Position, 0.0, 1.0);
    glColor = vecColor;
};