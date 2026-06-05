#include "Application.h"

#include "BaseTaro.h"
#include <iostream>
#include <raylib.h>
#include <vector>
#include <random>


namespace MathLibrary
{
	Application::Application(const int width, const int height, const char* title, const Color clrColor)
		: m_width{ width }, m_height{ height }, m_title{ title }, m_running{ true }, m_clearColor{ clrColor }
	{}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		InitWindow(m_width, m_height, m_title);

		BeginPlay();

		while (m_running)
		{
			Tick(GetFrameTime());

			BeginDrawing();
			ClearBackground(m_clearColor);

			Render();

			EndDrawing();

			if (WindowShouldClose())
			{
				m_running = false;
			}
		}

		EndPlay();

		CloseWindow();
	}

	void Application::Quit()
	{
		m_running = false;
	}

	void Application::BeginPlay()
	{
		//Setting up default values for the vial
		m_vial = LoadTexture("Resources/Vial.png");
		m_vialCount = 5;

		//Loading Taro stuff
		m_taroSprite = LoadTexture("Resources/TaroBallNormal.png");
		m_taroMaxCount = 16;

		m_taroXPos = 13;
		m_taroYPos = 120;
	
	}

	void Application::Tick(float dt)
	{

		for (size_t i = m_currentTaro.size(); i < m_taroMaxCount - m_vialCount; i++)
		{
			std::vector<TaroColor> randomColor =
			{
				TaroColor::Red,
				TaroColor::Yellow, 
				TaroColor::Blue,
				TaroColor::Green
			};

			 static  std::random_device img;
			 static std::mt19937 rng(img());

			std::uniform_int_distribution<std::mt19937::result_type> dist(0, randomColor.size() - 1);
			TaroColor chosenColor = randomColor[dist(rng)];

			// Moving the taro's
			if (m_currentTaro.size() < 5)
			{
				BaseTaro* taro = new BaseTaro{ m_taroXPos + static_cast<float>(i) * 100, m_taroYPos, chosenColor, m_taroSprite };
				m_taroStack.Push(taro);
				m_currentTaro.emplace_back(taro);
			}
			if (m_currentTaro.size() >= 5 && m_currentTaro.size() <= 10)
			{
				m_taroXPos = 13;
				m_taroYPos = 60;

				BaseTaro* taro = new BaseTaro{ m_taroXPos + static_cast<float>(i - 5) * 100, m_taroYPos, chosenColor, m_taroSprite };
				m_taroStack.Push(taro);
				m_currentTaro.emplace_back(taro);
			}
			if (m_currentTaro.size() > 10)
			{
				m_taroXPos = 13;
				m_taroYPos = 0;

				BaseTaro* taro = new BaseTaro{ m_taroXPos + static_cast<float>(i - 10) * 100, m_taroYPos, chosenColor, m_taroSprite };
				m_taroStack.Push(taro);
				m_currentTaro.emplace_back(taro);
				
			}
		}

	}

	void Application::Render()
	{
		for (int i = 0; i < m_vialCount; i++)
		{
			DrawTextureV(m_vial, { (10 + static_cast<float>(i) * 100), -50}, WHITE);
		}

		for (size_t i = 0; i < m_currentTaro.size(); i++)
		{
			m_currentTaro[i]->DrawSprite();
		}
	}

	void Application::EndPlay()
	{
		m_currentTaro.clear();
	}
}
