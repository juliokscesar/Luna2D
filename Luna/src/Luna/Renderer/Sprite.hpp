#pragma once

#include "Core/Luna.hpp"
#include "Texture2D.hpp"

#include <cstdint>

namespace Luna 
{
    class Sprite
    {
    public:
	Sprite();
	Sprite(Ref<Texture2D> spriteTexture);
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

	Sprite& operator=(Sprite&& other) noexcept
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

	inline void SetTexture2D(Ref<Texture2D> texture) { m_texture = texture; }
	inline Ref<Texture2D> GetTexture() const noexcept { return m_texture; }
	inline bool IsUsingTexture() const noexcept { return m_useTexture; }

	inline uint32_t GetVAO() const noexcept { return m_VAO; }
	inline uint32_t GetVBO() const noexcept { return m_VBO; }

    private:
	uint32_t m_VAO = 0;
	uint32_t m_VBO = 0;

	Ref<Texture2D> m_texture;
	bool m_useTexture = false;
    };
}

