#include "pch.h"
#include "GameEntity.h"
#include "ResourceLoader.h"
#include "InputHandler.h"
#include "Clickable.h"
#include "Towerspot.h"
#include "TowerButton.h"
#include "TowerButtonHandler.h"
#include "Behaviour.h"

int main()
{
	int screenWidth = 1024;
	int screenHeight = 512;

	InitWindow(screenWidth, screenHeight, "Tower Defense Pre-Alpha");
	ResourceLoader::GetInstance().Load("Resources");
	GameEntity background(GETTEXTURE("tutorial-background"), {0,0}, 0, 1);
	Towerspot spotOne(GETTEXTURE("towerspot"), { 607,226 }, 0, 1);
	Towerspot spotTwo(GETTEXTURE("towerspot"), { 350,400 }, 0, 1);
	Towerspot spotThree(GETTEXTURE("towerspot"), { 300,100 }, 0, 1);

	TowerButton button1(Tower::ARCHER, "Presets//archer.txt","tower", GETTEXTURE("archer-icon"), { 0,0 }, 0, 1);
	button1.setStatus(false);
	TowerButton button2(Tower::MAGIC, "Presets//magic.txt", "tower", GETTEXTURE("magic-icon"), { 0,0 }, 0, 1);
	button2.setStatus(false);
	TowerButton button3(Tower::ARCHER, "Presets//archer.txt", "tower", GETTEXTURE("tower-button"), { 0,0 }, 0, 1);
	button3.setStatus(false);
	TowerButtonHandler::GetInstance().AddButton(button1);
	TowerButtonHandler::GetInstance().AddButton(button2);
	TowerButtonHandler::GetInstance().AddButton(button3);
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
		//Draw static entities
		background.Draw();
		spotOne.Draw();
		spotTwo.Draw();
		spotThree.Draw();
		button1.Draw();
		button2.Draw();
		button3.Draw();
		//Draw dynamic entities
		Behaviour::GetInstance().DrawEntities();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}