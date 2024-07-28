#include "Luna/Core/Application.hpp"
#include "SandboxApp.hpp"
#include "Luna/Core/Engine.hpp"
#include <iostream>

int main()
{
    Luna::ApplicationSpecification appSpec;
    appSpec.Name = "Luna Sandbox";
    appSpec.WindowWidth = 800;
    appSpec.WindowHeight = 600;
    Sandbox::SandboxApp* app = new Sandbox::SandboxApp(appSpec);

    Luna::Engine* engine = new Luna::Engine(app);
    if (!engine->Start())
    {
	std::cerr << "Something went wrong when trying to start engine\n";
	delete engine;
	delete app;

	return 1;
    }

    engine->Run();

    delete engine;
    delete app;
}
