#pragma once

#include "vertexBuffer.h"

#include <glad/glad.h>

#include <vector>

namespace Scorch
{

// Handles OpenGL vertex array object operations.
class VertexArray
{
public:

	// Initialization constructor.
	template <typename... Args>
	inline VertexArray(const VertexBuffer& vb, Args... args)
	{
		// Generate a unique vertex array ID and bind it.
		glGenVertexArrays(1, &m_vertexArrayID);
		bind();

		m_numFloats = sum(args...);
		m_numAttributes = sizeof...(Args);

		// Store variadic template arguments.
		storeElements(args...);

		generateAttributeLayouts();
		unbind();
	}

	// Deletes the vertex array.
	~VertexArray();

	// Binds the vertex array.
	void bind();

	// Unbinds the vertex array.
	void unbind();

private:
	// Unique vertex array ID.
	unsigned int m_vertexArrayID;

	// Number of total attributes passed into the variadic constructor.
	unsigned int m_numAttributes;

	// Sum of total floats passed into the variadic constructor.
	int m_numFloats;

	// Index access to the variadic constructor arguments.
	std::vector<unsigned int> m_attributes;

	// Store constructor parameters into a vector.
	template <typename... Args>
	void storeElements(Args... args)
	{
		(m_attributes.push_back(static_cast<unsigned int>(args)), ...);
	}

	// Generate vertex attribute layouts.
	void generateAttributeLayouts();

	// Sums all floats passed into the variadic constructor.
	template<typename... Args>
	unsigned int sum(Args... args)
	{
		return (args + ...);
	}
};

} // namespace Scorch