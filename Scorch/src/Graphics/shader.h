#pragma once

#include <glad/glad.h>

#include <string>

namespace Scorch
{

// Reads in, compiles, and links vertex and fragment shaders.
class Shader
{
public:
	// Initialization constructor.
	Shader(const std::string& vertexShaderFilePath,
           const std::string& fragmentShaderFilePath);

    // Deletes shader program.
    ~Shader();

    // Activates shader program.
    void useProgram() const;

private:
    // Unique vertex shader ID.
    unsigned int m_vertexShaderID;

    // Unique fragment shader ID.
    unsigned int m_fragmentShaderID;

    // Unique shader program ID.
    unsigned int m_shaderProgramID;
    std::string m_vertexShaderFilePath;
    std::string m_fragmentShaderFilePath;

    // Compiles vertex and fragment shaders.
    void compileShaders() const;

    // Ensure shaders were compiled and linked successfully.
    void shaderErrorCheck(unsigned int shaderID, GLenum type,
                          const std::string& shaderType) const;

    // Links vertex and fragment shaders to shader program.
    void linkShaders() const;

    // Loads GLSL code from the specified file path.
    std::string loadShaderSource(const std::string& shaderFilePath) const;
};

} // namespace Scorch