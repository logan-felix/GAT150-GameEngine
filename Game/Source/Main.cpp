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

	std::string s;
	File::ReadFile("text.txt", s);
	std::cout << s;

	rapidjson::Document document;
	Json::Load("text.txt", document);

	std::string name;
	int age;
	bool isAwake;

	READ_DATA(document, age);
	READ_DATA(document, name);
	READ_DATA(document, isAwake);

	std::cout << name << " " << age << " " << isAwake << std::endl;

	{
		// create texture, using shared_ptr so texture can be shared
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Zelda-Image.png", engine->GetRenderer());

		res_t<Font> font = ResourceManager::Instance().Get<Font>("ArcadeClassic.ttf", 50);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "WOWIE!", { 1, 1, 0, 1 });

		Transform t{ { 30, 30 } };
		std::unique_ptr<Actor> actor = std::make_unique<Actor>(t);
		std::unique_ptr<TextureComponent> component = std::make_unique<TextureComponent>();
		component->texture = texture;
		actor->AddComponent(std::move(component));

		while (!engine->IsQuit())
		{
			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			// draw texture
			//engine->GetRenderer().DrawTexture(texture.get(), 200, 150);
			
			// draw text
			text->Draw(engine->GetRenderer(), 50, 50);
			actor->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}

	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}