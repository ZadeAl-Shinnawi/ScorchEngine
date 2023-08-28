#pragma once

#include <span>

namespace Scorch
{

// Handles OpenGL vertex buffer object operations.
class VertexBuffer
{
public:
	// Initialization constructor:.
	VertexBuffer(const std::span<float>& vertices);

    // Deletes the vertex buffer.
    ~VertexBuffer();

    // Binds the vertex buffer.
    void bind();

    // Unbinds the vertex buffer.
    void unbind();

private:
    // Unique window ID.
    unsigned int m_vertexBufferID;

    // Vertex buffer data.
    std::span<float> m_vertices;
};

} // namespace Scorch