#pragma once

#include <cstdint>

namespace Remus
{
    class Sprite
    {
    public:
	Sprite();
	~Sprite();

	void InitRenderData();

	void Draw();

    private:
	uint32_t m_VAO = 0;
	uint32_t m_VBO = 0;

	// TODO: implement Texture2D
	// Texture2D tex;
    };
}

