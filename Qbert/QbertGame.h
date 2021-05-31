#pragma once
#include "../Minigin/Game.h"

namespace dae {
	class GameObject;
	class Scene;
}

class QbertGame final : public dae::Game
{
public:
	QbertGame() = default;
	virtual ~QbertGame() override = default;
	void LoadGame() override;
	void CreateLevel(dae::Scene& scene, const std::string& path);
private:
	const static  int m_LevelRows{ 7 };
	const static  int m_LevelCols{ 7 };
	dae::GameObject* m_Level[m_LevelRows][m_LevelCols];
};
