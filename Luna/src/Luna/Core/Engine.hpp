#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Luna.hpp"
#include "Application.hpp"
#include "Window.hpp"

namespace Luna
{
    class Engine
    {
    public:
	Engine();

	Engine(Application* app);

	~Engine();

	bool Start();

	void Run();

    private:
	Application* m_app;
	Scope<Window> m_window;

	bool m_initialized = false;
    };
}

