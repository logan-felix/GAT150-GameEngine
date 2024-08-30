#pragma once

// ** core **
#include "Core/ETime.h"
#include "Core/EAssert.h"
#include "Core/EFile.h"
#include "Core/EString.h"
#include "Core/Json.h"
#include "Core/Singleton.h"
#include "Core/Factory.h"

// ** systems **
// renderer
#include "Renderer/Renderer.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Model.h"
#include "Renderer/Color.h"
#include "Renderer/Texture.h"

// input
#include "Input/Input.h"

// audio
#include "Audio/Audio.h"
#include "Audio/AudioClip.h"
#include "Audio/AudioSource.h"

// ** math **
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/MathUtil.h"
#include "Math/Transform.h"
#include "Math/Rect.h"

// ** framework **
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"

// ** resources **
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

// ** event system **
#include "Event/EventSystem.h"

// ** components **
#include "Components/TextureComponent.h"
#include "Components/TextureAnimationComponent.h"
#include "Components/EnginePhysicsComponent.h"
#include "Components/TextComponent.h"
#include "Components/CircleCollisionComponent.h"
#include "Components/AudioComponent.h"

// ** physics **
#include "Physics/Physics.h"

#include <fmod.hpp>
#include <SDL.h>

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }
	ParticleSystem& GetPS() { return *m_particleSystem; }
	Physics& GetPhysics() { return *m_physics; }

	Time& GetTime() { return *m_time; }

	bool IsQuit() { return quit; }

private:
	bool quit{ false };

	std::shared_ptr<Time> m_time;

	std::shared_ptr<Renderer> m_renderer;
	std::shared_ptr<Input> m_input;
	std::shared_ptr<Audio> m_audio;

	std::unique_ptr<ParticleSystem> m_particleSystem;

	std::unique_ptr<Physics> m_physics;
};


