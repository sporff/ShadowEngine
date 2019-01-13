#include "pch.h"


GfxTexture::GfxTexture()
{
}


GfxTexture::~GfxTexture()
{
}


bool GfxTexture::Load(std::string filename) {
	sf::Texture texture;
	bool loadRet = texture.loadFromFile(filename);
	if (loadRet) {
		sf::Sprite sprite;
		sprite.setTexture(texture);

		_texture.draw(sprite);
	}

	return loadRet;
}

bool GfxTexture::Create(int width, int height) {
	return false;
}