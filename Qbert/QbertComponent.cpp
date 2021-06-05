#include "MiniginPCH.h"
#include "QbertComponent.h"
#include "HealthDisplayComponent.h"
#include "ResourceManager.h"
#include "PointsDisplayComponent.h"
#include "QbertObserver.h"

qbert::QbertComponent::QbertComponent(dae::GameObject* pOwner)
	:Component(pOwner),
	HealthComponent(3)
{
}

void qbert::QbertComponent::Update()
{
}

void qbert::QbertComponent::Kill()
{
	m_Health -= 1;
	std::cout << "qbert lost a live\n";
	for (auto observer : m_Observers)
	{
		observer->Died();
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