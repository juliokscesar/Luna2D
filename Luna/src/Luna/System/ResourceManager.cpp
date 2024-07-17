#include "ResourceManager.hpp"

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

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

	if (vertexCode.empty() || fragCode.empty())
	{
	    std::cerr << "Unable to load shader with vertexPath=" << vertexPath << " and fragPath=" << fragPath << '\n';
	    return Shader();
	}

	// Get Shader name based on vertexPath name
	const std::string vertexExt(".vert");
	const size_t vertexExtSize = vertexExt.size();

	constexpr char PATH_DIVIDER = '/';
	const size_t lastDividerPos = vertexPath.rfind(&PATH_DIVIDER);

	const std::string shaderName = std::string(vertexPath.begin() + lastDividerPos + 1, vertexPath.end() - vertexExtSize);

	return Shader(shaderName, vertexCode.c_str(), fragCode.c_str());
    }
    

    ImageData::~ImageData()
    {
	if (Data) stbi_image_free(Data);
	Data = nullptr;
    }

    ImageData* LoadImage(const std::string& path, bool flip)
    {
	if (!CheckPath(path))
	{
	    std::cerr << "Couldn't find image: " << path << '\n';
	    return nullptr;
	}

	stbi_set_flip_vertically_on_load(flip);
	int width, height, nrChannels;
	uint8_t* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	
	if (!data)
	{
	    std::cerr << "stbi_load returned a nullptr when loading " << path << '\n';
	    return nullptr;
	}

	// TODO: i don't think this is the best way to find out imgSourceFormat, but it's better than having that enum ImageFormat
	GLenum srcFormat{};	
	switch (nrChannels)
	{
	case 3:	    srcFormat =  GL_RGB;	break;
	case 4:	    srcFormat = GL_RGBA;	break;
	}

	return new ImageData(
		static_cast<uint32_t>(width),
		static_cast<uint32_t>(height),
		static_cast<uint32_t>(nrChannels),
		srcFormat,
		data
	);
    }

    Texture2D LoadTexture2D(const std::string &path, uint32_t textureUnit, bool flipImgOnLoad)
    {
	ImageData* img = LoadImage(path, flipImgOnLoad);
	if (!img || !img->Data)
	{
	    std::cerr << "img.Data is nullptr when loading texture " << path << '\n';
	    return Texture2D();
	}

	TextureSpecificiation textureSpec(GL_RGB, img->SourceFormat, img->Width, img->Height);

	Texture2D texture(img->Data, textureSpec, textureUnit);

	delete img;
	return texture;
    }
}

