#include "MiniginPCH.h"
#include "UggOrWrongWayComponent.h"

#include <iostream>

#include "GameObject.h"
#include "GameTime.h"
#include "QbertComponent.h"
#include "QbertGame.h"

qbert::UggOrWrongWayComponent::UggOrWrongWayComponent(dae::GameObject* pOwner, EnemyType type, MovementComponent* movementComponent)
	:EnemyComponent(pOwner, type, movementComponent),
	HealthComponent(1)
{
}

void qbert::UggOrWrongWayComponent::DoNextMove()
{
	if (m_Type == EnemyType::WRONGWAY)
	{
		// go left to right
		if (rand() % 2 == 0)
		{
			// up
			m_MovementComponent->Move(MovementComponent::MoveDirection::UP, false, false);
		}
		else
		{
			// sideways right
			m_MovementComponent->Move(MovementComponent::MoveDirection::SIDEWAYS_RIGHT, false, false);
		}
	}
	else
	{
		// go right to left
		if (rand() % 2 == 0)
		{
			// left
			m_MovementComponent->Move(MovementComponent::MoveDirection::LEFT, false, false);
		}
		else
		{
			// sideways left
			m_MovementComponent->Move(MovementComponent::MoveDirection::SIDEWAYS_LEFT, false, false);
		}
	}
}

void qbert::UggOrWrongWayComponent::Kill()
{
	std::cout << "ugg/wrongway died\n";
	m_MovementComponent->GetQbertGame()->Destroy(m_pOwner);
}

void qbert::UggOrWrongWayComponent::CollisionWithPlayer(dae::GameObject* player)
{
	if (m_PlayerCollisionCooldown >= m_MaxPlayerCollisionCooldown)
	{
		m_PlayerCollisionCooldown = 0;
		player->GetComponentByType<QbertComponent>()->Kill();
	}
}

void qbert::UggOrWrongWayComponent::UpdateTimers()
{
	m_PlayerCollisionCooldown += dae::GameTime::GetInstance()->GetDeltaTime();
}