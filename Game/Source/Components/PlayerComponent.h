#pragma once
#include "Components/Component.h"

class PlayerComponent : public Component
{
	CLASS_DECLARATION(PlayerComponent)

	void Initialize() override;
	void Update(float dt) override;

public:
	float speed{ 0 };
};