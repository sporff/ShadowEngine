#pragma once



class GfxWrap
{
public:
	static constexpr GfxKey InvalidKey = { 0 };

	GfxWrap();
	~GfxWrap();
	//bool (*mainCallback)(GfxWrap&)
	bool Init(std::string title, int windowWidth, int windowHeight, std::function<bool(GfxWrap&)> );
	void Shutdown();
	void Clear();
	void Clear(GfxColor clr);
	bool Present();
	bool SetTarget(GfxKey key);
	void UnsetTarget();
	bool Blit(GfxKey key, double x, double y, double width, double height);
	bool BlitEx(GfxKey key, double x, double y, double width, double height, double ox, double oy, double degrees, double scale);
	void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, GfxColor clr);
	GfxKey LoadTexture(std::string filename);
	GfxKey CreateTexture(int width, int height);

	void Begin();

private:
	//bool(*_mainCallback)(GfxWrap&) = nullptr;
	std::function<bool(GfxWrap&)> _mainCallback;
	sf::RenderWindow _window;
	std::shared_ptr<GfxTexture> _targetTexture = nullptr;
	GfxKey _nextTextureKey = { 1 };
	std::unordered_map<GfxKey, std::shared_ptr<GfxTexture>> _textures;

	GfxKey _getNextTextureKey();
	std::shared_ptr<GfxTexture> _getTexture(GfxKey key);
};

