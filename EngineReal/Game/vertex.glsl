#version 330 

layout(location = 0) in vec3 aPos; 
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 proj; 
uniform mat4 view; 
uniform mat4 model;



void main() 
{    
	TexCoords = aTexCoords; 
	gl_Position = proj*view*model*vec4(aPos, 1.0);   
	
}