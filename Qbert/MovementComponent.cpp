#include "MiniginPCH.h"
#include "MovementComponent.h"

#include "GameObject.h"
#include "LevelTileComponent.h"
#include "QbertGame.h"
#include "QbertComponent.h"

qbert::MovementComponent::MovementComponent(dae::GameObject* pOwner, qbert::QbertGame* qbertGame, glm::ivec2 spawnPos)
	:Component(pOwner),
	m_QbertGame(qbertGame),
	m_PosRow(0),
	m_PosCol(3),
	m_SpawnPos(spawnPos)
{
}

void qbert::MovementComponent::Update()
{
}

void qbert::MovementComponent::Move(MoveDirection direction)
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
	}
	auto newTileToStandOn = m_QbertGame->GetTile(m_PosRow, m_PosCol);
	if (newTileToStandOn != nullptr && newTileToStandOn->GetComponentByType<LevelTileComponent>()->GetTileType() != LevelTileComponent::TileType::DEATH)
	{
		auto newPos = newTileToStandOn->GetTransform()->GetPosition();
		m_pOwner->GetTransform()->SetPosition(newPos);
		if (newTileToStandOn->GetComponentByType<LevelTileComponent>()->GetTileType() == LevelTileComponent::TileType::DISK)
		{
			m_QbertGame->RemoveDisk(m_PosRow, m_PosCol);
			Respawn();
			newTileToStandOn = m_QbertGame->GetTile(m_PosRow, m_PosCol);
		}
	}
	else
	{
		// qbert loses a life
		Respawn();
		m_pOwner->GetComponentByType<QbertComponent>()->Kill();
		newTileToStandOn = m_QbertGame->GetTile(m_PosRow, m_PosCol);
	}
	newTileToStandOn->GetComponentByType<LevelTileComponent>()->ChangeColor();
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
void qbert::MovementComponent::Respawn()
{
	m_PosRow = m_SpawnPos.x;
	m_PosCol = m_SpawnPos.y;
	m_QbertGame->SetQbertOnSpawnPos();
}