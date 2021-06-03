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
		void CreateLevel(dae::Scene& scene, const std::string& path);
		dae::GameObject* CreatePlayer(dae::Scene& scene);
		dae::GameObject* GetTile(int row, int col);
		dae::GameObject* GetTopOfLevel();
		void SetQbertOnSpawnPos();
		void RemoveDisk(int row, int col);
	private:
		const static  int m_LevelRows{ 7 };
		const static  int m_LevelCols{ 7 };
		dae::GameObject* m_Level[m_LevelRows][m_LevelCols]{ nullptr };
		dae::GameObject* m_Qbert;
		dae::Scene& m_Scene;
	};
}