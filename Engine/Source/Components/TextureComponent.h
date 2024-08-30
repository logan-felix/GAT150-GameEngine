#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"

class TextureComponent : public RenderComponent
{
public:
	CLASS_DECLARATION(TextureComponent)
	CLASS_PROTOTYPE(TextureComponent)

	TextureComponent() = default;

	void Initialize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

public:
	std::string textureName;
	Rect source;
	bool hflip{ false };
	res_t<Texture> texture;
};