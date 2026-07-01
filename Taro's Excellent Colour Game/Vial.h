
#pragma once
#include <raylib.h>
#include "BaseTaro.h"
#include <vector>

using std::vector;

class Vial
{
public:
	Vial();
	~Vial();

	//Returns true if completed, false otherwise.
	bool isCompleted();
	//Gets the Taro* at the top of the vial.
	//Taro* Top();
	void Draw();

public:
	int height;
	int width;
	Vector2 position;
private:
	//An vector of Taro pointers that represents how many taros currently in the vial. Maximum of 5.
	vector<BaseTaro*> m_taroArray;
	//The vial's texture
	Texture2D m_vialTexture;
	//A bool to check if the vial has been completed
	bool m_completed;
};

//***************************** Definitions *********************************

inline Vial::Vial()
	: height{ 50 }, width{ 20 }, position{ 0, 0 }, m_taroArray{ nullptr }, m_vialTexture{ LoadTexture("Resources/Vial.png") }
{}

inline Vial::~Vial()
{}

inline bool Vial::isCompleted()
{
	return m_completed;
}

inline void Vial::Draw()
{
	DrawTexture(m_vialTexture, position.x, position.y, WHITE);
}



