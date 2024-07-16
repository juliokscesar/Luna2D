#include "SandboxApp.hpp"

int main()
{
    Luna::ApplicationSpecification appSpec;
    appSpec.AppWindowSpec = Luna::WindowSpecification("Sandbox", 1280, 720, true);

    Luna::SandboxApp *app = new Luna::SandboxApp(appSpec);

    if (app->Init() != LUNA_INIT_SUCCESS)
        return -1;

    app->Run();

    delete app;
}
