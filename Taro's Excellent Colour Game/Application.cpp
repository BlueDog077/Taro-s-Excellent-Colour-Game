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
		m_vialTex = LoadTexture("Resources/Vial.png");
		m_taroTex = LoadTexture("Resources/TaroBallNormal.png");

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
				vialPos,																	//Base position of the vial
				{ vialPos.x + m_vialTex.width/2, vialPos.y + m_vialTex.height - 30},		//First point (bottom of vial)
				{ vialPos.x + m_vialTex.width / 2, vialPos.y + m_vialTex.height - 90 },		//Second point
				{ vialPos.x + m_vialTex.width / 2, vialPos.y + m_vialTex.height - 150 },	//Third point
				{ vialPos.x + m_vialTex.width / 2, vialPos.y + m_vialTex.height - 210},		//Fourth point (top of vial)
				m_vialTex																		//Texture
			);

			//Putting vial pointers into vector to be used later
			m_vials.emplace_back(vial);
		}	

		//********************************************* CREATING TAROS ***********************************************

		//TODO: replace random color algorithm with the correct color formula later when i actually invent one bruhhh)
	
			//Going through each vial
			for (Vial* vial : m_vials)
			{
				while (vial->capacity <= 3)
				{

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

					Vector2 pos = vial->GetPoint(vial->capacity);

					//Initialising taro
					taroBall->Init
					(
						//The position must subtract half the image width and height to centre it
						{(pos.x - m_taroTex.width / 2), (pos.y - m_taroTex.height / 2)},
						chosenColor,
						m_taroTex
					);
					//Pushing four taros to each vial.
					vial->taroArray.emplace_back(taroBall);
					vial->capacity++;
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
		//Deleting all vials from vector
		for (Vial* vial : m_vials)
		{
			delete vial;
		}
		m_vials.clear();

		//Unloading textures
		UnloadTexture(m_taroTex);
		UnloadTexture(m_vialTex);
	}
}