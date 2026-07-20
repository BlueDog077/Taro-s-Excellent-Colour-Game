
#pragma once
#include <raylib.h>
#include <iostream>
#include "TaroBall.h"
#include <vector>

using std::vector;

class Vial
{
public:
	Vial();
	~Vial();
	
	void Init(Vector2 pos, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Texture2D tex);
	//Sets vial to completed
	void SetComplete();
	//Returns true if completed, false otherwise.
	bool IsCompleted();
	//Gets the position of the vial
	Vector2 GetPosition();
	//Gets the specific point that the taro ball must draw to. Uses capacity as the deciding variable.
	Vector2 GetPoint(int point);
	//Gets the area of the rectangle. Used for selecting specific vials
	Rectangle GetArea();
	//Returns true if a vial is toggled, false otherwise
	bool IsToggled();
	//Sets a vial to toggled/untoggled and repositions its texture slightly
	void SetToggled(bool toggled);

	void Draw();


private:
	int m_width;
	int m_height;
	Vector2 m_position;

	Rectangle m_area;
	
	//The vial's texture
	Texture2D m_vialTexture;


	//A bool to check if the vial has been completed
	bool m_completed;
	//A bool to check if a vial has been toggled/selected
	bool m_toggled;
	//Offset that defines how much the vial and its contents should move upwards by when toggled.
	const int m_toggleOffset;


public:
	//All points in each vial
	vector<Vector2> allPoints;
	//An vector of Taro pointers that represents how many taros currently in the vial. Maximum of 5.
	vector<TaroBall*> taroArray;
	//Amount of taro balls in vial
	int capacity;
};

//***************************** Definitions *********************************

inline Vial::Vial()
	: m_width{ 0 }, m_height{ 0 }, m_position{ 0, 0 }, 
	m_vialTexture{ }, m_toggleOffset{ 20 }, m_completed { false }, m_toggled{ false }
{}

inline Vial::~Vial()
{
	for (TaroBall* taro : taroArray)
	{
		delete taro;
	}
	taroArray.clear();
}

inline void Vial::Init(Vector2 pos, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Texture2D tex)
{
	m_position = pos;

	allPoints.emplace_back(p1);
	allPoints.emplace_back(p2);
	allPoints.emplace_back(p3);
	allPoints.emplace_back(p4);

	
	m_vialTexture = tex;

	//Width and height vars of the vial are equal to the width & height of the texture image
	m_width = tex.width;
	m_height = tex.height;

	//Rectangle defining the area of a given vial
	m_area = 
	{
			pos.x,
			(pos.y),
			(float)tex.width,
			(float)tex.height 
	};

}

inline void Vial::SetComplete()
{
	m_completed = true;
}

inline bool Vial::IsCompleted()
{
	return m_completed;
}

inline Vector2 Vial::GetPoint(int point)
{
	
	return allPoints[point];
}

inline Rectangle Vial::GetArea()
{
	return m_area;
}

inline bool Vial::IsToggled()
{
	return m_toggled;
}

inline void Vial::SetToggled(bool toggled)
{
	m_toggled = toggled;

	if (m_toggled)
	{
		m_position.y -= m_toggleOffset;

		for (TaroBall* taro : taroArray)
		{
			taro->OffsetY(m_toggleOffset);
		}
	}
	else
	{
		m_position.y += m_toggleOffset;

		for (TaroBall* taro : taroArray)
		{
			taro->OffsetY(-m_toggleOffset);
		}
	}
}

inline void Vial::Draw()
{
	DrawTexture(m_vialTexture, m_position.x, m_position.y, WHITE);

	/*
	for (Vector2 point : allPoints)
	{
		DrawCircle(point.x, point.y, 5.f, RED);
	}
	*/
}



