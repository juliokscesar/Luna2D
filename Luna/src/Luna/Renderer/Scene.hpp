#pragma once

#include "Camera.hpp"
#include "Projection.hpp"
#include "Entity.hpp"

#include <vector>

namespace Luna
{
    class Scene
    {
    public:
	Scene();
	Scene(Ref<Camera> camera, const Projection& projection);
	~Scene();

	inline Ref<Camera> GetCamera() { return m_camera; }
	inline void SetCamera(Ref<Camera> camera) { m_camera = camera; }

	inline Projection& GetProjection() { return m_projection; }
	inline void SetProjection(const Projection& projection) { m_projection = projection; }

	inline const glm::mat4& GetWorldTransform() { return m_worldTransform; }

	int RegisterEntity(Ref<Entity> entity);
	Ref<Entity> GetEntityById(int id);
	void DeleteEntity(int id);

	inline std::vector<Ref<Entity>>& GetAllEntities() { return m_entities; }

	Ref<Entity> CreateEntity(const std::string& name, Ref<Sprite> sprite, const glm::vec3& position=glm::vec3(0.0f), const glm::vec3& rotation=glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f));

	void UpdateScene(float deltaTime, float viewportWidth, float viewportHeight);

    private:
	Ref<Camera> m_camera;
	Projection m_projection;
	glm::mat4 m_worldTransform;

	std::vector<Ref<Entity>> m_entities;
    };
}
