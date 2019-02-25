#include "pch.h"
#include "GameEntity.h"
#include "ResourceLoader.h"
#include "Towerspot.h"

int main()
{
	int screenWidth = 1024;
	int screenHeight = 512;

	InitWindow(screenWidth, screenHeight, "Tower Defense Pre-Alpha");
	ResourceLoader::GetInstance().Load("Resources");
	GameEntity background(GETTEXTURE("tutorial-background"), {0,0}, 0, 1);
	Towerspot spotOne(GETTEXTURE("towerspot"), { 607,226 }, 0, 1);
	SetTargetFPS(60);
	
	while (!WindowShouldClose())
	{
		//Update Method
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))//click test
		{
			InputHandler::GetInstance().HandleClick(GetMousePosition());
		}
		//Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);
		background.Draw();
		spotOne.Draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}