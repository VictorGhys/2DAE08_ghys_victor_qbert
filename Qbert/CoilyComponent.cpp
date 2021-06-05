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
		auto playerPos = m_Player->GetComponentByType<MovementComponent>()->GetPosRowCol();
		auto coilyPos = m_MovementComponent->GetPosRowCol();
		glm::ivec2 diff = playerPos - coilyPos;
		if (diff.x <= 0)
		{
			// player is above or on same row
			if (diff.y >= 0)
			{
				// player is to the right or same col
				if (coilyPos.x % 2 == 0)
				{
					m_MovementComponent->Move(MovementComponent::MoveDirection::UP, false, false);
				}
				else
				{
					// because of crooked collumns go left if uneven row
					m_MovementComponent->Move(MovementComponent::MoveDirection::LEFT, false, false);
				}
			}
			else
			{
				// player is to the left
				m_MovementComponent->Move(MovementComponent::MoveDirection::LEFT, false, false);
			}
		}
		else
		{
			// player is below
			if (diff.y >= 0)
			{
				// player is to the right or same col
				if (coilyPos.x % 2 == 0)
				{
					m_MovementComponent->Move(MovementComponent::MoveDirection::RIGHT, false, false);
				}
				else
				{
					// because of crooked collumns go down if uneven row
					m_MovementComponent->Move(MovementComponent::MoveDirection::DOWN, false, false);
				}
			}
			else
			{
				// player is to the left
				m_MovementComponent->Move(MovementComponent::MoveDirection::DOWN, false, false);
			}
		}
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