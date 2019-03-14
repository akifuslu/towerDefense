#include "pch.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "Behaviour.h"
#include "Button.h"
#include "ResourceLoader.h"
#include "Towerspot.h"
#include "TowerButton.h"
#include "TowerButtonHandler.h"
#include "Player.h"
#include "UIText.h"
#include "Mob.h"

void GameStateMachine::LoadMainMenu()
{
	onLoad = true;
	onPause = false;
	ClearStaticEntities();
	ClearUIEntities();
	menuPanel.clear();
	levelPanel.clear();
	creditsPanel.clear();
	pausePanel.clear();
	TowerButtonHandler::GetInstance().ClearButtons();
	InputHandler::GetInstance().Clear();
	currentLevel = 0;
	//menu background
	GameEntity* menuBackground = new GameEntity(GETTEXTURE("menu-background"));
	uiEntities.push_back(menuBackground);
	//create buttons
	Button* startBtn = new Button("Start Game", { 155, 417}, GETTEXTURE("menu-button"), {70, 390});
	Button* creditsBtn = new Button("Credits", { 184,517}, GETTEXTURE("menu-button"), {70, 490});
	Button* exitBtn = new Button("Quit", { 197,617}, GETTEXTURE("menu-button"), {70, 590});
	Button* levelBackBtn = new Button("", { 0,0 }, GETTEXTURE("back-button"), {913, 645});
	Button* creditsBackBtn = new Button("", { 0,0 }, GETTEXTURE("back-button"), { 913, 645 });
	Button* levelBtn1 = new Button("Level 1", { 170,430},GETTEXTURE("level-button"), { 130, 360});
	Button* levelBtn2 = new Button("Level 2", { 370,430 }, GETTEXTURE("level-button"), { 330, 360 });
	Button* levelBtn3 = new Button("Level 3", { 570,430 }, GETTEXTURE("level-button"), { 530, 360 });
	Button* levelBtn4 = new Button("Level 4", { 770,430 }, GETTEXTURE("level-button"), { 730, 360 });
	//Credits panel
	GameEntity* credits = new GameEntity(GETTEXTURE("credits"), {312,400});
	uiEntities.push_back(credits);
	uiEntities.push_back(creditsBackBtn);
	creditsPanel.push_back(credits);
	creditsPanel.push_back(creditsBackBtn);
	//add functionality to buttons
	std::function<void()> start = std::bind(&GameStateMachine::DisplayLevelSelect, this);	
	std::function<void()> exit = std::bind(&GameStateMachine::ExitGame, this);
	std::function<void(int)> loadLevel = std::bind(&GameStateMachine::LoadLevel, this, std::placeholders::_1);
	std::function<void()> dispMenu = std::bind(&GameStateMachine::DisplayMenu, this);
	std::function<void()> dispCredits = std::bind(&GameStateMachine::DisplayCredits, this);
	startBtn->AddEvent(start);
	creditsBtn->AddEvent(dispCredits);
	exitBtn->AddEvent(exit);
	levelBackBtn->AddEvent(dispMenu);
	creditsBackBtn->AddEvent(dispMenu);
	levelBtn1->AddEvent(loadLevel, 1);	
	levelBtn2->AddEvent(loadLevel, 2);
	levelBtn3->AddEvent(loadLevel, 3);
	levelBtn4->AddEvent(loadLevel, 4);
	//register buttons for drawing
	uiEntities.push_back(startBtn);
	uiEntities.push_back(creditsBtn);
	uiEntities.push_back(exitBtn);
	uiEntities.push_back(levelBackBtn);
	uiEntities.push_back(levelBtn1);
	uiEntities.push_back(levelBtn2);
	uiEntities.push_back(levelBtn3);
	uiEntities.push_back(levelBtn4);
	//register buttons to panels
	menuPanel.push_back(startBtn);
	menuPanel.push_back(creditsBtn);
	menuPanel.push_back(exitBtn);
	levelPanel.push_back(levelBackBtn);
	levelPanel.push_back(levelBtn1);
	levelPanel.push_back(levelBtn2);
	levelPanel.push_back(levelBtn3);
	levelPanel.push_back(levelBtn4);

	//display menu panel
	DisplayMenu();
	onLoad = false;
}

void GameStateMachine::LoadLevel(int level)
{
	onLoad = true;
	onPause = false;
	pausePanel.clear();
	winPanel.clear();
	losePanel.clear();
	InputHandler::GetInstance().Clear();
	Behaviour::GetInstance().ClearAll();
	TowerButtonHandler::GetInstance().ClearButtons();
	currentLevel = level;
	std::string path = "Presets//level";
	path += std::to_string(level) + ".txt";
	std::ifstream levelPreset;
	levelPreset.open(path.c_str());
	if (!levelPreset.is_open())
	{
		LOG("Preset couldn't found! Can not load level.");
		return;
	}
	ClearStaticEntities();
	ClearUIEntities();
	//parse level preset
	std::string line, tmp, strVal;
	std::getline(levelPreset, line);
	std::stringstream backss(line);
	backss >> tmp >> strVal;
	GameEntity* background = new GameEntity(GETTEXTURE(strVal));//load background
	staticEntities.push_back(background);
	int count = 0;
	std::getline(levelPreset, line);
	std::stringstream spotCount(line);
	spotCount >> tmp >> count;
	for (int i = 0; i < count; i++)//load tower spots
	{
		float x, y;
		std::getline(levelPreset, line);
		std::stringstream spots(line);
		spots >> tmp >> x >> y;
		Towerspot* spot = new Towerspot(GETTEXTURE("towerspot"), {x, y});
		staticEntities.push_back(spot);
	}
	//load tower buttons
	TowerButton* towerButton1 = new TowerButton(Tower::ARCHER, "Presets//archer.txt", "archer0", GETTEXTURE("archer-icon"));
	towerButton1->setStatus(false);
	TowerButton* towerButton2 = new TowerButton(Tower::MAGIC, "Presets//magic.txt", "magic0", GETTEXTURE("magic-icon"));
	towerButton2->setStatus(false);
	TowerButton* towerButton3 = new TowerButton(Tower::BOMBARD, "Presets//bombard.txt", "bombard0", GETTEXTURE("bombard-icon"));
	towerButton3->setStatus(false);
	Button* upgradeButton = new Button("", { 0, 0 }, GETTEXTURE("upgrade-button"));
	upgradeButton->setStatus(false);
	Button* destroyButton = new Button("", { 0, 0 }, GETTEXTURE("destroy-button"));
	destroyButton->setStatus(false);
	UIText* upgradeText = new UIText("", 15, WHITE, GETTEXTURE("coin"), {25,5});
	upgradeText->setStatus(false);
	TowerButtonHandler::GetInstance().AddButton(*towerButton1);
	TowerButtonHandler::GetInstance().AddButton(*towerButton2);
	TowerButtonHandler::GetInstance().AddButton(*towerButton3);
	TowerButtonHandler::GetInstance().AddButton(*upgradeButton);
	TowerButtonHandler::GetInstance().AddButton(*destroyButton);
	TowerButtonHandler::GetInstance().upgradeText = upgradeText;
	uiEntities.push_back(towerButton1);
	uiEntities.push_back(towerButton2);
	uiEntities.push_back(towerButton3);
	uiEntities.push_back(upgradeButton);
	uiEntities.push_back(destroyButton);
	uiEntities.push_back(upgradeText);
	std::function<void()> upgrade = std::bind(&TowerButtonHandler::UpgradeTower, &TowerButtonHandler::GetInstance());
	upgradeButton->AddEvent(upgrade);
	std::function<void()> destroy = std::bind(&TowerButtonHandler::DestroyTower, &TowerButtonHandler::GetInstance());
	destroyButton->AddEvent(destroy);
	//load pause button
	Button* pauseButton = new Button("", {0,0}, GETTEXTURE("pause-button"), { 945,20 }, 0, 0.7f);
	std::function<void()> pause = std::bind(&GameStateMachine::PauseGame, this);
	pauseButton->AddEvent(pause);
	uiEntities.push_back(pauseButton);
	//load pause panel
	GameEntity* pausePanelBack = new GameEntity(GETTEXTURE("pause-panel"), {302,264}, 0, 1, false);
	Button* resumeButton = new Button("Continue", {456, 395}, GETTEXTURE("panel-button"), { 382, 370 }, 0, 1);
	Button* menuButton = new Button("Main Menu", { 441, 496}, GETTEXTURE("panel-button"), { 382, 470 }, 0, 1);
	Button* quitButton = new Button("Quit", { 485, 598 }, GETTEXTURE("panel-button"), { 382, 570 }, 0, 1);
	UIText* pausedText = new UIText("Game Paused", 50, WHITE, NULL, { 0,0 }, { 366,281 }, 0, 1, false);
	resumeButton->setStatus(false);
	menuButton->setStatus(false);
	quitButton->setStatus(false);
	pausedText->setStatus(false);
	std::function<void()> resume = std::bind(&GameStateMachine::ResumeGame, this);
	std::function<void()> mainmenu = std::bind(&GameStateMachine::LoadMainMenu, this);
	std::function<void()> exit = std::bind(&GameStateMachine::ExitGame, this);
	resumeButton->AddEvent(resume);
	menuButton->AddEvent(mainmenu);
	quitButton->AddEvent(exit);
	uiEntities.push_back(pausePanelBack);
	uiEntities.push_back(resumeButton);
	uiEntities.push_back(menuButton);
	uiEntities.push_back(quitButton);
	uiEntities.push_back(pausedText);
	pausePanel.push_back(pausePanelBack);
	pausePanel.push_back(resumeButton);
	pausePanel.push_back(menuButton);
	pausePanel.push_back(quitButton);
	pausePanel.push_back(pausedText);
	//load level win panel
	Button* nextLevelButton = new Button("Next Level", { 456, 395 }, GETTEXTURE("panel-button"), { 382, 370 }, 0, 1);
	UIText* winText = new UIText("Level Cleared", 50, WHITE, NULL, { 0,0 }, { 366,281 }, 0, 1, false);
	nextLevelButton->setStatus(false);
	std::function<void(int)> nextLevel = std::bind(&GameStateMachine::LoadLevel, this, std::placeholders::_1);
	nextLevelButton->AddEvent(nextLevel, currentLevel + 1);
	uiEntities.push_back(nextLevelButton);
	uiEntities.push_back(winText);
	winPanel.push_back(pausePanelBack);
	winPanel.push_back(nextLevelButton);
	winPanel.push_back(menuButton);
	winPanel.push_back(quitButton);
	winPanel.push_back(winText);
	//load level lose panel
	Button* restartButton = new Button("Restart", { 456, 395 }, GETTEXTURE("panel-button"), { 382, 370 }, 0, 1);
	UIText* loseText = new UIText("You Lose", 50, WHITE, NULL, { 0,0 }, { 366,281 }, 0, 1, false);
	restartButton->setStatus(false);
	std::function<void(int)> restartLevel = std::bind(&GameStateMachine::LoadLevel, this, std::placeholders::_1);
	restartButton->AddEvent(restartLevel, currentLevel);
	uiEntities.push_back(restartButton);
	uiEntities.push_back(loseText);
	losePanel.push_back(pausePanelBack);
	losePanel.push_back(restartButton);
	losePanel.push_back(menuButton);
	losePanel.push_back(quitButton);
	losePanel.push_back(loseText);

	//display user stats
	UIText* playerGold = new UIText("0", 25, WHITE, GETTEXTURE("coin"), { 40, 5 }, { 10, 10 }, 0, 1.5f);
	Player::GetInstance().setGoldText(playerGold);
	uiEntities.push_back(playerGold);	
	UIText* playerHealth = new UIText("0", 25, WHITE, GETTEXTURE("health"), { 45, 5 }, { 10, 60 }, 0, 1.5f);
	Player::GetInstance().setHealthText(playerHealth);
	uiEntities.push_back(playerHealth);
	//load initial player gold
	std::getline(levelPreset, line);
	int gold;
	std::stringstream plGold(line);
	plGold >> tmp >> gold;
	Player::GetInstance().addGold(gold - Player::GetInstance().getGold());
	//load initial player health
	std::getline(levelPreset, line);
	int health;
	std::stringstream plHealth(line);
	plHealth >> tmp >> health;
	Player::GetInstance().setHealth(health);
	//parsing waves
	std::string lanePath = "Presets//lanes";
	lanePath += std::to_string(level) + ".txt";
	Behaviour::GetInstance().getLanesFromTxt(lanePath);
	int waveCount;
	std::vector<int> waves;
	std::getline(levelPreset, line);
	std::stringstream waveC(line);
	waveC >> tmp >> waveCount;
	for (int i = 0; i < waveCount; i++)
	{
		int m1Count, m2Count, m3Count;
		std::getline(levelPreset, line);
		std::stringstream wave(line);
		wave >> tmp >> m1Count >> tmp >> m2Count >> tmp >> m3Count;
		waves.push_back(m1Count+m2Count+m3Count);
		for (int j = 0; j < m1Count; j++) {
			Behaviour::GetInstance().RegisterMob(new Mob(GETTEXTURE("bandit"), { 0, 0 }, 0, 0.12, .8, 50, 150, "banditdead"));
		}
		for (int j = 0; j < m2Count; j++) {
			Behaviour::GetInstance().RegisterMob(new Mob(GETTEXTURE("rogue"), { 0, 0 }, 0, 0.12, 1.500, 100, 250, "roguedead"));
		}
		for (int j = 0; j < m3Count; j++) {
			Behaviour::GetInstance().RegisterMob(new Mob(GETTEXTURE("knight"), { 0, 0 }, 0, 0.12, 1, 200, 400, "knightdead"));
		}
	}
	Behaviour::GetInstance().SetWaves(waves);
	//all loaded close file and run!
	levelPreset.close();
	onLoad = false;
}

int GameStateMachine::CurrentLevel()
{
	return currentLevel;
}

bool GameStateMachine::GameLoop()
{
	if (onLoad)//dont update anything on load
		return true;
	//Handle click events
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		InputHandler::GetInstance().HandleClick(GetMousePosition());
	}
	if (currentLevel == -1)//check if game exit
		return false;
	//Update mob and tower behaviours
	if(currentLevel > 0 && onPause == false)
		Behaviour::GetInstance().Update();
	//Begin drawing
	BeginDrawing();
	ClearBackground(RAYWHITE);
	//Draw static entities
	DrawStaticEntities();
	//Draw dynamic entities
	if (currentLevel > 0 )
		Behaviour::GetInstance().DrawEntities();
	//Draw ui entities
	DrawUIEntities();
	EndDrawing();
	return true;
}

void GameStateMachine::ExitGame()
{
	currentLevel = -1;
}

void GameStateMachine::PauseGame()
{
	if (onPause)//already paused
		return;
	onPause = true;
	DisplayPause(true);
}

void GameStateMachine::ResumeGame()
{
	onPause = false;
	DisplayPause(false);
}

bool GameStateMachine::OnPause()
{
	return onPause;
}

void GameStateMachine::LevelFinished(bool isWin)
{
	onPause = true;
	DisplayPause(false);
	if (isWin)
		DisplayWinPanel(true);
	else
		DisplayLosePanel(true);
}

void GameStateMachine::DrawStaticEntities()
{
	for (auto const& entity : staticEntities)
		entity->Draw();
}

void GameStateMachine::DrawUIEntities()
{
	for (auto const& entity : uiEntities)
		entity->Draw();
}

void GameStateMachine::ClearStaticEntities()
{
	for (auto & entity : staticEntities)
		delete entity;
	staticEntities.clear();
}

void GameStateMachine::ClearUIEntities()
{
	for (auto & entity : uiEntities)
		delete entity;
	uiEntities.clear();
}

void GameStateMachine::DisplayMenu()
{
	for (auto const& item : menuPanel)
		item->setStatus(true);
	for (auto const& item : creditsPanel)
		item->setStatus(false);
	for (auto const& item : levelPanel)
		item->setStatus(false);
}

void GameStateMachine::DisplayLevelSelect()
{
	for (auto const& item : menuPanel)
		item->setStatus(false);
	for (auto const& item : creditsPanel)
		item->setStatus(false);
	for (auto const& item : levelPanel)
		item->setStatus(true);
}

void GameStateMachine::DisplayCredits()
{
	for (auto const& item : menuPanel)
		item->setStatus(false);
	for (auto const& item : creditsPanel)
		item->setStatus(true);
	for (auto const& item : levelPanel)
		item->setStatus(false);
}

void GameStateMachine::DisplayPause(bool disp)
{
	for (auto & item : pausePanel)
	{
		item->setStatus(disp);
	}
}

void GameStateMachine::DisplayWinPanel(bool disp)
{
	for (auto & item : winPanel)
	{
		item->setStatus(disp);
	}
}

void GameStateMachine::DisplayLosePanel(bool disp)
{
	for (auto & item : losePanel)
	{
		item->setStatus(disp);
	}
}