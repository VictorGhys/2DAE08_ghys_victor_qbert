#pragma once
#include "EnemyComponent.h"
#include "HealthComponent.h"

namespace qbert
{
	class CoilyComponent : public EnemyComponent, public HealthComponent
	{
	public:
		CoilyComponent(dae::GameObject* pOwner, EnemyType type, MovementComponent* movementComponent, dae::GameObject* player, QbertGame* qbertGame, bool isControlledByPlayer = false);
		void DoNextMove() override;
		void Kill() override;
		void CollisionWithPlayer(dae::GameObject* player) override;
	private:
		void BreakOutEgg();
		void DoAiMovement() const;

		dae::GameObject* m_Player;
		bool m_IsInEggState;
		QbertGame* m_QbertGame;
		bool m_IsControlledByPlayer;
	};
}
