#pragma once
class GfxTexture
{
public:
	GfxTexture();
	~GfxTexture();

	bool Load(std::string filename);
	bool Create(int width, int height);
	bool LoadFromMemory(int width, int height, GfxColorComponent* memory);



	sf::RenderTexture* _getTexture();
private:
	sf::RenderTexture _texture;
};

