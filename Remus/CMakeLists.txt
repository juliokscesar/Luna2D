# TODO: this should build 'Remus' as a static library. The code here only contains the 'core' functionality of the engine
cmake_minimum_required(VERSION 3.28)
project(RemusCore)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # export compiler commands for clangd (nvim coc)

set(GLAD_SRC ext/glad/src/glad.c)

set(SRC_DIR src/Remus)

set(REMUS_CORE_SRC
    ${SRC_DIR}/Core/Application.cpp
    ${SRC_DIR}/Core/Window.cpp
    ${SRC_DIR}/Core/Input.cpp
    ${SRC_DIR}/Renderer/Renderer.cpp
    ${SRC_DIR}/Renderer/Shader.cpp
    ${SRC_DIR}/Renderer/Sprite.cpp
    ${SRC_DIR}/System/ResourceManager.cpp
)

add_library(RemusCoreStatic STATIC
    ${GLAD_SRC}
    ${REMUS_CORE_SRC}
)

target_include_directories(RemusCoreStatic PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/ext/
    ${CMAKE_CURRENT_LIST_DIR}/ext/glad/include/
)

target_compile_definitions(RemusCoreStatic PRIVATE "RM_DEBUG=$<CONFIG:Debug>")

install(TARGETS RemusCoreStatic
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
