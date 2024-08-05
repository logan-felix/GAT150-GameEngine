#pragma once
#include "../Resources/Resource.h"
#include "Renderer.h"
#include "../Math/Vector2.h"

class Texture : public Resource
{
public:
	Texture() = default;
	~Texture();

	bool Create(std::string name, ...) override;
	bool Load(const std::string& filename, class Renderer& renderer);

	Vector2 GetSize();

	friend class Renderer;

private:
	struct SDL_Texture* m_texture{ nullptr };
};