#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; 
  
//out vec3 ourColor; 
out vec3 ourPosition;
uniform vec3 size = vec3(0.5,0.2,1.0);
uniform float xOffset;

void main()
{
    ourPosition = vec3((aPos.x * size.x) + xOffset, aPos.y * size.y, aPos.z * size.z);
    gl_Position = vec4(ourPosition, 1.0);
    //ourColor = aColor;    
}       