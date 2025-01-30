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
std::vector<float> vertices = {};

void drawSelf(GL::Program program, GL::Context& gl)
{
    // Vertices for a full-screen square, in normalized device coordinates (-1 to 1)
    if (vertices.size() / 2 == 0) 
    {
        std::cout << "not enough vertices\n";
        return;
    }
    // Create the vertex buffer
    GL::VertexBuffer vbo(vertices.data(), vertices.size() * sizeof(float), GL::BufferUsage::DynamicDraw);
    GL::VertexArray vao;




    vao.BindAttribute(program.GetAttribute("position"), vbo, GL::Type::Float, 2, 0, 0);
    gl.DrawArrays(vao, GL::Primitive::Lines, 0, vertices.size()/2 );
}
float lerp(float f1, float f2, float t)
{
    float ret = f1 * (1.f - t) + (f2 * t);
    return ret;
}
std::pair<float, float> lerp(std::pair<float, float> f1, std::pair<float, float> f2, float t)
{
    float x = lerp(f1.first, f2.first, t);
    float y = lerp(f1.second, f2.second, t);
    return { x,y };

}
void renderBezier(GL::Program program, GL::Context& gl)
{
    std::vector<float> vertices_copy = vertices;




    const float divisions = 10;
    for (float x = 0; x < divisions; x++)
    {

        auto vec1 = lerp({ vertices_copy[0],vertices_copy[1] }, { vertices_copy[2],vertices_copy[3] },(1.f/ divisions )*x);
        auto vec2 = lerp({ vertices_copy[4],vertices_copy[5] }, { vertices_copy[6],vertices_copy[7] }, (1.f / divisions) * x);
        vertices_copy.push_back(vec1.first);
        vertices_copy.push_back(vec1.second);

        vertices_copy.push_back(vec2.first);
        vertices_copy.push_back(vec2.second);
    }
    GL::VertexBuffer vbo(vertices_copy.data(), vertices_copy.size() * sizeof(float), GL::BufferUsage::DynamicDraw);
    GL::VertexArray vao;
    vao.BindAttribute(program.GetAttribute("position"), vbo, GL::Type::Float, 2, 0, 0);
    gl.DrawArrays(vao, GL::Primitive::Lines, 0, vertices_copy.size() / 2);

}
int main()
{
    // Set up the window and OpenGL context
    GL::Window window(800, 800, "OpenGL Window", GL::WindowStyle::Fullscreen);
    GL::Context& gl = window.GetContext();
    startTime = std::chrono::high_resolution_clock::now();


    using std::filesystem::path;

    GL::Shader vert;
    GL::Shader frag;
    std::filesystem::path script_path(SCRIPTS);

    vert = GL::Shader(GL::ShaderType::Vertex, script_path / "demo_vertex.glsl");
    frag = GL::Shader(GL::ShaderType::Fragment, script_path / "demo_frag.glsl");

    float time = getTimeSinceStart();

    // Create the OpenGL program with the shaders
    GL::Program program(vert, frag);

    //adding resolution uniform.
    GL::Uniform reolution = program.GetUniform("resolution");
    glUniform2f(reolution, 800, 800);
    GL::Uniform utime_id = program.GetUniform("u_time");
    glUniform1f(utime_id, getTimeSinceStart());

    // Event loop
    GL::Event ev;
    bool hasToUpdate = true;
    bool timeToRenderBezier = false;

    while (window.IsOpen())
    {
        bool keyDown = false;
        while (window.GetEvent(ev))
        {
            // Handle key events (can be expanded later)

            if (ev.Key.Code == GL::Key::W) 
            {
                // Handle W key press
            }
            if (ev.Key.Code == GL::Key::S) 
            {
                // Handle S key press
            }

            if (ev.Mouse.Button == GL::MouseButton::Left and ev.Type == GL::Event::MouseDown and not timeToRenderBezier)
            {

                //std::cout << "Click\n";
                float x = (2.0f * float(window.GetMouseX()) / float(window.GetWidth())) - 1.0f;
                float y = 1.0f - (2.0f * float(window.GetMouseY()) / float(window.GetHeight()));
                
                vertices.push_back(x);
                vertices.push_back(y);
                if (vertices.size() >= 8)
                {
                    timeToRenderBezier = true;
                }
                if (vertices.size() / 4 > 0)
                {
                    vertices.push_back(x);
                    vertices.push_back(y);
                    
                }
                std::cout << "Pos " << x << ',' << y << '\n';
                hasToUpdate = true;
            }
        }

        if (hasToUpdate)
        {
            gl.Clear();

            hasToUpdate = false;
            GL::Uniform utime_id = program.GetUniform("u_time");

            glUniform1f(utime_id, getTimeSinceStart());
            // Draw the full-screen square
            drawSelf(program, gl);
            if (timeToRenderBezier)
            {
                renderBezier(program, gl);
                //render it.
            }

            // Present the window
            window.Present();
            
        }

    }

    return 0;
}
