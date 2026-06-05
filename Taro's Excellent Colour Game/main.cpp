#include "Application.h"
#include <format>
#include <iostream>

int main()
{
	MathLibrary::Application* app = new MathLibrary::Application(720, 480, "TARO'S EXCELLENT COLOUR GAME", RAYWHITE);

	app->Run();

	delete app;

	return 0;
}