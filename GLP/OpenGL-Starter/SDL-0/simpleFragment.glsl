#version 330 core

out vec4 FragColor;  
//in vec3 ourColor;
in vec3 ourPosition;
uniform float xOffset;
  
void main()
{
    FragColor = vec4(ourPosition, 1.0);
}