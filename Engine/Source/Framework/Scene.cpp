#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
#include <algorithm>

void Scene::Initialize()
{
	for (auto& actor : actors)
	{
		actor->Initialize();
	}
}

void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			AddActor(std::move(actor));
		}
	}
}

void Scene::Write(json_t& value)
{
}

void Scene::Update(float dt)
{
	// update
	for (auto& actor : actors)
	{
		actor->Update(dt);
	}

	std::erase_if(actors, [](auto& actor) { return actor->destroyed; });
}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : actors)
	{
		actor->Draw(renderer);
	}
}

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->scene = this;
	actors.push_back(std::move(actor));
}

void Scene::RemoveAll()
{
	actors.clear();
}

