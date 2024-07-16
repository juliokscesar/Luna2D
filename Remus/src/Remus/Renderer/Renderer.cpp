#include "Renderer.hpp"

namespace Remus::Renderer
{
    static ViewportSpecifications g_viewportSpecs;

    void Init(const ViewportSpecifications &viewportSpecs)
    {
        g_viewportSpecs = viewportSpecs;

        glViewport(0, 0, viewportSpecs.Width, viewportSpecs.Height);
    }

    void UpdateViewport(uint32_t newWidth, uint32_t newHeight)
    {
        g_viewportSpecs.Width = newWidth;
        g_viewportSpecs.Height = newHeight;
        g_viewportSpecs.AspectRatio = static_cast<float>(newWidth) / static_cast<float>(newHeight);

        glViewport(0, 0, g_viewportSpecs.Width, g_viewportSpecs.Height);
    }

    void ClearColor(float r, float g, float b, float a)
    {
        // TODO: test if glClear can be in NewFrame function
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void NewFrame(GLFWwindow *window)
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
