#pragma once

#include "TransformComponent.hpp"

namespace Luna
{
class Camera
{
public:
    Camera();
    Camera(const Camera& other);
    Camera(const glm::vec3& direction, const glm::vec3& worldUp);

    Camera& operator=(const Camera& other)
    {
	if (this != &other)
	{
	    this->Transform = other.Transform;
	    this->m_front = other.m_front;
	    this->m_right = other.m_right;
	    this->m_up = other.m_up;
	}

	updateVectors();
	return *this;
    }

    void Update(float deltaTime);

    const glm::mat4& GetViewMatrix() const noexcept;

private:
    void updateVectors();

public:
    TransformComponent Transform;

private:
    const glm::vec3 m_worldUp;
    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;

    glm::mat4 m_viewMatrix;
};
}
