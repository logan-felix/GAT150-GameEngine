#include "Engine.h"
#include "Components/PlayerComponent.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());
	Factory::Instance().Register<EnginePhysicsComponent>(EnginePhysicsComponent::GetTypeName());
	Factory::Instance().Register<PlayerComponent>("PlayerComponent");


	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::string buffer;
	File::ReadFile("Scenes/scene.json", buffer);
	std::cout << buffer << std::endl;

	rapidjson::Document document;
	Json::Load("Scenes/scene.json", document);

	std::unique_ptr<Scene> scene = std::make_unique<Scene>(engine.get());
	scene->Read(document);
	scene->Initialize();

	{
		// create texture, using shared_ptr so texture can be shared
		//res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Zelda-Image.png", engine->GetRenderer());
		//res_t<Font> font = ResourceManager::Instance().Get<Font>("ArcadeClassic.ttf", 50);
		//std::unique_ptr<Text> text = std::make_unique<Text>(font);
		//text->Create(engine->GetRenderer(), "WOWIE!", { 0.537f, 0.812f, 0.941f, 1 });

		//auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		//actor->transform = Transform{ { 200, 150 } };
		//auto component = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
		//component->texture = texture;
		//actor->AddComponent(std::move(component));

		while (!engine->IsQuit())
		{
			engine->Update();
			scene->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			scene->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}

	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}