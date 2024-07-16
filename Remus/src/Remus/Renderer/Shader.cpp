#include "Shader.hpp"

#include <cstdint>
#include <iostream>
#include <memory>

namespace Remus 
{
    Shader::Shader()
	: m_progID(0)
    {
    }

    Shader::Shader(const char* vertCode, const char* fragCode)
    {
	InitShader(vertCode, fragCode);
    }

    Shader::~Shader()
    {
	glDeleteProgram(m_progID);
    }

    void Shader::InitShader(const char* vertCode, const char* fragCode)
    {
	uint32_t vertexId = CreateShader(GL_VERTEX_SHADER, vertCode);
	uint32_t fragId = CreateShader(GL_FRAGMENT_SHADER, fragCode);

	m_progID = CreateProgram(vertexId, fragId);

	glDeleteShader(vertexId);
	glDeleteShader(fragId);
    }


    void Shader::Use()
    {
	glUseProgram(m_progID);
    }


    int Shader::GetUniformLocation(const std::string& name) const noexcept
    {
	return glGetUniformLocation(m_progID, name.c_str());
    }


    void Shader::SetUniformInt(const std::string& name, int val)
    {
	int loc = GetUniformLocation(name);
	glUniform1i(loc, val);
    }

    void Shader::SetUniformUInt(const std::string& name, uint32_t val)
    {
	int loc = GetUniformLocation(name);
	glUniform1ui(loc, val);
    }

    void Shader::SetUniformFloat(const std::string& name, float val)
    {
	int loc = GetUniformLocation(name);
	glUniform1f(loc, val);
    }

    void Shader::SetUniformBool(const std::string& name, bool val)
    {
	int loc = GetUniformLocation(name);
	glUniform1i(loc, val);
    }

    uint32_t Shader::CreateShader(GLenum type, const char *code)
    {
	uint32_t id = glCreateShader(type);
	glShaderSource(id, 1, &code, nullptr);
	glCompileShader(id);

	if (!CheckShaderError(id))
	    return 0;

	return id;
    }

    uint32_t Shader::CreateProgram(uint32_t vertexId, uint32_t fragId)
    {
	uint32_t id = glCreateProgram();
	glAttachShader(id, vertexId);
	glAttachShader(id, fragId);
	glLinkProgram(id);

	if (!CheckProgramError(id))
	    return 0;
	
	return id;
    }

    bool Shader::CheckShaderError(uint32_t id)
    {
	int success{};
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
	    glGetShaderInfoLog(id, 512, nullptr, infoLog);
	    std::cerr << "Compiling shader error: " << infoLog << "\n";
	    return false;
	}

	return true;
    }

    bool Shader::CheckProgramError(uint32_t id)
    {
	int success{};
	char infoLog[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
	    glGetProgramInfoLog(id, 512, nullptr, infoLog);
	    std::cerr << "Linking program error: " << infoLog << "\n";
	    return false;
	}
	
	return true;
    }


    void ShaderLibrary::Add(const std::string& name, const Shader& shader)
    {
	m_shaders[name] = std::make_shared<Shader>(shader);
    }

    std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name) const noexcept
    {
	return m_shaders.at(name);
    }
}

