#include "TransformComponent.hpp"

#define LUNA_RADIANS(deg) ((deg) * (3.141592f/180.0f))

#include <glm/gtc/matrix_transform.hpp>

namespace Luna
{
TransformComponent::TransformComponent()
    : m_position(0.0f), m_rotation(0.0f), m_scale(1.0f), m_changed(true), m_transformMatrix(1.0f)
{
    Update();
}

TransformComponent::TransformComponent(const TransformComponent& other)
    :	m_position(other.m_position),
	m_rotation(other.m_rotation),
	m_scale(other.m_scale)
{
    m_changed = true;
    Update();
}

TransformComponent::TransformComponent(TransformComponent&& other)
    :	m_position(std::move(other.m_position)),
	m_rotation(std::move(other.m_rotation)),
	m_scale(std::move(other.m_scale))
{
    m_changed = true;
    Update();
}

void TransformComponent::Update()
{
    // Avoid doing calculations when no properties has changed
    if (!m_changed)
	return;

    m_transformMatrix = glm::mat4(1.0f);

    m_transformMatrix = glm::translate(m_transformMatrix, m_position);

    const float radX = LUNA_RADIANS(m_rotation.x);
    const float radY = LUNA_RADIANS(m_rotation.y);
    const float radZ = LUNA_RADIANS(m_rotation.z);

    if (radX)
	m_transformMatrix = glm::rotate(m_transformMatrix, radX, glm::vec3(1.0f, 0.0f, 0.0f));
    if (radY)
	m_transformMatrix = glm::rotate(m_transformMatrix, radY, glm::vec3(0.0f, 1.0f, 0.0f));
    if (radZ)
	m_transformMatrix = glm::rotate(m_transformMatrix, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

    m_transformMatrix = glm::scale(m_transformMatrix, m_scale);

    m_changed = false;
}

void TransformComponent::SetPosition(const glm::vec3& pos) noexcept
{
    m_position = pos;
    m_changed = true;
}

void TransformComponent::SetPosition(float x, float y, float z) noexcept
{
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;

    m_changed = true;
}

void TransformComponent::SetRotation(const glm::vec3& degRot) noexcept
{
    m_rotation = degRot;
    m_changed = true;
}

void TransformComponent::SetRotation(float degX, float degY, float degZ) noexcept
{
    m_rotation.x = degX;
    m_rotation.y = degY;
    m_rotation.z = degZ;

    m_changed = true;
}

void TransformComponent::Rotate(float deg, const glm::vec3& axis) noexcept
{
    m_rotation = glm::normalize(axis) * deg;
    m_changed = true;
}

void TransformComponent::SetScale(const glm::vec3& scale) noexcept
{
    m_scale = scale;
    m_changed = true;
}

void TransformComponent::SetScale(float x, float y, float z) noexcept
{
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;

    m_changed = true;
}

void TransformComponent::Scale(float factor) noexcept
{
    m_scale = glm::vec3(factor);

    m_changed = true;
}


const glm::mat4& TransformComponent::GetTransformMatrix() noexcept
{
    Update();
    return m_transformMatrix;
}

}
