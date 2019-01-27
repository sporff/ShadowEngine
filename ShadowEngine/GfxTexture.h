#pragma once
class GfxTexture
{
public:
	GfxTexture();
	~GfxTexture();

	bool IsLoaded();

	bool Load(std::string filename);
	bool Create(int width, int height);

	void DrawLine(double x1, double y1, double x2, double y2, GfxColor clr);
	void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, GfxColor clr);
	void DrawQuad(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, GfxColor clr);

	sf::RenderTexture* _getTexture();
private:
	sf::RenderTexture _texture;
};

