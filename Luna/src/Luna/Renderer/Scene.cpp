#include "Scene.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace Luna
{
    Scene::Scene(Ref<Camera> camera, const Projection& projection)
	: m_camera(camera), m_projection(projection), m_worldTransform(glm::mat4(1.0f))
    {
    }

    int Scene::RegisterEntity(Ref<Entity> entity)
    {
	m_entities.push_back(entity);
	return ((int)m_entities.size() - 1);
    }

    Ref<Entity> Scene::GetEntityById(int id)
    {
	if ((size_t)id > m_entities.size())
	{
	    std::cerr << "Trying to access out-of-bounds entity id: " << id << '\n';
	    return nullptr;
	}

	return m_entities[id];
    }

    Ref<Entity> Scene::CreateEntity(const std::string& name, Ref<Sprite> sprite)
    {
	int newId = RegisterEntity(CreateRef<Entity>(name, sprite));
	return m_entities[newId];
    }
    
    void Scene::UpdateScene(float deltaTime, float viewportWidth, float viewportHeight)
    {
	m_camera->Update(deltaTime);
	m_projection.UpdateFrustum(viewportWidth, viewportHeight);
	m_worldTransform = glm::translate(m_worldTransform, glm::vec3(viewportWidth / 2.0f, viewportHeight / 2.0f, 0.0f));

	for (auto& entity : m_entities)
	{
	    entity->OnUpdate(deltaTime);
	}
    }
}

