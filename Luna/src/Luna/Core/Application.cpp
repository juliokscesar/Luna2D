#include "Application.hpp"

namespace Luna 
{
    Application::Application(const ApplicationSpecification& appSpec)
	: m_appSpecs(appSpec)
    {
    }

    Application::Application(const Application& other)
	: m_appSpecs(other.m_appSpecs)
    {
    }

    Application::Application(Application&& other)
	: m_appSpecs(std::move(other.m_appSpecs))
    {
    }

    Application::~Application()
    {
    }


    void Application::UpdateWindowSize(uint32_t width, uint32_t height)
    {
	m_appSpecs.WindowWidth = width;
	m_appSpecs.WindowHeight = height;
    }
}

