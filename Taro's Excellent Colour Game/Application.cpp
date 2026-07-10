#include "Application.h"

#include "TaroBall.h"
#include <iostream>
#include <raylib.h>
#include <algorithm>
#include <vector>
#include <random>

using std::random_shuffle;


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

		//Misc inits
		m_selectedVial = nullptr;

		//rng
		static std::random_device img;
		static std::mt19937 rng(img());

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

		
		//Going through each vial - 1 (to generate enough taro balls for only four vials)
		for (int i = 0; i < MAX_VIAL_COUNT - 1; i++)
		{
			std::uniform_int_distribution<std::mt19937::result_type> dist(0, 3);

			Color chosenColor = m_colors[dist(rng)];


			//Counter to help us create four taro balls for each of the four vials
			int taroBallCounter = 0;

			while (taroBallCounter <= 3)
			{
				taroBallCounter++;
				//Creating a new taro object
				TaroBall* taroBall = new TaroBall;


				//Initialising taro
				taroBall->Init
				(
					//Setting to 0,0 so that shuffle can correctly place taros in position
					{0, 0},
					chosenColor,
					0,					///NEED COLOR ID SOMEHWOW. THIS WILL; HELP US COMPARE THE TARO BALL COLORS TO ONE ANOTHER LATER USING THE IDS GIVEN
					m_taroTex
				);
				//Adding taro to the pool to be shuffled 
				m_taroPool.emplace_back(taroBall);
			}
		}

		//Choosing one of the five vials at random and clearing it before continuing to the taro ball creation logic
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, 4);
		int emptyVial = dist(rng);
		m_vials[1]->taroArray.clear();

		std::shuffle(m_taroPool.begin(), m_taroPool.end(), rng);

		int counter = 0;

		for (int i = 0; i < MAX_VIAL_COUNT; i++)
		{
			//Continue the loop if the current vial = the random vial cleared previously
			//This is because this vial will remain empty and we only want 4 taro balls in 4 vials, not 5.
			if (i == emptyVial)
			{
				continue;
			}
			//Picking a random color from m_colors
			std::uniform_int_distribution<std::mt19937::result_type> dist(0, 3);
			Color chosenColor = m_colors[dist(rng)];

			//While the capacity of the vial is not full
			while (m_vials[i]->capacity <= 3)
			{
				//Pushing four taros to each vial.
				Vector2 pos = (m_vials[i]->GetPoint(m_vials[i]->capacity));

				m_taroPool[counter]->SetPosition(pos, m_taroTex.width / 2, m_taroTex.height / 2);
				m_vials[i]->taroArray.emplace_back(m_taroPool[counter]);
				m_vials[i]->capacity++;
				counter++;
			}
		}
	}

	void Application::Tick(float dt)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Vector2 clickPos = GetMousePosition();

			for (Vial* vial : m_vials)
			{
				Rectangle vialArea = vial->GetArea();

				//If the position is within the bounds of the rectangle/area of the vial
				if (clickPos.x >= vialArea.x && clickPos.x <= (vialArea.x + vialArea.width) 
					&& clickPos.y >= vialArea.y && clickPos.y <= (vialArea.y + vialArea.height))
				{
					//If a vial has not already been selected/toggled
					if (m_selectedVial == nullptr)
					{
						vial->SetToggled(true);
						m_selectedVial = vial;

						//Exit loop as a vial was found
						break;
					}
					else
					{
						//TODO: LOGIC FOR MOVING TARO BALL TO NEXT VIAL GOES HERE
						//Breaking out of the loop/toggle logic if the vial is empty
						if (m_selectedVial->taroArray.empty())
						{
							m_selectedVial->SetToggled(false);
							m_selectedVial = nullptr;
							break;
						}

						//Getting the taro at the top of the selected vial
						TaroBall* movingTaro = m_selectedVial->taroArray.front();
						std::cout << movingTaro->GetColorId();

						m_selectedVial->SetToggled(false);
						m_selectedVial = nullptr;
					}
				}
			}
		}
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
			vial->taroArray.clear();
			delete vial;
		}
		m_vials.clear();

		//Unloading textures
		UnloadTexture(m_taroTex);
		UnloadTexture(m_vialTex);
	}
}