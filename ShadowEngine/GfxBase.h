#pragma once

using GfxColor = sf::Color;
using GfxKey = uint64_t;
using GfxVector2f = sf::Vector2f;
using GfxVector2i = sf::Vector2i;

enum GfxBlendMode {
	GfxBlendAdd,
	GfxBlendMod,
	GfxBlendNone,
	GfxBlendAlpha
};