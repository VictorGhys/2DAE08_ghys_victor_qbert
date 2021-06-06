#pragma once
#include <iostream>

#include "Command.h"
#include "QbertComponent.h"
#include "ServiceLocator.h"
#include "GameObject.h"
#include "MovementComponent.h"

namespace qbert
{
	class KillQbertCommand : public Command
	{
	public:
		KillQbertCommand(dae::GameObject* qbert)
			:m_Qbert(qbert)
		{
		}
		virtual void Execute() override { KillQbert(); };
	private:
		void KillQbert()
		{
			std::cout << "Kill\n";
			m_Qbert->GetComponentByType<QbertComponent>()->Kill();
		};
		dae::GameObject* m_Qbert;
	};

	class AddPointsCommand : public Command
	{
	public:
		AddPointsCommand(dae::GameObject* qbert)
			:m_Qbert(qbert)
		{
		}
		virtual void Execute() override { AddPoints(); };
	private:
		void AddPoints()
		{
			std::cout << "Add Points\n";
			m_Qbert->GetComponentByType<QbertComponent>()->ChangeTile();
		};
		dae::GameObject* m_Qbert;
	};

	class ToggleMuteCommand : public Command
	{
	public:
		virtual void Execute() override { ToggleMute(); };
	private:
		void ToggleMute() { dae::ServiceLocator::GetSoundSystem().ToggleMute(); };
	};

	class MoveCommand : public Command
	{
	public:
		MoveCommand(MovementComponent* movementComponent, MovementComponent::MoveDirection direction)
			:m_MovementComponent(movementComponent),
			m_Direction(direction)
		{
		}
		virtual void Execute() override { Move(); }
	private:
		void Move()
		{
			m_MovementComponent->Move(m_Direction, true, true);
			dae::ServiceLocator::GetSoundSystem().Play("../Data/jump.wav", 10);
		}
		MovementComponent* m_MovementComponent;
		MovementComponent::MoveDirection m_Direction;
	};
}