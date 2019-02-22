#include "pch.h"


int main()
{
	int screenWidth = 1024;
	int screenHeight = 768;

	InitWindow(screenWidth, screenHeight, "Tower Defense Pre-Alpha");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		//Update Method

		//Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Tower Defense!!", 512, 384, 30, RED);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}