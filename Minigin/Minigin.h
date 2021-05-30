#pragma once
#include <functional>
#include "Game.h"
#include "MiniginLibType.h"
struct SDL_Window;
namespace dae
{
	//class Game;
	class GameObject;

	class MINIGIN_ENTRY Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run(Game* game);
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}