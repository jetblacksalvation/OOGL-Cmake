#version 430 core

out vec4 outColor;
uniform vec2 resolution;  // Screen resolution (used for scaling)
uniform float u_time;  // Time variable, passed by the application

void main()
{
    // Calculate the glow factor using cos and sin
    float glow = (sin(u_time * 2.0) * 0.5 + 0.5); // Oscillates between 0 and 1
    
    // Calculate a smooth color change using sin and cos over time
    float red   = (sin(u_time * 1.0) * 0.5 + 0.5); // Red oscillates between 0 and 1
    float green = (sin(u_time * 1.5) * 0.5 + 0.5); // Green oscillates at a different speed
    float blue  = (cos(u_time * 1.2) * 0.5 + 0.5); // Blue oscillates with a different speed

    // Set the color with the glowing effect applied to the alpha channel
    outColor = vec4(red, green, blue, glow); // The color oscillates between red, green, and blue with a glowing effect
}