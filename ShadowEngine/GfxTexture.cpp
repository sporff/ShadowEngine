#include "pch.h"


GfxTexture::GfxTexture()
{
}


GfxTexture::~GfxTexture()
{
}


bool GfxTexture::IsLoaded() {
	return false;
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

void GfxTexture::DrawLine(double x1, double y1, double x2, double y2, GfxColor clr) {
	/*sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(x1, y1), clr),
		sf::Vertex(sf::Vector2f(x2, y2), clr)
	};
	_texture.draw(line, 2, sf::Lines);*/

	sf::VertexArray line(sf::Lines, 2);
	line[0].position = { x1, y1 };
	line[1].position = { x1, y1 };

	line[0].color = clr;
	line[1].color = clr;

	_texture.draw(line);

}


void GfxTexture::DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, GfxColor clr) {
	sf::VertexArray triangle(sf::Triangles, 3);

	triangle[0].position = { x1,y1 };
	triangle[1].position = { x2,y2 };
	triangle[2].position = { x3,y3 };

	triangle[0].color = clr;
	triangle[1].color = clr;
	triangle[2].color = clr;

	_texture.draw(triangle);
}

void GfxTexture::DrawQuad(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, GfxColor clr) {

}