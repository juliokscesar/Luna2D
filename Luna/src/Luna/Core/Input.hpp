#pragma once

#include <stdint.h>

#include <GLFW/glfw3.h>

namespace Luna::Input
{
    int GetKeyGLFWAction(int key) noexcept;

    bool GetKeyState(int key) noexcept;

    void RegisterCallbacks(GLFWwindow* window);

    void AddKeyListener(int key);

    void AddKeyListener(int keys[], size_t n);

    float GetMouseXOffset() noexcept;
    float GetMouseYOffset() noexcept;
    float GetMouseScroll()  noexcept;
}