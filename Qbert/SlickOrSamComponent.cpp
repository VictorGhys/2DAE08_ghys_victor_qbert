#include "MiniginPCH.h"
#include "SlickOrSamComponent.h"

#include "QbertComponent.h"
#include "GameObject.h"

qbert::SlickOrSamComponent::SlickOrSamComponent(dae::GameObject* pOwner, EnemyType type, MovementComponent* movementComponent)
	:EnemyComponent(pOwner, type, movementComponent),
	HealthComponent(1)
{
}
void qbert::SlickOrSamComponent::DoNextMove()
{
	if (rand() % 2 == 0)
	{
		// right
		m_MovementComponent->Move(MovementComponent::MoveDirection::RIGHT, false, false);
	}
	else
	{
		// down
		m_MovementComponent->Move(MovementComponent::MoveDirection::DOWN, false, false);
	}
}
void qbert::SlickOrSamComponent::Kill()
{
	std::cout << "slick/sam died\n";
	m_MovementComponent->GetQbertGame()->Destroy(m_pOwner);
}
void qbert::SlickOrSamComponent::CollisionWithPlayer(dae::GameObject* player)
{
	player->GetComponentByType<QbertComponent>()->CatchSlickOrSlam();
	Kill();
}