#pragma once

#include <glm/glm.hpp>

namespace Luna
{
class TransformComponent
{
public:
    TransformComponent();
    TransformComponent(const TransformComponent& other);
    TransformComponent(TransformComponent&& other);

    TransformComponent& operator=(const TransformComponent& other)
    {
	if (this != &other)
	{
	    this->m_position = other.m_position;
	    this->m_rotation = other.m_rotation;
	    this->m_scale = other.m_scale;
	}

	m_changed = true;
	Update();
	return *this;
    }

    TransformComponent& operator=(TransformComponent&& other)
    {
	if (this != &other)
	{
	    this->m_position = std::move(other.m_position);
	    this->m_rotation = std::move(other.m_rotation);
	    this->m_scale = std::move(other.m_scale);
	}

	m_changed = true;
	Update();
	return *this;
    }

    // Updates the transform matrix
    // Not necessary to call every frame.
    // When calling GetTransformMatrix(), Update is already called
    void Update();

    // Set position based on world origin (0,0,0)
    // Z-component has no effect in 2D
    void SetPosition(const glm::vec3& pos) noexcept;
    
    // Set position based on world oigin (0,0,0)
    // Z-component has no effect in 2D
    void SetPosition(float x, float y, float z) noexcept;

    // Get position vec3 component 
    inline const glm::vec3& GetPosition() const noexcept { return m_position; }
    

    // Set rotation with values in DEGREES
    void SetRotation(const glm::vec3& degRot) noexcept;

    // Set rotation with values in DEGREES
    void SetRotation(float degX, float degY, float degZ) noexcept;

    // Rotate around a given axis. AXIS MUST BE NORMALIZED
    void Rotate(float deg, const glm::vec3& axis) noexcept;

    // Get rotation with values in DEGREES
    inline const glm::vec3& GetRotation() const noexcept { return m_rotation; }


    // Scale transform (original scale is (1.0, 1.0, 1.0))
    void SetScale(const glm::vec3& scale) noexcept;

    // Scale transform (original scale is 1.0, 1.0, 1.0)
    void SetScale(float x, float y, float z) noexcept;

    // Scale in all axis by a given factor
    void Scale(float factor) noexcept;


    // Get calculated transform matrix.
    // This is not a const function because it calls Update() before returning the matrix.
    const glm::mat4& GetTransformMatrix() noexcept;

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

    bool m_changed = false;
    glm::mat4 m_transformMatrix;
};
}
