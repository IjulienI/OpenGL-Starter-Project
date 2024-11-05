#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; 
  
uniform vec3 color = vec3(1,1,1);
out vec3 ourColor; 
out vec3 ourPosition;
uniform vec3 size = vec3(0.5,0.5,0.5);
uniform vec2 offsets;
uniform float aspectRatio;
uniform int rotation = 0;
uniform float PI = 3.14159265359f;

vec2 Rotate(float angle){   
    angle *= (PI/180);
    return vec2((aPos.x * cos(angle) + aPos.y * sin(angle)), (aPos.y * cos(angle) - aPos.x * sin(angle)));
}

void main()
{
    vec2 facingRot;
    switch(rotation){
        case 0:
            //Left
            facingRot = Rotate(180);
            break;
        case 1:
            //Right
            facingRot = Rotate(0);
            break;
        case 2:
            //Up            
            facingRot = Rotate(270);
            break;
        case 3:
            //Down
            facingRot = Rotate(90);
            break;
    }
    ourPosition = vec3((facingRot.x * size.x) + offsets.x, ((facingRot.y * size.y) * aspectRatio) + offsets.y, aPos.y * size.z);
    gl_Position = vec4(ourPosition, 1.0);
    ourColor = color;    
}       