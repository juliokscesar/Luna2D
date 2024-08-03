#pragma once

#include <cstdint>
#include <utility>

#include <glad/glad.h>

namespace Luna 
{
    struct TextureSpecificiation
    {
	TextureSpecificiation() = default;
	
	TextureSpecificiation(uint32_t glStoreFormat, GLenum imgSourceFormat, uint32_t width, uint32_t height)
	    : GLStoreFormat(glStoreFormat), ImgSourceFormat(imgSourceFormat), Width(width), Height(height) {}

	GLenum GLStoreFormat = GL_RGBA;
	GLenum ImgSourceFormat = GL_RGBA;
	uint32_t Width = 0;
	uint32_t Height = 0;
    };

    class Texture2D
    {
    public:
	Texture2D() = default;
	Texture2D(uint8_t* imgData, const TextureSpecificiation& textureSpec, uint32_t textureUnit = 0);

	Texture2D(const Texture2D& other)
	    : m_textureID(other.m_textureID), m_textureUnit(other.m_textureUnit) {}

	Texture2D(Texture2D&& other)
	    : m_textureID(std::move(other.m_textureID)), m_textureUnit(std::move(other.m_textureUnit)) {}

	Texture2D& operator=(const Texture2D& other)
	{
	    if (this != &other)
	    {
		this->m_textureID = other.m_textureID;
		this->m_textureUnit = other.m_textureUnit;
	    }

	    return *this;
	}

	Texture2D& operator=(Texture2D&& other)
	{
	    if (this != &other)
	    {
		this->m_textureID = std::move(other.m_textureID);
		this->m_textureUnit = std::move(other.m_textureUnit);
	    }

	    return *this;
	}

	void Load(uint8_t* imgData, const TextureSpecificiation& textureSpec);

	void Use() const noexcept;

	uint32_t GetTextureID() const noexcept;
	int GetTextureUnit() const noexcept;

	void DeleteResources();

    private:
	uint32_t m_textureID	= 0;
	int m_textureUnit	= 0;
    };
}

