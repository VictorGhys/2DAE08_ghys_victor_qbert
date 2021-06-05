#pragma once
#include "EnemyComponent.h"
#include "HealthComponent.h"

namespace qbert
{
	class SlickOrSamComponent : public EnemyComponent, public HealthComponent
	{
	public:
		SlickOrSamComponent(dae::GameObject* pOwner, EnemyType type, MovementComponent* movementComponent);
		void DoNextMove() override;
		void Kill() override;
		void CollisionWithPlayer(dae::GameObject* player) override;
	private:
	};
}
