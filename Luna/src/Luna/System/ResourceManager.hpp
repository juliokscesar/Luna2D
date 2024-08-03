#pragma once

#include <string>

#include "Renderer/Shader.hpp"
#include "Renderer/Texture2D.hpp"

namespace Luna::ResourceManager
{
    void Init();
    void Terminate();

    bool CheckPath(const std::string& path);

    std::string FormatPath(const std::string& path);

    std::string LoadFile(const std::string& path);
    
    Ref<Shader> LoadShader(const std::string& vertexPath, const std::string& fragPath);
    ShaderLibrary* GetShaderLib();

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

    enum class ImgLoadFlags : uint8_t
    {
	NONE = 0,
	FLIP = 1 << 0
    };

    ImageData* LoadImage(const std::string& path, uint8_t flags=0);

    Ref<Texture2D> LoadTexture2D(const std::string& path, uint32_t textureUnit=0, bool flipImgOnLoad=false);
}

