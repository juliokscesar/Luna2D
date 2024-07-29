#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer/Scene.hpp"

namespace Luna::GUI
{
    void InitContext(GLFWwindow* glfwWindow);

    void NewFrame();
    void Render();
    void Terminate();

    // Useful windows:
    void FrameStatsWindow(float deltaTime);
    
    void EntityPropertiesManager(Scene* scene);
}

