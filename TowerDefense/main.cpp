#include "pch.h"
#include "GameEntity.h"
#include "ResourceLoader.h"

#define GETTEXTURE(x) ResourceLoader::GetInstance()->GetTexture(x)
#define LOG(x) std::cout << x << std::endl;

int main()
{
	int screenWidth = 1024;
	int screenHeight = 512;

	InitWindow(screenWidth, screenHeight, "Tower Defense Pre-Alpha");
/*	Texture2D skyImage = LoadTexture("Resources\\sky.png");
	Texture2D cloudImage = LoadTexture("Resources\\cloud.png");
	Texture2D swordImage = LoadTexture("Resources\\sword.png");*/
	ResourceLoader::GetInstance()->Load("Resources");

	GameEntity background(GETTEXTURE("sky"), { 0, 0 }, 0, 2),
		cloud1(ResourceLoader::GetInstance()->GetTexture("cloud"), {100, 100}, 0, (float)0.7),
		cloud2(ResourceLoader::GetInstance()->GetTexture("cloud"), { 600, 30 }, 0, (float)0.7),
		sword(ResourceLoader::GetInstance()->GetTexture("sword"), {450, 275}, 0, (float)1.5);

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