#pragma once
#include "Object.h"

#include <list>
#include <memory>

class Renderer;
class Actor;
class Game;
class Engine;

class Scene : public Object
{
public:
	Scene(Engine* engine, Game* game = nullptr) : 
		engine{ engine },
		game{ game }
	{}

	CLASS_DECLARATION(Scene);

	void Initialize() override;
	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor);
	void RemoveAll();

	template<typename T>
	T* GetActor();

	Game* GetGame() { return game; }

public:
	Engine* engine{ nullptr };
	Game* game{ nullptr };

protected:
	std::list<std::unique_ptr<Actor>> actors;
};

template<typename T>
T* Scene::GetActor()
{
	for (auto& actor : actors)
	{
		T* result = dynamic_cast<T*>(actor.get());
		if (result != nullptr) return result;
	}

	return nullptr;
}