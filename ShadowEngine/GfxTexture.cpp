#include "pch.h"


GfxTexture::GfxTexture()
{
}

GfxTexture::~GfxTexture()
{
}

sf::RenderTexture* GfxTexture::_getTexture() {
	return &_texture; 
}

sf::Sprite* GfxTexture::_getSprite() {
	return &_sprite;
}

bool GfxTexture::Load(std::string filename) {
	sf::Texture texture;
	bool loadRet = texture.loadFromFile(filename.c_str());
	if (loadRet) {
		sf::Sprite sprite;
		sprite.setTexture(texture);

		sf::Vector2u size = texture.getSize();
		_texture.create(size.x, size.y);
		_texture.draw(sprite);
	}

	return loadRet;
}

bool GfxTexture::Create(uint64_t width, uint64_t height) {
	bool createRet = _texture.create(width, height);

	return createRet;
}

