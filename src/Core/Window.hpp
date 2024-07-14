#pragma once

#include <stdint.h>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Remus
{

    struct WindowSpecification
    {   
        WindowSpecification(const std::string& title, uint32_t width, uint32_t height, bool vsync)
            : Title(title), Width(width), Height(height), AspectRatio(static_cast<float>(width) / static_cast<float>(height)), VSync(vsync) {}

        std::string Title;
        uint32_t Width;
        uint32_t Height;
        float AspectRatio;
        bool VSync;
    };

    class Window
    {
    public:
        Window();
        Window(const WindowSpecification& specification);
        ~Window();

        WindowSpecification GetSpecs() const noexcept;
        void SetSpecs(const WindowSpecification& specification);

        int CreateWindow();

        void SetClose(bool close);
        bool CloseRequested() const noexcept;
        
        void ResizeWindow(uint32_t newWidth, uint32_t newHeight);

        GLFWwindow* GetGLFWWindow() const noexcept;

    private:
        GLFWwindow* m_glfwWindow;
        WindowSpecification m_winSpecs;
    };

}