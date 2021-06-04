#pragma once
#include <Component.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>

#include "QbertGame.h"
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
			RIGHT,
			SIDEWAYS_LEFT,
			SIDEWAYS_RIGHT,
		};
		MovementComponent(dae::GameObject* pOwner, qbert::QbertGame* qbertGame, glm::ivec2 spawnPos);

		void Update() override;
		void Move(MoveDirection direction, bool changeColor, bool canTakeDisk);
		void Respawn();
		QbertGame* GetQbertGame() const { return m_QbertGame; }
		dae::GameObject* GetTileStandingOn() const { return m_QbertGame->GetTile(m_PosRow, m_PosCol); }
	private:
		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();
		void MoveSidewaysLeft();
		void MoveSidewaysRight();

		int m_PosRow;
		int m_PosCol;
		qbert::QbertGame* m_QbertGame;
		glm::ivec2 m_SpawnPos;
		bool m_IsSpawned;
	};
}
