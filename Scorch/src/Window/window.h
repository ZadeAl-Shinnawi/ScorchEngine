#pragma once

#include "../Math/float4.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Scorch
{

// GLFW window wrapper class.
class Window
{
public:
    // Initialization constructor.
    Window(int windowWidth,                int windowHeight,
           int viewportWidth,              int viewportHeight,
           const std::string& windowTitle, const std::string& openGLVersion);

    // Terminates GLFW.
    ~Window();

    // Clears the window background (default black color).
    void clear() const;

    // Clears the window background with the specified RGBA color.
    void clearColor(const Float4& rgba) const;

    // Polls user input events and acts accordingly.
    void pollEvents() const;

    // Swaps front and back buffers of window.
    void swapBuffers() const;

    // Process user window input.
    void processInput() const;

    // Whether the given window should close or not based off of user input.
    bool shouldClose() const;

    // Returns the unique window ID.
    // inline GLFWwindow* getID() const { return m_windowID; }

private:
    int m_windowWidth;
    int m_windowHeight;
    int m_viewportWidth;
    int m_viewportHeight;
    std::string m_windowTitle;
    std::string m_openGLVersion;

    // Unique window ID.
    GLFWwindow* m_windowID;

    // Initializes and creates a window.
    void createWindow() const;

    // Adjusts the given window dimensions as the user resizes it.
    static void viewportSizeCallback(GLFWwindow* window,
                                     int width, int height);
};

} // namespace Scorch