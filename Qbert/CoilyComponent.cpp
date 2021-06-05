#include "MiniginPCH.h"
#include "CoilyComponent.h"

#include "QbertComponent.h"
#include "GameObject.h"
#include "RenderComponent.h"

qbert::CoilyComponent::CoilyComponent(dae::GameObject* pOwner, EnemyType type, MovementComponent* movementComponent, dae::GameObject* player)
	:EnemyComponent(pOwner, type, movementComponent),
	HealthComponent(1),
	m_Player(player),
	m_IsInEggState(true)
{
}
void qbert::CoilyComponent::DoNextMove()
{
	if (m_IsInEggState)
	{
		// go down the pyramid
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
		if (m_MovementComponent->IsOnLastRow())
		{
			m_IsInEggState = false;
			auto renderComponent = m_pOwner->GetComponentByType<dae::RenderComponent>();
			renderComponent->SetTexture("../Data/Coily.png");
			renderComponent->SetWidth(28);
			renderComponent->SetHeight(32);
		}
	}
	else
	{
		// hunt for qbert
		std::cout << "hunting\n";
	}
}
void qbert::CoilyComponent::Kill()
{
	std::cout << "Coily died\n";
	m_MovementComponent->GetQbertGame()->Destroy(m_pOwner);
	m_Player->GetComponentByType<QbertComponent>()->DefeatCoily();
}
void qbert::CoilyComponent::CollisionWithPlayer(dae::GameObject* player)
{
	player->GetComponentByType<QbertComponent>()->Kill();
	Kill();
}