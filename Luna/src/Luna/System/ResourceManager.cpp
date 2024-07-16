#include "ResourceManager.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Luna::ResourceManager 
{
    std::string LoadFile(const std::string &path)
    {
	if (!std::filesystem::exists(std::filesystem::path(path)))
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
}

