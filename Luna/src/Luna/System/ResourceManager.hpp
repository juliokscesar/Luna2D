#pragma once

#include <string>

#include "../Renderer/Shader.hpp"

namespace Luna::ResourceManager
{
    std::string LoadFile(const std::string& path);
    
    Shader LoadShader(const std::string& vertexPath, const std::string& fragPath);
}

