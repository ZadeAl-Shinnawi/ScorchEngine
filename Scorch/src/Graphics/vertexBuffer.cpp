#include "vertexBuffer.h"

#include <glad/glad.h>

namespace Scorch
{

VertexBuffer::VertexBuffer(const std::span<float>& vertices)
	: m_vertices(vertices)
{
	glGenBuffers(1, &m_vertexBufferID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size_bytes(), &m_vertices.front(), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_vertexBufferID);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace Scorch