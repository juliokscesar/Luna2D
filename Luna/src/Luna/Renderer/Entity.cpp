#include "Entity.hpp"

namespace Luna
{
    Entity::Entity()
    {
    }

    Entity::Entity(const std::string& name, Ref<Sprite> sprite)
	: Name(name), m_sprite(sprite)
    {
    }
    
    void Entity::OnUpdate(float deltaTime)
    {
        LN_UNUSED(deltaTime);
    }
}

