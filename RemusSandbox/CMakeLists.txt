cmake_minimum_required(VERSION 3.28)
project(RemusSandbox)

set(REMUS_CORE_INCLUDE 
    ${CMAKE_SOURCE_DIR}/Remus/src/
    ${CMAKE_SOURCE_DIR}/Remus/ext/
    ${CMAKE_SOURCE_DIR}/Remus/ext/glad/include
)

set(REMUS_SANDBOX_SRC
    src/SandboxApp.cpp
    src/main.cpp
)

set(REMUS_SANDBOX_INCLUDE ${REMUS_CORE_INCLUDE})

add_executable(RemusSandbox ${REMUS_SANDBOX_SRC})

target_include_directories(RemusSandbox PUBLIC ${REMUS_SANDBOX_INCLUDE})

target_link_libraries(RemusSandbox PUBLIC
    -lglfw
    -lGL
    -lX11
    -lpthread
    -lXrandr
    -lXi
    -ldl
    RemusCoreStatic
)

install(TARGETS RemusSandbox RUNTIME DESTINATION bin)

