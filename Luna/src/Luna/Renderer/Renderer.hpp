#pragma once

#include <stdint.h>

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

	// TODO: implement DrawTriangle. Find out a way to store simple mesh vertices (like triangle, quad, etc)
	/* void DrawTriangle(); */

	// TODO: implement DrawQuad. Create function to DrawSprite and also DrawQuad with texture
	//void DrawQuad();

        void ClearColor(float r, float g, float b, float a);
        void NewFrame(GLFWwindow* window);
    };
}
