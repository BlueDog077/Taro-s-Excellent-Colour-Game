#pragma once
#include <raylib.h>
#include <vector>


class TaroBall
{
public:
	TaroBall();
	~TaroBall();

	void Init(Vector2 pos, Color color, Texture2D tex);
	void Draw() const;
	void SetPosition(Vector2 pos, float bufferX, float bufferY);

private:
	Vector2 m_position;
	Color m_color;
	Texture2D m_taroTexture;

	
};

/*************************************** Defining ***************************************/

inline TaroBall::TaroBall() 
	: m_position{ 0, 0 }, m_color{ WHITE }, m_taroTexture{ }
{}

inline TaroBall::~TaroBall()
{}


inline void TaroBall::Init(Vector2 pos, Color color, Texture2D tex)
{
	m_position = pos;
	m_color = color;
	m_taroTexture = tex;
}

inline void TaroBall::Draw() const
{
	DrawTexture(m_taroTexture, m_position.x, m_position.y, m_color);
}

inline void TaroBall::SetPosition(Vector2 pos, float bufferX, float bufferY)
{
	m_position = {(pos.x - bufferX),(pos.y - bufferY)};
}
