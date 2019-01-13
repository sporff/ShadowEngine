#pragma once

using GfxColor = sf::Color;
using GfxKey = uint64_t;

class GfxWrap
{
public:
	GfxWrap();
	~GfxWrap();
	//bool (*mainCallback)(GfxWrap&)
	bool Init(std::string title, int windowWidth, int windowHeight, std::function<bool(GfxWrap&)> );
	void Shutdown();
	void Clear();
	void Clear(GfxColor clr);
	bool Present();
	void SetTarget(GfxTexture* newTarget);
	void UnsetTarget();
	bool LoadTexture(std::string filename);
	bool CreateTexture(int width, int height);

	void Begin();

private:
	//bool(*_mainCallback)(GfxWrap&) = nullptr;
	std::function<bool(GfxWrap&)> _mainCallback;
	sf::RenderWindow _window;
	GfxTexture* _targetTexture = nullptr;
	std::unordered_map<GfxKey, GfxTexture> _textures;
};

