#include "Application.h"
#include "BaseTaro.h"

#include <raylib.h>

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

		//Loading Taro sprites
		m_taroSprite = LoadTexture("Resources/TaroBallNormal.png");
	

	}

	void Application::Tick(float dt)
	{}

	void Application::Render()
	{
		for (int i = 0; i < m_vialCount; i++)
		{
			DrawTextureV(m_vial, { (10 + static_cast<float>(i) * 100), -50}, WHITE);
		}

		BaseTaro* taro = new BaseTaro{ 100, 100, TaroColor::Green, m_taroSprite};
		taro->DrawSprite();
	
	}

	void Application::EndPlay()
	{}
}