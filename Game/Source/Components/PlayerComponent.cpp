#include "PlayerComponent.h"
#include "Resources/Resource.h"
#include "Engine.h"

FACTORY_REGISTER(PlayerComponent)

void PlayerComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1);
	lives = 1;
}

void PlayerComponent::Update(float dt)
{
	if (lives <= 0) {
		owner->destroyed = true;
	}
	else {
		float thrust = 0;
		Vector2 direction{ 0, 0 };
		if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) { direction.x = -1; }
		if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) { direction.x = 1; }
		if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W)) { direction.y = -1; }
		if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S)) { direction.y = 1; }

		if (owner->transform.position.x > 790) owner->transform.position.x = 790;
		if (owner->transform.position.x < 10) owner->transform.position.x = 10;
		if (owner->transform.position.y > 590) owner->transform.position.y = 590;
		if (owner->transform.position.y < 10) owner->transform.position.y = 10;

		//owner->GetComponent<PhysicsComponent>()->ApplyTorque(rotate * 90 * dt);
		//Vector2 direction = Vector2{ 1, 0 }.Rotate(Math::DegToRad(owner->transform.rotation * dt));
		owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed);

		fireCooldown--;
		if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireCooldown <= 0)
		{
			auto rocket = Factory::Instance().Create<Actor>("rocket");
			rocket->transform.rotation = owner->transform.rotation;
			rocket->transform.position = owner->transform.position;
			rocket->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed * thrust);
			owner->scene->AddActor(std::move(rocket), true);
			fireCooldown = 600;
		}

		dmgTimer -= 1;

		owner->GetComponent<TextComponent>()->SetText("Score " + std::to_string(score));
	}
}

void PlayerComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "enemy" && dmgTimer <= 0) {
		lives -= 1;
		std::cout << "wow\n";
		dmgTimer = 5000;
	}
}

void PlayerComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void PlayerComponent::Write(json_t& value)
{
}