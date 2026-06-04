#pragma once
#include <raylib.h>

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

		int m_vialCount;
		Texture2D m_vial;

	private:
		void BeginPlay();

		void Tick(float dt);
		void Render();

		void EndPlay();

	};
}