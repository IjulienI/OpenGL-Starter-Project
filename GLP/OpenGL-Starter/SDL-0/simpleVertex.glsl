#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; 
  
uniform vec3 color = vec3(1,1,1);
out vec3 ourColor; 
out vec3 ourPosition;
uniform vec3 size = vec3(0.5,0.5,0.5);
uniform vec2 offsets;

void main()
{
    ourPosition = vec3((aPos.x * size.x) + offsets.x, (aPos.y * size.y) + offsets.y, aPos.z * size.z);
    gl_Position = vec4(ourPosition, 1.0);
    ourColor = color;    
}       