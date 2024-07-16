#include "Window.hpp"

#include "Remus.hpp"

namespace Remus
{
    Window::Window()
        : m_winSpecs("Blank", 800, 600, true)
    {
    }

    Window::Window(const WindowSpecification &specification)
        : m_winSpecs(specification)
    {
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_glfwWindow);
    }

    WindowSpecification Window::GetSpecs() const noexcept
    {
        return m_winSpecs;
    }

    void Window::SetSpecs(const WindowSpecification &specification)
    {
        m_winSpecs = specification;
    }

    int Window::CreateWindow()
    {
        m_glfwWindow = glfwCreateWindow(m_winSpecs.Width, m_winSpecs.Height, m_winSpecs.Title.c_str(), nullptr, nullptr);
        if (!m_glfwWindow)
            return REMUS_INIT_FAILURE;

        return REMUS_INIT_SUCCESS;
    }

    void Window::SetClose(bool close)
    {
        glfwSetWindowShouldClose(m_glfwWindow, static_cast<int>(close));
    }

    bool Window::CloseRequested() const noexcept
    {
        return glfwWindowShouldClose(m_glfwWindow);
    }

    void Window::ResizeWindow(uint32_t newWidth, uint32_t newHeight)
    {
        m_winSpecs.Width  = newWidth;
        m_winSpecs.Height = newHeight;
        
        m_winSpecs.AspectRatio = static_cast<float>(newWidth) / static_cast<float>(newHeight);
    }

    GLFWwindow *Window::GetGLFWWindow() const noexcept
    {
        return m_glfwWindow;
    }

}
