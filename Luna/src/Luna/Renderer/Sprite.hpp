#pragma once

#include "Texture2D.hpp"

#include <cstdint>

namespace Luna 
{
    class Sprite
    {
    public:
	Sprite();
	Sprite(const Texture2D& spriteTexture);
	Sprite(const Sprite& other);
	Sprite(Sprite&& other);
	~Sprite();

	Sprite& operator=(const Sprite& other)
	{
	    if (this != &other)
	    {
		this->m_VAO = other.m_VAO;
		this->m_VBO = other.m_VBO;

		this->m_texture = other.m_texture;
		this->m_useTexture = other.m_useTexture;
	    }

	    return *this;
	}

	Sprite& operator=(Sprite&& other)
	{
	    if (this != &other)
	    {
		this->m_VAO = std::move(other.m_VAO);
		this->m_VBO = std::move(other.m_VBO);

		this->m_texture = std::move(other.m_texture);
		this->m_useTexture = std::move(other.m_useTexture);
	    }

	    return *this;
	}

	void InitRenderData();

	void SetTexture2D(const Texture2D& texture);
	inline const Texture2D& GetTexture() const noexcept { return m_texture; }
	inline bool IsUsingTexture() const noexcept { return m_useTexture; }

	inline uint32_t GetVAO() const noexcept { return m_VAO; }
	inline uint32_t GetVBO() const noexcept { return m_VBO; }

    private:
	uint32_t m_VAO = 0;
	uint32_t m_VBO = 0;

	Texture2D m_texture;
	bool m_useTexture = false;
    };
}

