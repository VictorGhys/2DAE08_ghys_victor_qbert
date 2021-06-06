#pragma once
#include <Component.h>
#include "QbertGame.h"

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
			RIGHT,
			SIDEWAYS_LEFT,
			SIDEWAYS_RIGHT,
		};
		MovementComponent(dae::GameObject* pOwner, QbertGame* qbertGame, const glm::ivec2& spawnPos);

		void Update() override;
		void Move(MoveDirection direction, bool changeColor = false, bool canTakeDisk = false, bool revertColor = false);
		void Respawn();
		QbertGame* GetQbertGame() const { return m_QbertGame; }
		dae::GameObject* GetTileStandingOn() const;
		bool IsOnLastRow() const;
		glm::ivec2 GetPosRowCol() const;
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
