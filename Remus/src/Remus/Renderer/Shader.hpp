#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

#include <glad/glad.h>

namespace Remus 
{
    class Shader
    {
    public:
	Shader();
	Shader(const char* vertCode, const char* fragCode);

	Shader(const Shader& other)
	{
	    this->m_progID = other.m_progID;
	}
	
	Shader(Shader&& other)
	{
	    this->m_progID = std::move(other.m_progID);
	}

	~Shader();

	Shader& operator=(const Shader& other)
	{
	    if (this != &other)
	    {
		this->m_progID = other.m_progID;
	    }
	    return *this;
	}

	Shader& operator=(Shader&& other)
	{
	    if (this != &other)
	    {
		this->m_progID = std::move(other.m_progID);
	    }
	    return *this;
	}

	void InitShader(const char* vertCode, const char* fragCode);
	void Use();

	int GetUniformLocation(const std::string& name) const noexcept;

	void SetUniformInt(const std::string& name, int val);
	void SetUniformUInt(const std::string& name, uint32_t val);
	void SetUniformFloat(const std::string& name, float val);
	void SetUniformBool(const std::string& name, bool val);

	static uint32_t CreateShader(GLenum type, const char* code);
	static uint32_t CreateProgram(uint32_t vertexId, uint32_t fragId);

	static bool CheckShaderError(uint32_t id);
	static bool CheckProgramError(uint32_t id);

    private:
	uint32_t m_progID = 0;
    };


    class ShaderLibrary
    {
    public:
	void Add(const std::string& name, const Shader& shader);
	std::shared_ptr<Shader> Get(const std::string& name) const noexcept;
    private:
	std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
    };
}

