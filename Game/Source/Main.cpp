#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	// create texture, using shared_ptr so texture can be shared
	res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Zelda-Image.png", engine->GetRenderer());

	while (!engine->IsQuit())
	{
		engine->Update();

		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		engine->GetRenderer().DrawTexture(texture.get(), 200, 150);

		engine->GetRenderer().EndFrame();
	}

	engine->Shutdown();

	return 0;
}