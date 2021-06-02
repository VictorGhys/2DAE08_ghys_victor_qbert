#pragma once
#include <Component.h>

namespace qbert {
	class QbertGame;
}

namespace qbert
{
	class MovementComponent final : public dae::Component
	{
	public:
		enum class MoveDirection
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
		MovementComponent(dae::GameObject* pOwner, qbert::QbertGame* qbertGame);

		void Update() override;
		void Move(MoveDirection direction);
	private:
		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();

		int m_PosRow;
		int m_PosCol;
		qbert::QbertGame* m_QbertGame;
	};
}
