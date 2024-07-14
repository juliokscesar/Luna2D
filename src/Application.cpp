#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Remus.hpp"
#include "Core/Renderer.hpp"
#include "Core/Input.hpp"

static bool g_bResized = false;
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    g_bResized = true;
}

namespace Remus
{
    Application::Application()
    {
        WindowSpecification specs("Remus2D", 1280, 720, true);
        m_window = std::make_unique<Window>(specs);
    }

    Application::~Application()
    {
        glfwTerminate();
    }

    int Application::Init()
    {
        if (!glfwInit())
            return REMUS_INIT_FAILURE;

        
        // Using OpenGL 3.3. and core profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // focus when window opens
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);

        if (m_window->CreateWindow() != REMUS_INIT_SUCCESS)
        {
            glfwTerminate();
            return REMUS_INIT_FAILURE;
        }
        
        glfwMakeContextCurrent(m_window->GetGLFWWindow());

        // set VSync
        glfwSwapInterval(static_cast<int>(m_window->GetSpecs().VSync));

        // initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwTerminate();
            return REMUS_INIT_FAILURE;
        }

        Renderer::Init(ViewportSpecifications(m_window->GetSpecs().Width, m_window->GetSpecs().Height));
        Input::RegisterCallbacks(m_window->GetGLFWWindow());

        // resize callback
        glfwSetFramebufferSizeCallback(m_window->GetGLFWWindow(), framebufferSizeCallback);

        return REMUS_INIT_SUCCESS;
    }

    void Application::Run()
    {
        while (!m_window->CloseRequested())
        {
            Renderer::ClearColor(1.0f, 0.0f, 0.0f, 1.0f);

            if (Input::GetKeyState(GLFW_KEY_ESCAPE))
            {
                m_window->SetClose(true);
                continue;
            }

            if (g_bResized)
            {
                int width = 0, height = 0;
                glfwGetWindowSize(m_window->GetGLFWWindow(), &width, &height);

                m_window->ResizeWindow(width, height);
                Renderer::UpdateViewport(width, height);

                g_bResized = false;
            }

            Renderer::NewFrame(m_window->GetGLFWWindow());
        }
    }
}
