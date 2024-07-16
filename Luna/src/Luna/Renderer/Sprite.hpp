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
	~Sprite();

	void InitRenderData();

	void SetTexture2D(const Texture2D& texture);

	void Draw();

    private:
	uint32_t m_VAO = 0;
	uint32_t m_VBO = 0;

	Texture2D m_texture;
	bool m_useTexture = false;
    };
}

