#pragma once

#include "Luna/Core/Application.hpp"
#include "Luna/Renderer/Scene.hpp"

namespace Sandbox
{
    class SandboxApp : public Luna::Application
    {
    public:
	SandboxApp(const Luna::ApplicationSpecification& appSpec);

	// Called inside the Engine constructor
	void OnCreate() override;
	
	// Called inside Engine::Start()
	void OnStart() override;

	// Called every frame
	void OnUpdate(float deltaTime) override;

	// Called in the Engine's destructor
	void OnDestroy() override;
    
    private:
	Luna::Scene* m_mainScene;
    };
}
