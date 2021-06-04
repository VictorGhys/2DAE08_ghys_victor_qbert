#pragma once
#include "EnemyComponent.h"

namespace qbert
{
	class EnemyFactory
	{
	public:
		static dae::GameObject* CreateEnemy(EnemyComponent::EnemyType type, QbertGame* qbertGame);
	};
}
