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