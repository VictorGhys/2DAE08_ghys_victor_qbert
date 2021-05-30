#pragma once
#include "../Minigin/Game.h"

namespace dae {
	class Scene;
}

class QbertGame final : public dae::Game
{
public:
	QbertGame() = default;
	virtual ~QbertGame() override = default;
	void LoadGame() override;
	void CreateLevel(dae::Scene& scene, int levelNb);
};
