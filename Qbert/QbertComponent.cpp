#include "MiniginPCH.h"
#include "QbertComponent.h"
#include "HealthDisplayComponent.h"
#include "QbertGame.h"
#include "QbertObserver.h"
#include "ServiceLocator.h"

qbert::QbertComponent::QbertComponent(dae::GameObject* pOwner, qbert::QbertGame* qbertGame)
	:Component(pOwner),
	HealthComponent(3),
	m_QbertGame(qbertGame)
{
}

void qbert::QbertComponent::Update()
{
}

void qbert::QbertComponent::Kill()
{
	m_Health -= 1;
	for (auto observer : m_Observers)
	{
		observer->Died();
	}
	if (m_Health > 0)
	{
		dae::ServiceLocator::GetSoundSystem().Play("../Data/swear.wav", 10);
	}
	else
	{
		dae::ServiceLocator::GetSoundSystem().Play("../Data/fall.wav", 10);
		m_QbertGame->RestartGame(m_QbertGame->GetGameMode());
	}
}

void qbert::QbertComponent::ChangeTile()
{
	for (auto observer : m_Observers)
	{
		observer->ChangedTile();
	}
}

void qbert::QbertComponent::DefeatCoily()
{
	for (auto observer : m_Observers)
	{
		observer->DefeatCoily();
	}
}

void qbert::QbertComponent::CatchSlickOrSlam()
{
	for (auto observer : m_Observers)
	{
		observer->CatchSlickOrSlam();
	}
}

void qbert::QbertComponent::RemainingDisk()
{
	for (auto observer : m_Observers)
	{
		observer->RemainingDisk();
	}
}

void qbert::QbertComponent::AddObserver(qbert::QbertObserver* observer)
{
	m_Observers.push_back(observer);
}
void qbert::QbertComponent::RemoveObserver(qbert::QbertObserver* observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
}