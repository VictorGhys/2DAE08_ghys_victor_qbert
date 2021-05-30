#pragma once
namespace dae
{
	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;
		virtual void LoadGame() = 0;
	};
}
