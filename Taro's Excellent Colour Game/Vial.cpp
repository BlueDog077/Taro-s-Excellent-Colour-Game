#include "Vial.h"

Vial::Vial(Texture2D* texture, float x, float y)
	: m_texture { texture }, m_x { x }, m_y { y }
{}

void Vial::PushVial(BaseTaro taro)
{
	if (IsFull()) return;
	m_contents.Push(taro);
}

void Vial::PopVial()
{}

TaroColor Vial::VialTop() const
{
	return m_count > 0 ? m_contents[m_count - 1] : ;
}

int Vial::VialCount() const
{
	return 0;
}

bool Vial::IsFull() const
{
	return false;
}

bool Vial::IsEmpty() const
{
	return false;
}

bool Vial::IsSolved() const
{
	return false;
}

void Vial::Draw() const
{}
