#pragma once
#include "EnemyComponent.h"
#include "HealthComponent.h"

namespace qbert
{
	class MovementComponent;

	class UggOrWrongWayComponent : public EnemyComponent, public HealthComponent
	{
	public:
		UggOrWrongWayComponent(dae::GameObject* pOwner, EnemyType type, MovementComponent* movementComponent);
		void DoNextMove() override;
		void Kill() override;
		void CollisionWithPlayer(dae::GameObject* player) override;
	private:
	};
}
