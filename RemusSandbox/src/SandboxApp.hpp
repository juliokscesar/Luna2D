#pragma once

#include "Remus/Core/Application.hpp"
#include "Remus/Core/Remus.hpp"

namespace Remus
{
    class SandboxApp : public Application
    {
    public:
        SandboxApp(const ApplicationSpecification& appSpec)
    	: Application(appSpec) {}
    
	/* ~SandboxApp() override; */

        int Init() override;
	void Run() override;
    };
}
