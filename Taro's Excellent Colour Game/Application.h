#pragma once
#include <raylib.h>
#include <vector>
#include "Vial.h"

using std::vector;

//Max size a vial can have
constexpr int MAX_VIAL_COUNT = 5;
constexpr int MAX_TARO_COUNT = 4;

namespace MathLibrary
{

	class Application
	{
	public:
		Application(int width, int height, const char* title, Color clrColor);
		~Application();

	public:
		void Run();
		void Quit();

	private:

		int m_width;
		int m_height;
		const char* m_title;

		bool m_running;
		Color m_clearColor;

		bool m_roundWon;

		//Vials
		//Vector of all five vials
		vector<Vial*> m_vials;
		//Stores the vial that has been clicked/selected
		Vial* m_selectedVial;

		//****Taros*****
		//Vector of all necessary taro balls neeeded for one round. They are shuffled and pushed to individual vials
		vector<TaroBall*> m_taroPool;
		//Array of possible colors
		Color m_colors[4]{
				RED,
				YELLOW,
				BLUE,
				GREEN
		};

		//Textures
		Texture2D m_vialTex;
		Texture2D m_taroTex;


	private:
		void BeginPlay();

		void Tick(float dt);
		void Render();

		void InitVials();
		void InitTaros();

		void WinCheck();

		void EndPlay();

	};
}
