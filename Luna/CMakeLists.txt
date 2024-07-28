cmake_minimum_required(VERSION 3.28)
project(LunaCore)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # export compiler commands for clangd (nvim coc)

set(CMAKE_CXX_STANDARD 20)

set(GLAD_SRC ext/glad/src/glad.c)

set(IMGUI_DIR ext/imgui)
set(IMGUI_SRC 
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set(SRC_DIR src/Luna)

set(LUNA_CORE_SRC
    ${SRC_DIR}/Core/Application.cpp
    ${SRC_DIR}/Core/Window.cpp
    ${SRC_DIR}/Core/Input.cpp
    ${SRC_DIR}/Renderer/Renderer.cpp
    ${SRC_DIR}/Renderer/Shader.cpp
    ${SRC_DIR}/Renderer/Sprite.cpp
    ${SRC_DIR}/Renderer/Texture2D.cpp
    ${SRC_DIR}/Renderer/Scene.cpp
    ${SRC_DIR}/Renderer/Camera.cpp
    ${SRC_DIR}/Renderer/Entity.cpp
    ${SRC_DIR}/Renderer/Projection.cpp
    ${SRC_DIR}/Renderer/TransformComponent.cpp
    ${SRC_DIR}/System/ResourceManager.cpp
    ${SRC_DIR}/Core/Engine.cpp
    ${SRC_DIR}/System/DebugTools.cpp
)

add_library(LunaCoreStatic STATIC
    ${GLAD_SRC}
    ${IMGUI_SRC}
    ${LUNA_CORE_SRC}
)

target_include_directories(LunaCoreStatic PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/ext/ 
    ${CMAKE_CURRENT_LIST_DIR}/ext/glad/include/
    ${CMAKE_CURRENT_LIST_DIR}/ext/imgui/
    ${CMAKE_CURRENT_LIST_DIR}/ext/imgui/backends
) 

target_compile_definitions(LunaCoreStatic PRIVATE "LN_DEBUG=$<CONFIG:Debug>")

if(MSVC)
    target_compile_options(LunaCoreStatic PRIVATE /W4 /WX)
else()
    target_compile_options(LunaCoreStatic PRIVATE -Wall -Wextra -Wpedantic)
endif()

install(TARGETS LunaCoreStatic
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
