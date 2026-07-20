#pragma once
#include <raylib.h>
#include <vector>


class TaroBall
{
public:
	TaroBall();
	~TaroBall();

	void Init(Vector2 pos, Color color, uint16_t colorId, Texture2D tex);
	void Draw() const;
	uint16_t GetColorId();
	Vector2 GetPosition();
	void SetPosition(Vector2 pos, float bufferX, float bufferY);
	void OffsetY(int offset);

private:
	Vector2 m_position;
	Color m_color;
	uint16_t m_colorId;
	Texture2D m_taroTexture;

};

/*************************************** Defining ***************************************/

inline TaroBall::TaroBall() 
	: m_position{ 0, 0 }, m_color{ WHITE }, m_taroTexture{ }
{}

inline TaroBall::~TaroBall()
{}


inline void TaroBall::Init(Vector2 pos, Color color, uint16_t colorId, Texture2D tex)
{
	m_position = pos;
	m_color = color;
	m_taroTexture = tex;
	m_colorId = colorId;
}

inline void TaroBall::Draw() const
{
	DrawTexture(m_taroTexture, m_position.x, m_position.y, m_color);
}

inline uint16_t TaroBall::GetColorId()
{
	return m_colorId;
}

inline Vector2 TaroBall::GetPosition()
{
	return m_position;
}

inline void TaroBall::SetPosition(Vector2 pos, float bufferX, float bufferY)
{
	m_position = {(pos.x - bufferX),(pos.y - bufferY)};
}

inline void TaroBall::OffsetY(int offset)
{
	m_position.y -= offset;
}
