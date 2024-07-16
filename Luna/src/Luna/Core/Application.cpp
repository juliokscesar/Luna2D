#include "Application.hpp"

namespace Luna 
{
    Application::Application(const ApplicationSpecification& appSpec)
    {
	m_window = std::make_unique<Window>(appSpec.AppWindowSpec);
    }

    Application::~Application()
    {
	glfwTerminate();
    }
}

