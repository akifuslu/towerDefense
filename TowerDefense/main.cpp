#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "pch.h"

#include "GameEntity.h"
#include "ResourceLoader.h"
#include "InputHandler.h"
#include "Clickable.h"
#include "Towerspot.h"
#include "TowerButton.h"
#include "TowerButtonHandler.h"
#include "Behaviour.h"
#include "Mob.h"
#include "Player.h"
#include "GameStateMachine.h"

int main()
{
	int screenWidth = SCREENWIDTH;
	int screenHeight = SCREENHEIGHT;
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(screenWidth, screenHeight, "Tower Defense Alpha 0.0");
	SetTargetFPS(60);
	ResourceLoader::GetInstance().Load("Resources");
	GameStateMachine::GetInstance().LoadMainMenu();
	while (!WindowShouldClose())
	{
		if (!GameStateMachine::GetInstance().GameLoop())
			break;
	}
	
	CloseWindow();
	_CrtDumpMemoryLeaks();
	return 0;
}