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
	void PauseGame();
	void ResumeGame();
	bool OnPause();
	void LevelFinished(bool isWin);
private:
	GameStateMachine() {};
	~GameStateMachine() 
	{
		ClearStaticEntities();
		ClearUIEntities();
		menuPanel.clear();
		levelPanel.clear();
		creditsPanel.clear();
		pausePanel.clear();
	};
	int currentLevel;//-1 game closed, 0 main menu, 1,2.. levels
	std::list<GameEntity*> staticEntities;
	std::list<GameEntity*> uiEntities;
	void DrawStaticEntities();
	void DrawUIEntities();
	void ClearStaticEntities();
	void ClearUIEntities();
	void DisplayMenu();
	void DisplayLevelSelect();
	void DisplayCredits();
	void DisplayPause(bool disp);
	void DisplayWinPanel(bool disp);
	void DisplayLosePanel(bool disp);

	std::vector<GameEntity*> menuPanel;
	std::vector<GameEntity*> levelPanel;
	std::vector<GameEntity*> creditsPanel;
	std::vector<GameEntity*> pausePanel;
	std::vector<GameEntity*> winPanel;
	std::vector<GameEntity*> losePanel;
	bool onLoad;
	bool onPause;
};

