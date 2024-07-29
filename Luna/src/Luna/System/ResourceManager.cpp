#include "ResourceManager.hpp"

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
    void InitWorkingPath()
    {
	std::filesystem::path curr = std::filesystem::current_path();
	while (curr.filename() != "Luna2D")
	    curr = curr.parent_path();

	std::filesystem::current_path(curr / "LunaSandbox" / "assets");
	std::cout << "Working path = " << std::filesystem::current_path() << '\n';
    }

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
	std::filesystem::path filePath{vertexPath};
	const std::string shaderName = filePath.stem().string();

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
	int width, height;
	// load image and force 4 channels (RGBA)
	uint8_t* data = stbi_load(path.c_str(), &width, &height, nullptr, 4);
	
	if (!data)
	{
	    std::cerr << "stbi_load returned a nullptr when loading " << path << '\n';
	    return nullptr;
	}

	return new ImageData(
		static_cast<uint32_t>(width),
		static_cast<uint32_t>(height),
		GL_RGBA,
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

	TextureSpecificiation textureSpec(GL_RGBA, img->SourceFormat, img->Width, img->Height);

	Texture2D texture(img->Data, textureSpec, textureUnit);

	delete img;
	return texture;
    }
}

