#pragma once

using GfxColor = sf::Color;
using GfxKey = uint64_t;

class GfxWrap
{
public:
	static const GfxKey Invalid = 0;
	GfxWrap();
	~GfxWrap();

	GfxKey NextTextureKey();
	bool Init(std::string title, int windowWidth, int windowHeight, std::function<bool(GfxWrap&)> );
	void Shutdown();
	void Begin();

	void Clear();
	void Clear(GfxColor clr);
	bool Present();
	bool DrawTexture(GfxKey key);

	void SetTarget(GfxTexture* newTarget);
	void UnsetTarget();
	GfxKey LoadTexture(std::string filename);
	GfxKey CreateTexture(int width, int height);
	

private:
	std::function<bool(GfxWrap&)> _mainCallback;
	sf::RenderWindow _window;
	GfxTexture* _targetTexture = nullptr;
	std::unordered_map<GfxKey, std::shared_ptr<GfxTexture>> _textures;
	GfxKey _nextTextureKey = {1};
};

