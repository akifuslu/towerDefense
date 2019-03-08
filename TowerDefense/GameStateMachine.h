#pragma once
#include "GameEntity.h"


class GameStateMachine
{
public:
	static GameStateMachine& GetInstance() 
	{
		static GameStateMachine instance;
		return instance;
	}
	GameStateMachine(GameStateMachine const&) = delete;
	void operator=(GameStateMachine const&) = delete;
	void LoadMainMenu();
	void LoadLevel(int level);
	int CurrentLevel();
	bool GameLoop();
	void ExitGame();
private:
	GameStateMachine() {};
	int currentLevel;//-1 game closed, 0 main menu, 1,2.. levels
	std::list<GameEntity*> staticEntities;
	void DrawStaticEntities();
	void ClearStaticEntities();
	void DisplayMenu();
	void DisplayLevelSelect();
	void DisplayCredits();
	std::vector<GameEntity*> menuPanel;
	std::vector<GameEntity*> levelPanel;
	std::vector<GameEntity*> creditsPanel;
	bool onLoad;
};

