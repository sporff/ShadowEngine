#pragma once
class GfxTexture
{
public:
	GfxTexture();
	~GfxTexture();

	bool Load(std::string filename);
	bool Create(int width, int height);
private:
	sf::RenderTexture _texture;
};

