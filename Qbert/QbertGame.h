#pragma once
#include "../Minigin/Game.h"
#include "Scene.h"

namespace dae {
	class GameObject;
}

namespace qbert
{
	class QbertGame final : public dae::Game
	{
	public:
		//QbertGame() = default;
		QbertGame();
		virtual ~QbertGame() override = default;
		void LoadGame() override;

		dae::GameObject* GetTile(int row, int col);
		dae::GameObject* GetTopOfLevel();
		void SetQbertOnSpawnPos();
		void RemoveDisk(int row, int col);
		void LoadNextLevel();
		static int m_TilesActiveToWin;

	private:
		void CreateLevel(const std::string& path);
		dae::GameObject* CreatePlayer();

		const static  int m_LevelRows{ 7 };
		const static  int m_LevelCols{ 7 };
		dae::GameObject* m_Level[m_LevelRows][m_LevelCols]{ nullptr };
		dae::GameObject* m_Qbert;
		dae::Scene& m_Scene;
		int m_CurrentLevel;
	};
}