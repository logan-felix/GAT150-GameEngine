#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>("TextureComponent");

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::string s;
	File::ReadFile("text.txt", s);
	std::cout << s;

	rapidjson::Document document;
	Json::Load("text.txt", document);

	int age;
	std::string name;
	bool isAwake;
	Vector2 position;
	Color color;

	READ_DATA(document, age);
	READ_DATA(document, name);
	READ_DATA(document, isAwake);
	READ_DATA(document, position);
	READ_DATA(document, color);

	std::cout << "\n" << name << " " << age << " " << isAwake << std::endl;
	std::cout << position.x << " " << position.y << std::endl;
	std::cout << color.r << " " << color.g << " " << color.b << " " << color.a << std::endl;

	{
		// create texture, using shared_ptr so texture can be shared
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Zelda-Image.png", engine->GetRenderer());

		res_t<Font> font = ResourceManager::Instance().Get<Font>("ArcadeClassic.ttf", 50);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "WOWIE!", { 0.537, 0.812, 0.941, 1 });

		Transform t{ { 200, 150 } };
		auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		actor->SetTransform(t);
		auto component = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
		component->texture = texture;
		actor->AddComponent(std::move(component));

		while (!engine->IsQuit())
		{
			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			//engine->GetRenderer().DrawTexture(texture.get(), 200, 150);
			
			text->Draw(engine->GetRenderer(), 50, 50);
			actor->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}

	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}