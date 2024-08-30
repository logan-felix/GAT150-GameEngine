#include "EnemyComponent.h"
#include "Engine.h"

FACTORY_REGISTER(EnemyComponent)

void EnemyComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&EnemyComponent::OnCollisionEnter, this, std::placeholders::_1);
}

void EnemyComponent::Update(float dt)
{
	float thrust = 0;
	Vector2 direction{ 0, 1 };
	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed);
}

void EnemyComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "player") 
	{
		this->Deactivate();
	}
}

void EnemyComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void EnemyComponent::Write(json_t& value)
{
}