#pragma once
#include <Component.h>

#include "MovementComponent.h"

namespace qbert
{
	class MovementComponent;

	class EnemyComponent : public dae::Component
	{
	public:
		enum class EnemyType
		{
			COILY,
			UGG,
			WRONGWAY,
			SLICK,
			SAM
		};
		EnemyComponent(dae::GameObject* pOwner, EnemyType type, MovementComponent* movementComponent);
		void Update() override;
		virtual void CollisionWithPlayer(dae::GameObject* player) = 0;
	protected:
		virtual void DoNextMove() = 0;
		MovementComponent* m_MovementComponent;
		EnemyType m_Type;
	private:

		float m_MoveTime;
		const float m_MoveIntervalTime;
	};
}
