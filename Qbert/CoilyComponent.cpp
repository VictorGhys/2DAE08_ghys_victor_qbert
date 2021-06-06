#include "MiniginPCH.h"
#include "CoilyComponent.h"

#include "QbertComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "QbertCommands.h"
#include "RenderComponent.h"
#include "ServiceLocator.h"

qbert::CoilyComponent::CoilyComponent(dae::GameObject* pOwner, EnemyType type, MovementComponent* movementComponent, dae::GameObject* player, QbertGame* qbertGame, bool isControlledByPlayer)
	:EnemyComponent(pOwner, type, movementComponent),
	HealthComponent(1),
	m_Player(player),
	m_IsInEggState(true),
	m_QbertGame(qbertGame),
	m_IsControlledByPlayer(isControlledByPlayer)
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
			BreakOutEgg();
		}
	}
	else
	{
		if (!m_IsControlledByPlayer)
		{
			DoAiMovement();
		}
	}
}
void qbert::CoilyComponent::Kill()
{
	std::cout << "Coily died\n";
	m_MovementComponent->GetQbertGame()->Destroy(m_pOwner);
	m_Player->GetComponentByType<QbertComponent>()->DefeatCoily();
	dae::ServiceLocator::GetSoundSystem().Play("../Data/snake-fall.wav", 10);
}
void qbert::CoilyComponent::CollisionWithPlayer(dae::GameObject* player)
{
	player->GetComponentByType<QbertComponent>()->Kill();
	Kill();
}

void qbert::CoilyComponent::BreakOutEgg()
{
	m_IsInEggState = false;
	auto renderComponent = m_pOwner->GetComponentByType<dae::RenderComponent>();
	renderComponent->SetTexture("../Data/Coily.png");
	renderComponent->SetWidth(28);
	renderComponent->SetHeight(32);

	if (m_IsControlledByPlayer)
	{
		using namespace dae;
		auto movementComponent = m_pOwner->GetComponentByType<MovementComponent>();
		auto& input = InputManager::GetInstance();
		//create controller binds player 2
		input.BindCommand({ ControllerButton::ButtonUP,1 }, new MoveCommand(movementComponent, MovementComponent::MoveDirection::UP));
		input.BindCommand({ ControllerButton::ButtonDOWN,1 }, new MoveCommand(movementComponent, MovementComponent::MoveDirection::DOWN));
		input.BindCommand({ ControllerButton::ButtonLEFT,1 }, new MoveCommand(movementComponent, MovementComponent::MoveDirection::LEFT));
		input.BindCommand({ ControllerButton::ButtonRIGHT,1 }, new MoveCommand(movementComponent, MovementComponent::MoveDirection::RIGHT));
		//create keyboard binds player 2
		input.BindCommand('i', new MoveCommand(movementComponent, MovementComponent::MoveDirection::UP));
		input.BindCommand('k', new MoveCommand(movementComponent, MovementComponent::MoveDirection::DOWN));
		input.BindCommand('j', new MoveCommand(movementComponent, MovementComponent::MoveDirection::LEFT));
		input.BindCommand('l', new MoveCommand(movementComponent, MovementComponent::MoveDirection::RIGHT));
	}
}

void qbert::CoilyComponent::DoAiMovement() const
{
	// hunt for qbert
	auto coilyPos = m_MovementComponent->GetPosRowCol();
	glm::ivec2 diff = m_QbertGame->GetQbertPosForCoily() - coilyPos;
	if (diff.x <= 0)
	{
		// player is above or on same row
		if (diff.y >= 0)
		{
			// player is to the right or same col
			if (diff.y != 0 || coilyPos.x % 2 == 0)
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
			if (diff.y != 0 || coilyPos.x % 2 == 0)
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