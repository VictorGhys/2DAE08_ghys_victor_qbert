#pragma once
#include "../Minigin/Game.h"
//#include "Scene.h"
#include <string>
#include <vector>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

namespace dae {
	class Scene;
	class GameObject;
}

namespace qbert
{
	class QbertGame final : public dae::Game
	{
	public:
		QbertGame();
		virtual ~QbertGame() override = default;
		void LoadGame() override;
		void Update() override;

		dae::GameObject* GetTile(int row, int col);
		dae::GameObject* GetTopOfLevel();
		dae::GameObject* GetQbert() const { return m_Qbert; }
		dae::Scene& GetScene() const { return m_Scene; }

		void RemoveDisk(int row, int col);
		void LoadNextLevel();
		static int m_TilesActiveToWin;
		void Destroy(dae::GameObject* object);
		const static int m_LevelRows{ 7 };
		const static int m_LevelCols{ 7 };
		glm::ivec2 GetQbertPosForCoily() const;
		void SetQbertPosForCoily(glm::ivec2 qbertPos) { m_QbertLastPos = qbertPos; }
		void SetQbertHasTakenDisk(bool hasTakenDisk) { m_QbertHasTakenDisk = hasTakenDisk; }
	private:
		void CreateLevel(const std::string& path);
		dae::GameObject* CreatePlayer();
		void CheckLevelCompleted();
		void CollisionCheck();

		dae::GameObject* m_Level[m_LevelRows][m_LevelCols]{ nullptr };
		dae::GameObject* m_Qbert;
		dae::GameObject* m_Qbert2;
		dae::Scene& m_Scene;
		int m_CurrentLevel;
		const int m_MaxLevel;
		std::vector<int> m_TilesActiveToWinForLevels;
		std::vector<dae::GameObject*> m_GameObjectsToDestroy;
		std::vector<dae::GameObject*> m_Enemies;
		float m_CollisionTime;
		const float m_CollisionIntervalTime;
		glm::ivec2 m_QbertLastPos;
		bool m_QbertHasTakenDisk;
		const float m_MaxHasTakenDiskResetTime{ 4 };
		float m_HasTakenDiskResetTime;
		const float m_MaxCoilySpawnTime{ 8 };
		float m_CoilySpawnTime;
		dae::GameObject* m_Coily;
		const float m_MaxEnemySpawnTime{ 8 };
		float m_EnemySpawnTime;
	};
}