#pragma once
#include "Components/Component.h"

class EnemyComponent : public Component
{
	CLASS_DECLARATION(EnemyComponent)
	CLASS_PROTOTYPE(EnemyComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);

public:
	float speed{ 0 };
};