#pragma once

#include <cstdint>
#include <string>

namespace Luna 
{
    struct ApplicationSpecification
    {
	std::string Name = "Luna App";

	uint32_t GLVersionMajor = 3;
	uint32_t GLVersionMinor = 3;
	
	uint32_t WindowWidth = 800;
	uint32_t WindowHeight = 600;
	bool MaximizeOnOpen = false;
    };

    class Application
    {
    public:
	Application(const ApplicationSpecification& appSpec);

	Application(const Application& other);
	Application(Application&& other);

	virtual ~Application();

	inline ApplicationSpecification GetAppSpecs() const noexcept { return m_appSpecs; }
	void UpdateWindowSize(uint32_t width, uint32_t height);

	inline bool ExitRequested() const noexcept { return m_exit; }
	inline void SetExitRequest(bool exit) { m_exit = exit; }

	// This is called just after the App constructor.
	// It is called inside the Engine constructor.
	virtual void OnCreate() = 0;

	// This is called when Engine::Start() is called.
	// It is the first function to be called
	virtual void OnStart() = 0;

	// This is called every frame while the window is open
	virtual void OnUpdate(float deltaTime) = 0;

	// This is called in the Engine's destructor
	// just before destroying the Application pointer
	// with delete.
	virtual void OnDestroy() = 0;

    protected:
	ApplicationSpecification m_appSpecs;
	bool m_exit = false;
    };

}
