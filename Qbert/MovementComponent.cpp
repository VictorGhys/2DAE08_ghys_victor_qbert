#include "MiniginPCH.h"
#include "MovementComponent.h"

#include "GameObject.h"
#include "QbertGame.h"

qbert::MovementComponent::MovementComponent(dae::GameObject* pOwner, qbert::QbertGame* qbertGame)
	:Component(pOwner),
	m_QbertGame(qbertGame),
	m_PosRow(0),
	m_PosCol(3)
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
	if (newTileToStandOn != nullptr)
	{
		auto newPos = newTileToStandOn->GetTransform()->GetPosition();
		m_pOwner->GetTransform()->SetPosition(newPos);
	}
	else
	{
		std::cout << "qbert loses a life\n";
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