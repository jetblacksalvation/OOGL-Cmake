
#version 430 core
in vec2 position; 
uniform vec2 resolution; 
uniform float u_time; 

void main() 
{ 
	gl_Position = vec4(position, 0.0, 1.0); 
};