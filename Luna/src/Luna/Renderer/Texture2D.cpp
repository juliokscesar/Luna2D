#include "Texture2D.hpp"
#include <iostream>

namespace Luna 
{
    Texture2D::Texture2D(uint8_t* imgData, const TextureSpecificiation& textureSpec, uint32_t textureUnit)
	: m_textureUnit(textureUnit)
    {
	Load(imgData, textureSpec);
    }

    void Texture2D::Load(uint8_t* imgData, const TextureSpecificiation& textureSpec)
    {
	// load data into texture	
	if (!imgData)
	{
	    std::cerr << "imgData is null\n";
	    return;
	}

	glGenTextures(1, &m_textureID);

	glActiveTexture(GL_TEXTURE0 + m_textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	// wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		textureSpec.GLStoreFormat, 
		static_cast<GLsizei>(textureSpec.Width), 
		static_cast<GLsizei>(textureSpec.Height), 
		0, 
		textureSpec.ImgSourceFormat, 
		GL_UNSIGNED_BYTE, 
		imgData
	);

	glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    void Texture2D::Use() const noexcept
    {
	glActiveTexture(GL_TEXTURE0 + m_textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
    }

    uint32_t Texture2D::GetTextureID() const noexcept
    {
	return m_textureID;
    }

    int Texture2D::GetTextureUnit() const noexcept
    {
	return m_textureUnit;
    }

    void Texture2D::DeleteResources()
    {
	if (m_textureID)
	    glDeleteTextures(1, &m_textureID);
    }
}

