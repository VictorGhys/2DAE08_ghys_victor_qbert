#pragma once
#include <Component.h>
#include "MovementComponent.h"

namespace qbert
{
	class MovementComponent;

	class EnemyComponent : public dae::Component
	{
	public:
		enum class EnemyType : int
		{
			COILY = 0,
			UGG = 1,
			WRONGWAY = 2,
			SLICK = 3,
			SAM = 4
		};
		EnemyComponent(dae::GameObject* pOwner, EnemyType type, MovementComponent* movementComponent);
		void Update() override;
		virtual void UpdateTimers();
		virtual void CollisionWithPlayer(dae::GameObject* player) = 0;
		EnemyType GetType() const { return m_Type; }
	protected:
		virtual void DoNextMove() = 0;
		MovementComponent* m_MovementComponent;
		EnemyType m_Type;
	private:
		float m_MoveTime;
		const float m_MoveIntervalTime;
	};
}
