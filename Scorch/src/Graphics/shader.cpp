#include "shader.h"

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

namespace Scorch
{

Shader::Shader(const std::string& vertexShaderFilePath,
			   const std::string& fragmentShaderFilePath)
	: m_vertexShaderID(glCreateShader(GL_VERTEX_SHADER)),
	  m_fragmentShaderID(glCreateShader(GL_FRAGMENT_SHADER)),
	  m_shaderProgramID(glCreateProgram()),
	  m_vertexShaderFilePath(vertexShaderFilePath),
	  m_fragmentShaderFilePath(fragmentShaderFilePath)
{
	compileShaders();
	linkShaders();

	// Delete vertex and fragment shaders.
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

Shader::~Shader()
{
	glDeleteProgram(m_shaderProgramID);
}

void Shader::useProgram() const
{
	glUseProgram(m_shaderProgramID);
}

void Shader::compileShaders() const
{
	// Load vertex and fragment shader source code.
	std::string vertexShaderSourceString =
				loadShaderSource(m_vertexShaderFilePath);

	std::string fragmentShaderSourceString =
				loadShaderSource(m_fragmentShaderFilePath);

	// Convert vertex and fragment shader strings into C strings.
	const char* vertexShaderSourcePtr = vertexShaderSourceString.c_str();
	const char* fragmentShaderSourcePtr = fragmentShaderSourceString.c_str();

	// Compile vertex shader and check for errors.
	glShaderSource(m_vertexShaderID, 1, &vertexShaderSourcePtr, nullptr);
	glCompileShader(m_vertexShaderID);
	shaderErrorCheck(m_vertexShaderID, GL_COMPILE_STATUS, "VERTEX");

	// Compile fragment shader and check for errors.
	glShaderSource(m_fragmentShaderID, 1, &fragmentShaderSourcePtr, nullptr);
	glCompileShader(m_fragmentShaderID);
	shaderErrorCheck(m_fragmentShaderID, GL_COMPILE_STATUS, "FRAGMENT");
}

void Shader::shaderErrorCheck(unsigned int shaderID, GLenum type,
							  const std::string& shaderType) const
{
	int success;
	std::string infoLog;

	// Compilation errors.
	if (type == GL_COMPILE_STATUS)
	{
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shaderID, 512, nullptr, &infoLog[0]);

			std::cerr << "ERROR::SHADER::" << shaderType
					  << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
	// Linking errors.
	else if (type == GL_LINK_STATUS)
	{
		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderID, 512, nullptr, &infoLog[0]);
			std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
					  << infoLog << std::endl;
		}
	}
	// General errors.
	else
	{
		std::cerr << "Invalid shader type" << std::endl;
	}
}

void Shader::linkShaders() const
{
	// Attach vertex and fragment shaders.
	glAttachShader(m_shaderProgramID, m_vertexShaderID);
	glAttachShader(m_shaderProgramID, m_fragmentShaderID);

	// Link shader program.
	glLinkProgram(m_shaderProgramID);

	// Ensure the shader program was linked correctly.
	shaderErrorCheck(m_shaderProgramID, GL_LINK_STATUS, "LINK");
}

std::string Shader::loadShaderSource(const std::string& shaderFilePath) const
{
	// Retrieve the vertex and fragment  source code from filePath
	std::string shaderCode;
	std::ifstream vertexShaderFile;

	// Ensure that ifstream objects can throw exceptions.
	vertexShaderFile.exceptions(std::ifstream::failbit |
								std::ifstream::badbit);

	try
	{
		vertexShaderFile.open(shaderFilePath);
		std::stringstream vShaderStream;

		// Read the file's buffer contents into a stream.
		vShaderStream << vertexShaderFile.rdbuf();

		vertexShaderFile.close();

		// Convert the stream into a string.
		shaderCode = vShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: "
				  << e.what() << std::endl;
	}

	return shaderCode;
}

} // namespace Scorch