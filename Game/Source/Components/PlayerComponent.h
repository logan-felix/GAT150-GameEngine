#pragma once
#include "Components/Component.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"

class PlayerComponent : public Component
{
	CLASS_DECLARATION(PlayerComponent)
	CLASS_PROTOTYPE(PlayerComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);

public:
	float speed{ 0 };
	int fireCooldown = 0;
	int lives{ 0 };
	int score{ 0 };
	float dmgTimer = 0;
	Font* fontUi{ nullptr };
	Text* textScore{ nullptr };
	Text* textLives{ nullptr };
};