#pragma once
#include <Component.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

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
		MovementComponent(dae::GameObject* pOwner, qbert::QbertGame* qbertGame, glm::ivec2 spawnPos);

		void Update() override;
		void Move(MoveDirection direction);
		void Respawn();
	private:
		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();

		int m_PosRow;
		int m_PosCol;
		qbert::QbertGame* m_QbertGame;
		glm::ivec2 m_SpawnPos;
	};
}
