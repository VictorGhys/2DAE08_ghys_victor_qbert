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
			UGG_WRONGWAY,
			SLICK_SAM
		};
		EnemyComponent(dae::GameObject* pOwner, EnemyType type, MovementComponent* movementComponent);
		void Update() override;
	protected:
		virtual void DoNextMove() = 0;
		MovementComponent* m_MovementComponent;
	private:
		EnemyType m_Type;

		float m_MoveTime;
		const float m_MoveIntervalTime;
	};
}
