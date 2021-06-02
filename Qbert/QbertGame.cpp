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
#include "ServiceLocator.h"

/**
 * Code constructing the scene world starts here
 */
void qbert::QbertGame::LoadGame()
{
	using namespace dae;
	// best way to do this is to read it in from a file
	auto& scene = SceneManager::GetInstance().CreateScene("Qbert");

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

	auto go = new GameObject();
	RenderComponent* renderComponent = new RenderComponent(go);
	go->AddComponent(renderComponent);
	go->GetComponentByType<RenderComponent>()->SetTexture("background.jpg");
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new RenderComponent(go));
	go->GetComponentByType<RenderComponent>()->SetTexture("logo.png");
	//go->SetPosition(216, 180);
	go->GetComponentByType<RenderComponent>()->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = new GameObject();
	auto textComponent = new TextComponent(go, "Programming 4 Assignment", font);
	go->AddComponent(textComponent);
	textComponent->SetPosition(80, 20);
	//go->SetPosition(80, 20);
	scene.Add(go);

	go = new GameObject();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	go->AddComponent(new FPSComponent(go, "Programming 4 Assignment", font));
	go->SetPosition(0, 0);
	scene.Add(go);

	auto qbert = new GameObject();
	qbert->AddComponent(new QbertComponent(qbert));
	scene.Add(qbert);

	auto qbert2 = new GameObject();
	qbert2->AddComponent(new QbertComponent(qbert2));
	scene.Add(qbert2);

	go = new GameObject();
	auto pointsDisplayComponent = new PointsDisplayComponent(go, "", font);
	qbert->AddComponent(pointsDisplayComponent);
	pointsDisplayComponent->SetQbert(qbert->GetComponentByType<QbertComponent>());
	pointsDisplayComponent->SetPosition(300, 400);
	scene.Add(go);

	go = new GameObject();
	auto pointsDisplayComponent2 = new PointsDisplayComponent(go, "", font);
	qbert2->AddComponent(pointsDisplayComponent2);
	pointsDisplayComponent2->SetQbert(qbert2->GetComponentByType<QbertComponent>());
	pointsDisplayComponent2->SetPosition(350, 400);
	scene.Add(go);

	go = new GameObject();
	auto healthDisplayComponent = new HealthDisplayComponent(go, "", font);
	qbert->AddComponent(healthDisplayComponent);
	healthDisplayComponent->SetQbert(qbert->GetComponentByType<QbertComponent>());
	healthDisplayComponent->SetPosition(0, 400);
	scene.Add(go);

	go = new GameObject();
	auto healthDisplayComponent2 = new HealthDisplayComponent(go, "", font);
	qbert2->AddComponent(healthDisplayComponent2);
	healthDisplayComponent2->SetQbert(qbert2->GetComponentByType<QbertComponent>());
	healthDisplayComponent2->SetPosition(30, 400);
	scene.Add(go);

	ServiceLocator::RegisterSoundSystem(new LoggingSoundSystem(new SDL2SoundSystem()));
	ServiceLocator::GetSoundSystem().Play("../Data/highlands.wav", 50);
	ServiceLocator::GetSoundSystem().Play("../Data/door1.wav", 100);

	auto& input = InputManager::GetInstance();
	//create binds
	input.BindCommand(ControllerButton::ButtonA, new JumpCommand());
	input.BindCommand(ControllerButton::ButtonB, new FireCommand());
	input.BindCommand(ControllerButton::ButtonX, new DuckCommand());
	input.BindCommand(ControllerButton::ButtonY, new FartCommand());
	input.BindCommand(ControllerButton::ButtonRB, new KillQbertCommand(qbert));
	input.BindCommand(ControllerButton::ButtonLB, new AddPointsCommand(qbert));
	input.BindCommand(ControllerButton::ButtonRT, new KillQbertCommand(qbert2));
	input.BindCommand(ControllerButton::ButtonLT, new AddPointsCommand(qbert2));

	input.BindCommand(ControllerButton::ButtonSTART, new ToggleMuteCommand());

	// Create Level
	CreateLevel(scene, "../Data/Level1.txt");
	// Create Player
	CreatePlayer(scene);
}

void qbert::QbertGame::CreateLevel(dae::Scene& scene, const std::string& path)
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
					start.x + width * col + width / 2.f, start.y + height * row * 3.f / 4.f);
			}
			else
			{
				tileComponent = new LevelTileComponent(go, static_cast<LevelTileComponent::TileType>(character),
					start.x + width * col, start.y + height * row * 3.f / 4.f);
			}
			go->AddComponent(tileComponent);
			m_Level[row][col] = go;
			scene.Add(go);

			col++;
		}
		col = 0;
		row++;
	}
}
void qbert::QbertGame::CreatePlayer(dae::Scene& scene)
{
	using namespace dae;
	auto qbert = new GameObject();
	RenderComponent* renderComponent = new RenderComponent(qbert);
	qbert->AddComponent(renderComponent);
	renderComponent->SetTexture("Qbert.png");
	renderComponent->SetWidth(30);
	renderComponent->SetHeight(32);
	renderComponent->SetPosition(20, -20);

	qbert::MovementComponent* movementComponent = new MovementComponent(qbert, this);
	qbert->AddComponent(movementComponent);
	// set qbert on the top
	qbert->GetTransform()->SetPosition(GetTopOfLevel()->GetTransform()->GetPosition());

	scene.Add(qbert);

	//auto& input = InputManager::GetInstance();
	//create binds
	/*input.BindCommand(ControllerButton::ButtonUP, );
	input.BindCommand(ControllerButton::ButtonLEFT, );
	input.BindCommand(ControllerButton::ButtonDOWN, );
	input.BindCommand(ControllerButton::ButtonRIGHT, );*/
}

dae::GameObject* qbert::QbertGame::GetTile(int row, int col)
{
	return m_Level[row][col];
}
dae::GameObject* qbert::QbertGame::GetTopOfLevel()
{
	return m_Level[0][3];
}