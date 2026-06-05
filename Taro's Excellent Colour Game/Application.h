#pragma once
#include <raylib.h>
#include "Stack.h"
#include <vector>

using std::vector;

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

		Texture2D m_vial;
		int m_vialCount;
		vector<Texture2D*> m_vialList;

		//Taro
		Texture2D m_taroSprite;
		int m_taroMaxCount;
		vector<BaseTaro*> m_currentTaro;

		float m_taroXPos;
		float m_taroYPos;

		//Stack
		Stack<BaseTaro*> m_taroStack;


	private:
		void BeginPlay();

		void Tick(float dt);
		void Render();

		void EndPlay();

	};
}
