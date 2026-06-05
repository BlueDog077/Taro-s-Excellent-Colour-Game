#pragma once
#include <raylib.h>
#include <vector>

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
	Vector2 m_location;
	TaroColor m_taroColorIndex;
	Texture2D m_taroSprite;

	
};



