#pragma once
#include <raylib.h>

enum class TaroColor
{
	Red		= 1,
	Yellow	= 2,
	Green	= 3,
	Blue	= 4
};

class BaseTaro
{
public:
	BaseTaro(float x, float y, TaroColor taroColorIndex, Texture2D sprite);
	~BaseTaro();

public:
	void DrawSprite() const;

private:
	//need to store enum for color, size, x, and y.
	Vector2 m_location;
	TaroColor m_taroColorIndex;
	Texture2D m_taroSprite;
};



