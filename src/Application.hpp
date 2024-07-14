#pragma once

#include <memory>

#include "Core/Window.hpp"

namespace Remus
{

    class Application
    {
    public:
        Application();
        ~Application();

        int Init();
        void Run();

    private:
        std::unique_ptr<Window> m_window;
    };

}