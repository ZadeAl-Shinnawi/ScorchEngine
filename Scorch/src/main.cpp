#include "Window/window.h"
#include "Graphics/shader.h"
#include "Graphics/vertexBuffer.h"
#include "Graphics/vertexArray.h"

#include <glad/glad.h>

#include <array>

int main()
{
    // Create a window.
    Scorch::Window window(800, 600, 800, 600, "Scorch 3D Renderer", "3.3");

    // Create a shader.
    Scorch::Shader shader("src/Utilities/vertex_shader.txt", "src/Utilities/fragment_shader.txt");

    // Set up vertex data.
    std::array<float, 18> vertices =
    {
        // positions       // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
    };

    // Create and populate a vertex buffer.
    Scorch::VertexBuffer vb(vertices);

    // Create a vertex array: positions (3 floats), colors (3 floats)
    Scorch::VertexArray va(vb, 3, 3);
    vb.unbind();

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Render loop.
    while (!window.shouldClose())
    {
        // Handle user input.
        window.processInput();

        // Set background color.
        window.clearColor({1.0f, 0.0f, 0.5f, 1.0f});

        // Enable shader and bind the vertex array.
        shader.useProgram();
        va.bind();

        // Draw call.
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers and poll IO events.
        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}