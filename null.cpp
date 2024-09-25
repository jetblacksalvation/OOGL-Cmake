#include <GL/OOGL.hpp>
#include <iostream>
#include <array>
class Square {
public:
	float x, y, w; // Position (x, y) of the top-left corner and width w
	std::array<float,12> vertices; // Array to hold the vertices of the square

	// Constructor
	Square(float xPos, float yPos, float width) {
		x = xPos;
		y = yPos;
		w = width;
		setUpVertices();  // Set up vertices based on position and width
	}
	void SetPos(float xPos, float yPos) {
		x = xPos;
		y = yPos;
		setUpVertices(); // Recalculate the vertices when position changes
	}
	bool isOverlap(const Square& other) const {
		// Check for non-overlapping conditions. If any of these are true, they do not overlap.
		if (x + w <= other.x ||  // This square is completely to the left of the other
			x >= other.x + other.w ||  // This square is completely to the right of the other
			y + w <= other.y ||  // This square is completely above the other
			y >= other.y + other.w) {  // This square is completely below the other
			return false;
		}

		// If none of the above are true, the squares overlap
		return true;
	}
	// Set up vertices for rendering the square using GL_LINE_STRIP
	void setUpVertices() {
		vertices[0] = x;        vertices[1] = y;        // Top-left
		vertices[2] = x + w;    vertices[3] = y;        // Top-right
		vertices[4] = x + w;    vertices[5] = y - w;    // Bottom-right
		vertices[6] = x;        vertices[7] = y - w;    // Bottom-left
		vertices[8] = x;        vertices[9] = y;        // Top-left

	}
	void drawSelf(GL::Program program, GL::Context& gl)
	{
		GL::VertexBuffer vbo(vertices.data(), sizeof(vertices), GL::BufferUsage::StaticDraw);
		GL::VertexArray vao;

		vao.BindAttribute(program.GetAttribute("position"), vbo, GL::Type::Float, 2, 0, 0);
		gl.DrawArrays(vao, GL::Primitive::LineStrip, 0, 5);
	}

};

int main()
{
	GL::Window window(800, 800, "OpenGL Window", GL::WindowStyle::Close);
	GL::Context& gl = window.GetContext();

	GL::Shader vert(GL::ShaderType::Vertex, "#version 150\nin vec2 position; void main() { gl_Position = vec4(position, 0.0, 1.0); }");
	GL::Shader frag(GL::ShaderType::Fragment, "#version 150\nout vec4 outColor; void main() { outColor = vec4(1.0, 0.0, 0.0, 1.0); }");
	GL::Program program(vert, frag);
	Square square = { -.65,0,0.25f };
	Square squareEnemy = { .65,0,0.25f };
	Square squareBall = { 0,0,0.05 };
	float vx =.01, vy =.01; 

	GL::Event ev;
	while (window.IsOpen())
	{
		while (window.GetEvent(ev)) 
		{
			if (1)
			{
				if (ev.Key.Code == GL::Key::W) {
					square.SetPos(square.x, square.y+.1);
				}
				if (ev.Key.Code == GL::Key::S) {
					square.SetPos(square.x, square.y - .1);
				}
			}
		};

		gl.Clear();
		square.drawSelf(program, gl);
		squareEnemy.drawSelf(program, gl);
		squareBall.drawSelf(program, gl);
		if (squareBall.x < -1.0f || squareBall.x > 1.0f)
			vx *= -1;
		if (squareBall.y < -1.0f || squareBall.y > 1.0f)
			vy *= -1;
		if (squareBall.isOverlap(squareEnemy) || squareBall.isOverlap(square))
		{
			vx *= -1;
			vy *= -1;

		}
		squareBall.SetPos(squareBall.x+ vx, squareBall.y+vy);
		window.Present();
	}

	return 0;
}