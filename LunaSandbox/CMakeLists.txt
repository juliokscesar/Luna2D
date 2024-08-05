cmake_minimum_required(VERSION 3.28)
project(LunaSandbox)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # export compiler commands for clangd (nvim coc)

set(CMAKE_CXX_STANDARD 20)

set(LUNA_CORE_INCLUDE 
    ${CMAKE_SOURCE_DIR}/Luna/src/
    ${CMAKE_SOURCE_DIR}/Luna/ext/
    ${CMAKE_SOURCE_DIR}/Luna/ext/glad/include
)

set(LUNA_SANDBOX_SRC
    src/SandboxApp.cpp
    src/main.cpp
)

set(LUNA_SANDBOX_INCLUDE ${LUNA_CORE_INCLUDE})

add_executable(LunaSandbox ${LUNA_SANDBOX_SRC})

target_include_directories(LunaSandbox PUBLIC ${LUNA_SANDBOX_INCLUDE})

if(WIN32)
    set(GLFW_LIBS_DIR ${CMAKE_SOURCE_DIR}/Luna/ext/glfw/build/src/release)
else()
    set(GLFW_LIBS_DIR ${CMAKE_SOURCE_DIR}/Luna/ext/glfw/build)
endif()

target_link_directories(LunaSandbox PUBLIC
    ${GLFW_LIBS_DIR}
)

if(WIN32)
    set(LIBS
        glfw3
        opengl32
    )
else()
    set(LIBS
        -lGL
        -lX11
        -lpthread
        -lXrandr
        -lXi
        -ldl
        glfw
    )
endif()

target_link_libraries(LunaSandbox PUBLIC
    ${LIBS}
    LunaCoreStatic
)

if(MSVC)
    target_compile_options(LunaSandbox PRIVATE /W4 /WX)
else()
    target_compile_options(LunaSandbox PRIVATE -Wall -Wextra -Wpedantic)
endif()
  
install(TARGETS LunaSandbox RUNTIME DESTINATION bin)

