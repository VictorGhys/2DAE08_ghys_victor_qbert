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
#include "SceneManager.h"
#include "SDL2SoundSystem.h"
//#include "ServiceLocator.h"
#include "EnemyFactory.h"
#include "GameTime.h"
#include "UggOrWrongWayComponent.h"

int qbert::QbertGame::m_TilesActiveToWin = 28;

qbert::QbertGame::QbertGame()
	:m_Qbert(nullptr),
	m_Scene(dae::SceneManager::GetInstance().CreateScene("Qbert")),
	m_CurrentLevel(1),
	m_MaxLevel(3),
	m_CollisionTime(),
	m_CollisionIntervalTime(1)
{
}
void qbert::QbertGame::Update()
{
	CheckLevelCompleted();
	CollisionCheck();
	for (auto object : m_GameObjectsToDestroy)
	{
		m_Scene.Destroy(object);
	}
	m_GameObjectsToDestroy.clear();
}

/**
 * Code constructing the scene world starts here
 */
void qbert::QbertGame::LoadGame()
{
	using namespace dae;
	// best way to do this is to read it in from a file
	//Scene& scene = SceneManager::GetInstance().CreateScene("Qbert");

	/*auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);*/
	m_Scene.SetGame(this);
	srand(static_cast<unsigned>(time(nullptr)));

	m_TilesActiveToWinForLevels.push_back(28);
	m_TilesActiveToWinForLevels.push_back(56);
	m_TilesActiveToWinForLevels.push_back(28);

	auto go = new GameObject();
	RenderComponent* renderComponent = new RenderComponent(go);
	go->AddComponent(renderComponent);
	go->GetComponentByType<RenderComponent>()->SetTexture("background.jpg");
	m_Scene.Add(go);

	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->GetComponentByType<RenderComponent>()->SetTexture("logo.png");
	//go->SetPosition(216, 180);
	go->GetComponentByType<RenderComponent>()->SetPosition(216, 180);
	m_Scene.Add(go);

	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//go = new GameObject();
	//auto textComponent = new TextComponent(go, "Programming 4 Assignment", font);
	//go->AddComponent(textComponent);
	//textComponent->SetPosition(80, 20);
	////go->SetPosition(80, 20);
	//scene.Add(go);

	// FPS
	go = new GameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	go->AddComponent(new FPSComponent(go, "fps", font));
	go->SetPosition(0, 0);
	m_Scene.Add(go);

	// Create Player
	m_Qbert = CreatePlayer();

	// Create Level
	CreateLevel("../Data/Level1.txt");

	// put qbert on the foreground
	m_Scene.Remove(m_Qbert);
	m_Scene.Add(m_Qbert);

	auto qbert2 = new GameObject();
	qbert2->AddComponent(new QbertComponent(qbert2));
	m_Scene.Add(qbert2);

	go = new GameObject();
	auto pointsDisplayComponent = new PointsDisplayComponent(go, "", font);
	m_Qbert->AddComponent(pointsDisplayComponent);
	pointsDisplayComponent->SetQbert(m_Qbert->GetComponentByType<QbertComponent>());
	pointsDisplayComponent->SetPosition(0, 30);
	m_Scene.Add(go);

	go = new GameObject();
	auto pointsDisplayComponent2 = new PointsDisplayComponent(go, "", font, "Points2: ");
	qbert2->AddComponent(pointsDisplayComponent2);
	pointsDisplayComponent2->SetQbert(qbert2->GetComponentByType<QbertComponent>());
	pointsDisplayComponent2->SetPosition(0, 60);
	m_Scene.Add(go);

	go = new GameObject();
	auto healthDisplayComponent = new HealthDisplayComponent(go, "", font);
	m_Qbert->AddComponent(healthDisplayComponent);
	healthDisplayComponent->SetQbert(m_Qbert->GetComponentByType<QbertComponent>());
	healthDisplayComponent->SetPosition(0, 90);
	m_Scene.Add(go);

	go = new GameObject();
	auto healthDisplayComponent2 = new HealthDisplayComponent(go, "", font, "Lives2: ");
	qbert2->AddComponent(healthDisplayComponent2);
	healthDisplayComponent2->SetQbert(qbert2->GetComponentByType<QbertComponent>());
	healthDisplayComponent2->SetPosition(0, 110);
	m_Scene.Add(go);

	//UGG
	auto ugg = EnemyFactory::CreateEnemy(EnemyComponent::EnemyType::UGG, this);
	m_Scene.Add(ugg);
	m_Enemies.push_back(ugg);
	//WRONG-WAY
	auto wrongway = EnemyFactory::CreateEnemy(EnemyComponent::EnemyType::WRONGWAY, this);
	m_Scene.Add(wrongway);
	m_Enemies.push_back(wrongway);
	//SLICK
	auto slick = EnemyFactory::CreateEnemy(EnemyComponent::EnemyType::SLICK, this);
	m_Scene.Add(slick);
	m_Enemies.push_back(slick);
	//SAM
	auto sam = EnemyFactory::CreateEnemy(EnemyComponent::EnemyType::SAM, this);
	m_Scene.Add(sam);
	m_Enemies.push_back(sam);

	ServiceLocator::RegisterSoundSystem(new LoggingSoundSystem(new SDL2SoundSystem()));
	ServiceLocator::GetSoundSystem().Play("../Data/highlands.wav", 50);
	ServiceLocator::GetSoundSystem().Play("../Data/door1.wav", 100);

	auto& input = InputManager::GetInstance();
	//create binds
	input.BindCommand(ControllerButton::ButtonA, new JumpCommand());
	input.BindCommand(ControllerButton::ButtonB, new FireCommand());
	input.BindCommand(ControllerButton::ButtonX, new DuckCommand());
	input.BindCommand(ControllerButton::ButtonY, new FartCommand());
	input.BindCommand(ControllerButton::ButtonRB, new KillQbertCommand(m_Qbert));
	input.BindCommand(ControllerButton::ButtonLB, new AddPointsCommand(m_Qbert));
	input.BindCommand(ControllerButton::ButtonRT, new KillQbertCommand(qbert2));
	input.BindCommand(ControllerButton::ButtonLT, new AddPointsCommand(qbert2));

	input.BindCommand(ControllerButton::ButtonSTART, new ToggleMuteCommand());
}

void qbert::QbertGame::CreateLevel(const std::string& path)
{
	std::cout << "creating level...\n";

	glm::vec2 start{ 120,110 };//320,240//220,140
	const float size{ 32.f };//16
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
dae::GameObject* qbert::QbertGame::CreatePlayer()
{
	using namespace dae;
	auto qbert = new GameObject();
	RenderComponent* renderComponent = new RenderComponent(qbert);
	qbert->AddComponent(renderComponent);
	renderComponent->SetTexture("Qbert.png");
	renderComponent->SetWidth(30);
	renderComponent->SetHeight(32);
	renderComponent->SetPosition(20, -15);

	MovementComponent* movementComponent = new MovementComponent(qbert, this, { 0,3 });
	qbert->AddComponent(movementComponent);

	qbert->AddComponent(new QbertComponent(qbert));

	m_Scene.Add(qbert);

	auto& input = InputManager::GetInstance();
	//create controller binds
	input.BindCommand(ControllerButton::ButtonUP, new MoveCommand(movementComponent, MovementComponent::MoveDirection::UP));
	input.BindCommand(ControllerButton::ButtonDOWN, new MoveCommand(movementComponent, MovementComponent::MoveDirection::DOWN));
	input.BindCommand(ControllerButton::ButtonLEFT, new MoveCommand(movementComponent, MovementComponent::MoveDirection::LEFT));
	input.BindCommand(ControllerButton::ButtonRIGHT, new MoveCommand(movementComponent, MovementComponent::MoveDirection::RIGHT));
	//create keyboard binds
	input.BindCommand('w', new MoveCommand(movementComponent, MovementComponent::MoveDirection::UP));
	input.BindCommand('s', new MoveCommand(movementComponent, MovementComponent::MoveDirection::DOWN));
	input.BindCommand('a', new MoveCommand(movementComponent, MovementComponent::MoveDirection::LEFT));
	input.BindCommand('d', new MoveCommand(movementComponent, MovementComponent::MoveDirection::RIGHT));
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
	std::cout << "Loading next level\n";
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

	m_Qbert->GetComponentByType<MovementComponent>()->Respawn();
	// put qbert on the foreground
	m_Scene.Remove(m_Qbert);
	m_Scene.Add(m_Qbert);
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
	m_CollisionTime += dae::GameTime::GetInstance()->GetDeltaTime();
	if (m_CollisionTime >= m_CollisionIntervalTime)
	{
		m_CollisionTime -= m_CollisionIntervalTime;

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
		m_Enemies.erase(It);
	}
}