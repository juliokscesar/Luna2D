#include "ResourceManager.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb/stb_image.h>

namespace Luna::ResourceManager 
{
    bool CheckPath(const std::string &path)
    {
	return (std::filesystem::exists(path));
    }

    std::string LoadFile(const std::string &path)
    {
	if (!CheckPath(path))
	{
	    std::cerr << "Couldn't find file: " << path << "\n";
	    return "";
	}

	std::stringstream fileStream{};
	std::ifstream file(path);
	fileStream << file.rdbuf();

	file.close();
	return fileStream.str();
    }

    Shader LoadShader(const std::string& vertexPath, const std::string& fragPath)
    {
	std::string vertexCode = LoadFile(vertexPath);
	std::string fragCode = LoadFile(fragPath);

	return Shader(vertexCode.c_str(), fragCode.c_str());
    }
    

    ImageData::~ImageData()
    {
	if (Data) stbi_image_free(Data);
	Data = nullptr;
    }

    ImageData* LoadImage(const std::string& path, ImageFormat format)
    {
	if (!CheckPath(path))
	{
	    std::cerr << "Couldn't find image: " << path << '\n';
	    return nullptr;
	}

	int width, height, nrChannels;
	uint8_t* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (!data)
	{
	    std::cerr << "stbi_load returned a nullptr when loading " << path << '\n';
	    return nullptr;
	}

	return new ImageData(
		static_cast<uint32_t>(width),
		static_cast<uint32_t>(height),
		static_cast<uint32_t>(nrChannels),
		format,
		data
	);
    }

    Texture2D LoadTexture2D(const std::string &path, ImageFormat srcFormat, uint32_t textureUnit)
    {
	ImageData* img = LoadImage(path, srcFormat);
	if (!img || !img->Data)
	{
	    std::cerr << "img.Data is nullptr when loading texture " << path << '\n';
	    return Texture2D();
	}

	TextureSpecificiation textureSpec(GL_RGB, static_cast<uint32_t>(srcFormat), img->Width, img->Height);

	Texture2D texture(img->Data, textureSpec, textureUnit);

	delete img;
	return texture;
    }
}

