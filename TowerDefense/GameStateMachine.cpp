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
	//create buttons
	Button* startBtn = new Button("Start Game", GETTEXTURE("button"), {330, 227});
	Button* creditsBtn = new Button("Credits", GETTEXTURE("button"), { 330, 327 });
	Button* exitBtn = new Button("Exit", GETTEXTURE("button"), { 330, 427 });
	Button* levelBackBtn = new Button("Back", GETTEXTURE("back-button"), {800, 20});
	Button* levelBtn1 = new Button("Level 1", GETTEXTURE("level-button"), { 90, 70 });
	//add functionality to buttons
	std::function<void()> start = std::bind(&GameStateMachine::DisplayLevelSelect, this);	
	std::function<void()> exit = std::bind(&GameStateMachine::ExitGame, this);
	std::function<void(int)> loadLevel = std::bind(&GameStateMachine::LoadLevel, this, std::placeholders::_1);
	std::function<void()> dispMenu = std::bind(&GameStateMachine::DisplayMenu, this);
	startBtn->AddEvent(start);
	exitBtn->AddEvent(exit);
	levelBackBtn->AddEvent(dispMenu);
	levelBtn1->AddEvent(loadLevel, 1);	
	//register buttons for drawing
	staticEntities.push_back(startBtn);
	staticEntities.push_back(creditsBtn);
	staticEntities.push_back(exitBtn);
	staticEntities.push_back(levelBackBtn);
	staticEntities.push_back(levelBtn1);
	//register buttons to panels
	menuPanel.push_back(startBtn);
	menuPanel.push_back(creditsBtn);
	menuPanel.push_back(exitBtn);
	levelPanel.push_back(levelBackBtn);
	levelPanel.push_back(levelBtn1);
	//display menu panel
	DisplayMenu();
	onLoad = false;
}

void GameStateMachine::LoadLevel(int level)
{
	onLoad = true;
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
	TowerButton* towerButton1 = new TowerButton(Tower::ARCHER, "Presets//archer.txt", "tower", GETTEXTURE("archer-icon"));
	towerButton1->setStatus(false);
	TowerButton* towerButton2 = new TowerButton(Tower::ARCHER, "Presets//magic.txt", "tower-magic", GETTEXTURE("magic-icon"));
	towerButton2->setStatus(false);
	TowerButton* towerButton3 = new TowerButton(Tower::ARCHER, "Presets//archer.txt", "tower", GETTEXTURE("archer-icon"));
	towerButton3->setStatus(false);
	TowerButtonHandler::GetInstance().AddButton(*towerButton1);
	TowerButtonHandler::GetInstance().AddButton(*towerButton2);
	TowerButtonHandler::GetInstance().AddButton(*towerButton3);
	staticEntities.push_back(towerButton1);
	staticEntities.push_back(towerButton2);
	staticEntities.push_back(towerButton3);
	//display user stats
	UIText* playerGold = new UIText("0", 25, WHITE, GETTEXTURE("coin"), { 40, 5 }, { 10, 10 }, 0, 1.5f);
	Player::GetInstance().setGoldText(playerGold);
	staticEntities.push_back(playerGold);
	//load initial player gold
	std::getline(levelPreset, line);
	int gold;
	std::stringstream plGold(line);
	plGold >> tmp >> gold;
	Player::GetInstance().addGold(gold);
	//parsing waves
	Behaviour::GetInstance().getLanesFromTxt("Presets//lanes.txt");
	int waveCount;
	std::vector<int> waves;
	std::getline(levelPreset, line);
	std::stringstream waveC(line);
	waveC >> tmp >> waveCount;
	for (int i = 0; i < waveCount; i++)
	{
		int count = 0;
		std::getline(levelPreset, line);
		std::stringstream wave(line);
		wave >> tmp >> count;
		waves.push_back(count);
		for(int j = 0; j < count; j++)
			Behaviour::GetInstance().RegisterMob(new Mob(GETTEXTURE("mob"), { 0, 0}, 0, 2, 1));
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
	if (currentLevel == -1)//check if game exit
		return false;
	if (onLoad)//dont update anything on load
		return true;
	//Handle click events
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		InputHandler::GetInstance().HandleClick(GetMousePosition());
	}
	//Update mob and tower behaviours
	if(currentLevel != 0)
		Behaviour::GetInstance().Update();
	//Begin drawing
	BeginDrawing();
	ClearBackground(RAYWHITE);
	//Draw static entities
	DrawStaticEntities();
	//Draw dynamic entities
	if (currentLevel > 0 )
		Behaviour::GetInstance().DrawEntities();
	EndDrawing();
	return true;
}

void GameStateMachine::ExitGame()
{
	currentLevel = -1;
}

void GameStateMachine::DrawStaticEntities()
{
	for (auto const& entity : staticEntities)
		entity->Draw();
}

void GameStateMachine::ClearStaticEntities()
{
	for (auto const& entity : staticEntities)
		delete entity;
	staticEntities.clear();
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