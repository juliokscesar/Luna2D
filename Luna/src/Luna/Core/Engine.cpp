#include "Engine.hpp"

#include <chrono>

#include "Renderer/Renderer.hpp"
#include "Input.hpp"
#include "System/ResourceManager.hpp"
#include "GUI.hpp"

using ms = std::chrono::duration<float, std::milli>;

namespace Luna
{
    static struct { bool changed = false; uint32_t width; uint32_t height; } g_resizeSpecs;
    void framebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
	(void)window;

	g_resizeSpecs.changed = true;
	g_resizeSpecs.width = static_cast<uint32_t>(width);
	g_resizeSpecs.height = static_cast<uint32_t>(height);
    }


    Engine::Engine(Application* app)
	: m_app(app)
    {
	m_app->OnCreate();

	const ApplicationSpecification& appSpec = m_app->GetAppSpecs();
	WindowSpecification winSpecs(
	    appSpec.Name,
	    appSpec.WindowWidth,
	    appSpec.WindowHeight,
	    true
	);

	m_window = CreateScope<Window>(winSpecs); 

    }

    bool Engine::Start()
    {
	if (!glfwInit())
	    return false;

	const ApplicationSpecification& appSpec = m_app->GetAppSpecs();

	// Initialize OpenGL version with Core Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Focus when window opens and set to maximize based on app
	glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
	glfwWindowHint(GLFW_MAXIMIZED, appSpec.MaximizeOnOpen);

if (!m_window->CreateWindow())
	{
	    glfwTerminate();
	    return false;
	}

	glfwMakeContextCurrent(m_window->GetGLFWWindow());

	// Set VSync
	glfwSwapInterval((int)m_window->GetSpecs().VSync);

	// Initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
	    glfwTerminate();
	    return false;
	}

	ViewportSpecifications viewport{
	    appSpec.WindowWidth,
	    appSpec.WindowHeight
	};
	
	Renderer::Init(viewport);
	
	Input::RegisterCallbacks(m_window->GetGLFWWindow());
	
	ResourceManager::InitWorkingPath();

	GUI::InitContext(m_window->GetGLFWWindow());

	glfwSetFramebufferSizeCallback(m_window->GetGLFWWindow(), framebufferSizeCallback);

	m_app->OnStart();

	return true;
    }

    void Engine::Run()
    {
	float deltaTime = 0.0f;
	auto lastFrame = std::chrono::high_resolution_clock::now();
	while (!m_window->CloseRequested())
	{
	    auto currentFrame = std::chrono::high_resolution_clock::now();
	    deltaTime = std::chrono::duration_cast<ms>(currentFrame - lastFrame).count() / 1000.0f;
	    lastFrame = currentFrame;

	    GUI::NewFrame();
	    Renderer::ClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	    if (g_resizeSpecs.changed)
	    {
		g_resizeSpecs.changed = false;
		Renderer::UpdateViewport(g_resizeSpecs.width, g_resizeSpecs.height);
		m_window->UpdateWindowSize(g_resizeSpecs.width, g_resizeSpecs.height);
		m_app->UpdateWindowSize(g_resizeSpecs.width, g_resizeSpecs.height);
	    }

	    m_app->OnUpdate(deltaTime);
	    if (m_app->ExitRequested())
		m_window->SetClose(true);

	    GUI::Render();
	    Renderer::EndFrame(m_window->GetGLFWWindow());
	}
    }

    Engine::~Engine()
    {
	m_app->OnDestroy();

	GUI::Terminate();
	glfwTerminate();
    }
}

