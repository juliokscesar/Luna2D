#pragma once

#include <string>

#include "../Renderer/Shader.hpp"
#include "../Renderer/Texture2D.hpp"

namespace Luna::ResourceManager
{
    bool CheckPath(const std::string& path);

    std::string LoadFile(const std::string& path);
    
    Shader LoadShader(const std::string& vertexPath, const std::string& fragPath);

    enum class ImageFormat
    {
	RGB  = GL_RGB,
	RGBA = GL_RGBA
    };

    struct ImageData
    {
	ImageData() = default;

	ImageData(uint32_t width, uint32_t height, uint32_t channels, ImageFormat format, uint8_t* data)
	    : Width(width), Height(height), NrChannels(channels), Format(format), Data(data) {}

	~ImageData();

	uint32_t Width = 0;
	uint32_t Height = 0;
	uint32_t NrChannels = 0;

	ImageFormat Format = ImageFormat::RGB;

	uint8_t* Data = nullptr;
    };


    ImageData* LoadImage(const std::string& path, ImageFormat format);

    Texture2D LoadTexture2D(const std::string& path, ImageFormat srcFormat, uint32_t textureUnit=0);
}

