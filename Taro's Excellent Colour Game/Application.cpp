#include "Application.h"

#include "TaroBall.h"
#include <iostream>
#include <raylib.h>
#include <vector>
#include <random>


namespace MathLibrary
{
	Application::Application(const int width, const int height, const char* title, const Color clrColor)
		: m_width{ width }, m_height{ height }, m_title{ title }, m_running{ true }, m_clearColor{ clrColor }
	{}

	Application::~Application() = default;

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
		//Loading textures
		Texture2D vialTex = LoadTexture("Resources/Vial.png");
		Texture2D taroTex = LoadTexture("Resources/TaroBallNormal.png");

		//********************************************* CREATING VIALS ***********************************************

		for (int i = 0; i < MAX_VIAL_COUNT; i++)
		{
			//Creating a new vial object
			Vial* vial = new Vial;

			//Getting specific position for each vial based on the loop.
			Vector2 vialPos = { 130 + (100 * (float)i), 100 };

			//Initialising vials
			vial->Init
			(
				vialPos,																//Base position of the vial
				{ vialPos.x + vialTex.width/2, vialPos.y + vialTex.height - 20},		//First point (bottom of vial)
				{ vialPos.x + vialTex.width / 2, vialPos.y + vialTex.height - 80 },		//Second point
				{ vialPos.x + vialTex.width / 2, vialPos.y + vialTex.height - 140 },	//Third point
				{ vialPos.x + vialTex.width / 2, vialPos.y + vialTex.height - 200},		//Fourth point (top of vial)
				vialTex																	//Texture
			);

			//Putting vial pointers into vector to be used later
			m_vials.emplace_back(vial);
		}	

		//********************************************* CREATING TAROS ***********************************************

		//Creates four taro balls for every vial 
		for (int i = 0; i < (MAX_VIAL_COUNT * MAX_TARO_COUNT) - 2; i++)
		{
			//TODO: replace random color algorithm with the correct color formula later when i actually invent one bruhhh)
		//Choosing a random color
			Color randomColor[4] =
			{
				RED,
				YELLOW,
				BLUE,
				GREEN
			};

			static std::random_device img;
			static std::mt19937 rng(img());

			std::uniform_int_distribution<std::mt19937::result_type> dist(0, 3);
			Color chosenColor = randomColor[dist(rng)];

			//Creating a new taro object
			TaroBall* taroBall = new TaroBall;

			//TODO: Contain the taropos in a formula to ensure it aligns with each point in the vial.
			Vector2 taroPos = { 50, 50 };

			//Initialising taro
			taroBall->Init
			(
				taroPos,
				chosenColor,
				taroTex
			);

			//Going through each vial
			for (Vial* vial : m_vials)
			{
				while (vial->capacity != 4)
				{
					vial->taroArray.emplace_back(taroBall);
					vial->capacity++;
				}
			}
		}
		
	}

	void Application::Tick(float dt)
	{


	}

	void Application::Render()
	{
		for (Vial* vial : m_vials)
		{
			vial->Draw();

			for (TaroBall* taroBall : vial->taroArray)
			{
				taroBall->Draw();
			}
		}
		
	}

	void Application::EndPlay()
	{
	}
}