#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "FPSComponent.h"
#include "TextObject.h"
#include "GameObject.h"
#include "HealthDisplayComponent.h"
#include "PointsDisplayComponent.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "GameTime.h"
#include "audio.h"
#include "SDL2SoundSystem.h"
#include "LoggingSoundSystem.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	_putenv("SDL_AUDIODRIVER=DirectSound");	//to fix the audio of simple SDL2 audio
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment Victor Ghys",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		return;
	}
	initAudio();

	m_Qbert = new GameObject();
	m_Qbert2 = new GameObject();
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	// best way to do this is to read it in from a file
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

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

	m_Qbert->AddComponent(new QbertComponent(m_Qbert));
	scene.Add(m_Qbert);

	m_Qbert2->AddComponent(new QbertComponent(m_Qbert2));
	scene.Add(m_Qbert2);

	go = new GameObject();
	auto pointsDisplayComponent = new PointsDisplayComponent(go, "", font);
	m_Qbert->AddComponent(pointsDisplayComponent);
	pointsDisplayComponent->SetQbert(m_Qbert->GetComponentByType<QbertComponent>());
	pointsDisplayComponent->SetPosition(300, 400);
	scene.Add(go);

	go = new GameObject();
	auto pointsDisplayComponent2 = new PointsDisplayComponent(go, "", font);
	m_Qbert2->AddComponent(pointsDisplayComponent2);
	pointsDisplayComponent2->SetQbert(m_Qbert2->GetComponentByType<QbertComponent>());
	pointsDisplayComponent2->SetPosition(350, 400);
	scene.Add(go);

	go = new GameObject();
	auto healthDisplayComponent = new HealthDisplayComponent(go, "", font);
	m_Qbert->AddComponent(healthDisplayComponent);
	healthDisplayComponent->SetQbert(m_Qbert->GetComponentByType<QbertComponent>());
	healthDisplayComponent->SetPosition(0, 400);
	scene.Add(go);

	go = new GameObject();
	auto healthDisplayComponent2 = new HealthDisplayComponent(go, "", font);
	m_Qbert2->AddComponent(healthDisplayComponent2);
	healthDisplayComponent2->SetQbert(m_Qbert2->GetComponentByType<QbertComponent>());
	healthDisplayComponent2->SetPosition(30, 400);
	scene.Add(go);

	ServiceLocator::RegisterSoundSystem(new LoggingSoundSystem(new SDL2SoundSystem()));
	ServiceLocator::GetSoundSystem().Play("../Data/highlands.wav", 50);
	ServiceLocator::GetSoundSystem().Play("../Data/door1.wav", 100);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	GameTime::GetInstance()->Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	endAudio();
	SDL_Quit();
}

void dae::Minigin::Run()
{
	// to find memory leak
	//HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(267);

	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
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
		input.BindCommand(ControllerButton::ButtonUP, new KillQbertCommand(m_Qbert));
		input.BindCommand(ControllerButton::ButtonLEFT, new AddPointsCommand(m_Qbert));
		input.BindCommand(ControllerButton::ButtonDOWN, new KillQbertCommand(m_Qbert2));
		input.BindCommand(ControllerButton::ButtonRIGHT, new AddPointsCommand(m_Qbert2));
		input.BindCommand(ControllerButton::ButtonSTART, new ToggleMuteCommand());

		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			auto deltaTime = duration<float>(currentTime - lastTime);
			GameTime::GetInstance()->SetDeltaTime(static_cast<float>(deltaTime.count()));
			lastTime = currentTime;

			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();

			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
	//_CrtDumpMemoryLeaks();
}