#pragma once
class GfxTexture
{
public:
	GfxTexture();
	~GfxTexture();

	bool Load(std::string filename);
	bool Create(uint64_t width, uint64_t height);

	sf::RenderTexture* _getTexture();
	sf::Sprite* _getSprite();
private:
	sf::RenderTexture _texture;
	sf::Sprite _sprite;
};

