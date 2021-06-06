#include "MiniginPCH.h"
#include "MovementComponent.h"

#include "GameObject.h"
#include "LevelTileComponent.h"
#include "QbertGame.h"
#include "ServiceLocator.h"
#include "UggOrWrongWayComponent.h"

qbert::MovementComponent::MovementComponent(dae::GameObject* pOwner, QbertGame* qbertGame, const glm::ivec2& spawnPos)
	:Component(pOwner),
	m_QbertGame(qbertGame),
	m_PosRow(spawnPos.x),
	m_PosCol(spawnPos.y),
	m_SpawnPos({ 0,3 }),
	m_IsSpawned(false)
{
}

void qbert::MovementComponent::Update()
{
	if (!m_IsSpawned)
	{
		auto newPos = m_QbertGame->GetTile(m_PosRow, m_PosCol)->GetTransform()->GetPosition();
		m_pOwner->GetTransform()->SetPosition(newPos);
		m_IsSpawned = true;
	}
}

void qbert::MovementComponent::Move(MoveDirection direction, bool changeColor, bool canTakeDisk, bool revertColor)
{
	switch (direction)
	{
	case MoveDirection::UP:
		MoveUp();
		break;
	case MoveDirection::DOWN:
		MoveDown();
		break;
	case MoveDirection::LEFT:
		MoveLeft();
		break;
	case MoveDirection::RIGHT:
		MoveRight();
		break;
	case MoveDirection::SIDEWAYS_LEFT:
		MoveSidewaysLeft();
		break;
	case MoveDirection::SIDEWAYS_RIGHT:
		MoveSidewaysRight();
		break;
	}
	auto newTileToStandOn = m_QbertGame->GetTile(m_PosRow, m_PosCol);
	if (newTileToStandOn != nullptr && newTileToStandOn->GetComponentByType<LevelTileComponent>()->GetTileType() != LevelTileComponent::TileType::DEATH)
	{
		auto newPos = newTileToStandOn->GetTransform()->GetPosition();
		m_pOwner->GetTransform()->SetPosition(newPos);
		if (canTakeDisk && newTileToStandOn->GetComponentByType<LevelTileComponent>()->GetTileType() == LevelTileComponent::TileType::DISK)
		{
			dae::ServiceLocator::GetSoundSystem().Play("../Data/lift.wav", 10);
			m_QbertGame->RemoveDisk(m_PosRow, m_PosCol);
			m_QbertGame->SetQbertHasTakenDisk(true);
			m_QbertGame->SetQbertPosForCoily(glm::ivec2{ m_PosRow, m_PosCol });
			Respawn();
			newTileToStandOn = m_QbertGame->GetTile(m_PosRow, m_PosCol);
		}
	}
	else
	{
		// loses a life
		Respawn();

		auto healthComponent = m_pOwner->GetComponentByType<HealthComponent>();
		if (healthComponent)
		{
			healthComponent->Kill();
		}
		newTileToStandOn = m_QbertGame->GetTile(m_PosRow, m_PosCol);
	}
	if (changeColor)
	{
		newTileToStandOn->GetComponentByType<LevelTileComponent>()->ChangeColor();
	}
	if (revertColor)
	{
		newTileToStandOn->GetComponentByType<LevelTileComponent>()->RevertColor();
	}
}

void qbert::MovementComponent::MoveUp()
{
	if (m_PosRow % 2 == 0)
	{
		m_PosRow -= 1;
	}
	else
	{
		m_PosRow -= 1;
		m_PosCol += 1;
	}
}

void qbert::MovementComponent::MoveDown()
{
	if (m_PosRow % 2 == 0)
	{
		m_PosRow += 1;
		m_PosCol -= 1;
	}
	else
	{
		m_PosRow += 1;
	}
}

void qbert::MovementComponent::MoveLeft()
{
	if (m_PosRow % 2 == 0)
	{
		m_PosRow -= 1;
		m_PosCol -= 1;
	}
	else
	{
		m_PosRow -= 1;
	}
}

void qbert::MovementComponent::MoveRight()
{
	if (m_PosRow % 2 == 0)
	{
		m_PosRow += 1;
	}
	else
	{
		m_PosRow += 1;
		m_PosCol += 1;
	}
}

void qbert::MovementComponent::MoveSidewaysLeft()
{
	m_PosCol -= 1;
}

void qbert::MovementComponent::MoveSidewaysRight()
{
	m_PosCol += 1;
}

void qbert::MovementComponent::Respawn()
{
	m_PosRow = m_SpawnPos.x;
	m_PosCol = m_SpawnPos.y;
	auto newPos = m_QbertGame->GetTile(m_PosRow, m_PosCol)->GetTransform()->GetPosition();
	m_pOwner->GetTransform()->SetPosition(newPos);
}

bool qbert::MovementComponent::IsOnLastRow() const
{
	return m_PosRow == QbertGame::m_LevelRows - 1;
}

glm::ivec2 qbert::MovementComponent::GetPosRowCol() const
{
	return glm::ivec2{ m_PosRow, m_PosCol };
}

void qbert::MovementComponent::SetPosRowCol(const glm::ivec2& pos)
{
	m_PosRow = pos.x;
	m_PosCol = pos.y;
	const auto newPos = m_QbertGame->GetTile(m_PosRow, m_PosCol)->GetTransform()->GetPosition();
	m_pOwner->GetTransform()->SetPosition(newPos);
}

dae::GameObject* qbert::MovementComponent::GetTileStandingOn() const
{
	return m_QbertGame->GetTile(m_PosRow, m_PosCol);
}