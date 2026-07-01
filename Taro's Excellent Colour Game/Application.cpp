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
	{}

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
		for (int i = 0; i < m_vialCount; i++)
		{
			Vial* vial = new Vial;
			std::cout << "Vial " << i << ": " << vial->position.x << vial->position.y << "\n";
			vial->position = { (50 * (float)i) * 2, -50 };
			vial->Draw();
			m_vials.emplace_back(vial);

		}
	}

	void Application::Tick(float dt)
	{

		/*for (size_t i = m_currentTaro.size(); i < m_taroMaxCount; i++)
		{
			std::vector<TaroColor> randomColor =
			{
				TaroColor::Red,
				TaroColor::Yellow,
				TaroColor::Blue,
				TaroColor::Green
			};

			 static std::random_device img;
			 static std::mt19937 rng(img());

			std::uniform_int_distribution<std::mt19937::result_type> dist(0, randomColor.size() - 1);
			TaroColor chosenColor = randomColor[dist(rng)];


		}*/

	}

	void Application::Render()
	{
		for (Vial* vial : m_vials)
		{
			vial->Draw();
		}
	}

	void Application::EndPlay()
	{
		//m_currentTaro.clear();
	}
}