cmake_minimum_required(VERSION 3.12)
project(Remus2D)

# TODO: download glfw WIN64 binaries and link them if in windows

set(GLAD_SRC ext/glad/src/glad.c)

set(REMUS_SRC
    src/main.cpp
    src/Application.cpp
    src/Core/Window.cpp
    src/Core/Renderer.cpp
    src/Core/Input.cpp
)


add_executable(remus
    ${GLAD_SRC}
    ${REMUS_SRC}
)

target_include_directories(remus PUBLIC
    ${CMAKE_SOURCE_DIR}/ext/
    ${CMAKE_SOURCE_DIR}/ext/glad/include/
)

# TODO: implement for other platforms. this is only for linux
target_link_libraries(remus PUBLIC
    -lglfw
    -lGL
    -lX11
    -lpthread
    -lXrandr
    -lXi
    -ldl
)
