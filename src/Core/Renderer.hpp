#pragma once

#include <stdint.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Remus
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

        void ClearColor(float r, float g, float b, float a);
        void NewFrame(GLFWwindow* window);
    };
}
