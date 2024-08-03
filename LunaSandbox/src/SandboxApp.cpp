#include "SandboxApp.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <iostream>

#include "Luna/Core/Input.hpp"
#include "Luna/Core/Luna.hpp"
#include "Luna/Renderer/Camera.hpp"
#include "Luna/Renderer/Entity.hpp"
#include "Luna/Renderer/Projection.hpp"
#include "Luna/Renderer/Renderer.hpp"
#include "Luna/Renderer/Shader.hpp"
#include "Luna/Renderer/Sprite.hpp"
#include "Luna/Renderer/Texture2D.hpp"
#include "Luna/System/ResourceManager.hpp"
#include "Luna/Core/GUI.hpp"

namespace Sandbox
{
    SandboxApp::SandboxApp(const Luna::ApplicationSpecification& appSpec)
	: Luna::Application(appSpec)
    {
    }
    
    void SandboxApp::OnCreate()
    {
	Luna::Ref<Luna::Camera> camera = Luna::CreateRef<Luna::Camera>();
	camera->Transform.SetPosition(0.0f, 0.0f, 3.0f);

	Luna::Frustum frustum{
	    .Near = 0.1f, 
	    .Far = 100.0f, 
	    .O_Width = (float)m_appSpecs.WindowWidth,
	    .O_Height = (float)m_appSpecs.WindowHeight,
	    .P_FOV = 45.0f,
	    .P_AspectRatio = (float)m_appSpecs.WindowWidth / (float)m_appSpecs.WindowHeight,
	};
	Luna::Projection ortho = Luna::Projection(Luna::ProjectionType::ORTHOGONAL, frustum);

	m_mainScene = new Luna::Scene(camera, ortho);
    }

    void SandboxApp::OnStart()
    {
	// sprite_base shader
	Luna::ResourceManager::LoadShader("shaders/sprite_base.vert", "shaders/sprite_base.frag");

	// quad shader
	Luna::ResourceManager::LoadShader("shaders/quad.vert", "shaders/quad.frag");

	// quadTextured shader
	Luna::ResourceManager::LoadShader("shaders/quadTextured.vert", "shaders/quadTextured.frag");

	Luna::Ref<Luna::Texture2D> romaTex = Luna::ResourceManager::LoadTexture2D("textures/roma.png");
	Luna::Ref<Luna::Entity> roma = m_mainScene->CreateEntity("Roma", Luna::CreateRef<Luna::Sprite>(romaTex));
	
	Luna::Ref<Luna::Texture2D> containerTex = Luna::ResourceManager::LoadTexture2D("textures/container.jpg");
	Luna::Ref<Luna::Entity> container = m_mainScene->CreateEntity("Container", Luna::CreateRef<Luna::Sprite>(containerTex));
	container->Transform.SetPosition(1.0f, 0.0f, 0.0f);
    }

    void SandboxApp::OnUpdate(float deltaTime)
    {
	Luna::GUI::FrameStatsWindow(deltaTime);
	Luna::GUI::EntityPropertiesManager(m_mainScene);

	if (Luna::Input::GetKeyState(GLFW_KEY_ESCAPE))
	    this->SetExitRequest(true);

	m_mainScene->UpdateScene(deltaTime, (float)m_appSpecs.WindowWidth, (float)m_appSpecs.WindowHeight);

	Luna::Renderer::RenderScene(m_mainScene, "sprite_base");
    }
    
    void SandboxApp::OnDestroy()
    {
	delete m_mainScene;
    }
}
