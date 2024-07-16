#include "Application.hpp"

namespace Remus 
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

