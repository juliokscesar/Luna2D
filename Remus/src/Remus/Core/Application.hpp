#pragma once

#include <memory>

#include "Window.hpp"

namespace Remus
{
    struct ApplicationSpecification
    {
	WindowSpecification AppWindowSpec;
    };

    class Application
    {
    public:
	Application(const ApplicationSpecification& appSpec);
	virtual ~Application();

        virtual int Init() = 0;
        virtual void Run() = 0;

    protected:
        std::unique_ptr<Window> m_window;
    };

}
