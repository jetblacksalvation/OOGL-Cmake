#version 430 core

out vec4 outColor;
uniform vec2 resolution; 
uniform float u_time;

#ifdef GL_ES
precision mediump float;
#endif


void main(){
	vec2 st = gl_FragCoord.xy/resolution;
    float pct = 0.0;

    pct = distance(st,vec2(0.5));
    vec3 color = vec3(pct);

	gl_FragColor = vec4( color, 1.0 );
}