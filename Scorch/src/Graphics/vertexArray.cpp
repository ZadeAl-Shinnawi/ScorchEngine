#include "vertexArray.h"
#include "vertexBuffer.h"

#include <glad/glad.h>

#include <cstdint>

namespace Scorch
{

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void VertexArray::bind()
{
	glBindVertexArray(m_vertexArrayID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::generateAttributeLayouts()
{
    unsigned int offset = 0;
    unsigned int i = 0;

    for (auto& attribute : m_attributes)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attribute, GL_FLOAT, GL_FALSE,
                              m_numFloats * sizeof(float),
                              reinterpret_cast<std::uintptr_t*>(offset));

        offset += static_cast<unsigned int>(attribute * sizeof(float));

        ++i;
    }

}

} // namespace Scorch