
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
	//Returns true if completed, false otherwise.
	bool isCompleted();
	//Gets the position of the vial
	Vector2 GetPosition();
	//Gets the specific point that the taro ball must draw to. Uses capacity as the deciding variable.
	Vector2 GetPoint(int point);
	//Gets the area of the rectangle. Used for selecting specific vials
	Rectangle GetArea();
	//Returns true if a vial is toggled, false otherwise
	bool IsToggled();
	//Sets a vial to toggled/untoggled
	void SetToggled(bool toggled);


	void Draw();



private:
	int m_width;
	int m_height;
	Vector2 m_position;

	//Four specific points in the vial that indicate where a taro ball will be positioned.
	//Different for each vial asit is relative to the vials position.
	Vector2 m_point1;
	Vector2 m_point2;
	Vector2 m_point3;
	Vector2 m_point4;

	Rectangle m_area;
	
	//The vial's texture
	Texture2D m_vialTexture;

	//A bool to check if the vial has been completed
	bool m_completed;
	//A bool to check if a vial has been toggled/selected
	bool m_toggled;


public:
	//An vector of Taro pointers that represents how many taros currently in the vial. Maximum of 5.
	vector<TaroBall*> taroArray;
	//Amount of taro balls in vial
	int capacity;
};

//***************************** Definitions *********************************

inline Vial::Vial()
	: m_width{ 0 }, m_height{ 0 }, m_position{ 0, 0 }, 
	m_point1{ 0, 0 }, m_point2{ 0,0 }, m_point3{ 0, 0 }, m_point4{ 0, 0 },
	m_vialTexture{ }, m_completed{ false }, m_toggled{ false }
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
	m_point1 = p1;
	m_point2 = p2;
	m_point3 = p3;
	m_point4 = p4;
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

inline bool Vial::isCompleted()
{
	return m_completed;
}

inline Vector2 Vial::GetPosition()
{
	return m_position;
}

inline Vector2 Vial::GetPoint(int point)
{
	switch (point)
	{
		case 0:
		{
			return m_point1;
		}
		case 1:
		{
			return m_point2;
		}
		case 2:
		{
			return m_point3;
		}
		case 3:
		{
			return m_point4;
		}
	}
	return Vector2();
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
}

inline void Vial::Draw()
{
	DrawTexture(m_vialTexture, m_position.x, m_position.y, WHITE);

	//Temporary circles to see points positions
	DrawCircle(m_point1.x, m_point1.y, 5.f, RED);
	DrawCircle(m_point2.x, m_point2.y, 5.f, RED);
	DrawCircle(m_point3.x, m_point3.y, 5.f, RED);
	DrawCircle(m_point4.x, m_point4.y, 5.f, RED);

}



