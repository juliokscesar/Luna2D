#pragma once

#include "Luna/Core/Application.hpp"
#include "Luna/Core/Luna.hpp"

namespace Luna 
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
