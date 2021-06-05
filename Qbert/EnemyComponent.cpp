#include "MiniginPCH.h"
#include "EnemyComponent.h"

#include "GameTime.h"

qbert::EnemyComponent::EnemyComponent(dae::GameObject* pOwner, EnemyType type, MovementComponent* movementComponent)
	:Component(pOwner),
	m_Type(type),
	m_MovementComponent(movementComponent),
	m_MoveTime(),
	m_MoveIntervalTime(1)
{
}
void qbert::EnemyComponent::Update()
{
	m_MoveTime += dae::GameTime::GetInstance()->GetDeltaTime();
	if (m_MoveTime >= m_MoveIntervalTime)
	{
		m_MoveTime -= m_MoveIntervalTime;
		DoNextMove();
	}
	UpdateTimers();
}
void qbert::EnemyComponent::UpdateTimers()
{
}