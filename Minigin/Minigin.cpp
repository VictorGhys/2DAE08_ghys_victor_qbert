#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <functional>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameTime.h"
#include "audio.h"
#include "Game.h"
#include "SDL2SoundSystem.h"

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
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	endAudio();
	SDL_Quit();
}

void dae::Minigin::Run(Game* game)
{
	// to find memory leak
	//HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(267);

	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	if (game)
		game->LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			auto deltaTime = duration<float>(currentTime - lastTime);
			GameTime::GetInstance().SetDeltaTime(static_cast<float>(deltaTime.count()));
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