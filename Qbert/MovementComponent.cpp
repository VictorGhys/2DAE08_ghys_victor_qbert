#include "MiniginPCH.h"
#include "MovementComponent.h"

#include "GameObject.h"
#include "QbertGame.h"

qbert::MovementComponent::MovementComponent(dae::GameObject* pOwner, qbert::QbertGame* qbertGame)
	:Component(pOwner),
	m_QbertGame(qbertGame)
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
	auto newPos = m_QbertGame->GetTile(m_PosRow, m_PosCol)->GetTransform()->GetPosition();
	m_pOwner->GetTransform()->SetPosition(newPos);
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