#include "window.h"
#include "../Math/float4.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>

namespace Scorch
{

Window::Window(int windowWidth,			int windowHeight,
			   int viewportWidth,		int viewportHeight,
			   const std::string& windowTitle,
			   const std::string& openGLVersion)
	: m_windowWidth(windowWidth),	  m_windowHeight(windowHeight),
	  m_viewportWidth(viewportWidth), m_viewportHeight(viewportHeight),
	  m_windowTitle(windowTitle),	  m_openGLVersion(openGLVersion),
	  m_windowID((glfwInit(),		  glfwCreateWindow(windowWidth,
	  windowHeight, m_windowTitle.c_str(), nullptr, nullptr)))
{
	createWindow();
}

Window::~Window()
{
	glfwTerminate();
}

void Window::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::clearColor(const Float4& rgba) const
{
	glClearColor(rgba.red, rgba.green, rgba.blue, rgba.alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::pollEvents() const
{
	glfwPollEvents();
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_windowID);
}

void Window::processInput() const
{
	if (glfwGetKey(m_windowID, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_windowID, true);
	}
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_windowID);
}

void Window::createWindow() const
{
	// Initialize window properties.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_openGLVersion[0]);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_openGLVersion[2]);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Ensure the window was created successfully.
	if (m_windowID == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	// Set context to current window.
	glfwMakeContextCurrent(m_windowID);

	// Resize viewport as user changes window dimensions.
	glfwSetFramebufferSizeCallback(m_windowID, viewportSizeCallback);

	// Load GLAD for OpenGL functions and ensure the load was successful.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}
}

void Window::viewportSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

} // namespace Scorch