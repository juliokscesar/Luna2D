cmake_minimum_required(VERSION 3.28)
project(LunaCore)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # export compiler commands for clangd (nvim coc)

set(GLAD_SRC ext/glad/src/glad.c)

set(SRC_DIR src/Luna)

set(LUNA_CORE_SRC
    ${SRC_DIR}/Core/Application.cpp
    ${SRC_DIR}/Core/Window.cpp
    ${SRC_DIR}/Core/Input.cpp
    ${SRC_DIR}/Renderer/Renderer.cpp
    ${SRC_DIR}/Renderer/Shader.cpp
    ${SRC_DIR}/Renderer/Sprite.cpp
    ${SRC_DIR}/System/ResourceManager.cpp
)

add_library(LunaCoreStatic STATIC
    ${GLAD_SRC}
    ${LUNA_CORE_SRC}
)
target_include_directories(LunaCoreStatic PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/ext/ 
    ${CMAKE_CURRENT_LIST_DIR}/ext/glad/include/
) 

target_compile_definitions(LunaCoreStatic PRIVATE "LN_DEBUG=$<CONFIG:Debug>")

install(TARGETS LunaCoreStatic
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
