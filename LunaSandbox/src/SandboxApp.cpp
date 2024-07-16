#include "SandboxApp.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Luna/Core/Luna.hpp"
#include "Luna/Core/Input.hpp"
#include "Luna/Renderer/Renderer.hpp"
#include "Luna/Renderer/Shader.hpp"
#include "Luna/System/ResourceManager.hpp"
#include "Luna/Renderer/Sprite.hpp"

static bool g_bResized = false;
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    g_bResized = true;
}

namespace Luna 
{
    int SandboxApp::Init()
    {
        if (!glfwInit())
            return LUNA_INIT_FAILURE;

        
        // Using OpenGL 3.3. and core profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // focus when window opens
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);

        if (m_window->CreateWindow() != LUNA_INIT_SUCCESS)
        {
            glfwTerminate();
            return LUNA_INIT_FAILURE;
        }
        
        glfwMakeContextCurrent(m_window->GetGLFWWindow());

        // set VSync
        glfwSwapInterval(static_cast<int>(m_window->GetSpecs().VSync));

        // initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwTerminate();
            return LUNA_INIT_FAILURE;
        }

        Renderer::Init(ViewportSpecifications(m_window->GetSpecs().Width, m_window->GetSpecs().Height));
        Input::RegisterCallbacks(m_window->GetGLFWWindow());

        // resize callback
        glfwSetFramebufferSizeCallback(m_window->GetGLFWWindow(), framebufferSizeCallback);

        return LUNA_INIT_SUCCESS;
    }

    void SandboxApp::Run()
    {
	// TODO: DELETE THIS SPRITE DRAW (JUST TESTING)
	ShaderLibrary shaderLib;
	{
	    Shader quadShader = ResourceManager::LoadShader("LunaSandbox/assets/shaders/quad.vert", "LunaSandbox/assets/shaders/quad.frag");
	   shaderLib.Add("quadShader", quadShader);
	}
	Sprite quad{};

        while (!m_window->CloseRequested())
        {
            Renderer::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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

	    shaderLib.Get("quadShader")->Use();
	    quad.Draw();

            Renderer::NewFrame(m_window->GetGLFWWindow());
        }
    }
}
