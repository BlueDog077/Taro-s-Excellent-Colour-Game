#pragma once
#include <raylib.h>
#include "Stack.h"
#include <vector>
#include "Vial.h"

using std::vector;

//Max size a vial can have
constexpr int MAX_VIAL_COUNT = 5;
constexpr int MAX_TARO_COUNT = 4;

class BaseTaro;
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

		//Vials
		vector<Vial*> m_vials;


	private:
		void BeginPlay();

		void Tick(float dt);
		void Render();

		void EndPlay();

	};
}
