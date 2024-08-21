#include "Engine.h"
#include "SpaceGame.h"
#include "Components/PlayerComponent.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>(engine.get());
	game->Initialize();

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
			game->Update(engine->GetTime().GetDeltaTime());

			// render
			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			game->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}

	game->Shutdown();
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}