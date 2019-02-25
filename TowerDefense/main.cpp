#include "pch.h"
#include "GameEntity.h"

int main()
{
	int screenWidth = 1024;
	int screenHeight = 512;

	InitWindow(screenWidth, screenHeight, "Tower Defense Pre-Alpha");
	Texture2D skyImage = LoadTexture("Resources\\sky.png");
	Texture2D cloudImage = LoadTexture("Resources\\cloud.png");
	Texture2D swordImage = LoadTexture("Resources\\sword.png");

	GameEntity background(skyImage, { 0, 0 }, 0, 2),
		cloud1(cloudImage, {100, 100}, 0, (float)0.7),
		cloud2(cloudImage, { 600, 30 }, 0, (float)0.7),
		sword(swordImage, {450, 275}, 0, (float)1.5);

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		//Update Method

		//Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);

		background.Draw();
		cloud1.Draw();
		cloud2.Draw();
		sword.Draw();
		DrawText("Tower Defense!!", 400, 256, 30, RED);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}