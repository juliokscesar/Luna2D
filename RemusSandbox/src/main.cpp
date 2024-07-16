#include <iostream>

#include "Remus/Core/Window.hpp"
#include "SandboxApp.hpp"

int main()
{
    Remus::ApplicationSpecification appSpec;
    appSpec.AppWindowSpec = Remus::WindowSpecification("Sandbox", 1280, 720, true);

    Remus::SandboxApp *app = new Remus::SandboxApp(appSpec);

    if (app->Init() != REMUS_INIT_SUCCESS)
        return -1;

    app->Run();

    delete app;
}
