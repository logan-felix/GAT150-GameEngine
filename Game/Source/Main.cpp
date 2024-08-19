#include "Engine.h"
#include "Components/PlayerComponent.h"

#include <iostream>
#include <cstdlib>
#include <vector>

void func1(int i) { std::cout << "func1: " << i << std::endl; }
void func2(int i) { std::cout << "func2: " << i << std::endl; }

int main(int argc, char* argv[])
{
	void(*fp)(int);

	fp = &func1;
	fp(5);

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
			// update
			engine->Update();
			scene->Update(engine->GetTime().GetDeltaTime());

			auto* actor = scene->GetActor<Actor>("text");
			if (actor)
			{
				//actor->transform.scale = (1.0f + Math::Sin(engine->GetTime().GetTime())) * 5;
				//actor->transform.rotation += 90 * engine->GetTime().GetDeltaTime();
			}

			// render
			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			scene->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}

	scene->RemoveAll();
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}