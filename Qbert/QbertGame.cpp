#include <MiniginPCH.h>
#include "QbertGame.h"

#include <fstream>

#include "FPSComponent.h"
#include "GameObject.h"
#include "HealthDisplayComponent.h"
#include "InputManager.h"
#include "LevelTileComponent.h"
#include "LoggingSoundSystem.h"
#include "MovementComponent.h"
#include "PointsDisplayComponent.h"
#include "QbertCommands.h"
#include "QbertComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SDL2SoundSystem.h"
#include "EnemyFactory.h"
#include "GameTime.h"
#include "UggOrWrongWayComponent.h"
#include "../3rdParty/imgui-1.81/imgui.h"

int qbert::QbertGame::m_TilesActiveToWin = 28;

qbert::QbertGame::QbertGame(dae::Scene& scene, GameMode gameMode)
	:m_GameMode(gameMode),
	m_Qbert(nullptr),
	m_Qbert2(nullptr),
	m_Scene(scene),
	m_CurrentLevel(1),
	m_MaxLevel(3),
	m_TilesActiveToWinForLevels({ 28,56,28 }),
	m_CollisionTime(),
	m_CollisionIntervalTime(1),
	m_QbertHasTakenDisk(false),
	m_HasTakenDiskResetTime(),
	m_CoilySpawnTime(),
	m_Coily(nullptr),
	m_EnemySpawnTime()
{
	LevelTileComponent::m_ActiveTiles = 0;
	m_TilesActiveToWin = 28;
}
void qbert::QbertGame::Update()
{
	CheckLevelCompleted();
	CollisionCheck();

	// destroy the gameobjects
	for (auto object : m_GameObjectsToDestroy)
	{
		m_Scene.Destroy(object);
	}
	m_GameObjectsToDestroy.clear();

	// reset the qbertHasTakenDisk
	if (m_QbertHasTakenDisk)
		m_HasTakenDiskResetTime += dae::GameTime::GetInstance().GetDeltaTime();
	if (m_HasTakenDiskResetTime >= m_MaxHasTakenDiskResetTime)
	{
		m_HasTakenDiskResetTime = 0;
		m_QbertHasTakenDisk = false;
	}
	// Spawn coily when when there is none after a certain time
	if (m_Coily == nullptr)
	{
		m_CoilySpawnTime += dae::GameTime::GetInstance().GetDeltaTime();
		if (m_CoilySpawnTime >= m_MaxCoilySpawnTime)
		{
			m_CoilySpawnTime = 0;
			m_Coily = EnemyFactory::CreateEnemy(EnemyComponent::EnemyType::COILY, this, m_GameMode == GameMode::VERSUS);
			m_Enemies.push_back(m_Coily);
			m_Scene.Add(m_Coily);
		}
	}
	// Spawn enemies after a certain time
	m_EnemySpawnTime += dae::GameTime::GetInstance().GetDeltaTime();
	if (m_EnemySpawnTime >= m_MaxEnemySpawnTime)
	{
		m_EnemySpawnTime = 0;
		auto randomType = static_cast<EnemyComponent::EnemyType>((rand() % 4) + 1);
		auto enemy = EnemyFactory::CreateEnemy(randomType, this);
		m_Enemies.push_back(enemy);
		m_Scene.Add(enemy);
	}
}
void qbert::QbertGame::Render()
{
	// How to play
	ImGui::Begin("How to play");
	ImGui::Text("move with WASD or controller DPAD");
	if (m_GameMode == GameMode::CO_OP)
	{
		ImGui::Text("second player moves with IJKL or controller DPAD");
	}
	ImGui::Text("mute the audio with m or start button");
	ImGui::End();

	// To Switch game modes
	ImGui::Begin("Game Modes");
	if (ImGui::Button("Play Single Player"))
	{
		RestartGame(GameMode::SINGLE_PLAYER);
	}
	if (ImGui::Button("Play Co-op"))
	{
		RestartGame(GameMode::CO_OP);
	}
	if (ImGui::Button("Play Versus"))
	{
		RestartGame(GameMode::VERSUS);
	}
	ImGui::End();
}

void qbert::QbertGame::LoadGame()
{
	//Code constructing the scene world starts here
	using namespace dae;

	m_Scene.SetGame(this);
	srand(static_cast<unsigned>(time(nullptr)));

	auto go = new GameObject();
	RenderComponent* renderComponent = new RenderComponent(go);
	go->AddComponent(renderComponent);
	go->GetComponentByType<RenderComponent>()->SetTexture("background.jpg");
	m_Scene.Add(go);

	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->GetComponentByType<RenderComponent>()->SetTexture("logo.png");
	go->GetComponentByType<RenderComponent>()->SetPosition(216, 180);
	m_Scene.Add(go);

	// FPS
	go = new GameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	go->AddComponent(new FPSComponent(go, "fps", font));
	go->SetPosition(0, 0);
	m_Scene.Add(go);

	// Create Player 1
	m_Qbert = CreatePlayer(GetPlayerSpawnPos(false), font);
	auto movementComponent = m_Qbert->GetComponentByType<MovementComponent>();
	auto& input = InputManager::GetInstance();
	//create controller binds player 1
	input.BindCommand({ ControllerButton::ButtonUP,0 }, new MoveCommand(movementComponent, MovementComponent::MoveDirection::UP));
	input.BindCommand({ ControllerButton::ButtonDOWN, 0 }, new MoveCommand(movementComponent, MovementComponent::MoveDirection::DOWN));
	input.BindCommand({ ControllerButton::ButtonLEFT,0 }, new MoveCommand(movementComponent, MovementComponent::MoveDirection::LEFT));
	input.BindCommand({ ControllerButton::ButtonRIGHT,0 }, new MoveCommand(movementComponent, MovementComponent::MoveDirection::RIGHT));
	//create keyboard binds player 1
	input.BindCommand('w', new MoveCommand(movementComponent, MovementComponent::MoveDirection::UP));
	input.BindCommand('s', new MoveCommand(movementComponent, MovementComponent::MoveDirection::DOWN));
	input.BindCommand('a', new MoveCommand(movementComponent, MovementComponent::MoveDirection::LEFT));
	input.BindCommand('d', new MoveCommand(movementComponent, MovementComponent::MoveDirection::RIGHT));

	if (m_GameMode == GameMode::CO_OP)
	{
		// Create Player 2
		m_Qbert2 = CreatePlayer(GetPlayerSpawnPos(true), font, true);
		movementComponent = m_Qbert2->GetComponentByType<MovementComponent>();
		//create controller binds player 2
		input.BindCommand({ ControllerButton::ButtonUP,1 }, new MoveCommand(movementComponent, MovementComponent::MoveDirection::UP));
		input.BindCommand({ ControllerButton::ButtonDOWN,1 }, new MoveCommand(movementComponent, MovementComponent::MoveDirection::DOWN));
		input.BindCommand({ ControllerButton::ButtonLEFT,1 }, new MoveCommand(movementComponent, MovementComponent::MoveDirection::LEFT));
		input.BindCommand({ ControllerButton::ButtonRIGHT,1 }, new MoveCommand(movementComponent, MovementComponent::MoveDirection::RIGHT));
		//create keyboard binds player 2
		input.BindCommand('i', new MoveCommand(movementComponent, MovementComponent::MoveDirection::UP));
		input.BindCommand('k', new MoveCommand(movementComponent, MovementComponent::MoveDirection::DOWN));
		input.BindCommand('j', new MoveCommand(movementComponent, MovementComponent::MoveDirection::LEFT));
		input.BindCommand('l', new MoveCommand(movementComponent, MovementComponent::MoveDirection::RIGHT));
	}
	// Sound Binds
	input.BindCommand('m', new ToggleMuteCommand());
	input.BindCommand({ ControllerButton::ButtonSTART, 0 }, new ToggleMuteCommand());
	input.BindCommand({ ControllerButton::ButtonSTART, 1 }, new ToggleMuteCommand());

	// Create Level
	CreateLevel("../Data/Level1.txt");

	// put qbert on the foreground
	m_Scene.Remove(m_Qbert);
	m_Scene.Add(m_Qbert);
	if (m_GameMode == GameMode::CO_OP)
	{
		m_Scene.Remove(m_Qbert2);
		m_Scene.Add(m_Qbert2);
	}

	// Sounds
	ServiceLocator::RegisterSoundSystem(new LoggingSoundSystem(new SDL2SoundSystem()));
}

void qbert::QbertGame::CreateLevel(const std::string& path)
{
	glm::vec2 start{ 120,110 };
	const float size{ 32.f };
	const float height{ 2 * size };
	const float width{ sqrt(3.f) * size };

	std::ifstream levelInput;
	levelInput.open(path);
	if (!levelInput.is_open())
	{
		std::cout << "Failed to open " << path << std::endl;
		return;
	}
	std::string line;
	int row{};
	int col{};
	QbertComponent* qbertComponent = m_Qbert->GetComponentByType<QbertComponent>();
	while (std::getline(levelInput, line))
	{
		for (auto character : line)
		{
			auto go = new dae::GameObject();
			LevelTileComponent* tileComponent;
			if (row % 2 != 0)
			{
				// shift to right
				tileComponent = new LevelTileComponent(go, static_cast<LevelTileComponent::TileType>(character),
					start.x + width * col + width / 2.f, start.y + height * row * 3.f / 4.f, qbertComponent);
			}
			else
			{
				tileComponent = new LevelTileComponent(go, static_cast<LevelTileComponent::TileType>(character),
					start.x + width * col, start.y + height * row * 3.f / 4.f, qbertComponent);
			}
			go->AddComponent(tileComponent);
			m_Level[row][col] = go;
			m_Scene.Add(go);

			col++;
		}
		col = 0;
		row++;
	}
}

dae::GameObject* qbert::QbertGame::CreatePlayer(const glm::ivec2& spawnPos, std::shared_ptr<dae::Font> font, bool player2)
{
	using namespace dae;
	auto qbert = new GameObject();
	RenderComponent* renderComponent = new RenderComponent(qbert);
	qbert->AddComponent(renderComponent);
	renderComponent->SetTexture("Qbert.png");
	renderComponent->SetWidth(30);
	renderComponent->SetHeight(32);
	renderComponent->SetPosition(20, -15);

	MovementComponent* movementComponent = new MovementComponent(qbert, this, spawnPos);
	qbert->AddComponent(movementComponent);

	auto qbertComponent = new QbertComponent(qbert, this);
	qbert->AddComponent(qbertComponent);
	m_Scene.Add(qbert);

	float displayComponentOffset = 25;
	if (!player2)
		displayComponentOffset = 0;

	// points display player
	auto points = new GameObject();
	PointsDisplayComponent* pointsDisplayComponent;
	if (player2)
		pointsDisplayComponent = new PointsDisplayComponent(points, "", font, "Points2: ");
	else
		pointsDisplayComponent = new PointsDisplayComponent(points, "", font);
	qbert->AddComponent(pointsDisplayComponent);
	pointsDisplayComponent->SetQbert(qbertComponent);
	pointsDisplayComponent->SetPosition(0, 30 + displayComponentOffset);
	m_Scene.Add(points);

	// health display player
	auto health = new GameObject();
	HealthDisplayComponent* healthDisplayComponent;
	if (player2)
		healthDisplayComponent = new HealthDisplayComponent(health, "", font, "Lives2: ");
	else
		healthDisplayComponent = new HealthDisplayComponent(health, "", font);
	qbert->AddComponent(healthDisplayComponent);
	healthDisplayComponent->SetQbert(qbertComponent);
	healthDisplayComponent->SetPosition(0, 90 + displayComponentOffset);
	m_Scene.Add(health);
	return qbert;
}

dae::GameObject* qbert::QbertGame::GetTile(int row, int col)
{
	if (row >= 0 && col >= 0 && row < m_LevelRows && col < m_LevelCols)
	{
		return m_Level[row][col];
	}
	return nullptr;
}
dae::GameObject* qbert::QbertGame::GetTopOfLevel()
{
	return m_Level[0][3];
}
void qbert::QbertGame::RemoveDisk(int row, int col)
{
	m_Scene.Remove(m_Level[row][col]);
	delete m_Level[row][col];
	m_Level[row][col] = nullptr;
}
void qbert::QbertGame::LoadNextLevel()
{
	m_CurrentLevel++;
	LevelTileComponent::m_ActiveTiles = 0;
	if (m_CurrentLevel == 2)
	{
		m_TilesActiveToWin = m_TilesActiveToWinForLevels.at(m_CurrentLevel - 1);
	}
	// add points for every remaining disk in the level
	for (int r{}; r < m_LevelRows; ++r)
	{
		for (int c{}; c < m_LevelCols; ++c)
		{
			if (m_Level[r][c] != nullptr && m_Level[r][c]->GetComponentByType<LevelTileComponent>()->GetTileType() == LevelTileComponent::TileType::DISK)
			{
				m_Qbert->GetComponentByType<QbertComponent>()->RemainingDisk();
			}
		}
	}
	// remove all the enemies
	for (auto enemy : m_Enemies)
	{
		Destroy(enemy);
	}
	m_Enemies.clear();
	// reset spawn timers
	m_CoilySpawnTime = 0;
	m_EnemySpawnTime = 0;
	// delete old level
	for (int r{}; r < m_LevelRows; ++r)
	{
		for (int c{}; c < m_LevelCols; ++c)
		{
			m_Scene.Remove(m_Level[r][c]);
			delete m_Level[r][c];
			m_Level[r][c] = nullptr;
		}
	}
	// load new level
	CreateLevel("../Data/Level" + std::to_string(m_CurrentLevel) + ".txt");

	m_Qbert->GetComponentByType<MovementComponent>()->SetPosRowCol(GetPlayerSpawnPos(false));
	// put qbert on the foreground
	m_Scene.Remove(m_Qbert);
	m_Scene.Add(m_Qbert);
	if (m_GameMode == GameMode::CO_OP)
	{
		m_Qbert2->GetComponentByType<MovementComponent>()->SetPosRowCol(GetPlayerSpawnPos(true));
		m_Scene.Remove(m_Qbert2);
		m_Scene.Add(m_Qbert2);
	}
	dae::ServiceLocator::GetSoundSystem().Play("../Data/tune-2.wav", 10);
}

void qbert::QbertGame::CheckLevelCompleted()
{
	if (LevelTileComponent::m_ActiveTiles >= m_TilesActiveToWin)
	{
		if (m_CurrentLevel < m_MaxLevel)
		{
			LoadNextLevel();
		}
		else
		{
			//YOU WON!
			std::cout << "YOU WON!\n";
		}
	}
}

void qbert::QbertGame::CollisionCheck()
{
	dae::GameObject* qbertStandOnTile = m_Qbert->GetComponentByType<MovementComponent>()->GetTileStandingOn();
	auto It = std::find_if(m_Enemies.begin(), m_Enemies.end(), [&qbertStandOnTile](dae::GameObject* enemy)
		{
			return enemy->GetComponentByType<MovementComponent>()->GetTileStandingOn() == qbertStandOnTile;
		});
	if (It != m_Enemies.end())
	{
		// there is collision
		(*It)->GetComponentByType<EnemyComponent>()->CollisionWithPlayer(m_Qbert);
	}
	// collision with second player
	if (m_GameMode == GameMode::CO_OP)
	{
		dae::GameObject* qbert2StandOnTile = m_Qbert2->GetComponentByType<MovementComponent>()->GetTileStandingOn();
		auto It2 = std::find_if(m_Enemies.begin(), m_Enemies.end(), [&qbert2StandOnTile](dae::GameObject* enemy)
			{
				return enemy->GetComponentByType<MovementComponent>()->GetTileStandingOn() == qbert2StandOnTile;
			});
		if (It2 != m_Enemies.end())
		{
			// there is collision
			(*It2)->GetComponentByType<EnemyComponent>()->CollisionWithPlayer(m_Qbert2);
		}
	}
}

void qbert::QbertGame::Destroy(dae::GameObject* object)
{
	m_GameObjectsToDestroy.push_back(object);

	auto It = std::find_if(m_Enemies.begin(), m_Enemies.end(), [&object](dae::GameObject* enemy)
		{
			return enemy == object;
		});
	if (It != m_Enemies.end())
	{
		if ((*It)->GetComponentByType<EnemyComponent>()->GetType() == EnemyComponent::EnemyType::COILY)
		{
			m_Coily = nullptr;
			if (m_GameMode == GameMode::VERSUS)
			{
				auto& input = dae::InputManager::GetInstance();
				input.UnBindCommand('i');
				input.UnBindCommand('k');
				input.UnBindCommand('j');
				input.UnBindCommand('l');
			}
		}
		m_Enemies.erase(It);
	}
}
glm::ivec2 qbert::QbertGame::GetQbertPosForCoily() const
{
	if (m_QbertHasTakenDisk)
	{
		// give the last pos so that coily jumps off the pyramid
		return m_QbertLastPos;
	}
	else
	{
		// return the actual pos of qbert
		return m_Qbert->GetComponentByType<MovementComponent>()->GetPosRowCol();
	}
}

glm::ivec2 qbert::QbertGame::GetPlayerSpawnPos(bool player2) const
{
	switch (m_GameMode)
	{
	case GameMode::SINGLE_PLAYER:
		return glm::ivec2{ 0,3 };
	case GameMode::CO_OP:
		if (player2)
			return glm::ivec2{ 6,6 };
		return glm::ivec2{ 6,0 };
	case GameMode::VERSUS:
		return glm::ivec2{ 0,3 };
	default:
		return glm::ivec2{ 0,3 };
	}
}

void qbert::QbertGame::RestartGame(GameMode gameMode) const
{
	// create local copy of scene because this will be deleted
	auto& scene = m_Scene;
	scene.ResetGame();
	auto qbertGame = new QbertGame(scene, gameMode);
	scene.SetGame(qbertGame);
	// unbind commands because they will give errors when pressed
	auto& input = dae::InputManager::GetInstance();
	input.UnBindCommand('i');
	input.UnBindCommand('k');
	input.UnBindCommand('j');
	input.UnBindCommand('l');

	qbertGame->LoadGame();
}