#include "pch.h"
#include "ResourceLoader.h"

int main()
{
	int screenWidth = 1024;
	int screenHeight = 512;

	InitWindow(screenWidth, screenHeight, "Tower Defense Pre-Alpha");
	ResourceLoader resourceLoader;
	resourceLoader.Load("Resources");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		//Update Method

		//Draw
		BeginDrawing();
		DrawTexture(resourceLoader.GetTexture("sky"), 0, 0, WHITE);
		ClearBackground(RAYWHITE);
		DrawText("Tower Defense!!", 400, 256, 30, RED);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}