#include <MiniginPCH.h>
#include "QbertGame.h"

#include <fstream>

#include "FPSComponent.h"
#include "GameObject.h"
#include "HealthDisplayComponent.h"
#include "InputManager.h"
#include "LevelTileComponent.h"
#include "LoggingSoundSystem.h"
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
void QbertGame::LoadGame()
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
	input.BindCommand(ControllerButton::ButtonRB, new JumpCommand());
	input.BindCommand(ControllerButton::ButtonLB, new FireCommand());
	input.BindCommand(ControllerButton::ButtonRT, new DuckCommand());
	input.BindCommand(ControllerButton::ButtonLT, new FartCommand());
	input.BindCommand(ControllerButton::ButtonUP, new KillQbertCommand(qbert));
	input.BindCommand(ControllerButton::ButtonLEFT, new AddPointsCommand(qbert));
	input.BindCommand(ControllerButton::ButtonDOWN, new KillQbertCommand(qbert2));
	input.BindCommand(ControllerButton::ButtonRIGHT, new AddPointsCommand(qbert2));
	input.BindCommand(ControllerButton::ButtonSTART, new ToggleMuteCommand());

	// Create Level
	CreateLevel(scene, "../Data/Level1.txt");
}

void QbertGame::CreateLevel(dae::Scene& scene, const std::string& path)
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
				//go->GetComponentByType<LevelTileComponent>()->SetPosition(start.x + width * col + width / 2.f, start.y + height * row * 3.f / 4.f);
			}
			else
			{
				tileComponent = new LevelTileComponent(go, static_cast<LevelTileComponent::TileType>(character),
					start.x + width * col, start.y + height * row * 3.f / 4.f);
				//go->GetComponentByType<LevelTileComponent>()->SetPosition(start.x + width * col, start.y + height * row * 3.f / 4.f);
			}
			go->AddComponent(tileComponent);
			m_Level[row][col] = go;
			scene.Add(go);

			col++;
		}
		col = 0;
		row++;
	}
	//for (int r{}; r < 7; r++)
	//{
	//	for (int c{}; c < 7; c++)
	//	{
	//		auto go = new dae::GameObject();
	//		auto tileComponent = new LevelTileComponent(go);
	//		go->AddComponent(tileComponent);
	//		tileComponent->SetTile("../Data/Tile1.png");
	//		level[r][c] = go;
	//		scene.Add(go);
	//		if ((r + 1) % 2 == 0)
	//		{
	//			// shift to right
	//			go->GetComponentByType<LevelTileComponent>()->SetPosition(start.x + width * c + width / 2.f, start.y + height * r * 3.f / 4.f);
	//		}
	//		else
	//		{
	//			go->GetComponentByType<LevelTileComponent>()->SetPosition(start.x + width * c, start.y + height * r * 3.f / 4.f);
	//		}
	//	}
	//}
}