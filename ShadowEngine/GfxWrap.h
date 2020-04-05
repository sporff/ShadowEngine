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
	GfxKey LoadTexture(std::string filename);
	GfxKey CreateTexture(int width, int height);

	void Clear();
	void Clear(GfxColor clr);
	void Present();
	void Begin();

	bool SetTarget(GfxKey key);
	void UnsetTarget();
	bool Blit(GfxKey key, float x, float y, float width, float height);
	bool BlitEx(GfxKey key, float x, float y, float width, float height, float ox, float oy, float degrees, float scale, GfxBlendMode blendMode);
	bool BlitEx(GfxKey key, float x, float y, float width, float height, float ox, float oy, float degrees, float scale, float texScale, GfxBlendMode blendMode);

	void DrawLine(float x1, float y1, float x2, float y2, GfxColor clr);
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, GfxColor clr);
	void DrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, GfxColor clr);

	GfxVector2i GetMousePos();

private:
	//bool(*_mainCallback)(GfxWrap&) = nullptr;
	std::function<bool(GfxWrap&)> _mainCallback;
	sf::RenderWindow _window;
	bool _targetIsWindow = false;
	sf::RenderTarget* _renderTarget = nullptr;		// Either _window or a RenderTexture

	GfxKey _nextTextureKey = { 1 };
	GfxKey _getNextTextureKey();
	
	std::unordered_map<GfxKey, std::shared_ptr<GfxTexture>> _textures;
	std::shared_ptr<GfxTexture> _getTexture(GfxKey key);
};

