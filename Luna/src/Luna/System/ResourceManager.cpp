#include "ResourceManager.hpp"
#include "Renderer/Shader.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#ifndef LN_ROOT_FOLDER
    #define LN_ROOT_FOLDER "Luna2D"
#endif // LN_ROOT_FOLDER
#ifndef LN_PROJECT_FOLDER
    #define LN_PROJECT_FOLDER "LunaSandbox"
#endif // LN_PROJECT_FOLDER

namespace Luna::ResourceManager 
{
    std::filesystem::path g_assetsFolder;
    ShaderLibrary* g_shaderLib;
    std::unordered_map<std::string, Ref<Texture2D>> g_loadedTextures;

    void Init()
    {
	std::cout << "LN_ROOT_FOLDER: " << LN_ROOT_FOLDER << '\n';
	std::filesystem::path curr = std::filesystem::current_path();
	while (curr.filename().string() != LN_ROOT_FOLDER)
		curr = curr.parent_path();

	g_assetsFolder = curr / LN_PROJECT_FOLDER / "assets";
		
	std::cout << "g_assetsFolder = " << g_assetsFolder << '\n';


	g_shaderLib = new ShaderLibrary();
    }

    void Terminate()
    {
	delete g_shaderLib;

	for (auto& [path, texture] : g_loadedTextures)
	    texture->DeleteResources();
    }

    bool CheckPath(const std::string &path)
    {
	return (std::filesystem::exists(path));
    }

    std::string FormatPath(const std::string& path)
    {
	std::filesystem::path p(path);
	p = g_assetsFolder / p;
	return p.string();
    }

    std::string LoadFile(const std::string& path)
    {
	const std::string fPath = FormatPath(path);

	if (!CheckPath(fPath))
	{
	    std::cerr << "Couldn't find file: " << fPath << "\n";
	    return "";
	}

	std::stringstream fileStream{};
	std::ifstream file(fPath);
	fileStream << file.rdbuf();

	file.close();
	return fileStream.str();
    }

    Ref<Shader> LoadShader(const std::string& vertexPath, const std::string& fragPath)
    {
		// Get shader name based on vertex path
		const std::string shaderName = std::filesystem::path(vertexPath).stem().string();
		if (g_shaderLib->Contains(shaderName))
			return g_shaderLib->Get(shaderName);

		std::string vertexCode = LoadFile(vertexPath);
		std::string fragCode = LoadFile(fragPath);

		if (vertexCode.empty() || fragCode.empty())
		{
			std::cerr << "Unable to load shader with vertexPath=" << vertexPath << " and fragPath=" << fragPath << '\n';
			return Ref<Shader>(nullptr);
		}

		Ref<Shader> shader = CreateRef<Shader>(shaderName, vertexCode.c_str(), fragCode.c_str());
		g_shaderLib->Add(shader);

		return shader;
    }

    ShaderLibrary* GetShaderLib()
    {
		return g_shaderLib;
    }
    

    ImageData::~ImageData()
    {
	if (Data) stbi_image_free(Data);
	Data = nullptr;
    }

    ImageData* LoadImage(const std::string& path, uint8_t flags)
    {
	const std::string fPath = FormatPath(path);
	if (!CheckPath(fPath))
	{
	    std::cerr << "Couldn't find image: " << fPath << '\n';
	    return nullptr;
	}

	if (flags & (uint8_t)ImgLoadFlags::FLIP)
		stbi_set_flip_vertically_on_load(true);
	int width, height;
	// load image and force 4 channels (RGBA)
	uint8_t* data = stbi_load(fPath.c_str(), &width, &height, nullptr, 4);
	
	if (!data)
	{
	    std::cerr << "stbi_load returned a nullptr when loading " << fPath << '\n';
	    return nullptr;
	}

	return new ImageData(
		static_cast<uint32_t>(width),
		static_cast<uint32_t>(height),
		GL_RGBA,
		data
	);
    }

    Ref<Texture2D> LoadTexture2D(const std::string &path, uint32_t textureUnit, bool flipImgOnLoad)
    {
	// Check if texture was already loaded
	if (g_loadedTextures.contains(path))
	    return g_loadedTextures[path];

	ImageData* img = LoadImage(path, flipImgOnLoad);
	if (!img || !img->Data)
	{
	    std::cerr << "img.Data is nullptr when loading texture " << path << '\n';
	    return Ref<Texture2D>(nullptr);
	}

	TextureSpecificiation textureSpec(GL_RGBA, img->SourceFormat, img->Width, img->Height);

	Ref<Texture2D> texture = CreateRef<Texture2D>(img->Data, textureSpec, textureUnit);
	g_loadedTextures[path] = texture;

	delete img;
	return texture;
    }
}
