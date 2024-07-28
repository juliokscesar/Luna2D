#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "../Core/Luna.hpp"

namespace Luna 
{
    class Shader
    {
    public:
	Shader();
	Shader(const std::string& name, const char* vertCode, const char* fragCode);

	Shader(const Shader& other)
	{
	    this->m_progID = other.m_progID;
	    this->m_name   = other.m_name;
	}
	
	Shader(Shader&& other)
	{
	    this->m_progID = std::move(other.m_progID);
	    this->m_name   = std::move(other.m_name);
	}

	Shader& operator=(const Shader& other)
	{
	    if (this != &other)
	    {
		this->m_progID = other.m_progID;
		this->m_name   = other.m_name;
	    }
	    return *this;
	}

	Shader& operator=(Shader&& other)
	{
	    if (this != &other)
	    {
		this->m_progID = std::move(other.m_progID);
		this->m_name   = std::move(other.m_name);
	    }
	    return *this;
	}

	void InitShader(const char* vertCode, const char* fragCode);
	void Use();

	uint32_t GetProgramID() const noexcept;

	std::string GetName() const noexcept;
	void SetName(const std::string& name);

	int GetUniformLocation(const std::string& name) const noexcept;

	void SetUniformInt(const std::string& name, int val);
	void SetUniformUInt(const std::string& name, uint32_t val);
	void SetUniformFloat(const std::string& name, float val);
	void SetUniformBool(const std::string& name, bool val);
	void SetUniformMat4(const std::string& name, const glm::mat4& mat);
	void SetUniformVec3(const std::string& name, const glm::vec3& v);

	static uint32_t CreateShader(GLenum type, const char* code);
	static uint32_t CreateProgram(uint32_t vertexId, uint32_t fragId);

	static bool CheckShaderError(uint32_t id);
	static bool CheckProgramError(uint32_t id);

    private:
	uint32_t m_progID = 0;

	std::string m_name;
    };


    class ShaderLibrary
    {
    public:
	~ShaderLibrary();

	void Add(const Shader& shader);
	Ref<Shader> Get(const std::string& name) const noexcept;
    private:
	std::unordered_map<std::string, Ref<Shader>> m_shaders;
    };
}

