#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Components/Component.h"

#include <string>
#include <memory>
#include <vector>

class Renderer;
class Scene;

class Actor : public Object
{
public:
	Actor() = default;
	Actor(const Transform& transform) : m_transform{ transform } {}

	CLASS_DECLARATION(Actor);

	void Initialize() override;
	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer);

	void AddComponent(std::unique_ptr<Component> component);

	void SetDamping(float damping) { m_damping = damping; }

	const Transform& GetTransform() { return m_transform; }
	void SetTransform(Transform& transform) { m_transform = transform; }

	virtual void OnCollision(Actor* actor) {}
	float GetRadius() { return 0; };

	friend class Scene;

public:
	std::string tag;
	float lifespan = 0;

protected:
	bool m_destroyed = false;

	Transform m_transform;
	Vector2 m_velocity{ 0, 0 };
	float m_damping{ 0 };

	Scene* m_scene{ nullptr };

	std::vector<std::unique_ptr<Component>> m_components;
};
