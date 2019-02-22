#include "pch.h"
#include "ResourceLoader.h"

int main()
{
	int screenWidth = 1024;
	int screenHeight = 512;
	
	InitWindow(screenWidth, screenHeight, "Tower Defense Pre-Alpha");
	Texture2D sky = LoadTexture("Resources\\sky.png");
	Texture2D cloud = LoadTexture("Resources\\cloud.png");
	Texture2D sword = LoadTexture("Resources\\sword.png");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		//Update Method

		//Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTextureEx(sky, {0,0}, 0, 2, WHITE);
		DrawTextureEx(cloud, { 100,100 }, 0, 0.7, WHITE);
		DrawTextureEx(cloud, { 600,30 }, 0, 0.7, WHITE);
		DrawTextureEx(sword, { 450,275 }, 0, 1.5, WHITE);
		DrawText("Tower Defense!!", 400, 256, 30, RED);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}