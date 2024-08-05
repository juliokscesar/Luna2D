#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "Core/Luna.hpp"

namespace Luna
{
Camera::Camera()
    :	m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    	m_front(glm::vec3(0.0f, 0.0f, -1.0f))
{
    updateVectors();
}

Camera::Camera(const Camera& other)
    :	Transform(other.Transform),
	m_worldUp(other.m_worldUp),
	m_front(other.m_front)
{
    updateVectors();
}

Camera::Camera(const glm::vec3& direction, const glm::vec3& worldUp)
    :	m_worldUp(worldUp),
	m_front(direction)
{
    updateVectors();
}

void Camera::updateVectors()
{
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

const glm::mat4& Camera::GetViewMatrix() const noexcept
{
    return m_viewMatrix;
}

void Camera::Update(float deltaTime)
{
    LN_UNUSED(deltaTime);

    updateVectors();
    m_viewMatrix = glm::lookAt(Transform.GetPosition(), Transform.GetPosition() + m_front, m_up);
}

}
