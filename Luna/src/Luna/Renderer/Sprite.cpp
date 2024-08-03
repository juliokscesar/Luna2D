#include "Sprite.hpp"

#include <glad/glad.h>

namespace Luna 
{
    Sprite::Sprite()
    {
	InitRenderData();
    }

    Sprite::Sprite(Ref<Texture2D> spriteTexture)
	: m_texture(spriteTexture), m_useTexture(true)
    {
	InitRenderData();
    }

    Sprite::Sprite(const Sprite& other)
	: m_VAO(other.m_VAO), m_VBO(other.m_VBO), m_texture(other.m_texture), m_useTexture(other.m_useTexture)
    {
    }

    Sprite::Sprite(Sprite&& other)
	:   m_VAO(std::move(other.m_VAO)),
	    m_VBO(std::move(other.m_VBO)),
	    m_texture(std::move(other.m_texture)),
	    m_useTexture(std::move(other.m_useTexture))
    {
    }

    Sprite::~Sprite()
    {
	/* glDeleteBuffers(1, &m_VBO); */
	/* glDeleteVertexArrays(1, &m_VAO); */
    }

    void Sprite::InitRenderData()
    {
	const float quadVertices[] = {
	    // position		// tex coords
	    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
	     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
	    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
	    
	    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
	     0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
	     0.5f,  0.5f, 0.0f,  1.0f, 1.0f
	};

	// TODO: separate this functions in other places in Renderer namespace
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	// position vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);

	// texture coords vertex attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
    }

}
