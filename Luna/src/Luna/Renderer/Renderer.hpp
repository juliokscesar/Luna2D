#pragma once

#include "Scene.hpp"
#include "Shader.hpp"

#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Luna 
{
    struct ViewportSpecifications
    {
        ViewportSpecifications()
            : Width(0), Height(0), AspectRatio(0.0f) {}

        ViewportSpecifications(uint32_t width, uint32_t height)
            : Width(width), Height(height), AspectRatio(static_cast<float>(width) / static_cast<float>(height)) {}

        uint32_t Width;
        uint32_t Height;
        float AspectRatio;
    };

    namespace Renderer
    {
        void Init(const ViewportSpecifications& viewportSpecs);
        void UpdateViewport(uint32_t newWidth, uint32_t newHeight);
    
	std::string AddToShaderLib(const Shader& shader);
	Ref<Shader> GetFromShaderLib(const std::string& name);

	void RenderSprite(Ref<Sprite> sprite);
	void RenderEntity(Scene* scene, Ref<Entity> entity, Ref<Shader> shader);
	void RenderScene(Scene* scene, const std::string& baseShaderName);

        void ClearColor(float r, float g, float b, float a);
        void EndFrame(GLFWwindow* window);
    };
}
