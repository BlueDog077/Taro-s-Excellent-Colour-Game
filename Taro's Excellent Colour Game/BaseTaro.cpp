#include "BaseTaro.h"

BaseTaro::BaseTaro(float x, float y, TaroColor taroColorIndex, Texture2D sprite)
	: m_location{ x, y }, m_taroColorIndex{ taroColorIndex }, m_taroSprite{ sprite }
{}

BaseTaro::~BaseTaro() = default;

void BaseTaro::DrawSprite() const
{
	switch (m_taroColorIndex)
	{
		//Set sprites based on what the case/color chosen is
		//TODO: Set the default tarocolor enum for each derived taro type
		case TaroColor::Red:
		{
			DrawTextureV(m_taroSprite, m_location, RED);
			
			break;
		}

		case TaroColor::Yellow:
		{
			DrawTextureV(m_taroSprite, m_location, YELLOW);
			break;
		}

		case TaroColor::Blue:
		{
			DrawTextureV(m_taroSprite, m_location, BLUE);
			break;
		}

		case TaroColor::Green:
		{
			DrawTextureV(m_taroSprite, m_location, GREEN);
			break;
		}
	}
}
