#include <GL/OOGL.hpp>
#include <iostream>
#include <array>
#include <fstream>
#include <filesystem>
#include <chrono>



std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

// Function to calculate elapsed time since the start of the program
float getTimeSinceStart() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = currentTime - startTime; // Time duration in seconds
    return duration.count();  // Return time as a floating point value (seconds)
}

void drawSelf(GL::Program program, GL::Context& gl)
{
    // Vertices for a full-screen square, in normalized device coordinates (-1 to 1)
    
    std::array<float, 12> vertices = {
        -1,1, // Top-left corner
        -1,-1, // Bottom-left corner
        1,-1, // Bottom-right corner
        1,1 // Top-right corner
    };


    // Create the vertex buffer
    GL::VertexBuffer vbo(vertices.data(), vertices.size()*sizeof(float), GL::BufferUsage::StaticDraw);
    GL::VertexArray vao;


    // Draw the rectangle using Triangle Fan, covering the entire screen

    
    vao.BindAttribute(program.GetAttribute("position"), vbo, GL::Type::Float, 2, 0, 0);
    gl.DrawArrays(vao, GL::Primitive::TriangleFan, 0, 4);
}

int main()
{
    // Set up the window and OpenGL context
    GL::Window window(800, 800, "OpenGL Window", GL::WindowStyle::Close);
    GL::Context& gl = window.GetContext();
    startTime = std::chrono::high_resolution_clock::now();


    using std::filesystem::path ; 

    GL::Shader vert;
    GL::Shader frag;
    std::filesystem::path script_path(SCRIPTS);

    vert = GL::Shader(GL::ShaderType::Vertex, script_path / "demo_vertex.glsl") ;
    frag = GL::Shader(GL::ShaderType::Fragment, script_path / "demo_frag.glsl");

    float time = getTimeSinceStart();
    
    // Create the OpenGL program with the shaders
    GL::Program program(vert, frag);

    //adding resolution uniform.
    GL::Uniform reolution = program.GetUniform("resolution");
    glUniform2f(reolution, 800, 800);
    // Event loop
    GL::Event ev;
    while (window.IsOpen())
    {
        while (window.GetEvent(ev))
        {
            // Handle key events (can be expanded later)
            if (ev.Key.Code == GL::Key::W) {
                // Handle W key press
            }
            if (ev.Key.Code == GL::Key::S) {
                // Handle S key press
            }
        }
        GL::Uniform utime_id = program.GetUniform("u_time");
        
        glUniform1f(utime_id, getTimeSinceStart());
        // Draw the full-screen square
        drawSelf(program, gl);

        // Present the window
        window.Present();
    }

    return 0;
}
