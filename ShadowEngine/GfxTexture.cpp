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


bool GfxTexture::Load(std::string filename) {
	sf::Texture newTex;

	bool loadRet = newTex.loadFromFile(filename.c_str());
	if (!loadRet) {
		Logger::dprint({ "Error: ", "failed to load texture ", filename });
		return false;
	}

	sf::Sprite sprite;
	sprite.setTexture(newTex);

	sf::Vector2u texSize = newTex.getSize();
	_texture.create(texSize.x, texSize.y);
	_texture.draw(sprite);
	return true;
}

bool GfxTexture::Create(int width, int height) {
	bool createRet = _texture.create(width, height);
	if (!createRet) {
		Logger::dprint({ "Error: ", "failed to create texture ", std::to_string(width), std::to_string(height) });
		return false;
	}

	return true;
}

bool GfxTexture::LoadFromMemory(int width, int height, GfxColorComponent* memory) {
	/*sf::Image newImage;

	newImage.create(width, height, memory);*/

	return true;
}