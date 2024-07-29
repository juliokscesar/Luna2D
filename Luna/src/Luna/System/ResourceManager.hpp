#pragma once

#include <string>

#include "Renderer/Shader.hpp"
#include "Renderer/Texture2D.hpp"

namespace Luna::ResourceManager
{
    void InitWorkingPath();

    bool CheckPath(const std::string& path);

    std::string LoadFile(const std::string& path);
    
    Shader LoadShader(const std::string& vertexPath, const std::string& fragPath);

    struct ImageData
    {
	ImageData() = default;

	ImageData(uint32_t width, uint32_t height, GLenum imgSourceFormat, uint8_t* data)
	    : Width(width), Height(height), SourceFormat(imgSourceFormat), Data(data) {}

	~ImageData();

	uint32_t Width = 0;
	uint32_t Height = 0;

	GLenum SourceFormat = GL_RGBA;

	uint8_t* Data = nullptr;
    };


    ImageData* LoadImage(const std::string& path, bool flip=false);

    Texture2D LoadTexture2D(const std::string& path, uint32_t textureUnit=0, bool flipImgOnLoad=false);
}

