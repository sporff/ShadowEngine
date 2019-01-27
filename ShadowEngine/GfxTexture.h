#pragma once
class GfxTexture
{
public:
	GfxTexture();
	~GfxTexture();

	bool Load(std::string filename);
	bool Create(int width, int height);

	sf::RenderTexture* _getTexture();
private:
	sf::RenderTexture _texture;
};

