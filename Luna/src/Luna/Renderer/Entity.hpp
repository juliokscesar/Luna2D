#pragma once

#include "Core/Luna.hpp"
#include "TransformComponent.hpp"
#include "Sprite.hpp"

#include <string>

namespace Luna
{
    class Entity
    {
    public:
	Entity();
	Entity(const std::string& name, Ref<Sprite> sprite);

	virtual void OnUpdate(float deltaTime);

	inline bool IsVisible() const noexcept { return m_visible; }
	inline void SetVisible(bool visible) noexcept { m_visible = visible; }

	inline Ref<Sprite> GetSprite() const noexcept { return m_sprite; }

    public:
	TransformComponent Transform;
	std::string Name = "UnnamedEntity";

    protected:
	Ref<Sprite> m_sprite;
	bool m_visible = true;
    };
}

